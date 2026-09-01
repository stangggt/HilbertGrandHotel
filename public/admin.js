/* ============================================================
   หน้าแอดมิน — จัดการห้องและการจอง
   สารบัญ
     PART 1  ค่าคงที่ + สถานะหน้าจอ
     PART 2  ชั้นติดต่อ API
     PART 3  ตัวช่วยแสดงผล
     PART 4  ตารางห้อง
     PART 5  ประวัติการจอง + สรุปตัวเลข
     PART 6  กล่องแก้ไขการจอง
     PART 7  กล่องแก้ไขห้อง
     PART 8  ผูก event
   ============================================================ */


/* ============================================================
   PART 1 — ค่าคงที่ + สถานะหน้าจอ
   ============================================================ */
const POLL_MS = 2000;      // ดึงข้อมูลใหม่ทุก 2 วินาที เท่ากับหน้าผู้ใช้
const FLASH_MS = 8000;     // ไฮไลต์แถวที่เพิ่งจองเข้ามานานแค่ไหน

const $  = (id) => document.getElementById(id);
const th = (n)  => Number(n).toLocaleString("th-TH");

let rooms    = [];
let bookings = [];
let today    = "";
let filter   = "all";
let keyword  = "";
let editing  = null;   // booking ที่กำลังแก้ หรือ {newFor: roomId}
let editRoom = null;   // ห้องที่กำลังแก้ราคา
let knownIds = null;   // รหัสการจองที่หน้านี้เห็นแล้ว ใช้ตรวจว่ามีรายการใหม่เข้ามา
let flashIds = new Set();  // รายการใหม่ที่ยังไฮไลต์อยู่

const STATUS = {
  wait:      { label: "รอเช็คอิน",   cls: "st-wait" },
  checkin:   { label: "เช็คอินแล้ว", cls: "st-in"   },
  checkout:  { label: "เช็คเอาท์แล้ว", cls: "st-out" },
  cancelled: { label: "ยกเลิก",      cls: "st-cancel" }
};

function initTheme() {
  const saved = localStorage.getItem("gh_theme") || "light";
  document.documentElement.setAttribute("data-theme", saved);
  const icon = $("theme-icon");
  if (icon) icon.textContent = saved === "dark" ? "☀️" : "🌙";

  $("btn-theme-toggle")?.addEventListener("click", () => {
    const cur = document.documentElement.getAttribute("data-theme") || "light";
    const next = cur === "light" ? "dark" : "light";
    document.documentElement.setAttribute("data-theme", next);
    localStorage.setItem("gh_theme", next);
    if (icon) icon.textContent = next === "dark" ? "☀️" : "🌙";
  });
}

function initAdminUser() {
  const info = $("admin-user-info");
  if (!info) return;
  try {
    const raw = localStorage.getItem("gh_user");
    if (raw) {
      const u = JSON.parse(raw);
      info.innerHTML = `
        <div class="user-profile">
          <div class="user-avatar">${u.fullName ? u.fullName.charAt(0).toUpperCase() : 'A'}</div>
          <div>
            <span style="font-weight:600">${u.fullName || u.username}</span>
            <span class="role-badge ${u.role || 'admin'}">${u.role || 'ADMIN'}</span>
          </div>
        </div>
      `;
      return;
    }
  } catch (e) {}
  info.innerHTML = `<span class="role-badge admin">ADMIN MODE</span>`;
}

/* ============================================================
   PART 2 — ชั้นติดต่อ API
   ============================================================ */
const api = {
  async load() {
    const res = await fetch("/api/admin/data");
    return res.json();
  },
  async post(path, payload) {
    const res = await fetch(path, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(payload)
    });
    return res.json();
  }
};

// เซิร์ฟเวอร์รับข้อมูลแล้วแต่เขียน hotel.xlsx ไม่ลง (เช่นเปิดค้างใน Excel)
// ต้องบอกให้รู้ ไม่งั้นหน้าจอกับไฟล์จะไม่ตรงกันโดยไม่มีใครสังเกต
function warnIfNotSaved(data) {
  if (data && data.saved === false) {
    toast(data.saveError || "บันทึกลงไฟล์ Excel ไม่สำเร็จ", true);
    return true;
  }
  return false;
}

