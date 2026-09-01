// ============================================================
//  xlsx.hpp — อ่านและเขียนไฟล์ Excel (.xlsx) หลาย sheet ด้วย C++
//
//  .xlsx คือไฟล์ zip ที่ข้างในเป็น XML หลายไฟล์ ไฟล์นี้เลยทำ 2 ชั้น
//     ชั้นล่าง  บีบอัด/คลายซิป  ใช้ miniz (vendor/miniz.c ไม่ต้องลงอะไรเพิ่ม)
//     ชั้นบน    อ่าน/เขียน XML ของ Excel เขียนเองด้วยการค้นสตริง
//
//  สารบัญ
//     PART A  โครงสร้าง Sheet
//     PART B  ตัวช่วย XML (escape / unescape / ค้น tag และ attribute)
//     PART C  ตัวช่วยอ้างอิงเซลล์ (A1 -> แถว/คอลัมน์)
//     PART D  อ่าน .xlsx
//     PART E  เขียน .xlsx
// ============================================================
#pragma once

#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cctype>
#include "../vendor/miniz.h"

namespace xlsx {

// ============================================================
// PART A — โครงสร้าง Sheet
// ============================================================
struct Sheet {
    std::string name;                                // ชื่อแท็บใน Excel
    std::vector<std::string> header;                 // แถวแรก
    std::vector<std::vector<std::string>> rows;      // แถวข้อมูล
};

using Book = std::vector<Sheet>;

inline const Sheet* find(const Book& b, const std::string& name) {
    for (auto& s : b) if (s.name == name) return &s;
    return nullptr;
}

inline std::string cell(const std::vector<std::string>& r, size_t i) {
    return i < r.size() ? r[i] : "";
}


// ============================================================
// PART B — ตัวช่วย XML
// ============================================================
inline std::string xmlEscape(const std::string& s) {
    std::string o;
    for (char c : s) {
        switch (c) {
            case '&':  o += "&amp;";  break;
            case '<':  o += "&lt;";   break;
            case '>':  o += "&gt;";   break;
            case '"':  o += "&quot;"; break;
            case '\'': o += "&apos;"; break;
            default:
                // Excel ไม่รับอักขระควบคุม ตัดทิ้งเพื่อไม่ให้ไฟล์เสีย
                if ((unsigned char)c < 0x20 && c != '\t' && c != '\n') break;
                o += c;
        }
    }
    return o;
}

inline std::string xmlUnescape(const std::string& s) {
    std::string o;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] != '&') { o += s[i]; continue; }
        size_t sc = s.find(';', i);
        if (sc == std::string::npos || sc - i > 10) { o += s[i]; continue; }
        std::string e = s.substr(i + 1, sc - i - 1);
        if      (e == "amp")  o += '&';
        else if (e == "lt")   o += '<';
        else if (e == "gt")   o += '>';
        else if (e == "quot") o += '"';
        else if (e == "apos") o += '\'';
        else if (!e.empty() && e[0] == '#') {                 // &#1234; หรือ &#x4E2D;
            long cp = (e.size() > 1 && (e[1] == 'x' || e[1] == 'X'))
                    ? strtol(e.c_str() + 2, nullptr, 16)
                    : strtol(e.c_str() + 1, nullptr, 10);
            if (cp < 0x80) o += (char)cp;                      // เกินนี้เขียนเป็น UTF-8
            else if (cp < 0x800) { o += (char)(0xC0 | (cp >> 6)); o += (char)(0x80 | (cp & 0x3F)); }
            else { o += (char)(0xE0 | (cp >> 12)); o += (char)(0x80 | ((cp >> 6) & 0x3F)); o += (char)(0x80 | (cp & 0x3F)); }
        }
        else { o += s.substr(i, sc - i + 1); }
        i = sc;
    }
    return o;
}

// ค่าของ attribute ใน tag เช่น attrOf("<c r=\"A1\" t=\"s\">", "t") -> "s"
inline std::string attrOf(const std::string& tag, const std::string& name) {
    std::string k = name + "=\"";
    size_t p = tag.find(k);
    while (p != std::string::npos) {
        // ต้องมีช่องว่างนำหน้า กัน r= ไปตรงกับ sr=
        if (p == 0 || tag[p-1] == ' ' || tag[p-1] == '<') {
            size_t s = p + k.size();
            size_t e = tag.find('"', s);
            if (e == std::string::npos) return "";
            return tag.substr(s, e - s);
        }
        p = tag.find(k, p + 1);
    }
    return "";
}

