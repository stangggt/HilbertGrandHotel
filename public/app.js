/* ============================================================
   DEMO_01 — FRONTEND LOGIC
   สารบัญ
     PART 1  ค่าคงที่ + ตัวแปรสถานะ
     PART 2  ชั้นติดต่อ API (คุยกับ backend C++)
     PART 3  หน้า 1 — แถบสรุป + ผังห้อง
     PART 4  ภาพห้อง (SVG)
     PART 5  หน้า 2 — เปิดหน้าจอง + คำนวณราคา
     PART 6  ส่งคำขอจอง
     PART 7  polling อัปเดตสด
     PART 8  ผูก event
   ============================================================ */


/* ============================================================
   PART 1 — ค่าคงที่ + ตัวแปรสถานะ
   ============================================================ */
const API     = "";       // same origin — เสิร์ฟจากเซิร์ฟเวอร์ C++ เอง
const POLL_MS = 2000;     // อัปเดตสถานะห้องทุก 2 วินาที
const MAX_NIGHTS = 30;

const $  = (id) => document.getElementById(id);
const th = (n)  => n.toLocaleString("th-TH");

let rooms         = [];
let todayStr      = "";
let current       = null;      // ห้องที่กำลังจองอยู่
let pollTimer     = null;
let lastBookedSet = new Set();


/* ============================================================
   PART 2 — ชั้นติดต่อ API
   ============================================================ */
const api = {
  async getRooms() {
    const res = await fetch(API + "/api/rooms");
    return res.json();
  },
  async book(room, nights) {
    const res = await fetch(API + "/api/book", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ room, nights })
    });
    return res.json();
  }
};

async function loadRooms(firstTime = false) {
  try {
    const data = await api.getRooms();
    rooms = data.rooms;
    if (data.today) todayStr = data.today;
    renderStats();
    renderGrid(firstTime);
    $("live-text").textContent = "อัปเดตสด";
  } catch (e) {
    $("live-text").textContent = "ต่อเซิร์ฟเวอร์ไม่ได้";
  }
}


// บวกวัน  "2026-08-14" + 3 -> "2026-08-17"
function addDays(ymd, days) {
  if (!ymd) return "–";
  const d = new Date(ymd + "T12:00:00");
  if (isNaN(d)) return "–";
  d.setDate(d.getDate() + days);
  return d.toISOString().slice(0, 10);
}


/* ============================================================
   PART 3 — หน้า 1: แถบสรุป + ผังห้อง
   ============================================================ */
function renderStats() {
  const free   = rooms.filter(r => !r.booked);
  const vipOk  = free.filter(r => r.tier === "vip");
  const booked = rooms.length - free.length;
  const low    = free.length ? Math.min(...free.map(r => r.price)) : 0;

  $("stat-free").textContent   = free.length;
  $("stat-vip").textContent    = vipOk.length;
  $("stat-booked").textContent = booked;
  $("stat-low").textContent    = low ? th(low) : "เต็ม";
}

function renderGrid(firstTime) {
  const grid = $("grid");
  const nowBooked = new Set(rooms.filter(r => r.booked).map(r => r.number));

  grid.innerHTML = "";
  rooms.forEach(r => {
    const b = document.createElement("button");
    b.type = "button";
    b.className = "room" + (r.tier === "vip" ? " vip" : "") + (r.booked ? " booked" : "");
    b.disabled = r.booked;
    b.setAttribute("aria-label",
      `ห้อง ${r.number} ${r.bed === "twin" ? "เตียงคู่แยก" : "เตียงใหญ่"}` +
      `${r.tier === "vip" ? " วีไอพี" : ""} ${r.booked ? "จองแล้ว" : "ว่าง"}`);

    const tag = document.createElement("span");
    tag.className = "tag";
    tag.textContent = r.tier === "vip" ? "VIP" : (r.bed === "twin" ? "TW" : "DB");

    const state = document.createElement("span");
    state.className = "state";
    state.textContent = r.booked ? "จองแล้ว" : th(r.price) + " ฿";

    b.appendChild(tag);
    b.appendChild(document.createTextNode(r.number));
    b.appendChild(state);

    // ห้องที่เพิ่งถูกคนอื่นจอง -> เน้นให้เห็น
    if (!firstTime && r.booked && !lastBookedSet.has(r.number)) {
      b.classList.add("just-booked");
    }

    b.addEventListener("click", () => openBooking(r.number));
    grid.appendChild(b);
  });

  lastBookedSet = nowBooked;
}