async function refresh() {
  // ระหว่างเปิดกล่องแก้ไข ไม่วาดตารางทับ กันค่าที่กำลังพิมพ์หาย
  if (editing || editRoom) return;

  try {
    const d = await api.load();
    rooms = d.rooms;
    bookings = d.bookings;
    today = d.today;
    detectNew();
    renderStats();
    renderTable();
    renderHistory();
  } catch (e) {
    toast("ต่อเซิร์ฟเวอร์ไม่ได้", true);
  }
}

// เทียบกับรอบที่แล้ว ถ้ามีรหัสจองที่ไม่เคยเห็น = ลูกค้าเพิ่งกดจองจากหน้าผู้ใช้
function detectNew() {
  const ids = new Set(bookings.map(b => b.id));

  if (knownIds === null) { knownIds = ids; return; }   // รอบแรก ไม่ต้องแจ้ง

  const fresh = bookings.filter(b => !knownIds.has(b.id));
  fresh.forEach(b => {
    flashIds.add(b.id);
    toast(`การจองใหม่ ห้อง ${b.room} · ${b.booker} · ${b.nights} คืน`);
    setTimeout(() => { flashIds.delete(b.id); renderTable(); }, FLASH_MS);
  });

  knownIds = ids;
}


/* ============================================================
   PART 3 — ตัวช่วยแสดงผล
   ============================================================ */
let toastTimer = null;
function toast(msg, bad) {
  const t = $("toast");
  t.textContent = msg;
  t.className = "toast" + (bad ? " bad" : "");
  clearTimeout(toastTimer);
  toastTimer = setTimeout(() => t.classList.add("hidden"), 3200);
}

function statusChip(status) {
  const s = STATUS[status] || { label: status, cls: "" };
  return `<span class="chip ${s.cls}">${s.label}</span>`;
}

function tierChip(r) {
  return r.tier === "vip" ? `<span class="chip st-vip">VIP</span>` : "";
}

function dash(v) { return v && v !== "-" ? v : "—"; }


/* ============================================================
   PART 4 — ตารางห้อง
   ============================================================ */
function matchFilter(r) {
  const b = r.booking;
  if (filter === "all")  return true;
  if (filter === "free") return !b;
  return b && b.status === filter;
}

function matchKeyword(r) {
  if (!keyword) return true;
  const b = r.booking;
  const hay = [r.number, r.typeName, r.note,
               b ? b.booker : "", b ? b.phone : "", b ? b.email : "", b ? b.id : ""]
              .join(" ").toLowerCase();
  return hay.includes(keyword);
}

function renderTable() {
  const rowsHtml = rooms.filter(r => matchFilter(r) && matchKeyword(r)).map(r => {
    const b = r.booking;
    const actions = b
      ? `<div class="row-actions">
           ${b.status === "wait"    ? `<button class="mini go" data-act="status" data-id="${b.id}" data-to="checkin">เช็คอิน</button>` : ""}
           ${b.status === "checkin" ? `<button class="mini go" data-act="status" data-id="${b.id}" data-to="checkout">เช็คเอาท์</button>` : ""}
           <button class="mini" data-act="edit" data-id="${b.id}">แก้ไข</button>
           <button class="mini danger" data-act="status" data-id="${b.id}" data-to="cancelled">ยกเลิก</button>
         </div>`
      : `<div class="row-actions">
           <button class="mini go" data-act="add" data-room="${r.number}">เพิ่มการจอง</button>
           <button class="mini" data-act="room" data-room="${r.number}">แก้ห้อง</button>
         </div>`;

    const flash = b && flashIds.has(b.id) ? " is-new" : "";
    return `<tr class="${b ? "" : "is-free"}${flash}">
      <td class="cell-room"><strong>${r.number}</strong> ${tierChip(r)}<span class="sub">ชั้น ${r.floor}${r.note ? " · " + r.note : ""}</span></td>
      <td>${r.typeName}</td>
      <td class="num"><button class="linkish" data-act="room" data-room="${r.number}">${th(r.price)}</button></td>
      <td>${b ? b.booker : "—"}${b && b.note ? `<span class="sub">${b.note}</span>` : ""}</td>
      <td>${b ? `${dash(b.phone)}<span class="sub">${dash(b.email)}</span>` : "—"}</td>
      <td>${b ? `${b.checkIn} → ${b.checkOut}<span class="sub">${b.nights} คืน</span>` : "—"}</td>
      <td class="num">${b ? th(b.total) : "—"}</td>
      <td>${b ? statusChip(b.status) + (flash ? `<span class="chip st-new">ใหม่</span>` : "") : `<span class="chip st-free">ว่าง</span>`}</td>
      <td>${actions}</td>
    </tr>`;
  }).join("");

  $("tbody").innerHTML = rowsHtml || `<tr><td colspan="9" class="empty">ไม่มีห้องที่ตรงกับเงื่อนไข</td></tr>`;
  const shown = rooms.filter(r => matchFilter(r) && matchKeyword(r)).length;
  $("count").textContent = `แสดง ${shown} จาก ${rooms.length} ห้อง`;
}


