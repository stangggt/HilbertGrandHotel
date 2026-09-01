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
    case "crown":
    case "vip":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><path d="M2 4l3 12h14l3-12-6 7-4-7-4 7-6-7zm3 16h14v2H5v-2z"/></svg>`;
    case "sparkles":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><path d="M12 2l2.4 7.2L22 12l-7.6 2.8L12 22l-2.4-7.2L2 12l7.6-2.8z"/></svg>`;
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
    this.todayStr = "";
    this.currentUser = null;
    this.activePortal = "guest";
    this.guestViewMode = "cards"; // 'cards' or 'matrix'

    this.filterTier = "ALL";
    this.filterBed = "ALL";
    this.filterAvailableOnly = true;
    this.filterSortMode = "default";
    this.filterSearch = "";
    this.filterNights = 1;
    this.selectedRoomForDrawer = null;

    this.init();
  }

  async init() {
    this.initTheme();
    this.loadSession();
    this.setupEvents();
    await this.refreshData();
    this.renderAll();

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

  // ดึงข้อมูลทุกอย่างที่บทบาทปัจจุบันต้องใช้ ในลำดับเดียวกันเสมอ
  // (เดิมผู้ใช้ทั่วไปไม่เคยโหลด bookings เลย ทำให้ My Reservations ว่างตลอด)
  async refreshData() {
    await this.fetchRooms();
    if (this.isStaffLevel()) {
      await this.fetchAdminData();
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
    } catch (e) {
      console.warn("Failed to fetch /api/rooms", e);
    }
  }

  async fetchAdminData() {
    try {
      const res = await fetch("/api/admin/data");
      const data = await res.json();
      if (data.rooms) this.rooms = data.rooms;
      if (data.bookings) this.bookings = data.bookings;
      if (data.today) this.todayStr = data.today;
    } catch (e) {
      console.warn("Failed to fetch /api/admin/data", e);
    }
  }

  async bookRoom(roomId, booker, phone, email, checkIn, nights, note) {
    const res = await fetch("/api/book", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ room: roomId, booker, phone, email, checkIn, nights, note })
    });
    return res.json();
  }

  async updateBookingStatus(id, status) {
    const res = await fetch("/api/admin/status", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ id, status })
    });
    return res.json();
  }

  async updateRoomDetails(roomId, price, note) {
    const res = await fetch("/api/admin/room", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ room: roomId, price, note })
    });
    return res.json();
  }

  async reloadExcel() {
    const res = await fetch("/api/admin/reload", { method: "POST", headers: { "Content-Type": "application/json" }, body: "{}" });
    return res.json();
  }

  async login(username, password) {
    const res = await fetch("/api/auth/login", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ username, password })
    });
    return res.json();
  }

  async register(username, password, fullName, phone, email) {
    const res = await fetch("/api/auth/register", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ username, password, fullName, phone, email })
    });
    return res.json();
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
    } catch (e) {
      this.currentUser = null;
    }
  }

  saveSession(user) {
    this.currentUser = user;
    if (user) localStorage.setItem("gh_user", JSON.stringify(user));
    else localStorage.removeItem("gh_user");
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

          <div style="padding: 6px 0; border-bottom: 1px solid var(--border-subtle); display:flex; flex-direction:column; gap:4px;">
            <div style="font-size: 10px; text-transform: uppercase; color: var(--text-muted); font-weight: 700; padding: 0 4px;">Quick Switch Role:</div>
            <button class="dropdown-role-btn ${curRole === 'admin' ? 'active' : ''}" data-role="admin">
              👑 Administrator (Admin)
            </button>
            <button class="dropdown-role-btn ${curRole === 'staff' ? 'active' : ''}" data-role="staff">
              💼 Front Desk Staff
            </button>
            <button class="dropdown-role-btn ${curRole === 'guest' ? 'active' : ''}" data-role="guest">
              👤 Guest Customer
            </button>
          </div>

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
        this.saveSession(null);
        this.bookings = [];
        this.activePortal = "guest";
        this.renderAll();
        this.toast("Signed out successfully");
      });
    }
  }

  updateFloatingRoleBubble() {
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
      this.saveSession(res.user);
      if (targetRole === "admin") this.activePortal = "admin";
      else if (targetRole === "staff") this.activePortal = "staff";
      else this.activePortal = "guest";

      this.toast(`⚡ Switched to ${res.user.fullName} (${targetRole.toUpperCase()})`);
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
      if (this.filterAvailableOnly && r.booked) return false;
      if (this.filterTier !== "ALL" && r.tier !== this.filterTier) return false;
      if (this.filterBed !== "ALL" && r.bed !== this.filterBed) return false;
      if (this.filterSearch) {
        const q = this.filterSearch.toLowerCase();
        const numMatch = r.number.toLowerCase().includes(q);
        const nameMatch = (r.typeName || "").toLowerCase().includes(q);
        if (!numMatch && !nameMatch) return false;
      }
      return true;
    });

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
            <span class="photo-badge-tier">${isVip ? '★ VIP Villa' : 'Standard'}</span>
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
              <button class="btn btn-outline btn-sm" disabled style="opacity: 0.6; cursor: not-allowed;">
                ${getSvgIcon("check", 14)}
                <span>Reserved</span>
              </button>
            ` : `
              <button class="btn btn-luxury btn-sm book-drawer-trigger" data-room="${r.number}">
                <span>Reserve Suite</span>
              </button>
            `}
          </div>
        </div>
      `;
    }).join("");

    grid.querySelectorAll(".book-drawer-trigger").forEach(btn => {
      btn.addEventListener("click", () => this.openDrawer(btn.dataset.room));
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
          ${myBooks.map(b => `
            <div style="display:flex; justify-content:space-between; align-items:center; background: var(--bg-surface-subtle); padding: 10px 16px; border-radius: var(--radius-sm); border: 1px solid var(--border-subtle); flex-wrap: wrap; gap: 8px;">
              <div>
                <strong style="font-size: 15px;">Suite ${b.room || b.roomId}</strong>
                <span style="margin-left: 8px; color: var(--text-secondary); font-size: 12.5px;">(${b.checkIn} to ${b.checkOut}, ${b.nights} night${b.nights > 1 ? 's' : ''})</span>
              </div>
              <div style="display:flex; align-items:center; gap: 12px;">
                <span style="font-weight: 700; color: var(--text-primary);">฿${th(b.total)}</span>
                <span class="status-pill ${b.status === 'checkin' ? 'occupied' : (b.status === 'wait' ? 'cleaning' : 'available')}">${b.status}</span>
              </div>
            </div>
          `).join("")}
        </div>
      </div>
    `;
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

    $("staffCountReady") && ($("staffCountReady").textContent = available);
    $("staffCountOccupied") && ($("staffCountOccupied").textContent = occupied);
    $("staffCountWait") && ($("staffCountWait").textContent = wait);
    $("staffCountVip") && ($("staffCountVip").textContent = vip);

    const tbody = document.querySelector("#staffCheckoutTable tbody");
    if (!tbody) return;

    const activeRooms = this.rooms.filter(r => r.booked);
    if (activeRooms.length === 0) {
      tbody.innerHTML = `<tr><td colspan="8" style="text-align:center; color:var(--text-muted); padding:30px;">No active stays currently occupying hotel inventory.</td></tr>`;
      return;
    }

    tbody.innerHTML = activeRooms.map(r => {
      const b = r.booking || {};
      const isCheckin = b.status === "checkin";
      return `
        <tr>
          <td><strong style="font-size:14px;">#${r.number}</strong> <span style="font-size:11px;color:var(--text-muted);">(${r.tier})</span></td>
          <td><strong>${b.booker || 'Guest'}</strong></td>
          <td><span style="font-size:12px;">${b.phone || '-'}</span></td>
          <td>${b.checkIn || '-'} → ${b.checkOut || '-'}</td>
          <td>${b.nights || 1} nights</td>
          <td><strong style="color:var(--accent);">฿${th(b.total || r.price)}</strong></td>
          <td><span class="status-pill ${isCheckin ? 'occupied' : 'cleaning'}">${b.status || 'wait'}</span></td>
          <td>
            <div style="display:flex; gap:6px;">
              ${!isCheckin ? `
                <button class="btn btn-luxury btn-sm staff-act-btn" data-act="checkin" data-id="${b.id}">Check In</button>
              ` : `
                <button class="btn btn-outline btn-sm staff-act-btn" data-act="checkout" data-id="${b.id}" style="color:var(--status-maintenance);">Check Out</button>
              `}
              <button class="btn btn-outline btn-sm staff-act-btn" data-act="cancel" data-id="${b.id}">Cancel</button>
            </div>
          </td>
        </tr>
      `;
    }).join("");

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
      roomTbody.innerHTML = this.rooms.map(r => {
        const isBooked = r.booked;
        const b = r.booking || {};
        return `
          <tr>
            <td><strong>#${r.number}</strong></td>
            <td>Floor ${r.floor}</td>
            <td>${r.tier === 'vip' ? '★ VIP Luxury' : 'Standard Suite'}</td>
            <td>${r.bed === 'twin' ? 'Twin Beds' : 'Double / King'}</td>
            <td><strong>฿${th(r.price)}</strong></td>
            <td><span class="status-pill ${isBooked ? 'occupied' : 'available'}">${isBooked ? (b.status || 'Booked') : 'Available'}</span></td>
            <td>${isBooked && b.booker ? `${b.booker} (${b.id})` : '-'}</td>
            <td><span style="font-size:12px;color:var(--text-muted);">${r.note || '-'}</span></td>
            <td>
              <button class="btn btn-outline btn-sm admin-edit-room-btn" data-room="${r.number}" data-price="${r.price}" data-note="${r.note || ''}">
                ${getSvgIcon("edit", 13)}
                <span>Edit</span>
              </button>
            </td>
          </tr>
        `;
      }).join("");

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
        txnTbody.innerHTML = this.bookings.map(b => `
          <tr>
            <td><strong>${b.id}</strong></td>
            <td>#${b.room || b.roomId}</td>
            <td><strong>${b.booker}</strong></td>
            <td><span style="font-size:12px;">${b.phone || '-'}</span></td>
            <td>${b.checkIn} → ${b.checkOut}</td>
            <td>${b.nights}</td>
            <td><strong style="color:var(--text-primary);">฿${th(b.total)}</strong></td>
            <td><span class="status-pill ${b.status === 'checkin' ? 'occupied' : (b.status === 'wait' ? 'cleaning' : 'available')}">${b.status}</span></td>
            <td><span style="font-size:11.5px;color:var(--text-muted);">${b.createdAt || '-'}</span></td>
          </tr>
        `).join("");
      }
    }
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
            <h3 class="font-serif" style="font-size: 18px;">Level ${floorNum} ${floorNum === 3 ? '★ VIP Penthouse Floor' : 'Standard Guest Floor'}</h3>
            <span style="font-size: 12.5px; color: var(--text-secondary);">${floorRooms.length} Total Suites</span>
          </div>

          <div style="display: grid; grid-template-columns: repeat(auto-fill, minmax(200px, 1fr)); gap: 14px;">
            ${floorRooms.map(r => {
              const isBooked = r.booked;
              const statusClass = isBooked ? "occupied" : "available";
              const isVip = r.tier === "vip";
              return `
                <div style="background: var(--bg-surface-subtle); border: 1px solid var(--border-medium); border-radius: var(--radius-md); padding: 14px; display:flex; flex-direction:column; gap:6px;">
                  <div style="display:flex; justify-content:space-between; align-items:center;">
                    <strong style="font-size: 17px;">#${r.number}</strong>
                    <span class="status-pill ${statusClass}">${isBooked ? 'Booked' : 'Free'}</span>
                  </div>
                  <div style="font-size: 12px; color: var(--text-secondary);">${isVip ? 'VIP Luxury' : 'Standard'} • ${r.bed === 'twin' ? 'Twin' : 'Double'}</div>
                  <div style="margin-top:4px; font-weight:700; color:var(--accent); font-size:14px;">฿${th(r.price)} / night</div>
                </div>
              `;
            }).join("")}
          </div>
        </div>
      `;
    }).join("");
  }

  // ===========================================================================
  // 9. Modals, Drawers, and Toasts
  // ===========================================================================
  openDrawer(roomNumber) {
    const r = this.rooms.find(x => String(x.number) === String(roomNumber));
    if (!r || r.booked) return;
    this.selectedRoomForDrawer = r;

    $("drawerHeading").textContent = `Suite ${r.number}`;
    $("drawerSubheading").textContent = `${r.tier === 'vip' ? '★ VIP Penthouse Suite' : 'Standard Guest Suite'} • Floor ${r.floor}`;

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
          this.saveSession(res.user);
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
        this.saveSession(res.user);
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
        this.saveSession(res.user);
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
