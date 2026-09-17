/**
 * HILBERT GRAND HOTEL & RESORT
 * Luxury Boutique Front-End Engine & Client Application
 */

// =============================================================================
// 1. SVG Icon System (Stroke 1.5px, Consistent Geometry)
// =============================================================================
function getSvgIcon(name, size = 16, customClass = "") {
  const s = size;
  const cls = `svg-icon ${customClass}`.trim();
  switch (name) {
    case "bed":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><path d="M2 4v16M2 8h18a2 2 0 0 1 2 2v10M2 17h20M6 8v9"/></svg>`;
    case "users":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><path d="M17 21v-2a4 4 0 0 0-4-4H5a4 4 0 0 0-4 4v2"/><circle cx="9" cy="7" r="4"/><path d="M23 21v-2a4 4 0 0 0-3-3.87"/><path d="M16 3.13a4 4 0 0 1 0 7.75"/></svg>`;
    case "user":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><path d="M20 21v-2a4 4 0 0 0-4-4H8a4 4 0 0 0-4 4v2"/><circle cx="12" cy="7" r="4"/></svg>`;
    case "briefcase":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><rect x="2" y="7" width="20" height="14" rx="2" ry="2"/><path d="M16 21V5a2 2 0 0 0-2-2h-4a2 2 0 0 0-2 2v16"/></svg>`;
    case "crown":
    case "vip":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><path d="M2 4l3 12h14l3-12-6 7-4-7-4 7-6-7zm3 16h14v2H5v-2z"/></svg>`;
    case "sparkles":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><path d="M12 2l2.4 7.2L22 12l-7.6 2.8L12 22l-2.4-7.2L2 12l7.6-2.8z"/></svg>`;
    case "star":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><polygon points="12 2 15.09 8.26 22 9.27 17 14.14 18.18 21.02 12 17.77 5.82 21.02 7 14.14 2 9.27 8.91 8.26 12 2"/></svg>`;
    case "check":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><polyline points="20 6 9 17 4 12"/></svg>`;
    case "alert":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><path d="M10.29 3.86L1.82 18a2 2 0 0 0 1.71 3h16.94a2 2 0 0 0 1.71-3L13.71 3.86a2 2 0 0 0-3.42 0z"/><line x1="12" y1="9" x2="12" y2="13"/><line x1="12" y1="17" x2="12.01" y2="17"/></svg>`;
    case "search":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><circle cx="11" cy="11" r="8"/><line x1="21" y1="21" x2="16.65" y2="16.65"/></svg>`;
    case "building":
    case "floor":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><rect x="4" y="2" width="16" height="20" rx="2" ry="2"/><line x1="9" y1="22" x2="9" y2="22.01"/><line x1="15" y1="22" x2="15" y2="22.01"/></svg>`;
    case "grid":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><rect x="3" y="3" width="7" height="7"/><rect x="14" y="3" width="7" height="7"/><rect x="14" y="14" width="7" height="7"/><rect x="3" y="14" width="7" height="7"/></svg>`;
    case "dashboard":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><rect x="3" y="3" width="18" height="18" rx="2"/><line x1="3" y1="9" x2="21" y2="9"/><line x1="9" y1="21" x2="9" y2="9"/></svg>`;
    case "list":
    case "receipt":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><line x1="8" y1="6" x2="21" y2="6"/><line x1="8" y1="12" x2="21" y2="12"/><line x1="8" y1="18" x2="21" y2="18"/><line x1="3" y1="6" x2="3.01" y2="6"/><line x1="3" y1="12" x2="3.01" y2="12"/><line x1="3" y1="18" x2="3.01" y2="18"/></svg>`;
    case "arrow-up":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><line x1="12" y1="19" x2="12" y2="5"/><polyline points="5 12 12 5 19 12"/></svg>`;
    case "arrow-down":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><line x1="12" y1="5" x2="12" y2="19"/><polyline points="19 12 12 19 5 12"/></svg>`;
    case "edit":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><path d="M11 4H4a2 2 0 0 0-2 2v14a2 2 0 0 0 2 2h14a2 2 0 0 0 2-2v-7"/><path d="M18.5 2.5a2.121 2.121 0 0 1 3 3L12 15l-4 1 1-4 9.5-9.5z"/></svg>`;
    case "trash":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><polyline points="3 6 5 6 21 6"/><path d="M19 6v14a2 2 0 0 1-2 2H7a2 2 0 0 1-2-2V6m3 0V4a2 2 0 0 1 2-2h4a2 2 0 0 1 2 2v2"/></svg>`;
    case "shield":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><path d="M12 22s8-4 8-10V5l-8-3-8 3v7c0 6 8 10 8 10z"/></svg>`;
    case "lock":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><rect x="3" y="11" width="18" height="11" rx="2" ry="2"/><path d="M7 11V7a5 5 0 0 1 10 0v4"/></svg>`;
    case "clock":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><circle cx="12" cy="12" r="10"/><polyline points="12 6 12 12 16 14"/></svg>`;
    case "info":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><circle cx="12" cy="12" r="10"/><line x1="12" y1="16" x2="12" y2="12"/><line x1="12" y1="8" x2="12.01" y2="8"/></svg>`;
    case "phone":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><path d="M22 16.92v3a2 2 0 0 1-2.18 2 19.79 19.79 0 0 1-8.63-3.07 19.5 19.5 0 0 1-6-6 19.79 19.79 0 0 1-3.07-8.67A2 2 0 0 1 4.11 2h3a2 2 0 0 1 2 1.72 12.84 12.84 0 0 0 .7 2.81 2 2 0 0 1-.45 2.11L8.09 9.91a16 16 0 0 0 6 6l1.27-1.27a2 2 0 0 1 2.11-.45 12.84 12.84 0 0 0 2.81.7A2 2 0 0 1 22 16.92z"/></svg>`;
    case "mail":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><path d="M4 4h16c1.1 0 2 .9 2 2v12c0 1.1-.9 2-2 2H4c-1.1 0-2-.9-2-2V6c0-1.1.9-2 2-2z"/><polyline points="22,6 12,13 2,6"/></svg>`;
    case "keyboard":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><rect x="2" y="4" width="20" height="16" rx="2"/><line x1="6" y1="8" x2="6.01" y2="8"/><line x1="10" y1="8" x2="10.01" y2="8"/><line x1="14" y1="8" x2="14.01" y2="8"/><line x1="18" y1="8" x2="18.01" y2="8"/><line x1="6" y1="12" x2="6.01" y2="12"/><line x1="10" y1="12" x2="10.01" y2="12"/><line x1="14" y1="12" x2="14.01" y2="12"/><line x1="18" y1="12" x2="18.01" y2="12"/><line x1="8" y1="16" x2="16" y2="16"/></svg>`;
    case "eye":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><path d="M1 12s4-8 11-8 11 8 11 8-4 8-11 8-11-8-11-8z"/><circle cx="12" cy="12" r="3"/></svg>`;
    case "zap":
    case "bolt":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><polygon points="13 2 3 14 12 14 11 22 21 10 12 10 13 2"/></svg>`;
    case "calendar":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><rect x="3" y="4" width="18" height="18" rx="2" ry="2"/><line x1="16" y1="2" x2="16" y2="6"/><line x1="8" y1="2" x2="8" y2="6"/><line x1="3" y1="10" x2="21" y2="10"/></svg>`;
    case "moon":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><path d="M21 12.79A9 9 0 1 1 11.21 3 7 7 0 0 0 21 12.79z"/></svg>`;
    case "sun":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><circle cx="12" cy="12" r="5"/><path d="M12 1v2M12 21v2M4.22 4.22l1.42 1.42M18.36 18.36l1.42 1.42M1 12h2M21 12h2M4.22 19.78l1.42-1.42M18.36 5.64l1.42-1.42"/></svg>`;
    default:
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><circle cx="12" cy="12" r="10"/></svg>`;
  }
}

// =============================================================================
// 2. Curated Boutique Hotel Photography (High Resolution)
// =============================================================================
const ROOM_PHOTOS = {
  normal_twin: [
    "https://images.unsplash.com/photo-1590490360182-c33d57733427?auto=format&fit=crop&w=800&q=80",
    "https://images.unsplash.com/photo-1566665797739-1674de7a421a?auto=format&fit=crop&w=800&q=80"
  ],
  normal_double: [
    "https://images.unsplash.com/photo-1582719478250-c89cae4dc85b?auto=format&fit=crop&w=800&q=80",
    "https://images.unsplash.com/photo-1618773928121-c32242e63f39?auto=format&fit=crop&w=800&q=80",
    "https://images.unsplash.com/photo-1578683010236-d716f9a3f461?auto=format&fit=crop&w=800&q=80"
  ],
  vip: [
    "https://images.unsplash.com/photo-1631049307264-da0ec9d70304?auto=format&fit=crop&w=800&q=80",
    "https://images.unsplash.com/photo-1591088398332-8a7791972843?auto=format&fit=crop&w=800&q=80",
    "https://images.unsplash.com/photo-1582719508461-905c673771fd?auto=format&fit=crop&w=800&q=80"
  ]
};

function getRoomPhoto(tier, bed, roomNumber) {
  let list = ROOM_PHOTOS.normal_double;
  if (tier === "vip") {
    list = ROOM_PHOTOS.vip;
  } else if (bed === "twin") {
    list = ROOM_PHOTOS.normal_twin;
  }
  const idx = Math.abs(parseInt(roomNumber) || 0) % list.length;
  return list[idx];
}

const $  = (id) => document.getElementById(id);
const th = (n)  => Number(n).toLocaleString("th-TH");

// =============================================================================
// 3. Application State & Backend REST Bridge
// =============================================================================
class HotelAppEngine {
  constructor() {
    this.rooms = [];
    this.bookings = [];
    this.auditLogs = [];
    this.todayStr = "";
    this.currentUser = null;
    this.token = "";
    this.activePortal = "guest";
    this.guestViewMode = "cards"; // 'cards' or 'matrix'

    this.filterTier = "ALL";
    this.filterBed = "ALL";
    this.filterAvailableOnly = true;
    this.filterSortMode = "default";
    this.filterSearch = "";
    this.filterNights = 1;
    this.filterCheckIn = "";
    this.filterCheckOut = "";
    this.filterMaxPrice = 10000;
    this.selectedAmenities = new Set();
    this.auditSearch = "";
    this.adminUserSearch = "";
    this.adminUsers = [];
    this.cmdHistory = [];
    this.cmdHistoryIdx = -1;
    this.selectedRoomForDrawer = null;
    this.currentDensity = localStorage.getItem("hgh_table_density") || "comfortable";
    this.tableSort = {
      staffCheckout: { col: null, dir: "asc" },
      adminRooms: { col: null, dir: "asc" },
      adminTxn: { col: null, dir: "asc" },
      adminAudit: { col: null, dir: "desc" },
      adminUsers: { col: null, dir: "asc" }
    };

    this.init();
  }

  async init() {
    this.initTheme();
    this.loadSession();
    this.setupEvents();

    if (this.token) {
      await this.verifySession();
    }

    try {
      const cRes = await fetch("/api/config");
      const cData = await cRes.json();
      this.demoMode = !!cData.demoMode;
      if (this.demoMode) {
        document.body.classList.add("demo-mode-active");
      } else {
        document.body.classList.remove("demo-mode-active");
        const bubble = document.getElementById("floatingRoleBubble");
        if (bubble) bubble.style.display = "none";
        const demoBox = document.getElementById("authDemoProfilesBox");
        if (demoBox) demoBox.style.display = "none";
      }
    } catch (_) {}

    await this.refreshData();
    this.renderAll();
    this.applyTableDensity(this.currentDensity);

    // 2-second heartbeat
    setInterval(async () => {
      await this.refreshData();
      this.renderLiveViews();
    }, 2000);
  }

  // ---- REST API Calls ----

  isStaffLevel() {
    const role = this.currentUser && this.currentUser.role;
    return role === "admin" || role === "staff";
  }

  isAdminLevel() {
    return this.currentUser && this.currentUser.role === "admin";
  }

  async apiFetch(url, options = {}) {
    options.headers = options.headers || {};
    if (this.token) {
      options.headers["Authorization"] = `Bearer ${this.token}`;
      options.headers["X-Auth-Token"] = this.token;
    }
    const res = await fetch(url, options);
    if (res.status === 401) {
      this.handleSessionExpired();
      return res;
    }
    if (res.status === 403 && !options.silent) {
      try {
        const err = await res.clone().json();
        this.toast(err.error || "Access Denied: สิทธิ์ไม่เพียงพอ", "error");
      } catch (_) {
        this.toast("Access Denied: สิทธิ์ไม่เพียงพอ", "error");
      }
    }
    return res;
  }

  // ดึงข้อมูลทุกอย่างที่บทบาทปัจจุบันต้องใช้ ในลำดับเดียวกันเสมอ
  async refreshData() {
    await this.fetchRooms();
    if (this.isStaffLevel()) {
      await this.fetchAdminData();
      if (this.isAdminLevel()) {
        await this.fetchAdminUsers();
      }
    } else if (this.currentUser) {
      await this.fetchMyBookings();
    } else {
      this.bookings = [];
    }
  }

  async fetchMyBookings() {
    try {
      const res = await fetch("/api/my-bookings", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({
          booker: this.currentUser.fullName || this.currentUser.username || "",
          phone: this.currentUser.phone || ""
        })
      });
      const data = await res.json();
      this.bookings = data.bookings || [];
    } catch (e) {
      console.warn("Failed to fetch /api/my-bookings", e);
    }
  }

  // เตือนเมื่อเซิร์ฟเวอร์รับข้อมูลแล้วแต่เขียนลง hotel.xlsx ไม่สำเร็จ
  // (เดิมหน้าเว็บขึ้นว่าสำเร็จทั้งที่ไฟล์ไม่ได้ถูกอัปเดต ข้อมูลจึงหายเมื่อรีสตาร์ต)
  warnIfNotSaved(res) {
    if (res && res.saved === false) {
      this.toast(res.saveError || "บันทึกลงไฟล์ Excel ไม่สำเร็จ", "error");
      return true;
    }
    return false;
  }

  async fetchRooms(firstTime = false) {
    try {
      const res = await fetch("/api/rooms");
      const data = await res.json();
      this.rooms = data.rooms || [];
      if (data.today) this.todayStr = data.today;
      if (typeof data.demoMode !== "undefined") {
        this.demoMode = !!data.demoMode;
        if (this.demoMode) {
          document.body.classList.add("demo-mode-active");
        } else {
          document.body.classList.remove("demo-mode-active");
          const bubble = document.getElementById("floatingRoleBubble");
          if (bubble) bubble.style.display = "none";
          const demoBox = document.getElementById("authDemoProfilesBox");
          if (demoBox) demoBox.style.display = "none";
        }
        this.updateFloatingRoleBubble();
      }
    } catch (e) {
      console.warn("Failed to fetch /api/rooms", e);
    }
  }

  async fetchAdminData() {
    try {
      const res = await this.apiFetch("/api/admin/data", { silent: true });
      if (!res.ok) return;
      const data = await res.json();
      if (data.rooms) this.rooms = data.rooms;
      if (data.bookings) this.bookings = data.bookings;
      if (data.auditLogs) this.auditLogs = data.auditLogs;
      if (data.today) this.todayStr = data.today;
    } catch (e) {
      console.warn("Failed to fetch /api/admin/data", e);
    }
  }

  async fetchAdminUsers() {
    try {
      const res = await this.apiFetch("/api/admin/users", { silent: true });
      if (!res.ok) return;
      const data = await res.json();
      if (data.ok && data.users) {
        this.adminUsers = data.users;
      }
    } catch (e) {
      console.warn("Failed to fetch /api/admin/users", e);
    }
  }

  async createAdminUser(user) {
    const res = await this.apiFetch("/api/admin/users/create", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(user)
    });
    return res.json();
  }

  async updateAdminUser(user) {
    const res = await this.apiFetch("/api/admin/users/update", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(user)
    });
    return res.json();
  }

  async deleteAdminUser(username) {
    const res = await this.apiFetch("/api/admin/users/delete", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ username })
    });
    return res.json();
  }

  async backupDatabase() {
    const res = await this.apiFetch("/api/admin/backup", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: "{}"
    });
    return res.json();
  }

  async runConsoleCommand(cmd) {
    const res = await this.apiFetch("/api/admin/console", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ cmd })
    });
    return res.json();
  }

  async extendStay(bookingId, nights, note = "") {
    const res = await this.apiFetch("/api/booking/extend", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ id: bookingId, nights, note })
    });
    return res.json();
  }

  async bookRoom(roomId, booker, phone, email, checkIn, nights, note) {
    const res = await this.apiFetch("/api/book", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ room: roomId, booker, phone, email, checkIn, nights, note })
    });
    return res.json();
  }

  async updateBookingStatus(id, status) {
    const res = await this.apiFetch("/api/admin/status", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ id, status })
    });
    return res.json();
  }

  async updateRoomDetails(roomId, price, note) {
    const res = await this.apiFetch("/api/admin/room", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ room: roomId, price, note })
    });
    return res.json();
  }

  async reloadExcel() {
    const res = await this.apiFetch("/api/admin/reload", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: "{}"
    });
    return res.json();
  }

  async login(username, password) {
    const res = await fetch("/api/auth/login", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ username, password })
    });
    const data = await res.json();
    if (data.ok && data.token) {
      this.saveSession(data.user, data.token);
    }
    return data;
  }

  async register(username, password, fullName, phone, email) {
    const res = await fetch("/api/auth/register", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ username, password, fullName, phone, email })
    });
    const data = await res.json();
    if (data.ok && data.token) {
      this.saveSession(data.user, data.token);
    }
    return data;
  }

  // ---- Session & Theme ----
  initTheme() {
    const saved = localStorage.getItem("gh_theme") || "light";
    document.documentElement.setAttribute("data-theme", saved);
    this.updateThemeIcon(saved);
  }

  toggleTheme() {
    const cur = document.documentElement.getAttribute("data-theme") || "light";
    const next = cur === "light" ? "dark" : "light";
    document.documentElement.setAttribute("data-theme", next);
    localStorage.setItem("gh_theme", next);
    this.updateThemeIcon(next);
  }

  updateThemeIcon(theme) {
    const icon = $("themeIconSvg");
    if (icon) {
      icon.innerHTML = theme === "dark"
        ? `<circle cx="12" cy="12" r="5"/><path d="M12 1v2M12 21v2M4.22 4.22l1.42 1.42M18.36 18.36l1.42 1.42M1 12h2M21 12h2M4.22 19.78l1.42-1.42M18.36 5.64l1.42-1.42"/>`
        : `<path d="M21 12.79A9 9 0 1 1 11.21 3 7 7 0 0 0 21 12.79z"/>`;
    }
  }

  loadSession() {
    try {
      const raw = localStorage.getItem("gh_user");
      if (raw) this.currentUser = JSON.parse(raw);
      this.token = localStorage.getItem("gh_token") || "";
    } catch (e) {
      this.currentUser = null;
      this.token = "";
    }
  }

  saveSession(user, token) {
    this.currentUser = user;
    if (user) {
      localStorage.setItem("gh_user", JSON.stringify(user));
      if (token !== undefined && token !== null) {
        this.token = token;
        if (token) localStorage.setItem("gh_token", token);
        else localStorage.removeItem("gh_token");
      }
    } else {
      localStorage.removeItem("gh_user");
      localStorage.removeItem("gh_token");
      this.token = "";
      this.currentUser = null;
    }
  }

  async verifySession() {
    if (!this.token) return;
    try {
      const res = await fetch("/api/auth/me", {
        headers: {
          "Authorization": `Bearer ${this.token}`,
          "X-Auth-Token": this.token
        }
      });
      if (res.status === 401 || res.status === 403) {
        this.saveSession(null, null);
        this.activePortal = "guest";
        return;
      }
      const data = await res.json();
      if (data && data.ok && data.user) {
        this.saveSession(data.user, this.token);
      } else {
        this.saveSession(null, null);
        this.activePortal = "guest";
      }
    } catch (e) {
      console.warn("Session check offline or server unavailable:", e);
    }
  }

  handleSessionExpired() {
    if (!this.currentUser && !this.token) return;
    this.saveSession(null, null);
    this.activePortal = "guest";
    this.renderAll();

    const now = Date.now();
    if (!this.lastExpiredToastTime || (now - this.lastExpiredToastTime > 8000)) {
      this.lastExpiredToastTime = now;
      this.toast("เซสชันหมดอายุ กรุณาเข้าสู่ระบบใหม่อีกครั้ง", "warning");
    }
  }

  logout() {
    if (this.token) {
      fetch("/api/auth/logout", {
        method: "POST",
        headers: {
          "Authorization": `Bearer ${this.token}`,
          "X-Auth-Token": this.token
        }
      }).catch(() => {});
    }
    this.saveSession(null, null);
    this.activePortal = "guest";
    this.renderAll();
    this.toast("ออกจากระบบเรียบร้อยแล้ว", "info");
  }

  // ===========================================================================
  // 4. Rendering Views & Navigation
  // ===========================================================================
  renderAll() {
    this.renderNavTabs();
    this.renderAuthHeader();
    this.renderPortalViews();
  }

  renderLiveViews() {
    if (this.activePortal === "guest") {
      this.renderGuestCards();
      this.renderMyBookings();
    } else if (this.activePortal === "staff") {
      this.renderStaffPortal();
    } else if (this.activePortal === "admin") {
      this.renderAdminPortal();
    } else if (this.activePortal === "matrix") {
      this.renderMatrixPortal();
    }
  }

  renderNavTabs() {
    const nav = $("portalNavTabs");
    if (!nav) return;

    let tabs = [
      { id: "guest", label: "Guest Suites", icon: "bed" }
    ];

    if (this.currentUser) {
      if (this.currentUser.role === "admin" || this.currentUser.role === "staff") {
        tabs.push({ id: "staff", label: "Staff Hub", icon: "users" });
      }
      if (this.currentUser.role === "admin") {
        tabs.push({ id: "admin", label: "Admin Panel", icon: "dashboard" });
      }
    }
    tabs.push({ id: "matrix", label: "Floor Blueprint", icon: "building" });

    // Validate active portal
    if (!tabs.find(t => t.id === this.activePortal)) {
      this.activePortal = "guest";
    }

    nav.innerHTML = tabs.map(t => `
      <button class="nav-tab-btn ${t.id === this.activePortal ? 'active' : ''}" data-portal="${t.id}">
        ${getSvgIcon(t.icon, 14)}
        <span>${t.label}</span>
      </button>
    `).join("");

    nav.querySelectorAll(".nav-tab-btn").forEach(btn => {
      btn.addEventListener("click", () => {
        this.activePortal = btn.dataset.portal;
        this.renderAll();
      });
    });

    // Sync mobile bottom navigation bar state and role restrictions
    const curRole = (this.currentUser?.role || "guest").toLowerCase();
    $("mobNavStaff")?.classList.toggle("hidden", curRole !== "staff" && curRole !== "admin");
    $("mobNavAdmin")?.classList.toggle("hidden", curRole !== "admin");

    document.querySelectorAll(".mobile-nav-item").forEach(item => {
      item.classList.toggle("active", item.dataset.portal === this.activePortal);
    });
  }

  renderAuthHeader() {
    const container = $("authHeaderContainer");
    if (!container) return;

    this.updateFloatingRoleBubble();

    if (!this.currentUser) {
      container.innerHTML = `
        <button class="btn btn-luxury btn-sm" id="headerSignInBtn">
          ${getSvgIcon("user", 14)}
          <span>Sign In</span>
        </button>
      `;
      $("headerSignInBtn")?.addEventListener("click", () => this.openAuthModal());
    } else {
      const curRole = (this.currentUser.role || "guest").toLowerCase();
      const roleDisplay = curRole.toUpperCase();
      const initials = (this.currentUser.fullName || this.currentUser.username || "U").substring(0, 2).toUpperCase();

      container.innerHTML = `
        <div class="user-profile-badge" id="userProfileBadgeToggle">
          <div class="user-avatar">${initials}</div>
          <div class="user-info-text">
            <span class="user-name">${this.currentUser.fullName || this.currentUser.username}</span>
            <span class="user-role-tag">${roleDisplay}</span>
          </div>
          <span style="font-size: 10px; color: var(--text-muted); margin-left: 2px;">▼</span>
        </div>
        <div class="user-dropdown-popover hidden" id="userDropdownPopover">
          <div style="padding: 6px 8px 10px 8px; border-bottom: 1px solid var(--border-subtle);">
            <div style="font-weight: 700; font-size: 13.5px;">${this.currentUser.fullName || this.currentUser.username}</div>
            <div style="color: var(--text-muted); font-size: 11.5px;">${this.currentUser.email || this.currentUser.phone || ''}</div>
          </div>

          ${this.demoMode ? `
          <div style="padding: 6px 0; border-bottom: 1px solid var(--border-subtle); display:flex; flex-direction:column; gap:4px;">
            <div style="font-size: 10px; text-transform: uppercase; color: var(--text-muted); font-weight: 700; padding: 0 4px;">Quick Switch Role (Demo):</div>
            <button class="dropdown-role-btn ${curRole === 'admin' ? 'active' : ''}" data-role="admin">
              ${getSvgIcon("crown", 13)} Administrator (Admin)
            </button>
            <button class="dropdown-role-btn ${curRole === 'staff' ? 'active' : ''}" data-role="staff">
              ${getSvgIcon("briefcase", 13)} Front Desk Staff
            </button>
            <button class="dropdown-role-btn ${curRole === 'guest' ? 'active' : ''}" data-role="guest">
              ${getSvgIcon("user", 13)} Guest Customer
            </button>
          </div>
          ` : ''}

          <button class="btn btn-outline btn-sm" id="popoverSignOutBtn" style="margin-top: 4px; width: 100%; border: none; justify-content: flex-start; color: var(--status-maintenance);">
            ${getSvgIcon("alert", 14)}
            <span>Sign Out</span>
          </button>
        </div>
      `;

      $("userProfileBadgeToggle")?.addEventListener("click", (e) => {
        e.stopPropagation();
        $("userDropdownPopover")?.classList.toggle("hidden");
      });

      container.querySelectorAll(".dropdown-role-btn").forEach(btn => {
        btn.addEventListener("click", async (e) => {
          e.stopPropagation();
          $("userDropdownPopover")?.classList.add("hidden");
          await this.switchRole(btn.dataset.role);
        });
      });

      $("popoverSignOutBtn")?.addEventListener("click", (e) => {
        e.stopPropagation();
        this.logout();
      });
    }
  }

  updateFloatingRoleBubble() {
    if (!this.demoMode) {
      const bubble = document.getElementById("floatingRoleBubble");
      if (bubble) bubble.style.display = "none";
      const demoBox = document.getElementById("authDemoProfilesBox");
      if (demoBox) demoBox.style.display = "none";
      return;
    }
    const curRole = this.currentUser ? (this.currentUser.role || "guest").toLowerCase() : "guest";
    document.querySelectorAll(".role-pill-btn").forEach(btn => {
      btn.classList.toggle("active", btn.dataset.role === curRole);
    });
  }

  async switchRole(targetRole) {
    let u = "guest", p = "guest123";
    if (targetRole === "admin") { u = "admin"; p = "admin123"; }
    else if (targetRole === "staff") { u = "staff"; p = "staff123"; }

    const res = await this.login(u, p);
    if (res.ok && res.user) {
      if (targetRole === "admin") this.activePortal = "admin";
      else if (targetRole === "staff") this.activePortal = "staff";
      else this.activePortal = "guest";

      this.toast(`Switched to ${res.user.fullName} (${targetRole.toUpperCase()})`);
      await this.refreshData();
      this.renderAll();
    } else {
      this.toast("Failed to switch role", "error");
    }
  }

  renderPortalViews() {
    document.querySelectorAll(".portal-view").forEach(el => el.classList.remove("active"));
    const target = $(`${this.activePortal}Portal`);
    if (target) target.classList.add("active");

    this.renderLiveViews();
  }

  // ===========================================================================
  // 5. Portal 1: Guest Portal Rendering
  // ===========================================================================
  renderGuestCards() {
    const grid = $("guestCardsGrid");
    if (!grid) return;

    let filtered = this.rooms.filter(r => {
      // 1. Available Only filter
      if (this.filterAvailableOnly && r.booked) return false;

      // 2. Category / Tier filter
      if (this.filterTier !== "ALL" && r.tier !== this.filterTier) return false;

      // 3. Bed Type filter
      if (this.filterBed !== "ALL" && r.bed !== this.filterBed) return false;

      // 4. Max Price filter
      if (this.filterMaxPrice && r.price > this.filterMaxPrice) return false;

      // 5. Date-Range Availability Search (Check-In to Check-Out)
      if (this.filterCheckIn && this.filterCheckOut) {
        const reqIn = this.filterCheckIn;
        const reqOut = this.filterCheckOut;
        if (reqIn < reqOut) {
          const hasCollision = (r.activeBookings || []).some(bk => {
            const bIn = bk.checkIn;
            const bOut = bk.checkOut;
            return Math.max(new Date(reqIn).getTime(), new Date(bIn).getTime()) <
                   Math.min(new Date(reqOut).getTime(), new Date(bOut).getTime());
          });
          if (hasCollision) return false;
        }
      }

      // 6. Amenities Filter (All selected must match)
      if (this.selectedAmenities && this.selectedAmenities.size > 0) {
        const roomAms = (r.detail || []).map(a => a.toLowerCase());
        for (const am of this.selectedAmenities) {
          const target = am.toLowerCase();
          const match = roomAms.some(a => a.includes(target) || target.includes(a));
          if (!match) return false;
        }
      }

      // 7. Universal Omnibox Search
      if (this.filterSearch) {
        const q = this.filterSearch.toLowerCase();
        const numMatch = r.number.toLowerCase().includes(q);
        const nameMatch = (r.typeName || "").toLowerCase().includes(q);
        const bedMatch = (r.bed || "").toLowerCase().includes(q);
        const noteMatch = (r.note || "").toLowerCase().includes(q);
        // Match active booker name, phone, or booking ID if booked
        const bookingMatch = (this.bookings || []).some(b => 
          (b.room === r.number || b.roomId === r.number) && 
          (b.id.toLowerCase().includes(q) || (b.booker || "").toLowerCase().includes(q) || (b.phone || "").includes(q))
        );
        if (!numMatch && !nameMatch && !bedMatch && !noteMatch && !bookingMatch) return false;
      }

      return true;
    });

    // Update search results indicator and reset button
    const countEl = $("searchResultsCount");
    if (countEl) {
      countEl.textContent = `Showing ${filtered.length} of ${this.rooms.length} suites`;
    }

    // Update mobile search summary bar
    const mobSum = $("mobileSearchSummaryText");
    if (mobSum) {
      const parts = [];
      if (this.filterCheckIn && this.filterCheckOut) parts.push(`${this.filterNights}N`);
      if (this.filterTier !== "ALL") parts.push(this.filterTier.toUpperCase());
      if (this.filterBed !== "ALL") parts.push(this.filterBed);
      if (this.filterSearch) parts.push(`"${this.filterSearch}"`);
      mobSum.textContent = parts.length ? `Filters: ${parts.join(" • ")}` : `Search & Filter Suites (${filtered.length})`;
    }
    const mobBadge = $("mobileSearchActiveBadge");
    if (mobBadge) {
      mobBadge.textContent = `${filtered.length} Suites`;
    }

    const resetBtn = $("clearFiltersBtn");
    if (resetBtn) {
      const isFiltered = (this.filterTier !== "ALL") || (this.filterBed !== "ALL") ||
                         (!this.filterAvailableOnly) || (this.filterSearch !== "") ||
                         (this.filterCheckIn !== "") || (this.filterCheckOut !== "") ||
                         (this.filterMaxPrice < 10000) || (this.selectedAmenities.size > 0);
      resetBtn.style.display = isFiltered ? "inline-flex" : "none";
    }

    if (this.filterSortMode === "asc") {
      filtered.sort((a, b) => a.price - b.price);
    } else if (this.filterSortMode === "desc") {
      filtered.sort((a, b) => b.price - a.price);
    }

    if (filtered.length === 0) {
      grid.innerHTML = `
        <div style="grid-column: 1 / -1; text-align: center; padding: 60px 20px; background: var(--bg-surface); border: 1px solid var(--border-subtle); border-radius: var(--radius-lg);">
          <h3 class="font-serif" style="font-size: 20px; margin-bottom: 6px;">No Suites Available</h3>
          <p style="color: var(--text-secondary); font-size: 13.5px;">Try adjusting your filters or search keywords.</p>
        </div>
      `;
      return;
    }

    grid.innerHTML = filtered.map(r => {
      const isVip = r.tier === "vip";
      const photoUrl = getRoomPhoto(r.tier, r.bed, r.number);
      const isBooked = r.booked;
      const statusClass = isBooked ? "occupied" : "available";
      const statusText = isBooked ? "Occupied" : "Available";

      const categoryTitle = isVip ? "VIP Presidential Suite" : (r.bed === "twin" ? "Standard Twin Suite" : "Deluxe King Suite");
      const bedDesc = r.bed === "twin" ? "2 Single Beds" : "1 King Size Bed";
      const amenities = r.detail && r.detail.length ? r.detail : (isVip ? ["Smart TV", "WiFi", "Ocean Balcony", "Jacuzzi", "Breakfast"] : ["TV", "AC", "WiFi", "Artisan Breakfast"]);

      return `
        <div class="room-card-luxury">
          <div class="card-photo-banner">
            <img class="card-photo-img" src="${photoUrl}" alt="Room ${r.number}">
            <div class="card-photo-scrim"></div>
            <span class="photo-badge-tier">${isVip ? `${getSvgIcon('crown', 12)} VIP Villa` : 'Standard'}</span>
            <span class="photo-badge-floor">Floor ${r.floor}</span>
          </div>

          <div class="card-body-content">
            <div class="card-header-row">
              <div>
                <h3 class="room-suite-title font-serif">Suite ${r.number}</h3>
                <div class="room-details-line">
                  <span>${categoryTitle}</span>
                  <span>•</span>
                  <span>${bedDesc}</span>
                </div>
              </div>
              <span class="status-pill ${statusClass}">
                ${statusText}
              </span>
            </div>

            <div class="amenities-tag-group">
              ${amenities.slice(0, 4).map(a => `<span class="amenity-chip">${getSvgIcon("sparkles", 11)} ${a}</span>`).join("")}
              ${amenities.length > 4 ? `<span class="amenity-chip">+${amenities.length - 4} more</span>` : ""}
            </div>
          </div>

          <div class="card-footer-luxury">
            <div class="price-lockup">
              <div class="price-num-row">
                <span class="price-curr-sign">฿</span>
                <span class="price-big-text">${th(r.price)}</span>
                <span class="price-per-text">/ night</span>
              </div>
              <span class="price-total-sub">${this.filterNights} night${this.filterNights > 1 ? 's' : ''}: ฿${th(r.price * this.filterNights)}</span>
            </div>

            ${isBooked ? `
              <div style="display:flex; gap:6px;">
                ${this.isStaffLevel() ? `
                  <button class="btn btn-outline btn-sm guest-card-inspect-btn" data-room="${r.number}">
                    ${getSvgIcon("eye", 13)}
                    <span>Inspect</span>
                  </button>
                ` : ''}
                <button class="btn btn-outline btn-sm" disabled style="opacity: 0.6; cursor: not-allowed;">
                  ${getSvgIcon("check", 14)}
                  <span>Reserved</span>
                </button>
              </div>
            ` : `
              <div style="display:flex; gap:6px;">
                ${this.isStaffLevel() ? `
                  <button class="btn btn-outline btn-sm guest-card-inspect-btn" data-room="${r.number}" title="Inspect Room">
                    ${getSvgIcon("eye", 13)}
                  </button>
                ` : ''}
                <button class="btn btn-luxury btn-sm book-drawer-trigger" data-room="${r.number}">
                  <span>Reserve Suite</span>
                </button>
              </div>
            `}
          </div>
        </div>
      `;
    }).join("");

    grid.querySelectorAll(".book-drawer-trigger").forEach(btn => {
      btn.addEventListener("click", () => this.openDrawer(btn.dataset.room));
    });

    grid.querySelectorAll(".guest-card-inspect-btn").forEach(btn => {
      btn.addEventListener("click", () => this.openRoomInspector(btn.dataset.room));
    });
  }

  renderMyBookings() {
    const container = $("myBookingsContainer");
    if (!container) return;

    if (!this.currentUser) {
      container.innerHTML = "";
      return;
    }

    const myBooks = this.bookings.filter(b => 
      b.booker === this.currentUser.fullName || 
      b.booker === this.currentUser.username ||
      b.phone === this.currentUser.phone
    );

    if (myBooks.length === 0) {
      container.innerHTML = "";
      return;
    }

    container.innerHTML = `
      <div style="background: var(--bg-surface); border: 1px solid var(--border-medium); border-radius: var(--radius-lg); padding: 18px 22px; margin-bottom: 24px; box-shadow: var(--shadow-sm);">
        <div style="display: flex; align-items: center; justify-content: space-between; margin-bottom: 12px;">
          <h3 class="font-serif" style="font-size: 18px;">My Active Reservations (${myBooks.length})</h3>
          <span style="font-size: 12px; color: var(--accent); font-weight: 600;">Welcome back, ${this.currentUser.fullName || this.currentUser.username}</span>
        </div>
        <div style="display: grid; gap: 10px;">
          ${myBooks.map(b => {
            const rNum = b.room || b.roomId;
            const roomObj = this.rooms.find(x => String(x.number) === String(rNum));
            const price = roomObj ? roomObj.price : 0;
            const canExtend = b.status === "checkin" || b.status === "wait";

            return `
              <div style="display:flex; justify-content:space-between; align-items:center; background: var(--bg-surface-subtle); padding: 10px 16px; border-radius: var(--radius-sm); border: 1px solid var(--border-subtle); flex-wrap: wrap; gap: 8px;">
                <div>
                  <strong style="font-size: 15px;">Suite ${rNum}</strong>
                  <span style="margin-left: 8px; color: var(--text-secondary); font-size: 12.5px;">(${b.checkIn} to ${b.checkOut}, ${b.nights} night${b.nights > 1 ? 's' : ''})</span>
                </div>
                <div style="display:flex; align-items:center; gap: 10px;">
                  <span style="font-weight: 700; color: var(--text-primary);">฿${th(b.total)}</span>
                  <span class="status-pill ${b.status === 'checkin' ? 'occupied' : (b.status === 'wait' ? 'cleaning' : 'available')}">${b.status}</span>
                  ${canExtend ? `
                    <button class="btn btn-outline btn-sm my-extend-btn" data-id="${b.id}" data-room="${rNum}" data-booker="${b.booker}" data-checkout="${b.checkOut}" data-price="${price}">
                      ${getSvgIcon("zap", 13)} Extend Stay
                    </button>
                  ` : ''}
                  <button class="btn btn-outline btn-sm my-folio-btn" data-id="${b.id}">
                    ${getSvgIcon("receipt", 13)} Folio Receipt
                  </button>
                </div>
              </div>
            `;
          }).join("")}
        </div>
      </div>
    `;

    container.querySelectorAll(".my-extend-btn").forEach(btn => {
      btn.addEventListener("click", () => {
        this.openExtendStayModal(btn.dataset.id, btn.dataset.room, btn.dataset.booker, btn.dataset.checkout, parseFloat(btn.dataset.price) || 0);
      });
    });

    container.querySelectorAll(".my-folio-btn").forEach(btn => {
      btn.addEventListener("click", () => {
        this.openFolioModal(btn.dataset.id);
      });
    });
  }

  // ===========================================================================
  // 6. Portal 2: Staff Operations Hub
  // ===========================================================================
  renderStaffPortal() {
    const total = this.rooms.length;
    const occupied = this.rooms.filter(r => r.booked && r.booking && r.booking.status === 'checkin').length;
    const wait = this.rooms.filter(r => r.booked && (!r.booking || r.booking.status === 'wait')).length;
    const available = total - (occupied + wait);
    const vip = this.rooms.filter(r => r.tier === 'vip').length;

    // Update live clock
    const clockEl = $("staffLiveClock");
    if (clockEl) {
      const now = new Date();
      const datePart = now.toLocaleDateString("en-US", { weekday: "long", year: "numeric", month: "long", day: "numeric" });
      const timePart = now.toLocaleTimeString("en-US", { hour: "2-digit", minute: "2-digit" });
      clockEl.textContent = `${datePart}  •  ${timePart}`;
    }

    $("staffCountReady") && ($("staffCountReady").textContent = available);
    $("staffCountOccupied") && ($("staffCountOccupied").textContent = occupied);
    $("staffCountWait") && ($("staffCountWait").textContent = wait);
    $("staffCountVip") && ($("staffCountVip").textContent = vip);

    // Render PMS Suite Master Roster
    this.renderStaffRoomRoster();

    const tbody = document.querySelector("#staffCheckoutTable tbody");
    if (!tbody) return;

    let activeRooms = this.rooms.filter(r => r.booked);
    if (activeRooms.length === 0) {
      tbody.innerHTML = `<tr><td colspan="8" style="text-align:center; color:var(--text-muted); padding:30px;">No active stays currently occupying hotel inventory.</td></tr>`;
      return;
    }

    const sort = this.tableSort.staffCheckout;
    if (sort && sort.col) {
      const isAsc = sort.dir === "asc";
      activeRooms = [...activeRooms].sort((a, b) => {
        const bA = a.booking || {};
        const bB = b.booking || {};
        let vA, vB;
        if (sort.col === "room") { vA = a.number; vB = b.number; }
        else if (sort.col === "guest") { vA = (bA.booker || "").toLowerCase(); vB = (bB.booker || "").toLowerCase(); }
        else if (sort.col === "dates") { vA = bA.checkIn || ""; vB = bB.checkIn || ""; }
        else if (sort.col === "nights") { vA = bA.nights || 0; vB = bB.nights || 0; }
        else if (sort.col === "total") { vA = bA.total || a.price || 0; vB = bB.total || b.price || 0; }
        else if (sort.col === "status") { vA = bA.status || ""; vB = bB.status || ""; }
        if (vA < vB) return isAsc ? -1 : 1;
        if (vA > vB) return isAsc ? 1 : -1;
        return 0;
      });
    }

    tbody.innerHTML = activeRooms.map(r => {
      const b = r.booking || {};
      const isCheckin = b.status === "checkin";
      const canExtend = isCheckin || b.status === "wait";

      return `
        <tr>
          <td data-label="Suite"><strong style="font-size:14px;">#${r.number}</strong> <span style="font-size:11px;color:var(--text-muted);">(${r.tier})</span></td>
          <td data-label="Guest Name"><strong>${b.booker || 'Guest'}</strong></td>
          <td data-label="Contact"><span style="font-size:12px;">${b.phone || '-'}</span></td>
          <td data-label="Check-In – Out">${b.checkIn || '-'} → ${b.checkOut || '-'}</td>
          <td data-label="Nights">${b.nights || 1} nights</td>
          <td data-label="Total Bill"><strong style="color:var(--accent);">฿${th(b.total || r.price)}</strong></td>
          <td data-label="Status"><span class="status-pill ${isCheckin ? 'occupied' : 'cleaning'}">${b.status || 'wait'}</span></td>
          <td data-label="Operations">
            <div style="display:flex; gap:6px; flex-wrap:wrap;">
              ${!isCheckin ? `
                <button class="btn btn-luxury btn-sm staff-act-btn" data-act="checkin" data-id="${b.id}">Check In</button>
              ` : `
                <button class="btn btn-outline btn-sm staff-act-btn" data-act="checkout" data-id="${b.id}" style="color:var(--status-maintenance);">Check Out</button>
              `}
              ${canExtend ? `
                <button class="btn btn-outline btn-sm staff-extend-btn" data-id="${b.id}" data-room="${r.number}" data-booker="${b.booker}" data-checkout="${b.checkOut}" data-price="${r.price}">
                  Extend
                </button>
              ` : ''}
              <button class="btn btn-outline btn-sm staff-folio-btn" data-id="${b.id}">${getSvgIcon("receipt", 13)} Folio</button>
              <button class="btn btn-outline btn-sm staff-inspect-suite-btn" data-room="${r.number}">${getSvgIcon("eye", 13)} Inspect</button>
              <button class="btn btn-outline btn-sm staff-act-btn" data-act="cancel" data-id="${b.id}">Cancel</button>
            </div>
          </td>
        </tr>
      `;
    }).join("");

    tbody.querySelectorAll(".staff-inspect-suite-btn").forEach(btn => {
      btn.addEventListener("click", () => this.openRoomInspector(btn.dataset.room));
    });

    tbody.querySelectorAll(".staff-act-btn").forEach(btn => {
      btn.addEventListener("click", async () => {
        const id = btn.dataset.id;
        const act = btn.dataset.act;
        let targetStatus = act === "checkin" ? "checkin" : (act === "checkout" ? "checkout" : "cancelled");
        const res = await this.updateBookingStatus(id, targetStatus);
        if (res.ok) {
          this.warnIfNotSaved(res);
          this.toast(`Booking ${id} status updated to ${targetStatus}`);
          await this.refreshData();
          this.renderStaffPortal();
        } else {
          this.toast(res.error || "Update failed", "error");
        }
      });
    });

    tbody.querySelectorAll(".staff-extend-btn").forEach(btn => {
      btn.addEventListener("click", () => {
        this.openExtendStayModal(btn.dataset.id, btn.dataset.room, btn.dataset.booker, btn.dataset.checkout, parseFloat(btn.dataset.price) || 0);
      });
    });

    tbody.querySelectorAll(".staff-folio-btn").forEach(btn => {
      btn.addEventListener("click", () => {
        this.openFolioModal(btn.dataset.id);
      });
    });
  }

  renderStaffRoomRoster() {
    const grid = $("staffRoomRosterGrid");
    if (!grid) return;

    const query = ($("staffRosterSearch")?.value || "").trim().toLowerCase();
    const filter = $("staffRosterFilter")?.value || "all";

    let list = this.rooms.filter(r => {
      const isBooked = r.booked;
      const b = r.booking || {};

      if (filter === "available" && isBooked) return false;
      if (filter === "occupied" && !isBooked) return false;
      if (filter === "maintenance" && r.status !== "maintenance") return false;

      if (!query) return true;
      return String(r.number).includes(query) ||
             String(r.floor).includes(query) ||
             (r.tier || "").toLowerCase().includes(query) ||
             (b.booker || "").toLowerCase().includes(query) ||
             (b.phone || "").toLowerCase().includes(query);
    });

    if (list.length === 0) {
      grid.innerHTML = `<div style="grid-column: 1 / -1; text-align: center; color: var(--text-muted); padding: 30px; background: var(--bg-surface); border: 1px solid var(--border-subtle); border-radius: var(--radius-md);">No suites found matching criteria.</div>`;
      return;
    }

    grid.innerHTML = list.map(r => {
      const isBooked = r.booked;
      const b = r.booking || {};
      const isVip = r.tier === "vip";
      const isMaint = (r.status === "maintenance");
      const statusClass = isBooked ? (b.status === "wait" ? "cleaning" : "occupied") : (isMaint ? "maintenance" : "available");
      const statusText = isBooked ? (b.status === "wait" ? "Reserved (Wait)" : "Occupied") : (isMaint ? "Maintenance" : "Available");

      return `
        <div class="staff-pms-card is-${statusClass}" data-room="${r.number}">
          <div class="staff-pms-header">
            <div class="staff-pms-room-num">
              Suite ${r.number}
              ${isVip ? `<span style="font-size: 11px; color: var(--gold-accent);" title="VIP Penthouse">${getSvgIcon('crown', 12)}</span>` : ''}
            </div>
            <span class="status-pill ${statusClass}">${statusText}</span>
          </div>

          <div class="staff-pms-occupant-box">
            ${isBooked ? `
              <div class="staff-pms-occupant-name">
                ${getSvgIcon('user', 12)}
                <span>${b.booker || 'Current Occupant'}</span>
              </div>
              <div class="staff-pms-dates">
                ${getSvgIcon('clock', 11)} ${b.checkIn || '-'} → ${b.checkOut || '-'} (${b.nights || 1}n)
              </div>
            ` : `
              <div style="color: var(--text-muted); font-size: 11.5px; display: flex; align-items: center; gap: 4px;">
                ${getSvgIcon('check', 12)} ${isMaint ? 'Out of Service' : 'Vacant & Ready'}
              </div>
              <div class="staff-pms-dates" style="color: var(--text-muted);">
                ฿${th(r.price)} / night • Floor ${r.floor}
              </div>
            `}
          </div>

          <div class="staff-pms-footer">
            <span style="font-size: 11px; color: var(--text-muted);">
              ${r.bed === 'twin' ? 'Twin Beds' : 'Double / King'}
            </span>
            <button class="btn btn-outline btn-xs staff-inspect-btn" data-room="${r.number}" style="padding: 3px 8px; font-size: 11px; gap: 4px;">
              ${getSvgIcon('eye', 12)} Inspect
            </button>
          </div>
        </div>
      `;
    }).join("");

    grid.querySelectorAll(".staff-pms-card").forEach(card => {
      card.addEventListener("click", () => {
        this.openRoomInspector(card.dataset.room);
      });
    });
  }

  // ===========================================================================
  // 7. Portal 3: Admin Executive Control Panel
  // ===========================================================================
  renderAdminPortal() {
    const total = this.rooms.length;
    const occupiedStays = this.rooms.filter(r => r.booked).length;
    const occRate = total > 0 ? ((occupiedStays / total) * 100).toFixed(1) : 0;
    
    let totalRevenue = 0;
    this.bookings.forEach(b => {
      if (b.status === "checkin" || b.status === "wait" || b.status === "checkout") {
        totalRevenue += (b.total || 0);
      }
    });

    let avgPrice = 0;
    if (total > 0) {
      avgPrice = Math.round(this.rooms.reduce((sum, r) => sum + r.price, 0) / total);
    }

    $("adminKpiOccupancy") && ($("adminKpiOccupancy").textContent = `${occRate}%`);
    $("adminKpiOccupancySub") && ($("adminKpiOccupancySub").textContent = `${occupiedStays} of ${total} rooms occupied`);
    $("adminKpiRevenue") && ($("adminKpiRevenue").textContent = `฿${th(totalRevenue)}`);
    $("adminKpiAdr") && ($("adminKpiAdr").textContent = `฿${th(avgPrice)}`);
    $("adminKpiTotalRooms") && ($("adminKpiTotalRooms").textContent = total);
    $("adminKpiAvailSub") && ($("adminKpiAvailSub").textContent = `${total - occupiedStays} Available`);

    // Inventory Table
    const roomTbody = document.querySelector("#adminRoomsTable tbody");
    if (roomTbody) {
      const q = (this.adminRoomSearch || "").toLowerCase();
      let roomsList = this.rooms.filter(r => {
        if (!q) return true;
        const b = r.booking || {};
        return String(r.number).toLowerCase().includes(q) ||
               String(r.floor).toLowerCase().includes(q) ||
               (r.tier || "").toLowerCase().includes(q) ||
               (r.bed || "").toLowerCase().includes(q) ||
               (r.note || "").toLowerCase().includes(q) ||
               (b.booker || "").toLowerCase().includes(q);
      });

      const sort = this.tableSort.adminRooms;
      if (sort && sort.col) {
        const isAsc = sort.dir === "asc";
        roomsList = [...roomsList].sort((a, b) => {
          let vA, vB;
          if (sort.col === "room") { vA = a.number; vB = b.number; }
          else if (sort.col === "floor") { vA = a.floor; vB = b.floor; }
          else if (sort.col === "price") { vA = a.price; vB = b.price; }
          else if (sort.col === "status") { vA = a.booked ? 1 : 0; vB = b.booked ? 1 : 0; }
          if (vA < vB) return isAsc ? -1 : 1;
          if (vA > vB) return isAsc ? 1 : -1;
          return 0;
        });
      }

      roomTbody.innerHTML = roomsList.map(r => {
        const isBooked = r.booked;
        const b = r.booking || {};
        return `
          <tr>
            <td data-label="Room #"><strong>#${r.number}</strong></td>
            <td data-label="Floor">Floor ${r.floor}</td>
            <td data-label="Suite Category">${r.tier === 'vip' ? `${getSvgIcon('crown', 12)} VIP Luxury` : 'Standard Suite'}</td>
            <td data-label="Bed Type">${r.bed === 'twin' ? 'Twin Beds' : 'Double / King'}</td>
            <td data-label="Nightly Rate"><strong>฿${th(r.price)}</strong></td>
            <td data-label="Status"><span class="status-pill ${isBooked ? 'occupied' : 'available'}">${isBooked ? (b.status || 'Booked') : 'Available'}</span></td>
            <td data-label="Current Guest">${isBooked && b.booker ? `${b.booker} (${b.id})` : '-'}</td>
            <td data-label="Notes"><span style="font-size:12px;color:var(--text-muted);">${r.note || '-'}</span></td>
            <td data-label="Actions">
              <div style="display:flex; gap:6px;">
                <button class="btn btn-outline btn-sm admin-inspect-room-btn" data-room="${r.number}">
                  ${getSvgIcon("eye", 13)}
                  <span>Inspect</span>
                </button>
                <button class="btn btn-outline btn-sm admin-edit-room-btn" data-room="${r.number}" data-price="${r.price}" data-note="${r.note || ''}">
                  ${getSvgIcon("edit", 13)}
                  <span>Edit</span>
                </button>
              </div>
            </td>
          </tr>
        `;
      }).join("");

      roomTbody.querySelectorAll(".admin-inspect-room-btn").forEach(btn => {
        btn.addEventListener("click", () => {
          this.openRoomInspector(btn.dataset.room);
        });
      });

      roomTbody.querySelectorAll(".admin-edit-room-btn").forEach(btn => {
        btn.addEventListener("click", () => {
          this.openRoomEditModal(btn.dataset.room, btn.dataset.price, btn.dataset.note);
        });
      });
    }

    // Ledger Table
    const txnTbody = document.querySelector("#adminTxnTable tbody");
    if (txnTbody) {
      if (this.bookings.length === 0) {
        txnTbody.innerHTML = `<tr><td colspan="9" style="text-align:center; color:var(--text-muted); padding:30px;">No historical bookings found in database.</td></tr>`;
      } else {
        let bList = this.bookings;
        const sort = this.tableSort.adminTxn;
        if (sort && sort.col) {
          const isAsc = sort.dir === "asc";
          bList = [...bList].sort((a, b) => {
            let vA, vB;
            if (sort.col === "id") { vA = a.id; vB = b.id; }
            else if (sort.col === "room") { vA = parseInt(a.room || a.roomId) || 0; vB = parseInt(b.room || b.roomId) || 0; }
            else if (sort.col === "guest") { vA = (a.booker || "").toLowerCase(); vB = (b.booker || "").toLowerCase(); }
            else if (sort.col === "dates") { vA = a.checkIn || ""; vB = b.checkIn || ""; }
            else if (sort.col === "nights") { vA = a.nights || 0; vB = b.nights || 0; }
            else if (sort.col === "total") { vA = a.total || 0; vB = b.total || 0; }
            else if (sort.col === "status") { vA = a.status || ""; vB = b.status || ""; }
            else if (sort.col === "created") { vA = a.createdAt || ""; vB = b.createdAt || ""; }
            if (vA < vB) return isAsc ? -1 : 1;
            if (vA > vB) return isAsc ? 1 : -1;
            return 0;
          });
        }

        txnTbody.innerHTML = bList.map(b => `
          <tr>
            <td data-label="Booking ID">
              <div style="display:inline-flex; align-items:center; gap:6px;">
                <strong>${b.id}</strong>
                <button type="button" class="btn btn-outline btn-xs admin-txn-folio-btn" data-id="${b.id}" title="View Folio / Receipt" style="padding:2px 6px; font-size:11px;">${getSvgIcon("receipt", 12)}</button>
              </div>
            </td>
            <td data-label="Room">#${b.room || b.roomId}</td>
            <td data-label="Booker"><strong>${b.booker}</strong></td>
            <td data-label="Contact"><span style="font-size:12px;">${b.phone || '-'}</span></td>
            <td data-label="Dates">${b.checkIn} → ${b.checkOut}</td>
            <td data-label="Nights">${b.nights}</td>
            <td data-label="Total (THB)"><strong style="color:var(--text-primary);">฿${th(b.total)}</strong></td>
            <td data-label="Status"><span class="status-pill ${b.status === 'checkin' ? 'occupied' : (b.status === 'wait' ? 'cleaning' : 'available')}">${b.status}</span></td>
            <td data-label="Created At"><span style="font-size:11.5px;color:var(--text-muted);">${b.createdAt || '-'}</span></td>
          </tr>
        `).join("");

        txnTbody.querySelectorAll(".admin-txn-folio-btn").forEach(btn => {
          btn.addEventListener("click", () => {
            this.openFolioModal(btn.dataset.id);
          });
        });
      }
    }

    // System Change Log & Audit Trail Table
    this.renderAdminAuditTable();

    // User & Staff Account Management Table
    this.renderAdminUsersTable();
  }

  renderAdminAuditTable() {
    const auditTbody = document.querySelector("#adminAuditTable tbody");
    if (!auditTbody) return;

    const q = (this.auditSearch || "").toLowerCase();
    let filteredAudits = (this.auditLogs || []).filter(a => {
      if (!q) return true;
      return (a.id || "").toLowerCase().includes(q) ||
             (a.actorUser || "").toLowerCase().includes(q) ||
             (a.actorRole || "").toLowerCase().includes(q) ||
             (a.actionType || "").toLowerCase().includes(q) ||
             (a.targetEntity || "").toLowerCase().includes(q) ||
             (a.diff || "").toLowerCase().includes(q);
    });

    if (filteredAudits.length === 0) {
      auditTbody.innerHTML = `<tr><td colspan="7" style="text-align:center; color:var(--text-muted); padding:30px;">No audit trail events recorded.</td></tr>`;
      return;
    }

    const sort = this.tableSort.adminAudit;
    if (sort && sort.col) {
      const isAsc = sort.dir === "asc";
      filteredAudits = [...filteredAudits].sort((a, b) => {
        let vA, vB;
        if (sort.col === "id") { vA = a.id; vB = b.id; }
        else if (sort.col === "time") { vA = a.timestamp || ""; vB = b.timestamp || ""; }
        else if (sort.col === "actor") { vA = (a.actorUser || "").toLowerCase(); vB = (b.actorUser || "").toLowerCase(); }
        else if (sort.col === "role") { vA = (a.actorRole || "").toLowerCase(); vB = (b.actorRole || "").toLowerCase(); }
        else if (sort.col === "action") { vA = (a.actionType || "").toLowerCase(); vB = (b.actionType || "").toLowerCase(); }
        if (vA < vB) return isAsc ? -1 : 1;
        if (vA > vB) return isAsc ? 1 : -1;
        return 0;
      });
    }

    auditTbody.innerHTML = filteredAudits.map(a => {
      let badgeCls = "status";
      const act = (a.actionType || "").toUpperCase();
      if (act.includes("CREATE")) badgeCls = "create";
      else if (act.includes("EXTEND")) badgeCls = "extend";
      else if (act.includes("PRICE")) badgeCls = "price";
      else if (act.includes("RELOAD")) badgeCls = "reload";

      return `
        <tr>
          <td data-label="Log ID"><code style="font-size:12px; font-weight:700; color:var(--text-primary);">${a.id}</code></td>
          <td data-label="Timestamp"><span style="font-size:11.5px; color:var(--text-muted);">${a.timestamp}</span></td>
          <td data-label="Actor"><strong>${a.actorUser}</strong></td>
          <td data-label="Role"><span class="user-role-tag">${(a.actorRole || "user").toUpperCase()}</span></td>
          <td data-label="Action Type"><span class="badge-action ${badgeCls}">${a.actionType}</span></td>
          <td data-label="Target Entity"><strong>${a.targetEntity}</strong></td>
          <td data-label="Details"><span style="font-size:12.5px; color:var(--text-secondary);">${a.diff}</span></td>
        </tr>
      `;
    }).join("");
  }

  exportAuditCsv() {
    if (!this.auditLogs || this.auditLogs.length === 0) {
      this.toast("No audit logs to export", "error");
      return;
    }
    const headers = ["Log ID", "Timestamp", "Actor", "Role", "Action Type", "Target Entity", "Details"];
    const rows = this.auditLogs.map(a => [
      `"${a.id}"`,
      `"${a.timestamp}"`,
      `"${a.actorUser}"`,
      `"${a.actorRole}"`,
      `"${a.actionType}"`,
      `"${a.targetEntity}"`,
      `"${(a.diff || "").replace(/"/g, '""')}"`
    ]);
    const csvContent = "data:text/csv;charset=utf-8,\uFEFF" + [headers.join(","), ...rows.map(e => e.join(","))].join("\n");
    const encodedUri = encodeURI(csvContent);
    const link = document.createElement("a");
    link.setAttribute("href", encodedUri);
    link.setAttribute("download", `hotel_audit_log_${new Date().toISOString().slice(0, 10)}.csv`);
    document.body.appendChild(link);
    link.click();
    document.body.removeChild(link);
    this.toast("Audit log exported as CSV");
  }

  // ---- User & Staff Account Management (hotel.xlsx sheet users) ----
  renderAdminUsersTable() {
    const tbody = $("adminUsersTableBody");
    if (!tbody) return;

    const q = (this.adminUserSearch || "").toLowerCase();
    let filtered = (this.adminUsers || []).filter(u => {
      if (!q) return true;
      return (u.username || "").toLowerCase().includes(q) ||
             (u.fullName || "").toLowerCase().includes(q) ||
             (u.role || "").toLowerCase().includes(q) ||
             (u.phone || "").toLowerCase().includes(q) ||
             (u.email || "").toLowerCase().includes(q);
    });

    if (filtered.length === 0) {
      tbody.innerHTML = `<tr><td colspan="7" style="text-align:center; color:var(--text-muted); padding:30px;">No user accounts found matching query.</td></tr>`;
      return;
    }

    const sort = this.tableSort.adminUsers;
    if (sort && sort.col) {
      const isAsc = sort.dir === "asc";
      filtered = [...filtered].sort((a, b) => {
        let vA, vB;
        if (sort.col === "username") { vA = (a.username || "").toLowerCase(); vB = (b.username || "").toLowerCase(); }
        else if (sort.col === "role") { vA = (a.role || "").toLowerCase(); vB = (b.role || "").toLowerCase(); }
        else if (sort.col === "name") { vA = (a.fullName || "").toLowerCase(); vB = (b.fullName || "").toLowerCase(); }
        if (vA < vB) return isAsc ? -1 : 1;
        if (vA > vB) return isAsc ? 1 : -1;
        return 0;
      });
    }

    const curUser = this.currentUser ? this.currentUser.username : "";

    tbody.innerHTML = filtered.map(u => {
      const role = (u.role || "guest").toLowerCase();
      const isSelf = (u.username === curUser);
      return `
        <tr>
          <td data-label="Username"><strong>${u.username}</strong> ${isSelf ? '<span style="font-size:10.5px; color:var(--accent); font-weight:600;">(You)</span>' : ''}</td>
          <td data-label="Role"><span class="badge-role ${role}" style="display:inline-flex; align-items:center; gap:4px;">${getSvgIcon(role === 'admin' ? 'crown' : (role === 'staff' ? 'briefcase' : 'user'), 12)} ${role.toUpperCase()}</span></td>
          <td data-label="Full Name"><strong>${u.fullName || '-'}</strong></td>
          <td data-label="Phone"><span style="font-size:12.5px;">${u.phone || '-'}</span></td>
          <td data-label="Email"><span style="font-size:12.5px; color:var(--text-secondary);">${u.email || '-'}</span></td>
          <td data-label="Security"><span style="font-size:11px; font-weight:600; color:#10b981; background:rgba(16,185,129,0.12); padding:2px 6px; border-radius:4px; display:inline-flex; align-items:center; gap:4px;">${getSvgIcon("lock", 11)} Salted SHA-256</span></td>
          <td data-label="Actions">
            <div style="display:flex; gap:6px;">
              <button class="btn btn-outline btn-sm admin-edit-user-btn" data-username="${u.username}">
                ${getSvgIcon("edit", 12)} Edit
              </button>
              ${!isSelf ? `
                <button class="btn btn-outline btn-sm admin-del-user-btn" data-username="${u.username}" style="color:var(--status-maintenance); border-color:rgba(239,68,68,0.3);">
                  ${getSvgIcon("close", 12)}
                </button>
              ` : ''}
            </div>
          </td>
        </tr>
      `;
    }).join("");

    tbody.querySelectorAll(".admin-edit-user-btn").forEach(b => {
      b.addEventListener("click", () => this.openEditUserModal(b.dataset.username));
    });

    tbody.querySelectorAll(".admin-del-user-btn").forEach(b => {
      b.addEventListener("click", () => this.deleteUserAccount(b.dataset.username));
    });
  }

  openAddUserModal() {
    $("adminUserIsEdit").value = "false";
    $("adminUserModalTitle").textContent = "Add New System User";
    $("adminUsernameInput").value = "";
    $("adminUsernameInput").disabled = false;
    $("adminFullNameInput").value = "";
    $("adminRoleSelect").value = "guest";
    $("adminPasswordInput").value = "";
    $("adminPasswordInput").required = true;
    $("adminPasswordLabel").textContent = "Password / รหัสผ่าน (Salted SHA-256)";
    $("adminPasswordHint").textContent = "Minimum 4 characters. Encrypted via Salted SHA-256.";
    $("adminPhoneInput").value = "";
    $("adminEmailInput").value = "";
    $("adminUserModal")?.classList.add("open");
  }

  openEditUserModal(username) {
    const u = this.adminUsers.find(x => x.username === username);
    if (!u) return;

    $("adminUserIsEdit").value = "true";
    $("adminUserModalTitle").textContent = `Edit User: ${u.username}`;
    $("adminUsernameInput").value = u.username;
    $("adminUsernameInput").disabled = true;
    $("adminFullNameInput").value = u.fullName || "";
    $("adminRoleSelect").value = u.role || "guest";
    $("adminPasswordInput").value = "";
    $("adminPasswordInput").required = false;
    $("adminPasswordLabel").textContent = "Reset Password / รหัสผ่านใหม่ (Optional)";
    $("adminPasswordHint").textContent = "Leave blank to keep current cryptographic password.";
    $("adminPhoneInput").value = u.phone || "";
    $("adminEmailInput").value = u.email || "";
    $("adminUserModal")?.classList.add("open");
  }

  closeUserModal() {
    $("adminUserModal")?.classList.remove("open");
  }

  async saveUserForm() {
    const isEdit = $("adminUserIsEdit").value === "true";
    const username = $("adminUsernameInput").value.trim();
    const fullName = $("adminFullNameInput").value.trim();
    const role = $("adminRoleSelect").value;
    const password = $("adminPasswordInput").value;
    const phone = $("adminPhoneInput").value.trim();
    const email = $("adminEmailInput").value.trim();

    if (!username || !fullName) {
      this.toast("Please fill required fields (Username, Name)", "error");
      return;
    }

    if (!isEdit && (!password || password.length < 4)) {
      this.toast("Password must be at least 4 characters", "error");
      return;
    }

    let res;
    if (isEdit) {
      res = await this.updateAdminUser({ username, fullName, role, phone, email, password });
    } else {
      res = await this.createAdminUser({ username, fullName, role, phone, email, password });
    }

    if (res.ok) {
      this.closeUserModal();
      this.toast(`User ${username} saved successfully with Salted SHA-256`);
      await this.refreshData();
      this.renderAdminPortal();
    } else {
      this.toast(res.error || "Operation failed", "error");
    }
  }

  async deleteUserAccount(username) {
    if (!confirm(`Are you sure you want to delete user '${username}'?`)) return;

    const res = await this.deleteAdminUser(username);
    if (res.ok) {
      this.toast(`User ${username} deleted`);
      await this.refreshData();
      this.renderAdminPortal();
    } else {
      this.toast(res.error || "Delete failed", "error");
    }
  }

  // ---- Executive Terminal Console (Ctrl+K) ----
  openTerminal() {
    if (!this.isAdminLevel()) {
      this.toast("Terminal Console requires Administrator privileges", "error");
      return;
    }
    $("adminConsoleModal")?.classList.add("open");
    setTimeout(() => $("terminalInput")?.focus(), 50);
  }

  closeTerminal() {
    $("adminConsoleModal")?.classList.remove("open");
  }

  async runTerminalCommand(cmd) {
    const trimmed = cmd.trim();
    if (!trimmed) return;

    const outputEl = $("terminalOutput");
    const screenEl = $("terminalScreen");

    if (trimmed === "clear") {
      if (outputEl) outputEl.textContent = "";
      return;
    }

    if (outputEl) {
      outputEl.textContent += `\nHGH-Admin> ${trimmed}\n`;
    }

    // Save history
    this.cmdHistory.push(trimmed);
    this.cmdHistoryIdx = this.cmdHistory.length;

    try {
      const res = await this.runConsoleCommand(trimmed);
      if (outputEl) {
        if (res.ok && res.output) {
          outputEl.textContent += res.output;
        } else {
          outputEl.textContent += `[ERROR] ${res.error || 'Command failed'}\n`;
        }
        if (screenEl) screenEl.scrollTop = screenEl.scrollHeight;
      }
      // Refresh admin data in case database or price was modified
      if (trimmed.startsWith("room:price") || trimmed === "excel:reload" || trimmed === "backup:now") {
        await this.refreshData();
        this.renderAdminPortal();
      }
    } catch (e) {
      if (outputEl) outputEl.textContent += `[NETWORK ERROR] ${e.message}\n`;
    }
  }

  async triggerBackup() {
    const res = await this.backupDatabase();
    if (res.ok) {
      this.toast(`Database backup created: ${res.backupPath || 'data/backups/'}`);
      await this.refreshData();
      this.renderAdminPortal();
    } else {
      this.toast(res.error || "Backup snapshot failed", "error");
    }
  }

  // Extend Stay Modal Helpers
  openExtendStayModal(bookingId, roomNumber, booker, currentCheckOut, price) {
    if ($("extendBookingId")) $("extendBookingId").value = bookingId;
    if ($("extendRoomPrice")) $("extendRoomPrice").value = price;
    if ($("extendRoomNum")) $("extendRoomNum").textContent = `#${roomNumber}`;
    if ($("extendBookerName")) $("extendBookerName").textContent = booker || "Guest";
    if ($("extendCurrentCheckOut")) $("extendCurrentCheckOut").textContent = currentCheckOut;
    if ($("extendRatePreview")) $("extendRatePreview").textContent = `฿${th(price)} / night`;
    if ($("extendNightsInput")) $("extendNightsInput").value = 1;
    if ($("extendNoteInput")) $("extendNoteInput").value = "";

    this.updateExtendPreview(currentCheckOut, price, 1);
    $("extendStayModal")?.classList.add("active");
  }

  updateExtendPreview(currentCheckOut, price, additionalNights) {
    const nights = Math.max(1, parseInt(additionalNights) || 1);
    let newOut = currentCheckOut;
    if (currentCheckOut && currentCheckOut.length >= 10) {
      const parts = currentCheckOut.split("-");
      if (parts.length === 3) {
        const d = new Date(parseInt(parts[0]), parseInt(parts[1]) - 1, parseInt(parts[2]));
        d.setDate(d.getDate() + nights);
        const yyyy = d.getFullYear();
        const mm = String(d.getMonth() + 1).padStart(2, "0");
        const dd = String(d.getDate()).padStart(2, "0");
        newOut = `${yyyy}-${mm}-${dd}`;
      }
    }
    if ($("extendNewCheckOutPreview")) $("extendNewCheckOutPreview").textContent = newOut;
    if ($("extendCostPreview")) $("extendCostPreview").textContent = `+ ฿${th(price * nights)}`;
  }

  closeExtendStayModal() {
    $("extendStayModal")?.classList.remove("active");
  }

  // ===========================================================================
  // 8. Portal 4: Architectural Floor Matrix
  // ===========================================================================
  renderMatrixPortal() {
    const container = $("matrixFloorsContainer");
    if (!container) return;

    const floors = [3, 2, 1];
    container.innerHTML = floors.map(floorNum => {
      const floorRooms = this.rooms.filter(r => String(r.floor) === String(floorNum));
      return `
        <div style="background: var(--bg-surface); border: 1px solid var(--border-subtle); border-radius: var(--radius-lg); padding: 20px; margin-bottom: 20px; box-shadow: var(--shadow-sm);">
          <div style="display:flex; justify-content:space-between; align-items:center; margin-bottom: 16px; border-bottom: 1px solid var(--border-subtle); padding-bottom: 10px;">
            <h3 class="font-serif" style="font-size: 18px; display: flex; align-items: center; gap: 6px;">Level ${floorNum} ${floorNum === 3 ? `${getSvgIcon('crown', 15)} VIP Penthouse Floor` : 'Standard Guest Floor'}</h3>
            <span style="font-size: 12.5px; color: var(--text-secondary);">${floorRooms.length} Total Suites</span>
          </div>

          <div style="display: grid; grid-template-columns: repeat(auto-fill, minmax(200px, 1fr)); gap: 14px;">
            ${floorRooms.map(r => {
              const isBooked = r.booked;
              const statusClass = isBooked ? "occupied" : "available";
              const isVip = r.tier === "vip";
              return `
                <div class="matrix-room-card" data-room="${r.number}" style="background: var(--bg-surface-subtle); border: 1px solid var(--border-medium); border-radius: var(--radius-md); padding: 14px; display:flex; flex-direction:column; gap:6px; cursor: ${this.isStaffLevel() ? 'pointer' : 'default'};">
                  <div style="display:flex; justify-content:space-between; align-items:center;">
                    <strong style="font-size: 17px;">#${r.number}</strong>
                    <span class="status-pill ${statusClass}">${isBooked ? 'Booked' : 'Free'}</span>
                  </div>
                  <div style="font-size: 12px; color: var(--text-secondary);">${isVip ? 'VIP Luxury' : 'Standard'} • ${r.bed === 'twin' ? 'Twin' : 'Double'}</div>
                  <div style="margin-top:4px; font-weight:700; color:var(--accent); font-size:14px; display:flex; justify-content:space-between; align-items:center;">
                    <span>฿${th(r.price)} / night</span>
                    ${this.isStaffLevel() ? `<span style="font-size:11px; color:var(--text-muted); display:inline-flex; align-items:center; gap:3px;">${getSvgIcon('eye', 12)} Inspect</span>` : ''}
                  </div>
                </div>
              `;
            }).join("")}
          </div>
        </div>
      `;
    }).join("");

    if (this.isStaffLevel()) {
      container.querySelectorAll(".matrix-room-card").forEach(card => {
        card.addEventListener("click", () => this.openRoomInspector(card.dataset.room));
      });
    }
  }

  // ===========================================================================
  // 9. Modals, Drawers, and Toasts
  // ===========================================================================
  openDrawer(roomNumber) {
    const r = this.rooms.find(x => String(x.number) === String(roomNumber));
    if (!r || r.booked) return;
    this.selectedRoomForDrawer = r;

    $("drawerHeading").textContent = `Suite ${r.number}`;
    $("drawerSubheading").textContent = `${r.tier === 'vip' ? 'VIP Penthouse Suite' : 'Standard Guest Suite'} • Floor ${r.floor}`;

    const photo = getRoomPhoto(r.tier, r.bed, r.number);
    const today = this.todayStr || new Date().toISOString().slice(0, 10);
    const nights = this.filterNights || 1;
    const total = r.price * nights;

    const defaultBooker = this.currentUser ? (this.currentUser.fullName || this.currentUser.username) : "";
    const defaultPhone = this.currentUser ? (this.currentUser.phone || "") : "";
    const defaultEmail = this.currentUser ? (this.currentUser.email || "") : "";

    $("drawerBody").innerHTML = `
      <div style="height: 180px; border-radius: var(--radius-md); overflow: hidden; margin-bottom: 16px;">
        <img src="${photo}" style="width: 100%; height: 100%; object-fit: cover;">
      </div>

      <div style="display: flex; justify-content: space-between; align-items: baseline; margin-bottom: 16px; border-bottom: 1px solid var(--border-subtle); padding-bottom: 12px;">
        <div>
          <span style="font-size: 11px; text-transform: uppercase; color: var(--accent); font-weight: 700;">Nightly Rate</span>
          <div style="font-size: 24px; font-weight: 800; color: var(--text-primary);">฿${th(r.price)}</div>
        </div>
        <div style="text-align: right;">
          <span style="font-size: 11px; text-transform: uppercase; color: var(--text-muted); font-weight: 700;">Configuration</span>
          <div style="font-size: 13.5px; font-weight: 600;">${r.bed === 'twin' ? '2 Single Twin Beds' : '1 King Double Bed'}</div>
        </div>
      </div>

      <form id="drawerBookingForm" style="display: flex; flex-direction: column; gap: 12px;">
        <div class="field-group">
          <label class="field-label" for="drawerCheckIn">Check-In Date</label>
          <input type="date" id="drawerCheckIn" class="field-input" value="${today}" required>
        </div>

        <div class="field-group">
          <label class="field-label" for="drawerNights">Duration of Stay</label>
          <div style="display:flex; align-items:center; gap:8px;">
            <input type="number" id="drawerNights" class="field-input" min="1" max="30" value="${nights}" style="flex:1;" required>
            <span style="font-size:13px;color:var(--text-secondary);">nights</span>
          </div>
        </div>

        <div class="field-group">
          <label class="field-label" for="drawerBooker">Full Name</label>
          <input type="text" id="drawerBooker" class="field-input" placeholder="Your name" value="${defaultBooker}" required>
        </div>

        <div style="display:grid; grid-template-columns: 1fr 1fr; gap: 10px;">
          <div class="field-group">
            <label class="field-label" for="drawerPhone">Phone</label>
            <input type="tel" id="drawerPhone" class="field-input" placeholder="08x-xxx-xxxx" value="${defaultPhone}" required>
          </div>
          <div class="field-group">
            <label class="field-label" for="drawerEmail">Email</label>
            <input type="email" id="drawerEmail" class="field-input" placeholder="email@domain.com" value="${defaultEmail}">
          </div>
        </div>

        <div class="field-group">
          <label class="field-label" for="drawerNote">Special Requests / Notes</label>
          <input type="text" id="drawerNote" class="field-input" placeholder="e.g. Quiet room, late arrival">
        </div>

        <div style="background: var(--bg-surface-subtle); padding: 14px; border-radius: var(--radius-sm); border: 1px solid var(--border-subtle); margin-top: 6px;">
          <div style="display:flex; justify-content:space-between; font-size:13.5px; margin-bottom:4px;">
            <span>Calculation</span>
            <span id="drawerCalcLine">${nights} night × ฿${th(r.price)}</span>
          </div>
          <div style="display:flex; justify-content:space-between; font-size:18px; font-weight:800; color:var(--text-primary);">
            <span>Total Estimated Bill</span>
            <span id="drawerTotalText" style="color:var(--accent);">฿${th(total)}</span>
          </div>
        </div>

        <p id="drawerErrorMsg" class="err" style="color:var(--status-maintenance); font-size:12.5px;"></p>
      </form>
    `;

    $("drawerFooter").innerHTML = `
      <button type="button" class="btn btn-outline" id="drawerCancelBtn">Cancel</button>
      <button type="button" class="btn btn-luxury" id="drawerConfirmBookBtn">Confirm & Book Stay</button>
    `;

    // Dynamic calc
    const nightsInput = $("drawerNights");
    nightsInput?.addEventListener("input", () => {
      const n = Math.max(1, parseInt(nightsInput.value) || 1);
      $("drawerCalcLine").textContent = `${n} night${n > 1 ? 's' : ''} × ฿${th(r.price)}`;
      $("drawerTotalText").textContent = `฿${th(r.price * n)}`;
    });

    $("drawerCancelBtn")?.addEventListener("click", () => this.closeDrawer());
    $("drawerConfirmBookBtn")?.addEventListener("click", () => this.handleDrawerBookingSubmit());

    $("sideDrawer").classList.add("active");
    $("drawerBackdrop").classList.add("active");
  }

  closeDrawer() {
    $("sideDrawer")?.classList.remove("active");
    $("drawerBackdrop")?.classList.remove("active");
    this.selectedRoomForDrawer = null;
  }

  async handleDrawerBookingSubmit() {
    const r = this.selectedRoomForDrawer;
    if (!r) return;

    const checkIn = $("drawerCheckIn").value;
    const nights = parseInt($("drawerNights").value) || 1;
    const booker = $("drawerBooker").value.trim();
    const phone = $("drawerPhone").value.trim();
    const email = $("drawerEmail").value.trim();
    const note = $("drawerNote").value.trim();
    const err = $("drawerErrorMsg");
    if (err) err.textContent = "";

    if (!booker) { if (err) err.textContent = "Please provide guest name"; return; }
    if (!phone)  { if (err) err.textContent = "Please provide contact phone"; return; }

    const btn = $("drawerConfirmBookBtn");
    if (btn) { btn.disabled = true; btn.textContent = "Reserving..."; }

    try {
      const res = await this.bookRoom(r.number, booker, phone, email, checkIn, nights, note);
      if (res.ok) {
        this.closeDrawer();
        this.warnIfNotSaved(res);
        this.toast(`✓ Reservation confirmed! Booking ID: ${res.booking.id}`);
        await this.refreshData();
        this.renderAll();
      } else {
        if (err) err.textContent = res.error || "Booking failed";
      }
    } catch (e) {
      if (err) err.textContent = "Failed to communicate with hotel server";
    } finally {
      if (btn) { btn.disabled = false; btn.textContent = "Confirm & Book Stay"; }
    }
  }

  openAuthModal() {
    $("authModal")?.classList.add("active");
  }

  closeAuthModal() {
    $("authModal")?.classList.remove("active");
  }

  openRoomEditModal(roomNumber, currentPrice, currentNote) {
    $("modalRoomNum").value = roomNumber;
    $("modalPrice").value = currentPrice;
    $("modalNote").value = currentNote || "";
    $("roomEditModal")?.classList.add("active");
  }

  closeRoomEditModal() {
    $("roomEditModal")?.classList.remove("active");
  }

  toast(message, type = "success") {
    const hub = $("toastsHub");
    if (!hub) return;

    const toast = document.createElement("div");
    toast.className = `toast-pill ${type === 'error' ? 'error' : 'success'}`;
    toast.innerHTML = `${type === 'error' ? getSvgIcon('alert', 16) : getSvgIcon('check', 16)} <span>${message}</span>`;
    hub.appendChild(toast);

    setTimeout(() => {
      toast.style.opacity = "0";
      toast.style.transform = "translateY(-10px)";
      toast.style.transition = "all 0.25s ease";
      setTimeout(() => toast.remove(), 250);
    }, 3200);
  }

  switchPortal(portalId) {
    if (portalId === "my_bookings") {
      if (!this.currentUser) {
        this.openAuthModal();
        return;
      }
      this.activePortal = "guest";
      this.renderAll();
      setTimeout(() => {
        const el = $("myBookingsContainer");
        if (el) el.scrollIntoView({ behavior: "smooth", block: "start" });
      }, 120);
      return;
    }
    if (portalId === "staff" && !this.isStaffLevel()) {
      this.toast("Staff access required", "error");
      return;
    }
    if (portalId === "admin" && !this.isAdminLevel()) {
      this.toast("Administrator access required", "error");
      return;
    }
    this.activePortal = portalId;
    this.renderAll();
  }

  openFolioModal(bookingId) {
    const modal = $("folioModal");
    const container = $("folioPrintableArea");
    if (!modal || !container) return;

    let b = this.bookings.find(x => String(x.id) === String(bookingId));
    if (!b) {
      const room = this.rooms.find(r => r.booking && String(r.booking.id) === String(bookingId));
      if (room) b = room.booking;
    }

    if (!b) {
      this.toast("Booking details not found for folio generation", "error");
      return;
    }

    const rNum = b.room || b.roomId;
    const roomObj = this.rooms.find(x => String(x.number) === String(rNum)) || {};
    const totalAmount = b.total || (roomObj.price ? roomObj.price * (b.nights || 1) : 0);
    const subtotal = Math.round((totalAmount / 1.07) * 100) / 100;
    const vat = Math.round((totalAmount - subtotal) * 100) / 100;
    const nights = b.nights || 1;
    const nightlyRate = Math.round(subtotal / nights);
    const issueDate = b.createdAt || (new Date().toISOString().slice(0, 10));
    const isPaid = (b.status === "checkin" || b.status === "checkout");

    container.innerHTML = `
      <div class="folio-sheet">
        <div class="folio-header" style="display:flex; justify-content:space-between; align-items:flex-start; border-bottom:2px solid var(--accent); padding-bottom:16px; margin-bottom:20px; gap:16px; flex-wrap:wrap;">
          <div>
            <div style="display:flex; align-items:center; gap:10px; margin-bottom:6px;">
              <div class="brand-monogram" style="width:36px; height:36px; font-size:14px;">HGH</div>
              <h2 class="font-serif" style="font-size:22px; margin:0; letter-spacing:0.5px;">Hilbert Grand Hotel</h2>
            </div>
            <div style="font-size:12px; color:var(--text-secondary); line-height:1.5;">
              Infinite Hospitality Avenue, Bangkok 10110, Thailand<br>
              Tax ID: 0-1055-67890-12-3 • TEL: +66 2 999 8888 • concierge@hilbert.grand
            </div>
          </div>
          <div style="text-align:right;">
            <div style="font-size:18px; font-weight:800; color:var(--accent); letter-spacing:1px; text-transform:uppercase;">OFFICIAL FOLIO</div>
            <div style="font-size:13px; font-weight:700; margin-top:4px;">Folio #: FOL-${b.id}</div>
            <div style="font-size:12px; color:var(--text-secondary);">Date: ${issueDate}</div>
            <div style="margin-top:6px;">
              <span class="status-pill ${isPaid ? 'available' : 'cleaning'}" style="font-size:12px; font-weight:700;">
                ${isPaid ? 'PAID & SETTLED' : 'PENDING SETTLEMENT'}
              </span>
            </div>
          </div>
        </div>

        <div class="folio-meta-grid" style="display:grid; grid-template-columns:1fr 1fr; gap:18px; margin-bottom:24px; padding:14px 18px; background:var(--bg-surface-subtle); border-radius:var(--radius-sm); border:1px solid var(--border-subtle);">
          <div>
            <div style="font-size:11px; text-transform:uppercase; color:var(--text-muted); font-weight:700; letter-spacing:0.5px;">GUEST INFORMATION</div>
            <div style="font-size:15px; font-weight:700; color:var(--text-primary); margin-top:2px;">${b.booker}</div>
            <div style="font-size:12.5px; color:var(--text-secondary); margin-top:2px;">Contact: ${b.phone || '-'}</div>
            <div style="font-size:12.5px; color:var(--text-secondary);">Reservation ID: ${b.id}</div>
          </div>
          <div>
            <div style="font-size:11px; text-transform:uppercase; color:var(--text-muted); font-weight:700; letter-spacing:0.5px;">STAY DETAILS</div>
            <div style="font-size:15px; font-weight:700; color:var(--text-primary); margin-top:2px;">Suite #${rNum} <span style="font-size:12px; font-weight:normal; color:var(--text-muted);">(${roomObj.tier === 'vip' ? 'VIP Luxury Suite' : 'Standard Suite'})</span></div>
            <div style="font-size:12.5px; color:var(--text-secondary); margin-top:2px;">Period: ${b.checkIn} → ${b.checkOut} (${nights} Night${nights > 1 ? 's' : ''})</div>
            <div style="font-size:12.5px; color:var(--text-secondary);">Bed Arrangement: ${roomObj.bed === 'twin' ? 'Twin Beds' : 'Double / King'}</div>
          </div>
        </div>

        <table class="folio-table" style="width:100%; border-collapse:collapse; margin-bottom:20px;">
          <thead>
            <tr style="border-bottom:1px solid var(--border-medium); text-align:left; font-size:12px; text-transform:uppercase; color:var(--text-muted);">
              <th style="padding:10px 8px;">Description</th>
              <th style="padding:10px 8px; text-align:center;">Nights / Qty</th>
              <th style="padding:10px 8px; text-align:right;">Rate (THB)</th>
              <th style="padding:10px 8px; text-align:right;">Amount (THB)</th>
            </tr>
          </thead>
          <tbody style="font-size:13.5px;">
            <tr style="border-bottom:1px solid var(--border-subtle);">
              <td style="padding:12px 8px;">
                <strong>Suite Accommodation Charge</strong><br>
                <span style="font-size:12px; color:var(--text-secondary);">Suite #${rNum} (${b.checkIn} to ${b.checkOut})</span>
              </td>
              <td style="padding:12px 8px; text-align:center;">${nights}</td>
              <td style="padding:12px 8px; text-align:right;">฿${th(nightlyRate)}</td>
              <td style="padding:12px 8px; text-align:right; font-weight:600;">฿${th(subtotal)}</td>
            </tr>
            <tr style="border-bottom:1px solid var(--border-subtle);">
              <td style="padding:12px 8px;">
                <strong>Luxury Amenities & Concierge Access</strong><br>
                <span style="font-size:12px; color:var(--text-secondary);">Complimentary High-speed Wi-Fi, Infinite Pool & Lounge</span>
              </td>
              <td style="padding:12px 8px; text-align:center;">1</td>
              <td style="padding:12px 8px; text-align:right;">฿0</td>
              <td style="padding:12px 8px; text-align:right; font-weight:600;">฿0</td>
            </tr>
          </tbody>
        </table>

        <div style="display:flex; justify-content:flex-end; margin-bottom:24px;">
          <div style="width:280px; font-size:13px; line-height:1.8;">
            <div style="display:flex; justify-content:space-between; color:var(--text-secondary);">
              <span>Subtotal (Net):</span>
              <span>฿${th(subtotal)}</span>
            </div>
            <div style="display:flex; justify-content:space-between; color:var(--text-secondary);">
              <span>Value Added Tax (VAT 7%):</span>
              <span>฿${th(vat)}</span>
            </div>
            <div style="display:flex; justify-content:space-between; font-size:16px; font-weight:800; color:var(--text-primary); border-top:2px solid var(--accent); padding-top:6px; margin-top:4px;">
              <span>Grand Total:</span>
              <span style="color:var(--accent);">฿${th(totalAmount)}</span>
            </div>
          </div>
        </div>

        <div class="folio-footer" style="border-top:1px dashed var(--border-medium); padding-top:16px; display:flex; justify-content:space-between; align-items:center; font-size:11.5px; color:var(--text-muted); flex-wrap:wrap; gap:12px;">
          <div>
            Thank you for choosing Hilbert Grand Hotel.<br>
            For any queries regarding this folio, please quote folio number FOL-${b.id}.
          </div>
          <div style="text-align:center; border-top:1px solid var(--border-medium); padding-top:4px; min-width:160px;">
            Guest / Cashier Signature
          </div>
        </div>
      </div>
    `;

    modal.classList.add("open");
  }

  closeFolioModal() {
    $("folioModal")?.classList.remove("open");
  }

  async openRoomInspector(roomNumber) {
    if (!this.isStaffLevel()) {
      this.toast("Staff access required to inspect room dossiers", "error");
      return;
    }

    const modal = $("roomInspectorModal");
    const body = $("inspectorModalBody");
    if (!modal || !body) return;

    body.innerHTML = `
      <div style="text-align: center; padding: 40px; color: var(--text-muted);">
        <div style="font-size: 13px; margin-bottom: 8px;">Loading Suite #${roomNumber} telemetry & booking records...</div>
      </div>
    `;
    modal.classList.add("open");

    try {
      const res = await this.apiFetch(`/api/staff/room-detail?room=${encodeURIComponent(roomNumber)}`);
      const data = await res.json();
      if (!res.ok || !data.ok) {
        body.innerHTML = `<div class="error-box" style="padding: 20px; color: var(--status-maintenance);">${data.error || 'Failed to retrieve suite details'}</div>`;
        return;
      }

      const room = data.room || {};
      const active = data.activeBooking;
      const history = data.history || [];
      const isVip = (room.tier === "vip");

      $("inspectorRoomTitle").textContent = `Suite #${room.number} Inspector`;
      $("inspectorSubtitle").textContent = `Floor ${room.floor} • ${room.bed === 'twin' ? 'Twin Beds' : 'Double / King Bed'} • Base Rate ฿${th(room.price)} / night`;

      const badge = $("inspectorStatusBadge");
      if (badge) {
        const isMaint = (room.status === 'maintenance');
        badge.className = `status-pill ${room.booked ? 'occupied' : (isMaint ? 'maintenance' : 'available')}`;
        badge.textContent = room.booked ? 'Occupied' : (isMaint ? 'Maintenance' : 'Available');
      }

      const tierBadge = $("inspectorTierBadge");
      if (tierBadge) {
        tierBadge.textContent = isVip ? 'VIP Luxury' : 'Standard';
      }

      body.innerHTML = `
        <div class="inspector-grid">
          <!-- Room Specs Card -->
          <div class="inspector-card">
            <div class="inspector-card-title">
              ${getSvgIcon('building', 13)}
              Suite Specifications
            </div>
            <div class="inspector-meta-row">
              <span class="inspector-meta-label">Suite ID</span>
              <span class="inspector-meta-val">#${room.number}</span>
            </div>
            <div class="inspector-meta-row">
              <span class="inspector-meta-label">Floor Location</span>
              <span class="inspector-meta-val">Floor ${room.floor}</span>
            </div>
            <div class="inspector-meta-row">
              <span class="inspector-meta-label">Bed Setup</span>
              <span class="inspector-meta-val">${room.bed === 'twin' ? '2 Single Beds' : '1 King Size Bed'}</span>
            </div>
            <div class="inspector-meta-row">
              <span class="inspector-meta-label">Standard Rate</span>
              <span class="inspector-meta-val" style="color: var(--gold-accent);">฿${th(room.price)} / night</span>
            </div>
            <div class="inspector-meta-row">
              <span class="inspector-meta-label">Amenities Included</span>
              <span class="inspector-meta-val">${(room.detail || ['WiFi', 'Air Con', 'Smart TV']).join(', ')}</span>
            </div>
          </div>

          <!-- Current Occupant Dossier -->
          <div class="inspector-card">
            <div class="inspector-card-title">
              ${getSvgIcon('user', 13)}
              Current Active Occupant
            </div>
            ${active ? `
              <div class="inspector-meta-row">
                <span class="inspector-meta-label">Guest Name</span>
                <span class="inspector-meta-val" style="font-size: 13.5px; color: var(--gold-accent);"><strong>${active.booker}</strong></span>
              </div>
              <div class="inspector-meta-row">
                <span class="inspector-meta-label">Phone Contact</span>
                <span class="inspector-meta-val">
                  <a href="tel:${active.phone || ''}" style="color: var(--text-primary); text-decoration: underline;">
                    ${getSvgIcon('phone', 11)} ${active.phone || '-'}
                  </a>
                </span>
              </div>
              <div class="inspector-meta-row">
                <span class="inspector-meta-label">Email Address</span>
                <span class="inspector-meta-val">
                  ${active.email ? `<a href="mailto:${active.email}" style="color: var(--text-primary); text-decoration: underline;">${getSvgIcon('mail', 11)} ${active.email}</a>` : '-'}
                </span>
              </div>
              <div class="inspector-meta-row">
                <span class="inspector-meta-label">Stay Period</span>
                <span class="inspector-meta-val">${active.checkIn} → ${active.checkOut} (${active.nights} night${active.nights > 1 ? 's' : ''})</span>
              </div>
              <div class="inspector-meta-row">
                <span class="inspector-meta-label">Folio Balance</span>
                <span class="inspector-meta-val" style="font-size: 14px; font-weight: 800; color: var(--status-available);">฿${th(active.total)}</span>
              </div>
              <div class="inspector-meta-row">
                <span class="inspector-meta-label">Status</span>
                <span class="inspector-meta-val"><span class="status-pill ${active.status === 'checkin' ? 'occupied' : 'cleaning'}">${active.status}</span></span>
              </div>
            ` : `
              <div style="text-align: center; padding: 24px 10px; color: var(--text-muted);">
                <div style="margin-bottom: 6px;">${getSvgIcon('check', 22)}</div>
                <strong>Suite is Currently Vacant</strong>
                <p style="font-size: 12px; margin-top: 4px;">Ready for immediate walk-in arrival or new reservation.</p>
              </div>
            `}
          </div>
        </div>

        <!-- Housekeeping & Maintenance Quick Update Form -->
        <div class="inspector-card" style="margin-bottom: 16px;">
          <div class="inspector-card-title">
            ${getSvgIcon('edit', 13)}
            Housekeeping & Maintenance Controls
          </div>
          <form id="inspectorStatusForm" style="display: flex; flex-direction: column; gap: 10px;">
            <div style="display: grid; grid-template-columns: 1fr 2fr; gap: 12px;">
              <div class="field-group">
                <label class="field-label">Set Room Status</label>
                <select id="inspectorStatusSelect" class="field-select" style="font-size: 12.5px;">
                  <option value="available" ${!room.booked && room.status !== 'maintenance' ? 'selected' : ''}>Available (Clean / Ready)</option>
                  <option value="occupied" ${room.booked ? 'selected' : ''}>Occupied</option>
                  <option value="maintenance" ${room.status === 'maintenance' ? 'selected' : ''}>Maintenance (Out of Service)</option>
                </select>
              </div>
              <div class="field-group">
                <label class="field-label">Housekeeping / Front Desk Notes</label>
                <input type="text" id="inspectorNoteInput" class="field-input" value="${room.note || ''}" placeholder="e.g. Inspected & refreshed for arrival">
              </div>
            </div>
            <div style="display: flex; justify-content: flex-end;">
              <button type="submit" class="btn btn-luxury btn-sm" id="inspectorSaveStatusBtn">
                ${getSvgIcon('check', 13)}
                Save Status & Log Audit
              </button>
            </div>
          </form>
        </div>

        <!-- Room Schedule & Reservation History -->
        <div class="inspector-turnover-box">
          <div class="inspector-card-title">
            ${getSvgIcon('calendar', 13)}
            Turnover Schedule & Reservation Log (${history.length})
          </div>
          ${history.length === 0 ? `
            <div style="text-align: center; color: var(--text-muted); padding: 14px; font-size: 12px;">No historical or upcoming stays registered for this suite.</div>
          ` : `
            <div style="overflow-x: auto;">
              <table class="inspector-timeline-table">
                <thead>
                  <tr>
                    <th>Booking ID</th>
                    <th>Booker</th>
                    <th>Contact</th>
                    <th>Dates</th>
                    <th>Nights</th>
                    <th>Total Bill</th>
                    <th>Status</th>
                  </tr>
                </thead>
                <tbody>
                  ${history.map(b => `
                    <tr>
                      <td><strong>${b.id}</strong></td>
                      <td>${b.booker}</td>
                      <td>${b.phone || '-'}</td>
                      <td>${b.checkIn} → ${b.checkOut}</td>
                      <td>${b.nights}</td>
                      <td>฿${th(b.total)}</td>
                      <td><span class="status-pill ${b.status === 'checkin' ? 'occupied' : (b.status === 'wait' ? 'cleaning' : 'available')}">${b.status}</span></td>
                    </tr>
                  `).join("")}
                </tbody>
              </table>
            </div>
          `}
        </div>

        <!-- Actions Bar -->
        <div class="inspector-action-bar">
          ${active ? `
            <button class="btn btn-outline btn-sm inspector-print-folio-btn" data-id="${active.id}">
              ${getSvgIcon('receipt', 13)}
              Print Guest Folio
            </button>
          ` : ''}
          <button class="btn btn-outline btn-sm" id="inspectorDismissBtn">Close</button>
        </div>
      `;

      $("inspectorDismissBtn")?.addEventListener("click", () => this.closeRoomInspector());
      body.querySelector(".inspector-print-folio-btn")?.addEventListener("click", (e) => {
        const bId = e.currentTarget.dataset.id;
        this.closeRoomInspector();
        this.openFolioModal(bId);
      });

      $("inspectorStatusForm")?.addEventListener("submit", async (e) => {
        e.preventDefault();
        const newStatus = $("inspectorStatusSelect").value;
        const newNote = $("inspectorNoteInput").value;
        const saveBtn = $("inspectorSaveStatusBtn");
        if (saveBtn) saveBtn.disabled = true;

        try {
          const sRes = await this.apiFetch("/api/staff/room-status", {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({
              room: room.number,
              status: newStatus,
              note: newNote
            })
          });
          const sData = await sRes.json();
          if (sRes.ok && sData.ok) {
            this.toast(`Suite #${room.number} updated successfully`, "success");
            await this.refreshData();
            this.renderAll();
            this.openRoomInspector(room.number);
          } else {
            this.toast(sData.error || "Failed to update room status", "error");
          }
        } catch (err) {
          this.toast("Server communication error", "error");
        } finally {
          if (saveBtn) saveBtn.disabled = false;
        }
      });

    } catch (err) {
      body.innerHTML = `<div class="error-box" style="padding: 20px; color: var(--status-maintenance);">Error communicating with hotel server: ${err.message}</div>`;
    }
  }

  closeRoomInspector() {
    $("roomInspectorModal")?.classList.remove("open");
  }

  openShortcutsModal() {
    $("shortcutsModal")?.classList.add("open");
  }

  closeShortcutsModal() {
    $("shortcutsModal")?.classList.remove("open");
  }

  applyTableDensity(density, targetTableId = null) {
    this.currentDensity = density;
    const tables = targetTableId ? [$(targetTableId)] : document.querySelectorAll(".luxury-table");
    tables.forEach(table => {
      if (!table) return;
      table.classList.remove("table-compact", "table-comfortable", "table-spacious");
      table.classList.add(`table-${density}`);
    });

    const groups = targetTableId 
      ? document.querySelectorAll(`.density-toggle-group[data-table="${targetTableId}"]`)
      : document.querySelectorAll(`.density-toggle-group`);

    groups.forEach(grp => {
      grp.querySelectorAll(".density-btn").forEach(b => {
        b.classList.toggle("active", b.dataset.density === density);
      });
    });

    try {
      localStorage.setItem("hgh_table_density", density);
    } catch (_) {}
  }

  handleTableSort(tableKey, sortCol) {
    if (!this.tableSort[tableKey]) {
      this.tableSort[tableKey] = { col: null, dir: "asc" };
    }
    const sort = this.tableSort[tableKey];
    if (sort.col === sortCol) {
      sort.dir = sort.dir === "asc" ? "desc" : "asc";
    } else {
      sort.col = sortCol;
      sort.dir = "asc";
    }

    // Update sort indicators on headers
    document.querySelectorAll(`th.th-sortable[data-table="${tableKey}"]`).forEach(th => {
      const isCol = th.dataset.sort === sortCol;
      const indicator = th.querySelector(".sort-indicator");
      if (indicator) {
        indicator.textContent = isCol ? (sort.dir === "asc" ? "↑" : "↓") : "↕";
      }
      th.classList.toggle("sorted-asc", isCol && sort.dir === "asc");
      th.classList.toggle("sorted-desc", isCol && sort.dir === "desc");
    });

    // Re-render relevant table
    if (tableKey === "staffCheckout") {
      this.renderStaffCheckoutTable();
    } else if (tableKey === "adminRooms") {
      this.renderAdminPortal();
    } else if (tableKey === "adminTxn") {
      this.renderAdminPortal();
    } else if (tableKey === "adminAudit") {
      this.renderAdminAuditTable();
    } else if (tableKey === "adminUsers") {
      this.renderAdminUsersTable();
    }
  }

  // ===========================================================================
  // 10. Event Wiring
  // ===========================================================================
  setupEvents() {
    // Theme toggle
    $("themeToggleBtn")?.addEventListener("click", () => this.toggleTheme());

    // Drawer close
    $("drawerCloseBtn")?.addEventListener("click", () => this.closeDrawer());
    $("drawerBackdrop")?.addEventListener("click", () => this.closeDrawer());

    // Auth Modal close
    $("authModalCloseBtn")?.addEventListener("click", () => this.closeAuthModal());
    $("authTabSignIn")?.addEventListener("click", () => {
      $("signInForm").style.display = "flex";
      $("signUpForm").style.display = "none";
      $("authTabSignIn").style.background = "var(--bg-surface)";
      $("authTabSignIn").style.color = "var(--text-primary)";
      $("authTabSignUp").style.background = "transparent";
      $("authTabSignUp").style.color = "var(--text-secondary)";
    });
    $("authTabSignUp")?.addEventListener("click", () => {
      $("signInForm").style.display = "none";
      $("signUpForm").style.display = "flex";
      $("authTabSignUp").style.background = "var(--bg-surface)";
      $("authTabSignUp").style.color = "var(--text-primary)";
      $("authTabSignIn").style.background = "transparent";
      $("authTabSignIn").style.color = "var(--text-secondary)";
    });

    // 1-Click Demo Profiles Dropdown
    $("demoDropdownToggle")?.addEventListener("click", () => {
      $("demoChipsGrid")?.classList.toggle("open");
      const arrow = $("demoDropdownArrow");
      if (arrow) arrow.textContent = $("demoChipsGrid")?.classList.contains("open") ? "▲" : "▼";
    });

    document.querySelectorAll(".demo-chip-btn").forEach(btn => {
      btn.addEventListener("click", async () => {
        const u = btn.dataset.user;
        const p = btn.dataset.pass;
        const res = await this.login(u, p);
        if (res.ok && res.user) {
          this.closeAuthModal();
          this.toast(`Logged in as ${res.user.fullName} (${res.user.role})`);
          await this.refreshData();
          this.renderAll();
        }
      });
    });

    // Sign In form
    $("signInForm")?.addEventListener("submit", async (e) => {
      e.preventDefault();
      const u = $("signInUsername").value.trim();
      const p = $("signInPassword").value.trim();
      const err = $("signInErrorMsg");
      if (err) err.textContent = "";

      const res = await this.login(u, p);
      if (res.ok && res.user) {
        this.closeAuthModal();
        this.toast(`Welcome, ${res.user.fullName || res.user.username}`);
        await this.refreshData();
        this.renderAll();
      } else {
        if (err) err.textContent = res.error || "Invalid username or password";
      }
    });

    // Sign Up form
    $("signUpForm")?.addEventListener("submit", async (e) => {
      e.preventDefault();
      const u = $("signUpUsername").value.trim();
      const p = $("signUpPassword").value.trim();
      const name = $("signUpFullName").value.trim();
      const phone = $("signUpPhone").value.trim();
      const email = $("signUpEmail").value.trim();
      const err = $("signUpErrorMsg");
      if (err) err.textContent = "";

      const res = await this.register(u, p, name, phone, email);
      if (res.ok && res.user) {
        this.closeAuthModal();
        this.toast(`Account created! Welcome, ${res.user.fullName}`);
        await this.refreshData();
        this.renderAll();
      } else {
        if (err) err.textContent = res.error || "Registration failed";
      }
    });

    // Room Edit modal
    $("roomEditModalCloseBtn")?.addEventListener("click", () => this.closeRoomEditModal());
    $("roomEditModalCancelBtn")?.addEventListener("click", () => this.closeRoomEditModal());
    $("roomEditForm")?.addEventListener("submit", async (e) => {
      e.preventDefault();
      const roomId = $("modalRoomNum").value;
      const price = parseFloat($("modalPrice").value) || 0;
      const note = $("modalNote").value.trim();

      const res = await this.updateRoomDetails(roomId, price, note);
      if (res.ok) {
        this.closeRoomEditModal();
        if (!this.warnIfNotSaved(res)) this.toast(`Suite ${roomId} updated in Excel database`);
        await this.refreshData();
        this.renderAdminPortal();
      } else {
        this.toast(res.error || "Update failed", "error");
      }
    });

    // Admin Reload Excel button
    $("adminReloadExcelBtn")?.addEventListener("click", async () => {
      const res = await this.reloadExcel();
      if (res.ok) {
        this.toast("Reloaded data/hotel.xlsx successfully");
        await this.refreshData();
        this.renderAdminPortal();
      } else {
        this.toast(res.error || "Reload failed", "error");
      }
    });

    // Staff new walk-in button
    $("staffNewWalkinBtn")?.addEventListener("click", () => {
      const freeRoom = this.rooms.find(r => !r.booked);
      if (freeRoom) {
        this.openDrawer(freeRoom.number);
      } else {
        this.toast("No available rooms for walk-in booking", "error");
      }
    });

    // Guest Portal search & filters
    $("guestRoomTypeSelect")?.addEventListener("change", (e) => {
      this.filterTier = e.target.value;
      this.renderGuestCards();
    });
    $("guestBedSelect")?.addEventListener("change", (e) => {
      this.filterBed = e.target.value;
      this.renderGuestCards();
    });
    $("guestStayNightsInput")?.addEventListener("input", (e) => {
      this.filterNights = Math.max(1, parseInt(e.target.value) || 1);
      this.renderGuestCards();
    });
    $("guestSearchQuery")?.addEventListener("input", (e) => {
      this.filterSearch = e.target.value.trim();
      this.renderGuestCards();
    });

    // Filter chips
    $("chipAvailable")?.addEventListener("click", (e) => {
      this.filterAvailableOnly = !this.filterAvailableOnly;
      e.currentTarget.classList.toggle("active", this.filterAvailableOnly);
      this.renderGuestCards();
    });
    $("chipSortPriceAsc")?.addEventListener("click", (e) => {
      this.filterSortMode = this.filterSortMode === "asc" ? "default" : "asc";
      $("chipSortPriceAsc")?.classList.toggle("active", this.filterSortMode === "asc");
      $("chipSortPriceDesc")?.classList.remove("active");
      this.renderGuestCards();
    });
    $("chipSortPriceDesc")?.addEventListener("click", (e) => {
      this.filterSortMode = this.filterSortMode === "desc" ? "default" : "desc";
      $("chipSortPriceDesc")?.classList.toggle("active", this.filterSortMode === "desc");
      $("chipSortPriceAsc")?.classList.remove("active");
      this.renderGuestCards();
    });
    $("chipVipOnly")?.addEventListener("click", (e) => {
      const isVip = this.filterTier === "vip";
      this.filterTier = isVip ? "ALL" : "vip";
      $("guestRoomTypeSelect").value = this.filterTier;
      $("chipVipOnly")?.classList.toggle("active", !isVip);
      this.renderGuestCards();
    });

    // Floating Role Switcher Bubble pills
    document.querySelectorAll(".role-pill-btn").forEach(btn => {
      btn.addEventListener("click", async (e) => {
        e.stopPropagation();
        await this.switchRole(btn.dataset.role);
      });
    });

    // Global click listener to close user dropdown popover when clicking outside
    document.addEventListener("click", (e) => {
      const popover = $("userDropdownPopover");
      const badge = $("userProfileBadgeToggle");
      if (popover && !popover.classList.contains("hidden")) {
        if (!popover.contains(e.target) && (!badge || !badge.contains(e.target))) {
          popover.classList.add("hidden");
        }
      }
    });

    // Extend Stay Modal Events
    $("extendModalCloseBtn")?.addEventListener("click", () => this.closeExtendStayModal());
    $("extendModalCancelBtn")?.addEventListener("click", () => this.closeExtendStayModal());
    
    $("extendNightsMinus")?.addEventListener("click", () => {
      const input = $("extendNightsInput");
      if (!input) return;
      const cur = Math.max(1, (parseInt(input.value) || 1) - 1);
      input.value = cur;
      const checkOut = $("extendCurrentCheckOut")?.textContent || "";
      const price = parseFloat($("extendRoomPrice")?.value) || 0;
      this.updateExtendPreview(checkOut, price, cur);
    });

    $("extendNightsPlus")?.addEventListener("click", () => {
      const input = $("extendNightsInput");
      if (!input) return;
      const cur = Math.min(30, (parseInt(input.value) || 1) + 1);
      input.value = cur;
      const checkOut = $("extendCurrentCheckOut")?.textContent || "";
      const price = parseFloat($("extendRoomPrice")?.value) || 0;
      this.updateExtendPreview(checkOut, price, cur);
    });

    $("extendNightsInput")?.addEventListener("input", (e) => {
      const cur = Math.max(1, parseInt(e.target.value) || 1);
      const checkOut = $("extendCurrentCheckOut")?.textContent || "";
      const price = parseFloat($("extendRoomPrice")?.value) || 0;
      this.updateExtendPreview(checkOut, price, cur);
    });

    $("extendStayForm")?.addEventListener("submit", async (e) => {
      e.preventDefault();
      const bookingId = $("extendBookingId")?.value;
      const nights = parseInt($("extendNightsInput")?.value) || 1;
      const note = $("extendNoteInput")?.value.trim() || "";

      const res = await this.extendStay(bookingId, nights, note);
      if (res.ok) {
        this.closeExtendStayModal();
        if (!this.warnIfNotSaved(res)) this.toast(`Stay for Booking ${bookingId} extended by ${nights} night${nights > 1 ? 's' : ''}!`);
        await this.refreshData();
        this.renderLiveViews();
      } else {
        this.toast(res.error || "Failed to extend stay", "error");
      }
    });

    // Date-Range Availability Pickers
    $("guestSearchCheckIn")?.addEventListener("change", (e) => {
      this.filterCheckIn = e.target.value;
      // Auto-set checkout to +1 day if empty or before checkin
      const outInput = $("guestSearchCheckOut");
      if (outInput && (!this.filterCheckOut || this.filterCheckOut <= this.filterCheckIn)) {
        const parts = this.filterCheckIn.split("-");
        if (parts.length === 3) {
          const d = new Date(parseInt(parts[0]), parseInt(parts[1]) - 1, parseInt(parts[2]));
          d.setDate(d.getDate() + 1);
          const yyyy = d.getFullYear();
          const mm = String(d.getMonth() + 1).padStart(2, "0");
          const dd = String(d.getDate()).padStart(2, "0");
          outInput.value = `${yyyy}-${mm}-${dd}`;
          this.filterCheckOut = outInput.value;
        }
      }
      this.renderGuestCards();
    });

    $("guestSearchCheckOut")?.addEventListener("change", (e) => {
      this.filterCheckOut = e.target.value;
      this.renderGuestCards();
    });

    // Max Price Slider
    $("guestPriceSlider")?.addEventListener("input", (e) => {
      const val = parseInt(e.target.value) || 10000;
      this.filterMaxPrice = val;
      const label = $("guestPriceLabel");
      if (label) {
        label.textContent = val >= 10000 ? "Any" : `฿${th(val)}`;
      }
      this.renderGuestCards();
    });

    // Amenities Filter Chips
    document.querySelectorAll(".amenity-chip-btn").forEach(btn => {
      btn.addEventListener("click", () => {
        const amenity = btn.dataset.amenity;
        if (this.selectedAmenities.has(amenity)) {
          this.selectedAmenities.delete(amenity);
          btn.classList.remove("active");
        } else {
          this.selectedAmenities.add(amenity);
          btn.classList.add("active");
        }
        this.renderGuestCards();
      });
    });

    // Clear / Reset All Filters button
    $("clearFiltersBtn")?.addEventListener("click", () => {
      this.filterTier = "ALL";
      this.filterBed = "ALL";
      this.filterAvailableOnly = true;
      this.filterSearch = "";
      this.filterCheckIn = "";
      this.filterCheckOut = "";
      this.filterMaxPrice = 10000;
      this.selectedAmenities.clear();

      if ($("guestSearchQuery")) $("guestSearchQuery").value = "";
      if ($("guestRoomTypeSelect")) $("guestRoomTypeSelect").value = "ALL";
      if ($("guestBedSelect")) $("guestBedSelect").value = "ALL";
      if ($("guestSearchCheckIn")) $("guestSearchCheckIn").value = "";
      if ($("guestSearchCheckOut")) $("guestSearchCheckOut").value = "";
      if ($("guestPriceSlider")) $("guestPriceSlider").value = 10000;
      if ($("guestPriceLabel")) $("guestPriceLabel").textContent = "Any";
      $("chipAvailable")?.classList.add("active");
      $("chipVipOnly")?.classList.remove("active");
      document.querySelectorAll(".amenity-chip-btn").forEach(b => b.classList.remove("active"));

      this.renderGuestCards();
    });

    // Audit Search & Export CSV
    $("adminAuditSearchInput")?.addEventListener("input", (e) => {
      this.auditSearch = e.target.value.trim();
      this.renderAdminAuditTable();
    });
    $("exportAuditCsvBtn")?.addEventListener("click", () => this.exportAuditCsv());

    // Phase 2: User Account Management Events
    $("adminAddUserBtn")?.addEventListener("click", () => this.openAddUserModal());
    $("adminUserModalClose")?.addEventListener("click", () => this.closeUserModal());
    $("adminUserModalCancelBtn")?.addEventListener("click", () => this.closeUserModal());
    $("adminUserForm")?.addEventListener("submit", async (e) => {
      e.preventDefault();
      await this.saveUserForm();
    });
    $("adminUserSearchInput")?.addEventListener("input", (e) => {
      this.adminUserSearch = e.target.value.trim();
      this.renderAdminUsersTable();
    });

    // Phase 2: Database Backup Snapshot
    $("adminBackupBtn")?.addEventListener("click", () => this.triggerBackup());

    // Phase 2: Executive Terminal Console (Ctrl+K)
    $("adminConsoleBtn")?.addEventListener("click", () => this.openTerminal());
    $("adminConsoleCloseBtn")?.addEventListener("click", () => this.closeTerminal());
    $("terminalSendBtn")?.addEventListener("click", () => {
      const input = $("terminalInput");
      if (input) {
        this.runTerminalCommand(input.value);
        input.value = "";
      }
    });

    $("terminalInput")?.addEventListener("keydown", (e) => {
      if (e.key === "Enter") {
        e.preventDefault();
        const input = $("terminalInput");
        if (input) {
          this.runTerminalCommand(input.value);
          input.value = "";
        }
      } else if (e.key === "ArrowUp") {
        e.preventDefault();
        if (this.cmdHistory.length > 0 && this.cmdHistoryIdx > 0) {
          this.cmdHistoryIdx--;
          e.target.value = this.cmdHistory[this.cmdHistoryIdx];
        }
      } else if (e.key === "ArrowDown") {
        e.preventDefault();
        if (this.cmdHistoryIdx < this.cmdHistory.length - 1) {
          this.cmdHistoryIdx++;
          e.target.value = this.cmdHistory[this.cmdHistoryIdx];
        } else {
          this.cmdHistoryIdx = this.cmdHistory.length;
          e.target.value = "";
        }
      }
    });

    document.querySelectorAll(".term-chip").forEach(chip => {
      chip.addEventListener("click", () => {
        const cmd = chip.dataset.cmd;
        if (cmd) this.runTerminalCommand(cmd);
      });
    });

    // Admin room inventory filter
    $("adminRoomSearchInput")?.addEventListener("input", (e) => {
      this.adminRoomSearch = e.target.value.trim();
      this.renderAdminPortal();
    });

    // Staff PMS Roster live search & filter
    $("staffRosterSearch")?.addEventListener("input", () => this.renderStaffRoomRoster());
    $("staffRosterFilter")?.addEventListener("change", () => this.renderStaffRoomRoster());

    // Room Inspector Modal close handlers
    $("inspectorCloseBtn")?.addEventListener("click", () => this.closeRoomInspector());
    $("roomInspectorModal")?.addEventListener("click", (e) => {
      if (e.target.id === "roomInspectorModal") this.closeRoomInspector();
    });

    // Global keyboard shortcuts (Desktop & Ultra-wide power-user controls)
    document.addEventListener("keydown", (e) => {
      const tag = (e.target && e.target.tagName) ? e.target.tagName.toLowerCase() : "";
      const isInput = tag === "input" || tag === "textarea" || tag === "select";

      // 1. Terminal console: Ctrl+K / Cmd+K
      if ((e.ctrlKey || e.metaKey) && e.key.toLowerCase() === "k") {
        e.preventDefault();
        const modal = $("adminConsoleModal");
        if (modal && modal.classList.contains("open")) {
          this.closeTerminal();
        } else {
          this.openTerminal();
        }
        return;
      }

      // 2. Escape: Close any active modal, drawer, or console
      if (e.key === "Escape") {
        if ($("roomInspectorModal")?.classList.contains("open")) {
          this.closeRoomInspector();
          return;
        }
        if ($("folioModal")?.classList.contains("open")) {
          this.closeFolioModal();
          return;
        }
        if ($("shortcutsModal")?.classList.contains("open")) {
          this.closeShortcutsModal();
          return;
        }
        if ($("adminConsoleModal")?.classList.contains("open")) {
          this.closeTerminal();
          return;
        }
        if ($("adminUserModal")?.classList.contains("open")) {
          this.closeUserModal();
          return;
        }
        if ($("roomEditModal")?.classList.contains("active")) {
          this.closeRoomEditModal();
          return;
        }
        if ($("extendStayModal")?.classList.contains("active")) {
          this.closeExtendStayModal();
          return;
        }
        if ($("authModal")?.classList.contains("active")) {
          this.closeAuthModal();
          return;
        }
        this.closeDrawer();
        return;
      }

      // 3. Focus Universal Search: / key (when not typing in an input)
      if (e.key === "/" && !isInput && !e.ctrlKey && !e.metaKey && !e.altKey) {
        e.preventDefault();
        if (this.activePortal === "guest") {
          $("guestSearchQuery")?.focus();
        } else if (this.activePortal === "admin") {
          $("adminRoomSearchInput")?.focus();
        }
        return;
      }

      // 4. Portal navigation: Alt+1..4
      if (e.altKey && !e.ctrlKey && !e.metaKey) {
        if (e.key === "1") {
          e.preventDefault();
          this.switchPortal("guest");
        } else if (e.key === "2") {
          e.preventDefault();
          this.switchPortal("my_bookings");
        } else if (e.key === "3") {
          e.preventDefault();
          this.switchPortal("staff");
        } else if (e.key === "4") {
          e.preventDefault();
          this.switchPortal("admin");
        }
        return;
      }

      // 5. Cheat sheet guide: ? (Shift + /)
      if (e.key === "?" && !isInput && !e.ctrlKey && !e.metaKey && !e.altKey) {
        e.preventDefault();
        const sm = $("shortcutsModal");
        if (sm?.classList.contains("open")) this.closeShortcutsModal();
        else this.openShortcutsModal();
        return;
      }
    });

    // Shortcuts modal button triggers
    $("shortcutsGuideBtn")?.addEventListener("click", () => this.openShortcutsModal());
    $("shortcutsCloseBtn")?.addEventListener("click", () => this.closeShortcutsModal());
    $("shortcutsModal")?.addEventListener("click", (e) => {
      if (e.target === $("shortcutsModal")) this.closeShortcutsModal();
    });

    // Folio / Receipt modal button triggers
    $("folioCloseBtn")?.addEventListener("click", () => this.closeFolioModal());
    $("folioModal")?.addEventListener("click", (e) => {
      if (e.target === $("folioModal")) this.closeFolioModal();
    });
    $("printFolioBtn")?.addEventListener("click", () => window.print());

    // Mobile collapsible search header toggle
    $("mobileSearchToggleBtn")?.addEventListener("click", () => {
      $("guestFilterBar")?.classList.toggle("mobile-expanded");
    });

    // Mobile sticky bottom navigation items
    $("mobNavGuest")?.addEventListener("click", () => this.switchPortal("guest"));
    $("mobNavBookings")?.addEventListener("click", () => this.switchPortal("my_bookings"));
    $("mobNavStaff")?.addEventListener("click", () => this.switchPortal("staff"));
    $("mobNavAdmin")?.addEventListener("click", () => this.switchPortal("admin"));
    $("mobNavProfile")?.addEventListener("click", () => {
      if (!this.currentUser) {
        this.openAuthModal();
      } else {
        const popover = $("userDropdownPopover");
        if (popover) popover.classList.toggle("hidden");
      }
    });

    // Table display density toggle buttons
    document.querySelectorAll(".density-toggle-group").forEach(group => {
      const tableId = group.dataset.table;
      group.querySelectorAll(".density-btn").forEach(btn => {
        btn.addEventListener("click", () => {
          this.applyTableDensity(btn.dataset.density, tableId);
        });
      });
    });

    // Interactive sortable table column headers
    document.querySelectorAll("th.th-sortable").forEach(th => {
      th.addEventListener("click", () => {
        const tableKey = th.dataset.table;
        const sortCol = th.dataset.sort;
        if (tableKey && sortCol) {
          this.handleTableSort(tableKey, sortCol);
        }
      });
    });

    // View switchers
    $("guestViewCardsBtn")?.addEventListener("click", () => {
      this.activePortal = "guest";
      this.renderAll();
    });
    $("guestViewMatrixBtn")?.addEventListener("click", () => {
      this.activePortal = "matrix";
      this.renderAll();
    });
  }
}

// Instantiate Engine when DOM is ready
document.addEventListener("DOMContentLoaded", () => {
  window.hotelApp = new HotelAppEngine();
});