// ข้อความระหว่าง <t ...> กับ </t> ทุกอันในช่วงที่กำหนด (ต่อกัน รองรับ rich text)
inline std::string textOf(const std::string& xml, size_t from, size_t to) {
    std::string out;
    size_t p = from;
    while (true) {
        size_t a = xml.find("<t", p);
        if (a == std::string::npos || a >= to) break;
        size_t gt = xml.find('>', a);
        if (gt == std::string::npos || gt >= to) break;
        if (xml[gt-1] == '/') { p = gt + 1; continue; }       // <t/> ว่าง
        size_t b = xml.find("</t>", gt);
        if (b == std::string::npos || b > to) break;
        out += xmlUnescape(xml.substr(gt + 1, b - gt - 1));
        p = b + 4;
    }
    return out;
}


// ============================================================
// PART C — ตัวช่วยอ้างอิงเซลล์
// ============================================================
// "BC12" -> คอลัมน์ที่ 54 (นับจาก 0)
inline int colOf(const std::string& ref) {
    int c = 0;
    for (char ch : ref) {
        if (ch >= 'A' && ch <= 'Z') c = c * 26 + (ch - 'A' + 1);
        else if (ch >= 'a' && ch <= 'z') c = c * 26 + (ch - 'a' + 1);
        else break;
    }
    return c - 1;
}

// 0 -> "A", 26 -> "AA"
inline std::string colName(int i) {
    std::string s;
    ++i;
    while (i > 0) { int r = (i - 1) % 26; s = char('A' + r) + s; i = (i - 1) / 26; }
    return s;
}


// ============================================================
// PART D — อ่าน .xlsx
// ============================================================
namespace detail {

inline bool zipEntry(mz_zip_archive& z, const char* path, std::string& out) {
    int idx = mz_zip_reader_locate_file(&z, path, nullptr, 0);
    if (idx < 0) return false;
    size_t sz = 0;
    void* p = mz_zip_reader_extract_to_heap(&z, idx, &sz, 0);
    if (!p) return false;
    out.assign((const char*)p, sz);
    mz_free(p);
    return true;
}

// ตัด .0 ท้ายเลข เผื่อ Excel เขียน 1200.0 มา
inline std::string trimNum(std::string v) {
    if (v.size() > 2 && v.find('.') != std::string::npos) {
        while (!v.empty() && v.back() == '0') v.pop_back();
        if (!v.empty() && v.back() == '.') v.pop_back();
    }
    return v;
}

// แปลง XML ของ 1 worksheet เป็นตาราง
inline void parseSheet(const std::string& xml,
                       const std::vector<std::string>& shared,
                       Sheet& sh) {
    std::vector<std::vector<std::string>> table;
    size_t p = 0;

    while (true) {
        size_t rs = xml.find("<row", p);
        if (rs == std::string::npos) break;
        size_t rGt = xml.find('>', rs);
        if (rGt == std::string::npos) break;
        if (xml[rGt-1] == '/') { p = rGt + 1; table.push_back({}); continue; }   // แถวว่าง
        size_t re = xml.find("</row>", rGt);
        if (re == std::string::npos) break;

        std::vector<std::string> row;
        size_t q = rGt;
        while (true) {
            size_t cs = xml.find("<c", q);
            if (cs == std::string::npos || cs > re) break;
            // กัน <col ...> หรือ tag อื่นที่ขึ้นต้นด้วย c
            char after = cs + 2 < xml.size() ? xml[cs + 2] : ' ';
            if (after != ' ' && after != '>' && after != '/') { q = cs + 2; continue; }

            size_t cGt = xml.find('>', cs);
            if (cGt == std::string::npos || cGt > re) break;
            std::string tag = xml.substr(cs, cGt - cs + 1);
            int col = colOf(attrOf(tag, "r"));
            std::string type = attrOf(tag, "t");
            std::string val;

            if (xml[cGt-1] == '/') {                        // <c r="B2"/> เซลล์ว่าง
                q = cGt + 1;
            } else {
                size_t ce = xml.find("</c>", cGt);
                if (ce == std::string::npos || ce > re) break;
                if (type == "s") {                          // อ้างอิง sharedStrings
                    size_t vs = xml.find("<v>", cGt);
                    if (vs != std::string::npos && vs < ce) {
                        size_t ve = xml.find("</v>", vs);
                        long i = atol(xml.substr(vs + 3, ve - vs - 3).c_str());
                        if (i >= 0 && (size_t)i < shared.size()) val = shared[i];
                    }
                } else if (type == "inlineStr" || type == "str") {
                    val = textOf(xml, cGt, ce);
                    if (val.empty() && type == "str") {
                        size_t vs = xml.find("<v>", cGt);
                        if (vs != std::string::npos && vs < ce) {
                            size_t ve = xml.find("</v>", vs);
                            val = xmlUnescape(xml.substr(vs + 3, ve - vs - 3));
                        }
                    }
                } else {                                    // ตัวเลข
                    size_t vs = xml.find("<v>", cGt);
                    if (vs != std::string::npos && vs < ce) {
                        size_t ve = xml.find("</v>", vs);
                        val = trimNum(xml.substr(vs + 3, ve - vs - 3));
                    }
                }
                q = ce + 4;
            }

            if (col < 0) col = (int)row.size();
            while ((int)row.size() < col) row.push_back("");   // เติมช่องที่ Excel ข้ามไป
            row.push_back(val);
        }

        table.push_back(row);
        p = re + 6;
    }

    // แถวแรกที่ไม่ว่างคือหัวตาราง
    size_t i = 0;
    while (i < table.size()) {
        bool blank = true;
        for (auto& c : table[i]) if (!c.empty()) { blank = false; break; }
        if (!blank) break;
        ++i;
    }
    if (i < table.size()) { sh.header = table[i]; ++i; }
    for (; i < table.size(); ++i) sh.rows.push_back(table[i]);
}

} // namespace detail