/* ============================================================
   PART 4 — ภาพห้อง (SVG ตามประเภทเตียง)
   ============================================================ */
function roomArt(bed, vip) {
  const wall  = vip ? "#FAF2DE" : "#F2F8F1";
  const floor = vip ? "#E9D6A8" : "#DDEFDF";
  const line  = vip ? "#6B531A" : "#24603C";
  const soft  = vip ? "#C9A94F" : "#9FCDAA";

  const beds = bed === "twin"
    ? `<rect x="44" y="120" width="88" height="56" rx="8" fill="${soft}" opacity=".22" stroke="${line}" stroke-opacity=".5"/>
       <rect x="44" y="120" width="88" height="20" rx="8" fill="${soft}" opacity=".85"/>
       <rect x="168" y="120" width="88" height="56" rx="8" fill="${soft}" opacity=".22" stroke="${line}" stroke-opacity=".5"/>
       <rect x="168" y="120" width="88" height="20" rx="8" fill="${soft}" opacity=".85"/>`
    : `<rect x="72" y="114" width="156" height="64" rx="10" fill="${soft}" opacity=".22" stroke="${line}" stroke-opacity=".5"/>
       <rect x="72" y="114" width="156" height="22" rx="10" fill="${soft}" opacity=".85"/>
       <rect x="90" y="120" width="50" height="11" rx="5" fill="${wall}"/>
       <rect x="160" y="120" width="50" height="11" rx="5" fill="${wall}"/>`;

  return `<svg viewBox="0 0 300 200" xmlns="http://www.w3.org/2000/svg" role="img"
            aria-label="ภาพจำลองภายในห้อง">
    <rect width="300" height="200" fill="${wall}"/>
    <rect y="152" width="300" height="48" fill="${floor}"/>
    <rect x="196" y="32" width="74" height="54" rx="6" fill="none" stroke="${line}" stroke-width="2" stroke-opacity=".55"/>
    <line x1="233" y1="32" x2="233" y2="86" stroke="${line}" stroke-width="2" stroke-opacity=".55"/>
    <circle cx="58" cy="50" r="14" fill="none" stroke="${line}" stroke-width="2" stroke-opacity=".55"/>
    <line x1="58" y1="50" x2="58" y2="114" stroke="${line}" stroke-width="2" stroke-opacity=".3"/>
    ${beds}
    ${vip ? `<ellipse cx="262" cy="166" rx="24" ry="12" fill="none" stroke="${line}" stroke-width="2" stroke-opacity=".7"/>` : ""}
  </svg>`;
}


/* ============================================================
   PART 5 — หน้า 2: เปิดหน้าจอง + คำนวณราคา
   ============================================================ */
function openBooking(number) {
  const r = rooms.find(x => x.number === number);
  if (!r || r.booked) return;

  current = r;
  clearInterval(pollTimer);          // หยุด polling ระหว่างกรอกข้อมูล

  $("bk-title").textContent = r.typeName || (r.bed === "twin" ? "Twin bed" : "Double bed");
  $("bk-room").textContent  = r.number;
  $("bk-vip").classList.toggle("hidden", r.tier !== "vip");
  $("bk-art").innerHTML     = roomArt(r.bed, r.tier === "vip");
  $("bk-price").textContent = th(r.price);

  const list = $("bk-detail");
  list.innerHTML = "";
  r.detail.forEach(d => {
    const li = document.createElement("li");
    li.textContent = d;
    list.appendChild(li);
  });

  $("bk-nights").value  = 1;
  $("bk-checkin").value = todayStr;
  $("bk-name").value    = "";
  $("bk-phone").value   = "";
  $("bk-email").value   = "";
  $("bk-err").textContent = "";
  $("bk-msg").textContent = "";
  $("bk-msg").className = "msg";
  $("btn-book").disabled = false;
  calc();

  $("page-rooms").classList.add("hidden");
  $("page-booking").classList.remove("hidden");
  window.scrollTo(0, 0);
}