/* ============================================================
   PART 5 — ประวัติการจอง + สรุปตัวเลข
   ============================================================ */
function renderHistory() {
  const list = bookings.slice().reverse();
  $("hbody").innerHTML = list.map(b => `<tr>
      <td>${b.id}</td>
      <td>${b.room}</td>
      <td>${b.booker}</td>
      <td>${b.checkIn} → ${b.checkOut}</td>
      <td class="num">${b.nights}</td>
      <td class="num">${th(b.total)}</td>
      <td>${statusChip(b.status)}</td>
      <td class="sub-cell">${b.createdAt}</td>
    </tr>`).join("") || `<tr><td colspan="8" class="empty">ยังไม่มีรายการจอง</td></tr>`;
}

function renderStats() {
  const free = rooms.filter(r => !r.booking).length;
  const wait = rooms.filter(r => r.booking && r.booking.status === "wait").length;
  const din  = rooms.filter(r => r.booking && r.booking.status === "checkin").length;
  const rev  = rooms.reduce((s, r) => s + (r.booking ? r.booking.total : 0), 0);

  $("k-free").textContent = free;
  $("k-wait").textContent = wait;
  $("k-in").textContent   = din;
  $("k-rev").textContent  = th(rev);
}


/* ============================================================
   PART 6 — กล่องแก้ไขการจอง
   ============================================================ */
function openEdit(bookingId) {
  const b = bookings.find(x => x.id === bookingId);
  if (!b) return;
  editing = { mode: "edit", id: b.id };

  $("m-title").textContent = "แก้ไขการจอง " + b.id;
  $("m-sub").textContent   = `ห้อง ${b.room} · ${STATUS[b.status] ? STATUS[b.status].label : b.status}`;
  $("m-name").value    = b.booker;
  $("m-phone").value   = b.phone === "-" ? "" : b.phone;
  $("m-email").value   = b.email === "-" ? "" : b.email;
  $("m-checkin").value = b.checkIn;
  $("m-nights").value  = b.nights;
  $("m-note").value    = b.note;
  $("m-err").textContent = "";
  $("modal").classList.remove("hidden");
  $("m-name").focus();
}

function openAdd(roomId) {
  const r = rooms.find(x => x.number === roomId);
  if (!r) return;
  editing = { mode: "add", room: roomId };

  $("m-title").textContent = "เพิ่มการจอง ห้อง " + roomId;
  $("m-sub").textContent   = `${r.typeName} · ${th(r.price)} บาทต่อคืน`;
  $("m-name").value    = "";
  $("m-phone").value   = "";
  $("m-email").value   = "";
  $("m-checkin").value = today;
  $("m-nights").value  = 1;
  $("m-note").value    = "";
  $("m-err").textContent = "";
  $("modal").classList.remove("hidden");
  $("m-name").focus();
}

function closeEdit() { $("modal").classList.add("hidden"); editing = null; }