// อ่านทั้งไฟล์ ได้ทุก sheet ตามลำดับแท็บใน Excel
inline bool read(const std::string& path, Book& out) {
    out.clear();
    mz_zip_archive z;
    memset(&z, 0, sizeof(z));
    if (!mz_zip_reader_init_file(&z, path.c_str(), 0)) return false;

    std::string wb, rels, ss;
    if (!detail::zipEntry(z, "xl/workbook.xml", wb)) { mz_zip_reader_end(&z); return false; }
    detail::zipEntry(z, "xl/_rels/workbook.xml.rels", rels);
    detail::zipEntry(z, "xl/sharedStrings.xml", ss);

    // ---- sharedStrings ----
    std::vector<std::string> shared;
    {
        size_t p = 0;
        while (true) {
            size_t a = ss.find("<si", p);
            if (a == std::string::npos) break;
            size_t b = ss.find("</si>", a);
            if (b == std::string::npos) break;
            shared.push_back(textOf(ss, a, b));
            p = b + 5;
        }
    }

    // ---- rId -> ชื่อไฟล์ worksheet ----
    std::map<std::string, std::string> target;
    {
        size_t p = 0;
        while (true) {
            size_t a = rels.find("<Relationship", p);
            if (a == std::string::npos) break;
            size_t b = rels.find('>', a);
            if (b == std::string::npos) break;
            std::string t = rels.substr(a, b - a + 1);
            std::string id = attrOf(t, "Id"), tg = attrOf(t, "Target");
            if (!id.empty() && !tg.empty()) {
                if (tg.rfind("/", 0) == 0)      tg = tg.substr(1);
                else if (tg.rfind("xl/", 0) != 0) tg = "xl/" + tg;
                target[id] = tg;
            }
            p = b + 1;
        }
    }

    // ---- รายชื่อ sheet ตามลำดับ ----
    size_t p = 0;
    int fallback = 1;
    while (true) {
        size_t a = wb.find("<sheet ", p);
        if (a == std::string::npos) break;
        size_t b = wb.find('>', a);
        if (b == std::string::npos) break;
        std::string t = wb.substr(a, b - a + 1);

        Sheet sh;
        sh.name = xmlUnescape(attrOf(t, "name"));

        std::string rid = attrOf(t, "r:id");
        if (rid.empty()) rid = attrOf(t, "id");
        std::string file = target.count(rid) ? target[rid]
                         : "xl/worksheets/sheet" + std::to_string(fallback) + ".xml";
        ++fallback;

        std::string sxml;
        if (detail::zipEntry(z, file.c_str(), sxml))
            detail::parseSheet(sxml, shared, sh);
        out.push_back(sh);
        p = b + 1;
    }

    mz_zip_reader_end(&z);
    return !out.empty();
}