// จำนวนคืน x ราคาห้อง
function calc() {
  if (!current) return 1;
  let n = parseInt($("bk-nights").value, 10);
  if (isNaN(n) || n < 1) n = 1;
  if (n > MAX_NIGHTS) n = MAX_NIGHTS;
  $("bk-calc").textContent  = `${n} คืน × ${th(current.price)} บาท`;
  $("bk-total").textContent = th(n * current.price);
  $("bk-checkout").textContent = addDays($("bk-checkin").value, n);
  return n;
}

function stepNights(delta) {
  const el = $("bk-nights");
  let n = parseInt(el.value, 10);
  if (isNaN(n)) n = 1;
  n = Math.min(MAX_NIGHTS, Math.max(1, n + delta));
  el.value = n;
  $("bk-err").textContent = "";
  calc();
}

function backToRooms() {
  current = null;
  $("page-booking").classList.add("hidden");
  $("page-rooms").classList.remove("hidden");
  loadRooms();
  startPolling();
}


/* ============================================================
   PART 6 — ส่งคำขอจอง
   ============================================================ */
async function submitBooking() {
  if (!current) return;

  // ตรวจข้อมูลก่อนส่ง
  const raw     = $("bk-nights").value.trim();
  const n       = parseInt(raw, 10);
  const booker  = $("bk-name").value.trim();
  const phone   = $("bk-phone").value.trim();
  const email   = $("bk-email").value.trim();
  const checkIn = $("bk-checkin").value;
  const err     = $("bk-err");

  if (raw === "" || isNaN(n) || n < 1 || n > MAX_NIGHTS) {
    err.textContent = `กรอกจำนวนคืนระหว่าง 1 ถึง ${MAX_NIGHTS}`;
    $("bk-nights").focus(); return;
  }
  if (!checkIn)      { err.textContent = "เลือกวันเช็คอิน";        $("bk-checkin").focus(); return; }
  if (!booker)       { err.textContent = "กรอกชื่อผู้จอง";          $("bk-name").focus();    return; }
  if (!phone)        { err.textContent = "กรอกเบอร์โทรติดต่อ";      $("bk-phone").focus();   return; }
  if (email && !/^[^@\s]+@[^@\s]+\.[^@\s]+$/.test(email)) {
    err.textContent = "รูปแบบอีเมลไม่ถูกต้อง"; $("bk-email").focus(); return;
  }
  err.textContent = "";

  const msg = $("bk-msg");
  const btn = $("btn-book");
  btn.disabled = true;
  msg.className = "msg";
  msg.textContent = "กำลังส่งข้อมูลไปที่เซิร์ฟเวอร์";

  try {
    const data = await api.book({
      room: current.number, nights: n, booker, phone, email, checkIn
    });
    if (data.ok) {
      const b = data.booking;
      msg.className = "msg ok";
      msg.textContent = `จองห้อง ${b.room} แล้ว รหัส ${b.id} · ${b.checkIn} ถึง ${b.checkOut} · รวม ${th(b.total)} บาท`;
      setTimeout(backToRooms, 2400);
    } else {
      msg.className = "msg error";
      msg.textContent = data.error || "จองไม่สำเร็จ ลองใหม่อีกครั้ง";
      btn.disabled = false;
    }
  } catch (e) {
    msg.className = "msg error";
    msg.textContent = "ติดต่อเซิร์ฟเวอร์ไม่ได้ ตรวจสอบว่าโปรแกรม C++ ยังทำงานอยู่";
    btn.disabled = false;
  }
}


/* ============================================================
   PART 7 — polling อัปเดตสด
   ============================================================ */
function startPolling() {
  clearInterval(pollTimer);
  pollTimer = setInterval(loadRooms, POLL_MS);
}


/* ============================================================
   PART 8 — ผูก event + เริ่มทำงาน
   ============================================================ */
$("bk-nights").addEventListener("input", () => { $("bk-err").textContent = ""; calc(); });
$("bk-checkin").addEventListener("change", () => { $("bk-err").textContent = ""; calc(); });
$("btn-minus").addEventListener("click", () => stepNights(-1));
$("btn-plus").addEventListener("click",  () => stepNights(1));
$("btn-book").addEventListener("click", submitBooking);
$("btn-cancel").addEventListener("click", backToRooms);
$("btn-back").addEventListener("click", backToRooms);
document.addEventListener("keydown", e => {
  if (e.key === "Escape" && current) backToRooms();
});

loadRooms(true);
startPolling();