async function saveEdit() {
  if (!editing) return;
  const name   = $("m-name").value.trim();
  const nights = parseInt($("m-nights").value, 10);
  const ci     = $("m-checkin").value;

  if (!name)                                  return ($("m-err").textContent = "กรอกชื่อผู้จอง");
  if (isNaN(nights) || nights < 1 || nights > 30) return ($("m-err").textContent = "จำนวนคืนต้องอยู่ระหว่าง 1 ถึง 30");
  if (!ci)                                    return ($("m-err").textContent = "เลือกวันเช็คอิน");

  const payload = {
    booker:  name,
    phone:   $("m-phone").value.trim(),
    email:   $("m-email").value.trim(),
    checkIn: ci,
    nights:  nights,
    note:    $("m-note").value.trim()
  };

  let data;
  if (editing.mode === "edit") {
    payload.id = editing.id;
    data = await api.post("/api/admin/booking", payload);
  } else {
    payload.room = editing.room;
    data = await api.post("/api/admin/add", payload);
  }

  if (data.ok) {
    const wasAdd = editing && editing.mode === "add";   // ต้องอ่านก่อน closeEdit() ล้างค่า
    closeEdit();
    if (!warnIfNotSaved(data)) toast(wasAdd ? "เพิ่มการจองแล้ว" : "บันทึกแล้ว");
    refresh();
  } else {
    $("m-err").textContent = data.error || "บันทึกไม่สำเร็จ";
  }
}

async function setStatus(id, to) {
  if (to === "cancelled" && !confirm("ยกเลิกการจอง " + id + " ใช่ไหม")) return;
  const data = await api.post("/api/admin/status", { id, status: to });
  if (data.ok) {
    if (!warnIfNotSaved(data))
      toast(to === "cancelled" ? "ยกเลิกแล้ว" : "เปลี่ยนสถานะเป็น " + STATUS[to].label);
    refresh();
  } else {
    toast(data.error || "เปลี่ยนสถานะไม่สำเร็จ", true);
  }
}


/* ============================================================
   PART 7 — กล่องแก้ไขห้อง
   ============================================================ */
function openRoom(roomId) {
  const r = rooms.find(x => x.number === roomId);
  if (!r) return;
  editRoom = roomId;
  $("r-title").textContent = "ห้อง " + r.number + " · " + r.typeName;
  $("r-price").value = r.price;
  $("r-note").value  = r.note;
  $("r-err").textContent = "";
  $("rmodal").classList.remove("hidden");
  $("r-price").focus();
}

function closeRoom() { $("rmodal").classList.add("hidden"); editRoom = null; }

async function saveRoom() {
  if (!editRoom) return;
  const price = parseInt($("r-price").value, 10);
  if (isNaN(price) || price < 0) return ($("r-err").textContent = "กรอกราคาให้ถูกต้อง");

  const data = await api.post("/api/admin/room", {
    room: editRoom, price, note: $("r-note").value.trim()
  });
  if (data.ok) { closeRoom(); if (!warnIfNotSaved(data)) toast("บันทึกข้อมูลห้องแล้ว"); refresh(); }
  else         { $("r-err").textContent = data.error || "บันทึกไม่สำเร็จ"; }
}


/* ============================================================
   PART 8 — ผูก event + เริ่มทำงาน
   ============================================================ */
document.addEventListener("click", e => {
  const el = e.target.closest("[data-act]");
  if (!el) return;
  const act = el.dataset.act;
  if      (act === "edit")   openEdit(el.dataset.id);
  else if (act === "add")    openAdd(el.dataset.room);
  else if (act === "room")   openRoom(el.dataset.room);
  else if (act === "status") setStatus(el.dataset.id, el.dataset.to);
});

$("tabs").addEventListener("click", e => {
  const t = e.target.closest(".tab");
  if (!t) return;
  document.querySelectorAll(".tab").forEach(x => x.classList.remove("is-on"));
  t.classList.add("is-on");
  filter = t.dataset.f;
  renderTable();
});

$("q").addEventListener("input", e => {
  keyword = e.target.value.trim().toLowerCase();
  renderTable();
});

$("m-save").addEventListener("click", saveEdit);
$("m-cancel").addEventListener("click", closeEdit);
$("r-save").addEventListener("click", saveRoom);
$("r-cancel").addEventListener("click", closeRoom);

$("btn-reload").addEventListener("click", async () => {
  // เดิมไม่ดูผลลัพธ์เลย อ่านไฟล์ไม่สำเร็จก็ยังขึ้นว่าสำเร็จ
  const data = await api.post("/api/admin/reload", {});
  if (data && data.ok) { toast("อ่านไฟล์ Excel ใหม่แล้ว"); refresh(); }
  else toast((data && data.error) || "อ่านไฟล์ Excel ไม่สำเร็จ", true);
});

document.addEventListener("keydown", e => {
  if (e.key === "Escape") { closeEdit(); closeRoom(); }
});

initTheme();
initAdminUser();
refresh();
setInterval(refresh, POLL_MS);