// ============================================================
// PART E — เขียน .xlsx
// ============================================================
namespace detail {

// ตัวเลขล้วนเขียนเป็นตัวเลขจริง เพื่อให้ Excel คำนวณและจัดชิดขวาให้
inline bool isPlainNumber(const std::string& s) {
    if (s.empty() || s.size() > 9) return false;
    size_t i = (s[0] == '-') ? 1 : 0;
    if (i >= s.size()) return false;
    if (s[i] == '0' && s.size() - i > 1) return false;   // 081-xxx และ 0012 ให้เป็นข้อความ
    for (; i < s.size(); ++i) if (!isdigit((unsigned char)s[i])) return false;
    return true;
}

inline std::string cellXml(int col, int row, const std::string& v) {
    if (v.empty()) return "";
    std::string ref = colName(col) + std::to_string(row);
    if (isPlainNumber(v))
        return "<c r=\"" + ref + "\"><v>" + v + "</v></c>";
    return "<c r=\"" + ref + "\" t=\"inlineStr\"><is><t xml:space=\"preserve\">"
         + xmlEscape(v) + "</t></is></c>";
}

inline std::string sheetXml(const Sheet& sh) {
    std::string x =
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
        "<worksheet xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\">"
        "<sheetData>";

    int r = 1;
    x += "<row r=\"1\">";
    for (size_t c = 0; c < sh.header.size(); ++c) x += cellXml((int)c, r, sh.header[c]);
    x += "</row>";

    for (auto& row : sh.rows) {
        ++r;
        x += "<row r=\"" + std::to_string(r) + "\">";
        for (size_t c = 0; c < row.size(); ++c) x += cellXml((int)c, r, row[c]);
        x += "</row>";
    }
    x += "</sheetData></worksheet>";
    return x;
}

inline bool addFile(mz_zip_archive& z, const char* name, const std::string& data) {
    return mz_zip_writer_add_mem(&z, name, data.data(), data.size(), MZ_BEST_COMPRESSION) != 0;
}

} // namespace detail

// เขียนทั้งไฟล์ (ลง .tmp ก่อนแล้ว rename กันไฟล์พังถ้าโปรแกรมหยุดกลางคัน)
inline bool write(const std::string& path, const Book& book) {
    if (book.empty()) return false;
    std::string tmp = path + ".tmp";
    std::remove(tmp.c_str());

    mz_zip_archive z;
    memset(&z, 0, sizeof(z));
    if (!mz_zip_writer_init_file(&z, tmp.c_str(), 0)) return false;

    const size_t n = book.size();

    // ---- [Content_Types].xml ----
    {
        std::string x =
            "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
            "<Types xmlns=\"http://schemas.openxmlformats.org/package/2006/content-types\">"
            "<Default Extension=\"rels\" ContentType=\"application/vnd.openxmlformats-package.relationships+xml\"/>"
            "<Default Extension=\"xml\" ContentType=\"application/xml\"/>"
            "<Override PartName=\"/xl/workbook.xml\" ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.sheet.main+xml\"/>";
        for (size_t i = 0; i < n; ++i)
            x += "<Override PartName=\"/xl/worksheets/sheet" + std::to_string(i + 1) +
                 ".xml\" ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.worksheet+xml\"/>";
        x += "</Types>";
        detail::addFile(z, "[Content_Types].xml", x);
    }

    // ---- _rels/.rels ----
    detail::addFile(z, "_rels/.rels",
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
        "<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\">"
        "<Relationship Id=\"rId1\" Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument\" Target=\"xl/workbook.xml\"/>"
        "</Relationships>");

    // ---- xl/workbook.xml ----
    {
        std::string x =
            "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
            "<workbook xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\""
            " xmlns:r=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships\">"
            "<sheets>";
        for (size_t i = 0; i < n; ++i)
            x += "<sheet name=\"" + xmlEscape(book[i].name) +
                 "\" sheetId=\"" + std::to_string(i + 1) +
                 "\" r:id=\"rId" + std::to_string(i + 1) + "\"/>";
        x += "</sheets></workbook>";
        detail::addFile(z, "xl/workbook.xml", x);
    }

    // ---- xl/_rels/workbook.xml.rels ----
    {
        std::string x =
            "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
            "<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\">";
        for (size_t i = 0; i < n; ++i)
            x += "<Relationship Id=\"rId" + std::to_string(i + 1) +
                 "\" Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/worksheet\""
                 " Target=\"worksheets/sheet" + std::to_string(i + 1) + ".xml\"/>";
        x += "</Relationships>";
        detail::addFile(z, "xl/_rels/workbook.xml.rels", x);
    }

    // ---- worksheets ----
    for (size_t i = 0; i < n; ++i) {
        std::string name = "xl/worksheets/sheet" + std::to_string(i + 1) + ".xml";
        detail::addFile(z, name.c_str(), detail::sheetXml(book[i]));
    }

    bool ok = mz_zip_writer_finalize_archive(&z) != 0;
    mz_zip_writer_end(&z);
    if (!ok) { std::remove(tmp.c_str()); return false; }

    std::remove(path.c_str());
    return std::rename(tmp.c_str(), path.c_str()) == 0;
}

} // namespace xlsx
