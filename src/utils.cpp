// ============================================================
//  utils.cpp — ดูสารบัญที่ include/utils.h
// ============================================================
#include "../include/utils.h"

#include <fstream>
#include <sstream>
#include <cstring>
#include <cctype>
#include <ctime>
#include <cstdlib>

namespace utils {

// ============================================================
// PART 1 — JSON
// ============================================================
std::string esc(const std::string& s) {
    std::string o;
    for (char c : s) {
        switch (c) {
            case '"':  o += "\\\""; break;
            case '\\': o += "\\\\"; break;
            case '\n': o += "\\n";  break;
            case '\r': o += "\\r";  break;
            case '\t': o += "\\t";  break;
            default:   o += c;
        }
    }
    return o;
}

std::string q(const std::string& s) { return "\"" + esc(s) + "\""; }

long jsonInt(const std::string& b, const std::string& key, long def) {
    std::string k = "\"" + key + "\"";
    size_t p = b.find(k);
    if (p == std::string::npos) return def;
    p = b.find(':', p + k.size());
    if (p == std::string::npos) return def;
    ++p;
    while (p < b.size() && (b[p] == ' ' || b[p] == '"')) ++p;
    bool neg = false;
    if (p < b.size() && b[p] == '-') { neg = true; ++p; }
    if (p >= b.size() || !isdigit((unsigned char)b[p])) return def;
    long v = 0;
    while (p < b.size() && isdigit((unsigned char)b[p])) { v = v * 10 + (b[p] - '0'); ++p; }
    return neg ? -v : v;
}

std::string jsonStr(const std::string& b, const std::string& key, size_t maxLen) {
    std::string k = "\"" + key + "\"";
    size_t p = b.find(k);
    if (p == std::string::npos) return "";
    p = b.find(':', p + k.size());
    if (p == std::string::npos) return "";
    p = b.find('"', p);
    if (p == std::string::npos) return "";
    ++p;
    std::string out;
    while (p < b.size() && b[p] != '"') {
        if (b[p] == '\\' && p + 1 < b.size()) {
            ++p;
            char c = b[p];
            if      (c == 'n') out += '\n';
            else if (c == 't') out += '\t';
            else if (c == 'r') {}
            else out += c;
        } else out += b[p];
        ++p;
    }
    if (out.size() > maxLen) out = out.substr(0, maxLen);
    return out;
}

bool jsonHas(const std::string& b, const std::string& key) {
    return b.find("\"" + key + "\"") != std::string::npos;
}

std::string at(const std::vector<std::string>& row, size_t i) {
    return i < row.size() ? row[i] : "";
}


// ============================================================
// PART 2 — วันที่และเวลา
// ============================================================
static std::string fmtNow(const char* fmt) {
    time_t t = time(nullptr);
    tm lt{};
#ifdef _WIN32
    localtime_s(&lt, &t);
#else
    localtime_r(&t, &lt);
#endif
    char buf[32];
    strftime(buf, sizeof(buf), fmt, &lt);
    return buf;
}

std::string todayStr() { return fmtNow("%Y-%m-%d"); }
std::string nowStr()   { return fmtNow("%Y-%m-%d %H:%M:%S"); }

std::string addDays(const std::string& ymd, int days) {
    if (ymd.size() < 10) return ymd;
    tm t{};
    t.tm_year = atoi(ymd.substr(0, 4).c_str()) - 1900;
    t.tm_mon  = atoi(ymd.substr(5, 2).c_str()) - 1;
    t.tm_mday = atoi(ymd.substr(8, 2).c_str()) + days;
    t.tm_hour = 12;
    if (mktime(&t) == (time_t)-1) return ymd;
    char buf[32];
    strftime(buf, sizeof(buf), "%Y-%m-%d", &t);
    return buf;
}


// ============================================================
// PART 3 — HTTP
// ============================================================
std::string mimeOf(const std::string& p) {
    auto ends = [&](const char* e) {
        size_t n = strlen(e);
        return p.size() >= n && p.compare(p.size() - n, n, e) == 0;
    };
    if (ends(".html")) return "text/html; charset=utf-8";
    if (ends(".css"))  return "text/css; charset=utf-8";
    if (ends(".js"))   return "application/javascript; charset=utf-8";
    if (ends(".xlsx")) return "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    if (ends(".svg"))  return "image/svg+xml";
    if (ends(".png"))  return "image/png";
    if (ends(".jpg") || ends(".jpeg")) return "image/jpeg";
    return "text/plain; charset=utf-8";
}

std::string resp(const std::string& status, const std::string& mime, const std::string& body) {
    std::ostringstream o;
    o << "HTTP/1.1 " << status << "\r\n"
      << "Content-Type: " << mime << "\r\n"
      << "Content-Length: " << body.size() << "\r\n"
      << "Access-Control-Allow-Origin: *\r\n"
      << "Access-Control-Allow-Headers: Content-Type\r\n"
      << "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
      << "Cache-Control: no-store\r\n"
      << "Connection: close\r\n\r\n"
      << body;
    return o.str();
}

std::string jsonOk(const std::string& body) {
    return resp("200 OK", "application/json; charset=utf-8", body);
}

std::string jsonErr(const std::string& code, const std::string& msg) {
    return resp(code, "application/json; charset=utf-8",
                "{\"ok\":false,\"error\":" + q(msg) + "}");
}

bool readFile(const std::string& p, std::string& out) {
    std::ifstream f(p, std::ios::binary);
    if (!f) return false;
    std::ostringstream ss;
    ss << f.rdbuf();
    out = ss.str();
    return true;
}

} // namespace utils
