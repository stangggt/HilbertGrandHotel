/**
 * Grand Horizon Boutique Resort & Hotel
 * Client Application Engine, SVG Icon System & Database State
 */

// SVG Icon Helper Library (Stroke 1.5px, Consistent System)
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
    case "broom":
    case "cleaning":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><path d="M12 2v10"/><path d="M18.4 6.6L12 13l-6.4-6.4"/><path d="M4 14l4 8h8l4-8"/></svg>`;
    case "check":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><polyline points="20 6 9 17 4 12"/></svg>`;
    case "alert":
    case "maintenance":
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
    case "chevron-down":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><polyline points="6 9 12 15 18 9"/></svg>`;
    case "moon":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><path d="M21 12.79A9 9 0 1 1 11.21 3 7 7 0 0 0 21 12.79z"/></svg>`;
    case "sun":
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><circle cx="12" cy="12" r="5"/><path d="M12 1v2M12 21v2M4.22 4.22l1.42 1.42M18.36 18.36l1.42 1.42M1 12h2M21 12h2M4.22 19.78l1.42-1.42M18.36 5.64l1.42-1.42"/></svg>`;
    default:
      return `<svg class="${cls}" style="width:${s}px;height:${s}px;" viewBox="0 0 24 24"><circle cx="12" cy="12" r="10"/></svg>`;
  }
}

// Curated Boutique Hotel Photography (Warm Tones)
const ROOM_PHOTOS = {
  STANDARD: [
    "https://images.unsplash.com/photo-1590490360182-c33d57733427?auto=format&fit=crop&w=800&q=80",
    "https://images.unsplash.com/photo-1566665797739-1674de7a421a?auto=format&fit=crop&w=800&q=80",
    "https://images.unsplash.com/photo-1505693416388-ac5ce068fe85?auto=format&fit=crop&w=800&q=80"
  ],
  DELUXE: [
    "https://images.unsplash.com/photo-1582719478250-c89cae4dc85b?auto=format&fit=crop&w=800&q=80",
    "https://images.unsplash.com/photo-1618773928121-c32242e63f39?auto=format&fit=crop&w=800&q=80",
    "https://images.unsplash.com/photo-1578683010236-d716f9a3f461?auto=format&fit=crop&w=800&q=80"
  ],
  VIP: [
    "https://images.unsplash.com/photo-1631049307264-da0ec9d70304?auto=format&fit=crop&w=800&q=80",
    "https://images.unsplash.com/photo-1591088398332-8a7791972843?auto=format&fit=crop&w=800&q=80",
    "https://images.unsplash.com/photo-1582719508461-905c673771fd?auto=format&fit=crop&w=800&q=80"
  ]
};

function getRoomPhoto(roomType, roomNumber) {
  const list = ROOM_PHOTOS[roomType] || ROOM_PHOTOS.STANDARD;
  const idx = Math.abs(roomNumber) % list.length;
  return list[idx];
}

// Initial Seed Rooms Data (Boutique Pricing: $85 - $450)
const INITIAL_ROOMS_CSV = `room_number,floor,room_type,bed_type,capacity,price_per_night,amenities,status,housekeeping_status,current_guest,booked_nights,check_in_date
101,1,STANDARD,SINGLE,1,85.00,TV;AC;High-Speed WiFi;Espresso Bar,AVAILABLE,READY,,,
102,1,STANDARD,DOUBLE,2,95.00,TV;AC;High-Speed WiFi;Artisan Breakfast,OCCUPIED,READY,john_doe,3,2026-08-30
103,1,STANDARD,DOUBLE,2,95.00,TV;AC;High-Speed WiFi;Garden View,AVAILABLE,READY,,,
104,1,STANDARD,SINGLE,1,85.00,TV;AC;High-Speed WiFi;Work Desk,AVAILABLE,CLEANING,,,
105,1,DELUXE,DOUBLE,2,145.00,Smart TV;AC;WiFi;Balcony;Artisan Breakfast,AVAILABLE,READY,,,
106,1,DELUXE,DOUBLE,2,145.00,Smart TV;AC;WiFi;Balcony;Artisan Breakfast,OCCUPIED,READY,alice,2,2026-08-31
107,1,STANDARD,DOUBLE,2,95.00,TV;AC;High-Speed WiFi,MAINTENANCE,NEEDS_INSPECTION,,,
108,1,STANDARD,SINGLE,1,85.00,TV;AC;High-Speed WiFi,AVAILABLE,READY,,,
201,2,DELUXE,DOUBLE,2,155.00,Smart TV;AC;WiFi;Private Balcony;Breakfast,AVAILABLE,READY,,,
202,2,DELUXE,KING,2,175.00,Smart TV;AC;WiFi;Private Balcony;Bathtub,AVAILABLE,READY,,,
203,2,DELUXE,KING,2,175.00,Smart TV;AC;WiFi;Private Balcony;Bathtub,AVAILABLE,CLEANING,,,
204,2,DELUXE,DOUBLE,2,155.00,Smart TV;AC;WiFi;Private Balcony;Breakfast,AVAILABLE,READY,,,
205,2,VIP,KING,3,280.00,Smart TV;AC;WiFi;Ocean Balcony;Bathtub;Sea View;Wine Bar,AVAILABLE,READY,,,
206,2,VIP,KING,3,280.00,Smart TV;AC;WiFi;Ocean Balcony;Bathtub;Sea View;Wine Bar,OCCUPIED,READY,david_smith,4,2026-08-29
207,2,DELUXE,DOUBLE,2,155.00,Smart TV;AC;WiFi;Private Balcony;Breakfast,AVAILABLE,READY,,,
208,2,STANDARD,DOUBLE,2,110.00,Smart TV;AC;WiFi;Balcony,AVAILABLE,READY,,,
301,3,VIP,KING,4,360.00,Smart TV;AC;WiFi;Panoramic Balcony;Breakfast;Jacuzzi;Sea View,AVAILABLE,READY,,,
302,3,VIP,KING,4,360.00,Smart TV;AC;WiFi;Panoramic Balcony;Breakfast;Jacuzzi;Sea View,AVAILABLE,READY,,,
303,3,VIP,KING,4,360.00,Smart TV;AC;WiFi;Panoramic Balcony;Breakfast;Jacuzzi;Sea View,AVAILABLE,READY,,,
304,3,VIP,KING,4,450.00,Smart TV;AC;WiFi;Private Rooftop Pool;Jacuzzi;Butler Service;Sea View,MAINTENANCE,NEEDS_INSPECTION,,,`;

// Initial Seed Users
const INITIAL_USERS = [
  { username: "admin", password: "admin123", role: "ADMIN", fullName: "Alexander Wright", email: "admin@grandhorizon.com" },
  { username: "staff", password: "staff123", role: "STAFF", fullName: "Elena Rostova", email: "staff@grandhorizon.com" },
  { username: "john_doe", password: "pass123", role: "GUEST", fullName: "Johnathan Doe", email: "john.doe@example.com" },
  { username: "alice", password: "pass123", role: "GUEST", fullName: "Alice Wonderland", email: "alice@example.com" },
  { username: "david_smith", password: "pass123", role: "GUEST", fullName: "David Smith", email: "david.smith@example.com" }
];

// Initial Seed Transactions
const INITIAL_TRANSACTIONS = [
  { id: "TXN-1001", roomNumber: 102, guest: "john_doe", nights: 3, rate: 95.0, total: 285.0, timestamp: "2026-08-30 14:00:00", status: "ACTIVE" },
  { id: "TXN-1002", roomNumber: 106, guest: "alice", nights: 2, rate: 145.0, total: 290.0, timestamp: "2026-08-31 11:30:00", status: "ACTIVE" },
  { id: "TXN-1003", roomNumber: 206, guest: "david_smith", nights: 4, rate: 280.0, total: 1120.0, timestamp: "2026-08-29 15:15:00", status: "ACTIVE" },
  { id: "TXN-1000", roomNumber: 201, guest: "john_doe", nights: 2, rate: 155.0, total: 310.0, timestamp: "2026-08-25 10:00:00", status: "COMPLETED" }
];

class HotelEngine {
  constructor() {
    this.rooms = [];
    this.users = [...INITIAL_USERS];
    this.transactions = [...INITIAL_TRANSACTIONS];
    this.currentUser = null;
    this.loadRoomsFromCsv(INITIAL_ROOMS_CSV);
    this.loadSession();
  }

  loadRoomsFromCsv(csv) {
    const lines = csv.trim().split("\n");
    this.rooms = [];
    for (let i = 1; i < lines.length; ++i) {
      const l = lines[i].trim();
      if (!l) continue;
      const t = l.split(",");
      if (t.length >= 9) {
        this.rooms.push({
          roomNumber: parseInt(t[0]),
          floor: parseInt(t[1]),
          roomType: t[2],
          bedType: t[3],
          capacity: parseInt(t[4]),
          pricePerNight: parseFloat(t[5]),
          amenities: t[6] ? t[6].split(";") : [],
          status: t[7],
          housekeepingStatus: t[8],
          currentGuest: t[9] || "",
          bookedNights: parseInt(t[10]) || 0,
          checkInDate: t[11] || ""
        });
      }
    }
  }

  exportRoomsCsv() {
    let csv = "room_number,floor,room_type,bed_type,capacity,price_per_night,amenities,status,housekeeping_status,current_guest,booked_nights,check_in_date\n";
    this.rooms.forEach(r => {
      csv += `${r.roomNumber},${r.floor},${r.roomType},${r.bedType},${r.capacity},${r.pricePerNight.toFixed(2)},${r.amenities.join(";")},${r.status},${r.housekeepingStatus},${r.currentGuest},${r.bookedNights || ""},${r.checkInDate || ""}\n`;
    });
    return csv;
  }

  loadSession() {
    try {
      const saved = localStorage.getItem("gh_hotel_user");
      if (saved) {
        this.currentUser = JSON.parse(saved);
      } else {
        this.currentUser = this.users.find(u => u.username === "john_doe") || this.users[2];
      }
    } catch (e) {
      this.currentUser = this.users[2];
    }
  }

  saveSession() {
    if (this.currentUser) {
      localStorage.setItem("gh_hotel_user", JSON.stringify(this.currentUser));
    } else {
      localStorage.removeItem("gh_hotel_user");
    }
  }

  login(username, password) {
    const user = this.users.find(u => u.username === username && u.password === password);
    if (user) {
      this.currentUser = user;
      this.saveSession();
      return true;
    }
    return false;
  }

  register(username, password, fullName, email) {
    if (this.users.some(u => u.username === username)) {
      return { success: false, message: "Username already exists." };
    }
    const newUser = {
      username,
      password,
      role: "GUEST",
      fullName: fullName || username,
      email: email || `${username}@example.com`
    };
    this.users.push(newUser);
    this.currentUser = newUser;
    this.saveSession();
    return { success: true, user: newUser };
  }

  logout() {
    this.currentUser = null;
    this.saveSession();
  }

  getRoom(num) {
    return this.rooms.find(r => r.roomNumber === num);
  }

  addRoom(roomObj) {
    if (this.getRoom(roomObj.roomNumber)) return false;
    this.rooms.push(roomObj);
    return true;
  }

  updateRoom(roomObj) {
    const idx = this.rooms.findIndex(r => r.roomNumber === roomObj.roomNumber);
    if (idx !== -1) {
      this.rooms[idx] = roomObj;
      return true;
    }
    return false;
  }

  deleteRoom(num) {
    const r = this.getRoom(num);
    if (!r || r.status === "OCCUPIED") return false;
    this.rooms = this.rooms.filter(item => item.roomNumber !== num);
    return true;
  }

  checkIn(roomNumber, guestName, nights, date) {
    const room = this.getRoom(roomNumber);
    if (!room || room.status !== "AVAILABLE" || room.housekeepingStatus !== "READY") return false;

    room.status = "OCCUPIED";
    room.currentGuest = guestName;
    room.bookedNights = nights;
    room.checkInDate = date || new Date().toISOString().split("T")[0];

    const total = room.pricePerNight * nights;
    const txnId = "TXN-" + (1000 + this.transactions.length + 1);
    this.transactions.push({
      id: txnId,
      roomNumber: roomNumber,
      guest: guestName,
      nights: nights,
      rate: room.pricePerNight,
      total: total,
      timestamp: new Date().toISOString().replace("T", " ").substring(0, 19),
      status: "ACTIVE"
    });
    return { success: true, txnId, total };
  }

  checkOut(roomNumber) {
    const room = this.getRoom(roomNumber);
    if (!room || room.status !== "OCCUPIED") return null;

    const nights = room.bookedNights;
    const total = room.pricePerNight * nights;
    const guest = room.currentGuest;

    const txn = this.transactions.find(t => t.roomNumber === roomNumber && t.status === "ACTIVE");
    if (txn) txn.status = "COMPLETED";

    room.status = "AVAILABLE";
    room.housekeepingStatus = "CLEANING";
    room.currentGuest = "";
    room.bookedNights = 0;
    const checkIn = room.checkInDate;
    room.checkInDate = "";

    return { roomNumber, guest, nights, rate: room.pricePerNight, total, checkInDate: checkIn, checkOutDate: new Date().toISOString().split("T")[0] };
  }

  setHousekeeping(roomNumber, status) {
    const r = this.getRoom(roomNumber);
    if (!r) return false;
    r.housekeepingStatus = status;
    if (status === "READY" && r.status !== "OCCUPIED") {
      r.status = "AVAILABLE";
    }
    return true;
  }

  getMetrics() {
    const total = this.rooms.length;
    const occupied = this.rooms.filter(r => r.status === "OCCUPIED").length;
    const available = this.rooms.filter(r => r.status === "AVAILABLE" && r.housekeepingStatus === "READY").length;
    const cleaning = this.rooms.filter(r => r.housekeepingStatus === "CLEANING" || r.housekeepingStatus === "NEEDS_INSPECTION").length;
    const maintenance = this.rooms.filter(r => r.status === "MAINTENANCE").length;
    const occupancyRate = total > 0 ? ((occupied / total) * 100).toFixed(1) : "0.0";
    
    const revenue = this.transactions
      .filter(t => t.status !== "CANCELLED")
      .reduce((sum, t) => sum + t.total, 0);

    const avgPrice = total > 0 ? (this.rooms.reduce((sum, r) => sum + r.pricePerNight, 0) / total).toFixed(2) : "0.00";

    return { total, occupied, available, cleaning, maintenance, occupancyRate, revenue, avgPrice };
  }
}

// App Instance & Global State
const engine = new HotelEngine();
let activePortal = "guest"; // "guest", "staff", "admin", "matrix", "my_bookings"
let selectedRoomForDrawer = null;
let roomBeingEdited = null;

// Guest Search & Filters
const guestFilters = {
  roomType: "ALL",
  nights: 1,
  searchQuery: "",
  availableOnly: true,
  sortPrice: null, // "ASC", "DESC"
  readyOnly: false
};

// DOM References
const portalNavTabs = document.getElementById("portalNavTabs");
const authHeaderContainer = document.getElementById("authHeaderContainer");
const themeToggleBtn = document.getElementById("themeToggleBtn");
const globalExportCsvBtn = document.getElementById("globalExportCsvBtn");

// Portals
const guestPortal = document.getElementById("guestPortal");
const staffPortal = document.getElementById("staffPortal");
const adminPortal = document.getElementById("adminPortal");
const matrixPortal = document.getElementById("matrixPortal");

// Modals & Drawers
const authModal = document.getElementById("authModal");
const authModalCloseBtn = document.getElementById("authModalCloseBtn");
const authTabSignIn = document.getElementById("authTabSignIn");
const authTabSignUp = document.getElementById("authTabSignUp");
const signInForm = document.getElementById("signInForm");
const signUpForm = document.getElementById("signUpForm");
const demoDropdownToggle = document.getElementById("demoDropdownToggle");
const demoChipsGrid = document.getElementById("demoChipsGrid");

const sideDrawer = document.getElementById("sideDrawer");
const drawerBackdrop = document.getElementById("drawerBackdrop");
const drawerCloseBtn = document.getElementById("drawerCloseBtn");

const roomEditModal = document.getElementById("roomEditModal");
const roomEditModalCloseBtn = document.getElementById("roomEditModalCloseBtn");
const roomEditModalCancelBtn = document.getElementById("roomEditModalCancelBtn");
const roomEditForm = document.getElementById("roomEditForm");

const receiptModal = document.getElementById("receiptModal");
const receiptModalCloseBtn = document.getElementById("receiptModalCloseBtn");
const receiptBody = document.getElementById("receiptBody");

const toastsHub = document.getElementById("toastsHub");

// Initialize on DOM Ready
document.addEventListener("DOMContentLoaded", () => {
  initTheme();
  setupEventListeners();
  updateAuthHeader();
  renderPortalNavigation();
  renderCurrentPortal();
});

function initTheme() {
  const saved = localStorage.getItem("gh_theme") || "light";
  document.documentElement.setAttribute("data-theme", saved);
  updateThemeIcon(saved);
}

function updateThemeIcon(theme) {
  const iconWrap = document.getElementById("themeToggleBtn");
  if (iconWrap) {
    iconWrap.innerHTML = theme === "dark" ? getSvgIcon("sun", 18) : getSvgIcon("moon", 18);
  }
}

function setupEventListeners() {
  // Theme Switch
  themeToggleBtn.addEventListener("click", () => {
    const current = document.documentElement.getAttribute("data-theme");
    const next = current === "dark" ? "light" : "dark";
    document.documentElement.setAttribute("data-theme", next);
    localStorage.setItem("gh_theme", next);
    updateThemeIcon(next);
    showToast(`Switched to ${next} palette`);
  });

  // Global CSV Export
  globalExportCsvBtn.addEventListener("click", () => {
    const csvData = engine.exportRoomsCsv();
    const blob = new Blob([csvData], { type: "text/csv;charset=utf-8;" });
    const url = URL.createObjectURL(blob);
    const link = document.createElement("a");
    link.href = url;
    link.download = "rooms.csv";
    document.body.appendChild(link);
    link.click();
    document.body.removeChild(link);
    showToast("Exported rooms.csv successfully", "success");
  });

  // Home Brand Link
  document.getElementById("brandHomeLink").addEventListener("click", (e) => {
    e.preventDefault();
    if (engine.currentUser?.role === "ADMIN") switchPortal("admin");
    else if (engine.currentUser?.role === "STAFF") switchPortal("staff");
    else switchPortal("guest");
  });

  // Collapsible Demo Dropdown (^ Dropdown)
  demoDropdownToggle.addEventListener("click", () => {
    const isOpen = demoChipsGrid.classList.toggle("open");
    document.getElementById("demoDropdownArrow").textContent = isOpen ? "▲" : "▼";
  });

  // Demo Profile Buttons Click
  document.querySelectorAll(".demo-chip-btn").forEach(btn => {
    btn.addEventListener("click", () => {
      const u = btn.dataset.user;
      const p = btn.dataset.pass;
      document.getElementById("signInUsername").value = u;
      document.getElementById("signInPassword").value = p;
      if (engine.login(u, p)) {
        closeAuthModal();
        updateAuthHeader();
        renderPortalNavigation();
        autoRouteUserPortal();
        showToast(`Signed in as ${engine.currentUser.fullName} (${engine.currentUser.role})`, "success");
      }
    });
  });

  // Auth Tab Switch
  authTabSignIn.addEventListener("click", () => {
    authTabSignIn.style.background = "var(--bg-surface)";
    authTabSignIn.style.color = "var(--text-primary)";
    authTabSignUp.style.background = "transparent";
    authTabSignUp.style.color = "var(--text-secondary)";
    signInForm.style.display = "flex";
    signUpForm.style.display = "none";
  });

  authTabSignUp.addEventListener("click", () => {
    authTabSignUp.style.background = "var(--bg-surface)";
    authTabSignUp.style.color = "var(--text-primary)";
    authTabSignIn.style.background = "transparent";
    authTabSignIn.style.color = "var(--text-secondary)";
    signUpForm.style.display = "flex";
    signInForm.style.display = "none";
  });

  // Sign In Form Submit
  signInForm.addEventListener("submit", (e) => {
    e.preventDefault();
    const u = document.getElementById("signInUsername").value.trim();
    const p = document.getElementById("signInPassword").value;
    if (engine.login(u, p)) {
      closeAuthModal();
      updateAuthHeader();
      renderPortalNavigation();
      autoRouteUserPortal();
      showToast(`Welcome back, ${engine.currentUser.fullName}!`, "success");
    } else {
      showToast("Invalid credentials. Try demo accounts.", "error");
    }
  });

  // Sign Up Form Submit
  signUpForm.addEventListener("submit", (e) => {
    e.preventDefault();
    const u = document.getElementById("signUpUsername").value.trim();
    const p = document.getElementById("signUpPassword").value;
    const name = document.getElementById("signUpFullName").value.trim();
    const email = document.getElementById("signUpEmail").value.trim();
    
    const res = engine.register(u, p, name, email);
    if (res.success) {
      closeAuthModal();
      updateAuthHeader();
      renderPortalNavigation();
      autoRouteUserPortal();
      showToast(`Account created! Welcome, ${name}`, "success");
    } else {
      showToast(res.message, "error");
    }
  });

  authModalCloseBtn.addEventListener("click", closeAuthModal);
  authModal.addEventListener("click", (e) => {
    if (e.target === authModal) closeAuthModal();
  });

  // Drawer Close
  drawerCloseBtn.addEventListener("click", closeDrawer);
  drawerBackdrop.addEventListener("click", closeDrawer);

  // Room Edit Modal Close
  roomEditModalCloseBtn.addEventListener("click", closeRoomEditModal);
  roomEditModalCancelBtn.addEventListener("click", closeRoomEditModal);
  roomEditModal.addEventListener("click", (e) => {
    if (e.target === roomEditModal) closeRoomEditModal();
  });

  // Receipt Modal Close
  receiptModalCloseBtn.addEventListener("click", closeReceiptModal);
  receiptModal.addEventListener("click", (e) => {
    if (e.target === receiptModal) closeReceiptModal();
  });

  // Admin Room Add / Edit Form Submit
  roomEditForm.addEventListener("submit", (e) => {
    e.preventDefault();
    const num = parseInt(document.getElementById("modalRoomNum").value);
    const floor = parseInt(document.getElementById("modalFloor").value);
    const rType = document.getElementById("modalRoomType").value;
    const bType = document.getElementById("modalBedType").value;
    const cap = parseInt(document.getElementById("modalCapacity").value);
    const price = parseFloat(document.getElementById("modalPrice").value);
    const amenities = document.getElementById("modalAmenities").value.split(";").map(s => s.trim()).filter(Boolean);

    if (roomBeingEdited) {
      roomBeingEdited.roomNumber = num;
      roomBeingEdited.floor = floor;
      roomBeingEdited.roomType = rType;
      roomBeingEdited.bedType = bType;
      roomBeingEdited.capacity = cap;
      roomBeingEdited.pricePerNight = price;
      roomBeingEdited.amenities = amenities;
      engine.updateRoom(roomBeingEdited);
      showToast(`Suite ${num} updated successfully`, "success");
    } else {
      if (engine.getRoom(num)) {
        showToast(`Suite ${num} already exists!`, "error");
        return;
      }
      const newRoom = {
        roomNumber: num,
        floor: floor || Math.floor(num / 100),
        roomType: rType,
        bedType: bType,
        capacity: cap,
        pricePerNight: price,
        amenities: amenities,
        status: "AVAILABLE",
        housekeepingStatus: "READY",
        currentGuest: "",
        bookedNights: 0,
        checkInDate: ""
      };
      engine.addRoom(newRoom);
      showToast(`Suite ${num} added to inventory!`, "success");
    }
    closeRoomEditModal();
    renderCurrentPortal();
  });

  // Admin Controls
  document.getElementById("adminAddNewRoomBtn").addEventListener("click", () => {
    openRoomEditModal(null);
  });

  document.getElementById("adminResetDbBtn").addEventListener("click", () => {
    if (confirm("Reset hotel database to seed rooms.csv dataset?")) {
      engine.loadRoomsFromCsv(INITIAL_ROOMS_CSV);
      renderCurrentPortal();
      showToast("Database restored to default seed rooms", "success");
    }
  });

  document.getElementById("adminRoomSearchInput").addEventListener("input", (e) => {
    renderAdminRoomsTable(e.target.value.trim());
  });

  // Guest Search Inputs
  document.getElementById("guestRoomTypeSelect").addEventListener("change", (e) => {
    guestFilters.roomType = e.target.value;
    renderGuestCards();
  });

  document.getElementById("guestStayNightsInput").addEventListener("input", (e) => {
    const val = Math.max(1, Math.min(30, parseInt(e.target.value) || 1));
    guestFilters.nights = val;
    renderGuestCards();
    if (selectedRoomForDrawer) openDrawer(selectedRoomForDrawer);
  });

  document.getElementById("guestSearchQuery").addEventListener("input", (e) => {
    guestFilters.searchQuery = e.target.value.trim();
    renderGuestCards();
  });

  document.getElementById("guestSearchBtn").addEventListener("click", () => {
    renderGuestCards();
  });

  // Guest Chips
  document.getElementById("chipAvailable").addEventListener("click", function() {
    guestFilters.availableOnly = !guestFilters.availableOnly;
    this.classList.toggle("active", guestFilters.availableOnly);
    renderGuestCards();
  });

  document.getElementById("chipSortPriceAsc").addEventListener("click", function() {
    if (guestFilters.sortPrice === "ASC") {
      guestFilters.sortPrice = null;
      this.classList.remove("active");
    } else {
      guestFilters.sortPrice = "ASC";
      this.classList.add("active");
      document.getElementById("chipSortPriceDesc").classList.remove("active");
    }
    renderGuestCards();
  });

  document.getElementById("chipSortPriceDesc").addEventListener("click", function() {
    if (guestFilters.sortPrice === "DESC") {
      guestFilters.sortPrice = null;
      this.classList.remove("active");
    } else {
      guestFilters.sortPrice = "DESC";
      this.classList.add("active");
      document.getElementById("chipSortPriceAsc").classList.remove("active");
    }
    renderGuestCards();
  });

  document.getElementById("chipReady").addEventListener("click", function() {
    guestFilters.readyOnly = !guestFilters.readyOnly;
    this.classList.toggle("active", guestFilters.readyOnly);
    renderGuestCards();
  });

  // Guest View Switcher
  document.getElementById("guestViewCardsBtn").addEventListener("click", () => {
    switchPortal("guest");
  });

  document.getElementById("guestViewMatrixBtn").addEventListener("click", () => {
    switchPortal("matrix");
  });
}

function autoRouteUserPortal() {
  if (engine.currentUser?.role === "ADMIN") switchPortal("admin");
  else if (engine.currentUser?.role === "STAFF") switchPortal("staff");
  else switchPortal("guest");
}

function updateAuthHeader() {
  if (!engine.currentUser) {
    authHeaderContainer.innerHTML = `
      <button class="btn btn-luxury btn-sm" onclick="window.openAuthModal()">
        ${getSvgIcon("user", 14)} Sign In
      </button>
    `;
  } else {
    const initials = engine.currentUser.fullName
      .split(" ")
      .map(n => n[0])
      .join("")
      .substring(0, 2)
      .toUpperCase();

    authHeaderContainer.innerHTML = `
      <div class="user-profile-badge" onclick="window.toggleUserMenu(event)">
        <div class="user-avatar">${initials}</div>
        <div class="user-info-text">
          <span class="user-name">${engine.currentUser.fullName}</span>
          <span class="user-role-tag">${engine.currentUser.role}</span>
        </div>
        ${getSvgIcon("chevron-down", 12, "text-muted")}
      </div>
    `;
  }
}

// Anchored Dropdown Menu (Directly inside .user-profile-badge-wrapper)
window.toggleUserMenu = function(e) {
  e.stopPropagation();
  const existing = document.getElementById("userDropdownPopover");
  if (existing) {
    existing.remove();
    return;
  }

  const popover = document.createElement("div");
  popover.id = "userDropdownPopover";
  popover.className = "user-dropdown-popover";

  popover.innerHTML = `
    <div style="padding: 8px 10px; border-bottom: 1px solid var(--border-subtle); font-size: 12px;">
      <div style="font-weight: 700; color: var(--text-primary);">${engine.currentUser.fullName}</div>
      <div style="color: var(--text-muted);">${engine.currentUser.email || engine.currentUser.username}</div>
    </div>
    <div style="padding: 4px 0;">
      <div style="font-size: 10.5px; font-weight: 700; text-transform: uppercase; color: var(--text-muted); padding: 4px 10px;">Switch Persona</div>
      <button class="nav-tab-btn" style="width: 100%; border-radius: var(--radius-xs); padding: 6px 10px;" onclick="window.switchRoleDemo('ADMIN')">
        ${getSvgIcon("crown", 14)} Admin Console
      </button>
      <button class="nav-tab-btn" style="width: 100%; border-radius: var(--radius-xs); padding: 6px 10px;" onclick="window.switchRoleDemo('STAFF')">
        ${getSvgIcon("broom", 14)} Staff Operations
      </button>
      <button class="nav-tab-btn" style="width: 100%; border-radius: var(--radius-xs); padding: 6px 10px;" onclick="window.switchRoleDemo('GUEST')">
        ${getSvgIcon("user", 14)} Guest Portal
      </button>
    </div>
    <div style="border-top: 1px solid var(--border-subtle); padding-top: 4px;">
      <button class="nav-tab-btn" style="width: 100%; color: var(--status-maintenance); border-radius: var(--radius-xs); padding: 6px 10px;" onclick="window.handleSignOut()">
        Sign Out
      </button>
    </div>
  `;

  authHeaderContainer.appendChild(popover);

  const remover = (ev) => {
    if (!popover.contains(ev.target)) {
      popover.remove();
      document.removeEventListener("click", remover);
    }
  };
  setTimeout(() => document.addEventListener("click", remover), 10);
};

window.switchRoleDemo = function(role) {
  const target = engine.users.find(u => u.role.toUpperCase() === role.toUpperCase());
  if (target) {
    engine.currentUser = target;
    engine.saveSession();
    updateAuthHeader();
    renderPortalNavigation();
    autoRouteUserPortal();
    showToast(`Switched persona to ${role}`, "info");
  }
};

window.handleSignOut = function() {
  engine.logout();
  updateAuthHeader();
  renderPortalNavigation();
  switchPortal("guest");
  showToast("You have been signed out.", "info");
};

function renderPortalNavigation() {
  const role = engine.currentUser?.role || "GUEST";
  portalNavTabs.innerHTML = "";

  const tabs = [];

  if (role === "ADMIN") {
    tabs.push({ id: "admin", label: "Executive Dashboard", icon: "dashboard" });
    tabs.push({ id: "matrix", label: "Floor Blueprint", icon: "building" });
    tabs.push({ id: "guest", label: "Guest View Preview", icon: "grid" });
  } else if (role === "STAFF") {
    tabs.push({ id: "staff", label: "Operations Hub", icon: "broom" });
    tabs.push({ id: "matrix", label: "Floor Blueprint", icon: "building" });
    tabs.push({ id: "guest", label: "Guest View Preview", icon: "grid" });
  } else {
    tabs.push({ id: "guest", label: "Explore Suites", icon: "bed" });
    tabs.push({ id: "my_bookings", label: "My Reservations", icon: "receipt" });
    tabs.push({ id: "matrix", label: "Floor Blueprint", icon: "building" });
  }

  tabs.forEach(t => {
    const btn = document.createElement("button");
    btn.className = `nav-tab-btn ${activePortal === t.id ? "active" : ""}`;
    btn.innerHTML = `${getSvgIcon(t.icon, 15)} <span>${t.label}</span>`;
    btn.addEventListener("click", () => switchPortal(t.id));
    portalNavTabs.appendChild(btn);
  });
}

function switchPortal(portalId) {
  activePortal = portalId;
  renderPortalNavigation();

  guestPortal.classList.remove("active");
  staffPortal.classList.remove("active");
  adminPortal.classList.remove("active");
  matrixPortal.classList.remove("active");

  if (portalId === "admin") adminPortal.classList.add("active");
  else if (portalId === "staff") staffPortal.classList.add("active");
  else if (portalId === "matrix") matrixPortal.classList.add("active");
  else guestPortal.classList.add("active");

  renderCurrentPortal();
}

function renderCurrentPortal() {
  if (activePortal === "guest") renderGuestPortal();
  else if (activePortal === "my_bookings") renderMyBookingsPortal();
  else if (activePortal === "staff") renderStaffPortal();
  else if (activePortal === "admin") renderAdminPortal();
  else if (activePortal === "matrix") renderMatrixPortal();
}

/* ==========================================================================
   1. GUEST PORTAL (Photography Cards & Micro-copy Pluralization)
   ========================================================================== */
function renderGuestPortal() {
  document.getElementById("guestMainContent").innerHTML = `
    <div id="guestCardsGrid" class="rooms-grid"></div>
  `;
  renderGuestCards();
}

function renderGuestCards() {
  const container = document.getElementById("guestCardsGrid");
  if (!container) return;

  let rooms = [...engine.rooms];

  if (guestFilters.roomType !== "ALL") {
    rooms = rooms.filter(r => r.roomType === guestFilters.roomType);
  }
  if (guestFilters.availableOnly) {
    rooms = rooms.filter(r => r.status === "AVAILABLE");
  }
  if (guestFilters.readyOnly) {
    rooms = rooms.filter(r => r.housekeepingStatus === "READY");
  }
  if (guestFilters.searchQuery) {
    rooms = rooms.filter(r => r.roomNumber.toString().includes(guestFilters.searchQuery));
  }

  if (guestFilters.sortPrice === "ASC") {
    rooms.sort((a, b) => a.pricePerNight - b.pricePerNight);
  } else if (guestFilters.sortPrice === "DESC") {
    rooms.sort((a, b) => b.pricePerNight - a.pricePerNight);
  } else {
    rooms.sort((a, b) => a.roomNumber - b.roomNumber);
  }

  container.innerHTML = "";

  if (rooms.length === 0) {
    container.innerHTML = `
      <div style="grid-column: 1 / -1; text-align: center; padding: 60px 20px; color: var(--text-secondary);">
        <div style="font-size: 28px; margin-bottom: 8px;">${getSvgIcon("building", 36)}</div>
        <h3 class="font-serif" style="font-size: 20px; color: var(--text-primary);">No Suites Match Your Criteria</h3>
        <p style="margin-top: 4px; font-size: 13.5px;">Try adjusting your suite category filter or search query.</p>
      </div>
    `;
    return;
  }

  const nights = guestFilters.nights;
  const nightsText = `${nights} ${nights === 1 ? 'Night' : 'Nights'}`;

  rooms.forEach(room => {
    const card = document.createElement("div");
    card.className = "room-card-luxury";

    const totalCost = (room.pricePerNight * nights).toFixed(2);
    const photoUrl = getRoomPhoto(room.roomType, room.roomNumber);

    // Pluralization logic: "Up to 1 Guest" vs "Up to 2 Guests"
    const guestCapText = `Up to ${room.capacity} ${room.capacity === 1 ? 'Guest' : 'Guests'}`;

    let statusCls = "available";
    let statusTxt = "Available";
    if (room.status === "OCCUPIED") {
      statusCls = "occupied";
      statusTxt = `Occupied (${room.currentGuest || "Guest"})`;
    } else if (room.status === "MAINTENANCE") {
      statusCls = "maintenance";
      statusTxt = "Maintenance";
    } else if (room.housekeepingStatus === "CLEANING") {
      statusCls = "cleaning";
      statusTxt = "Cleaning In Progress";
    }

    const amenitiesHtml = room.amenities.map(a => `<span class="amenity-chip">${getSvgIcon("check", 11)} ${a}</span>`).join("");

    let actionBtnHtml = "";
    if (room.status === "AVAILABLE" && room.housekeepingStatus === "READY") {
      actionBtnHtml = `<button class="btn btn-luxury btn-sm" onclick="window.handleRoomAction(${room.roomNumber})">Reserve Suite</button>`;
    } else {
      actionBtnHtml = `<button class="btn btn-outline btn-sm" onclick="window.handleRoomAction(${room.roomNumber})">View Suite</button>`;
    }

    card.innerHTML = `
      <div class="card-photo-banner">
        <img class="card-photo-img" src="${photoUrl}" alt="Suite ${room.roomNumber}" loading="lazy">
        <div class="card-photo-scrim"></div>
        <span class="photo-badge-tier">${room.roomType} SUITE</span>
        <span class="photo-badge-floor">Floor ${room.floor}</span>
      </div>

      <div class="card-body-content">
        <div class="card-header-row">
          <div>
            <h3 class="room-suite-title font-serif">Suite ${room.roomNumber}</h3>
            <div class="room-details-line">
              <span>${getSvgIcon("bed", 13)} ${room.bedType} Bed</span> &bull;
              <span>${getSvgIcon("users", 13)} ${guestCapText}</span>
            </div>
          </div>
          <span class="status-pill ${statusCls}">
            <span style="width: 6px; height: 6px; border-radius: 50%; background: currentColor;"></span>
            ${statusTxt}
          </span>
        </div>

        <div class="amenities-tag-group">
          ${amenitiesHtml}
        </div>
      </div>

      <div class="card-footer-luxury">
        <div class="price-lockup">
          <div class="price-num-row">
            <span class="price-curr-sign">$</span>
            <span class="price-big-text">${room.pricePerNight.toFixed(0)}</span>
            <span class="price-per-text">/ night</span>
          </div>
          <div class="price-total-sub">${nightsText} Total: $${totalCost}</div>

          <!-- Interactive Tooltip Breakdown -->
          <div class="price-tooltip-popover">
            <strong>Transparent Price Calculation:</strong><br>
            $${room.pricePerNight.toFixed(2)} &times; ${nightsText} = <strong>$${totalCost}</strong><br>
            <span style="color: var(--text-muted); font-size: 10.5px;">All resort fees, high-speed WiFi, and breakfast included.</span>
          </div>
        </div>

        ${actionBtnHtml}
      </div>
    `;

    container.appendChild(card);
  });
}

function renderMyBookingsPortal() {
  guestPortal.classList.add("active");
  const guestUser = engine.currentUser?.username || "john_doe";
  const myRooms = engine.rooms.filter(r => r.status === "OCCUPIED" && r.currentGuest === guestUser);
  const myTxns = engine.transactions.filter(t => t.guest === guestUser);

  const container = document.getElementById("guestMainContent");
  container.innerHTML = `
    <div style="margin-top: 10px;">
      <h2 class="font-serif" style="font-size: 24px; margin-bottom: 4px;">My Active Reservations & Folio</h2>
      <p style="color: var(--text-secondary); margin-bottom: 24px; font-size: 13.5px;">Active suite bookings and historical reservation records for ${engine.currentUser?.fullName || guestUser}.</p>
      
      <div id="myActiveCards" class="rooms-grid" style="margin-bottom: 32px;"></div>

      <div class="data-table-card">
        <div class="table-toolbar">
          <div style="font-weight: 700; font-size: 16px;">Billing History & Reservation Ledger</div>
        </div>
        <div class="table-responsive">
          <table class="luxury-table">
            <thead>
              <tr>
                <th>Txn ID</th>
                <th>Suite #</th>
                <th>Stay Duration</th>
                <th>Nightly Rate</th>
                <th>Total Billed</th>
                <th>Timestamp</th>
                <th>Status</th>
              </tr>
            </thead>
            <tbody>
              ${myTxns.map(t => `
                <tr>
                  <td><strong>${t.id}</strong></td>
                  <td>Suite ${t.roomNumber}</td>
                  <td>${t.nights} ${t.nights === 1 ? 'Night' : 'Nights'}</td>
                  <td>$${t.rate.toFixed(2)}</td>
                  <td><strong style="color: var(--accent);">$${t.total.toFixed(2)}</strong></td>
                  <td>${t.timestamp}</td>
                  <td><span class="status-pill ${t.status === 'ACTIVE' ? 'occupied' : 'available'}">${t.status}</span></td>
                </tr>
              `).join("")}
            </tbody>
          </table>
        </div>
      </div>
    </div>
  `;

  const activeGrid = document.getElementById("myActiveCards");
  if (myRooms.length === 0) {
    activeGrid.innerHTML = `
      <div style="grid-column: 1 / -1; padding: 30px; background: var(--bg-surface); border: 1px solid var(--border-subtle); border-radius: var(--radius-md); text-align: center;">
        <p style="color: var(--text-muted); font-size: 13.5px;">You currently have no active room reservations.</p>
        <button class="btn btn-luxury btn-sm" style="margin-top: 10px;" onclick="switchPortal('guest')">Browse Available Suites</button>
      </div>
    `;
  } else {
    myRooms.forEach(r => {
      const card = document.createElement("div");
      card.className = "room-card-luxury";
      const total = (r.pricePerNight * r.bookedNights).toFixed(2);
      const photoUrl = getRoomPhoto(r.roomType, r.roomNumber);
      card.innerHTML = `
        <div class="card-photo-banner" style="height: 140px;">
          <img class="card-photo-img" src="${photoUrl}" alt="Suite ${r.roomNumber}">
          <div class="card-photo-scrim"></div>
          <span class="photo-badge-tier">${r.roomType} SUITE</span>
          <span class="photo-badge-floor">Floor ${r.floor}</span>
        </div>
        <div class="card-body-content" style="padding: 18px;">
          <div class="card-header-row">
            <div>
              <h3 class="room-suite-title font-serif">Suite ${r.roomNumber}</h3>
              <div style="font-size: 12.5px; color: var(--text-muted); margin-top: 2px;">Check-In: ${r.checkInDate || "Active"} (${r.bookedNights} ${r.bookedNights === 1 ? 'Night' : 'Nights'})</div>
            </div>
            <span class="status-pill occupied">🟢 Confirmed Stay</span>
          </div>
          <div class="bill-calc-card" style="margin-top: 10px;">
            <div class="bill-line"><span>Rate:</span><span>$${r.pricePerNight.toFixed(2)} / night</span></div>
            <div class="bill-line"><span>Duration:</span><span>${r.bookedNights} ${r.bookedNights === 1 ? 'Night' : 'Nights'}</span></div>
            <div class="bill-line grand-total"><span>Total Due:</span><span style="color: var(--accent);">$${total}</span></div>
          </div>
        </div>
      `;
      activeGrid.appendChild(card);
    });
  }
}

/* ==========================================================================
   2. STAFF PORTAL
   ========================================================================== */
function renderStaffPortal() {
  const m = engine.getMetrics();
  document.getElementById("staffCountCleaning").textContent = m.cleaning;
  document.getElementById("staffCountReady").textContent = m.available;
  document.getElementById("staffCountOccupied").textContent = m.occupied;
  document.getElementById("staffCountMaintenance").textContent = m.maintenance;

  const queueRooms = engine.rooms.filter(r => r.housekeepingStatus === "CLEANING" || r.housekeepingStatus === "NEEDS_INSPECTION" || r.status === "MAINTENANCE");
  const queueGrid = document.getElementById("staffHousekeepingGrid");
  queueGrid.innerHTML = "";

  if (queueRooms.length === 0) {
    queueGrid.innerHTML = `
      <div style="grid-column: 1 / -1; padding: 36px; background: var(--bg-surface); border: 1px solid var(--border-subtle); border-radius: var(--radius-md); text-align: center;">
        <span style="font-size: 28px;">${getSvgIcon("sparkles", 32)}</span>
        <h4 class="font-serif" style="margin-top: 8px; font-size: 18px;">All Suites Cleaned & Ready</h4>
        <p style="color: var(--text-muted); font-size: 13px; margin-top: 2px;">No rooms currently require housekeeping attention.</p>
      </div>
    `;
  } else {
    queueRooms.forEach(room => {
      const card = document.createElement("div");
      card.className = "task-card";

      let statusCls = room.housekeepingStatus === "CLEANING" ? "cleaning" : room.status === "MAINTENANCE" ? "maintenance" : "occupied";
      let statusLabel = room.housekeepingStatus === "CLEANING" ? "Cleaning In Progress" : room.status === "MAINTENANCE" ? "Maintenance" : "Needs Inspection";

      card.innerHTML = `
        <div style="display: flex; align-items: center; justify-content: space-between;">
          <div>
            <div style="font-weight: 700; font-size: 16px;">Suite ${room.roomNumber}</div>
            <span style="font-size: 12px; color: var(--text-muted);">${room.roomType} &bull; Floor ${room.floor}</span>
          </div>
          <span class="status-pill ${statusCls}">${statusLabel}</span>
        </div>

        <div style="font-size: 12.5px; color: var(--text-secondary);">
          Amenities: ${room.amenities.slice(0, 3).join(", ")}...
        </div>

        <div style="display: flex; gap: 8px; margin-top: 4px;">
          <button class="btn btn-luxury btn-sm" style="flex: 1;" onclick="window.staffMarkReady(${room.roomNumber})">
            ${getSvgIcon("check", 13)} Mark Clean & Ready
          </button>
          <button class="btn btn-outline btn-sm" onclick="window.handleRoomAction(${room.roomNumber})">
            Details
          </button>
        </div>
      `;
      queueGrid.appendChild(card);
    });
  }

  const occupiedRooms = engine.rooms.filter(r => r.status === "OCCUPIED");
  const checkoutTbody = document.querySelector("#staffCheckoutTable tbody");
  checkoutTbody.innerHTML = "";

  if (occupiedRooms.length === 0) {
    checkoutTbody.innerHTML = `<tr><td colspan="7" style="text-align: center; color: var(--text-muted); padding: 24px;">No guests currently due for check-out.</td></tr>`;
  } else {
    occupiedRooms.forEach(r => {
      const bill = (r.pricePerNight * r.bookedNights).toFixed(2);
      const tr = document.createElement("tr");
      tr.innerHTML = `
        <td><strong>Suite ${r.roomNumber}</strong></td>
        <td>${r.currentGuest || "Guest"}</td>
        <td>${r.checkInDate || "Today"}</td>
        <td>${r.bookedNights} ${r.bookedNights === 1 ? 'Night' : 'Nights'}</td>
        <td>$${r.pricePerNight.toFixed(2)}</td>
        <td><strong style="color: var(--accent);">$${bill}</strong></td>
        <td>
          <button class="btn btn-luxury btn-sm" onclick="window.processStaffCheckout(${r.roomNumber})">
            Settle & Check-Out
          </button>
        </td>
      `;
      checkoutTbody.appendChild(tr);
    });
  }
}

window.staffMarkReady = function(roomNumber) {
  if (engine.setHousekeeping(roomNumber, "READY")) {
    showToast(`Suite ${roomNumber} marked as CLEAN & READY for guests`, "success");
    renderStaffPortal();
  }
};

window.processStaffCheckout = function(roomNumber) {
  const receipt = engine.checkOut(roomNumber);
  if (receipt) {
    showReceiptModal(receipt);
    renderStaffPortal();
    showToast(`Suite ${roomNumber} checked out. Room set to CLEANING queue.`, "success");
  }
};

/* ==========================================================================
   3. ADMIN PORTAL
   ========================================================================== */
function renderAdminPortal() {
  const m = engine.getMetrics();
  document.getElementById("adminKpiOccupancy").textContent = `${m.occupancyRate}%`;
  document.getElementById("adminKpiOccupancySub").textContent = `${m.occupied} of ${m.total} rooms occupied`;
  document.getElementById("adminKpiRevenue").textContent = `$${m.revenue.toFixed(2)}`;
  document.getElementById("adminKpiAdr").textContent = `$${m.avgPrice}`;
  document.getElementById("adminKpiTotalRooms").textContent = m.total;
  document.getElementById("adminKpiAvailSub").textContent = `${m.available} Ready for guests`;

  renderAdminRoomsTable();
  renderAdminTransactionsTable();
}

function renderAdminRoomsTable(filterQuery = "") {
  const tbody = document.querySelector("#adminRoomsTable tbody");
  tbody.innerHTML = "";

  let list = [...engine.rooms];
  if (filterQuery) {
    list = list.filter(r => r.roomNumber.toString().includes(filterQuery) || r.roomType.toLowerCase().includes(filterQuery.toLowerCase()) || r.currentGuest.toLowerCase().includes(filterQuery.toLowerCase()));
  }

  list.forEach(r => {
    const tr = document.createElement("tr");
    tr.innerHTML = `
      <td><strong>${r.roomNumber}</strong></td>
      <td>Floor ${r.floor}</td>
      <td><span class="photo-badge-tier" style="position: static; font-size: 10px; padding: 2px 7px;">${r.roomType}</span></td>
      <td>${r.bedType}</td>
      <td>${r.capacity} ${r.capacity === 1 ? 'Guest' : 'Guests'}</td>
      <td><strong>$${r.pricePerNight.toFixed(2)}</strong></td>
      <td><span class="status-pill ${r.status.toLowerCase()}">${r.status}</span></td>
      <td><span class="status-pill ${r.housekeepingStatus === 'READY' ? 'available' : 'cleaning'}">${r.housekeepingStatus}</span></td>
      <td>${r.currentGuest || "-"}</td>
      <td>
        <div style="display: flex; gap: 4px;">
          <button class="btn btn-outline btn-sm" onclick="window.openRoomEditModal(${r.roomNumber})">
            ${getSvgIcon("edit", 12)} Edit
          </button>
          <button class="btn btn-outline btn-sm" style="color: var(--status-maintenance);" onclick="window.adminDeleteRoomPrompt(${r.roomNumber})">
            ${getSvgIcon("trash", 12)}
          </button>
        </div>
      </td>
    `;
    tbody.appendChild(tr);
  });
}

function renderAdminTransactionsTable() {
  const tbody = document.querySelector("#adminTxnTable tbody");
  tbody.innerHTML = "";

  engine.transactions.forEach(t => {
    const tr = document.createElement("tr");
    tr.innerHTML = `
      <td><strong>${t.id}</strong></td>
      <td>Suite ${t.roomNumber}</td>
      <td>${t.guest}</td>
      <td>${t.nights} ${t.nights === 1 ? 'Night' : 'Nights'}</td>
      <td>$${t.rate.toFixed(2)}</td>
      <td><strong style="color: var(--accent);">$${t.total.toFixed(2)}</strong></td>
      <td>${t.timestamp}</td>
      <td><span class="status-pill ${t.status === 'ACTIVE' ? 'occupied' : 'available'}">${t.status}</span></td>
    `;
    tbody.appendChild(tr);
  });
}

window.openRoomEditModal = function(roomNumber) {
  roomBeingEdited = roomNumber ? engine.getRoom(roomNumber) : null;
  const title = document.getElementById("roomEditModalTitle");
  const saveBtn = document.getElementById("roomEditModalSaveBtn");

  if (roomBeingEdited) {
    title.textContent = `Edit Suite ${roomBeingEdited.roomNumber}`;
    saveBtn.textContent = "Save Changes";
    document.getElementById("modalRoomNum").value = roomBeingEdited.roomNumber;
    document.getElementById("modalRoomNum").disabled = true;
    document.getElementById("modalFloor").value = roomBeingEdited.floor;
    document.getElementById("modalRoomType").value = roomBeingEdited.roomType;
    document.getElementById("modalBedType").value = roomBeingEdited.bedType;
    document.getElementById("modalCapacity").value = roomBeingEdited.capacity;
    document.getElementById("modalPrice").value = roomBeingEdited.pricePerNight;
    document.getElementById("modalAmenities").value = roomBeingEdited.amenities.join(";");
  } else {
    title.textContent = "Add New Room to Inventory";
    saveBtn.textContent = "Create Room";
    document.getElementById("modalRoomNum").value = "";
    document.getElementById("modalRoomNum").disabled = false;
    document.getElementById("modalFloor").value = 1;
    document.getElementById("modalRoomType").value = "STANDARD";
    document.getElementById("modalBedType").value = "DOUBLE";
    document.getElementById("modalCapacity").value = 2;
    document.getElementById("modalPrice").value = 85.0;
    document.getElementById("modalAmenities").value = "Smart TV;AC;WiFi;Breakfast";
  }

  roomEditModal.classList.add("active");
};

function closeRoomEditModal() {
  roomEditModal.classList.remove("active");
  roomBeingEdited = null;
}

window.adminDeleteRoomPrompt = function(roomNumber) {
  const r = engine.getRoom(roomNumber);
  if (!r) return;
  if (r.status === "OCCUPIED") {
    showToast(`Cannot delete Suite ${roomNumber} while occupied by guest ${r.currentGuest}.`, "error");
    return;
  }
  if (confirm(`Permanently delete Suite ${roomNumber} from CSV database?`)) {
    engine.deleteRoom(roomNumber);
    showToast(`Suite ${roomNumber} removed from inventory`, "success");
    renderAdminPortal();
  }
};

/* ==========================================================================
   4. FLOOR MATRIX
   ========================================================================== */
function renderMatrixPortal() {
  const container = document.getElementById("matrixFloorsContainer");
  container.innerHTML = "";

  for (let floor = 3; floor >= 1; --floor) {
    const floorRooms = engine.rooms.filter(r => r.floor === floor).sort((a, b) => a.roomNumber - b.roomNumber);

    const card = document.createElement("div");
    card.className = "floor-card-box";

    let tilesHtml = "";
    floorRooms.forEach(room => {
      let statusCls = room.status === "AVAILABLE" ? (room.housekeepingStatus === "READY" ? "available" : "cleaning") : (room.status === "OCCUPIED" ? "occupied" : "maintenance");
      let statusTxt = room.status === "OCCUPIED" ? "Occupied" : room.housekeepingStatus === "CLEANING" ? "Cleaning" : room.status === "MAINTENANCE" ? "Maint." : "Ready";

      tilesHtml += `
        <div class="floor-tile ${statusCls}" onclick="window.handleRoomAction(${room.roomNumber})">
          <div style="font-size: 16px; font-weight: 800;">${room.roomNumber}</div>
          <div style="font-size: 10px; font-weight: 700; text-transform: uppercase; color: var(--text-muted);">${room.roomType}</div>
          <div style="font-size: 11px; font-weight: 600;">${statusTxt}</div>
        </div>
      `;
    });

    card.innerHTML = `
      <div style="display: flex; align-items: center; justify-content: space-between; margin-bottom: 14px;">
        <h3 class="font-serif" style="font-size: 17px;">Floor Level ${floor} Matrix</h3>
        <span style="font-size: 12px; color: var(--text-muted);">${floorRooms.length} Suites</span>
      </div>
      <div class="floor-grid-tiles">
        ${tilesHtml}
      </div>
    `;

    container.appendChild(card);
  }
}

/* ==========================================================================
   5. SLIDING SIDE DRAWER
   ========================================================================== */
window.handleRoomAction = function(roomNumber) {
  const room = engine.getRoom(roomNumber);
  if (!room) return;
  openDrawer(room);
};

function openDrawer(room) {
  selectedRoomForDrawer = room;
  document.getElementById("drawerHeading").textContent = `Suite ${room.roomNumber}`;
  document.getElementById("drawerSubheading").textContent = `${room.roomType} Suite &bull; Level ${room.floor}`;

  const body = document.getElementById("drawerBody");
  const footer = document.getElementById("drawerFooter");
  const nights = guestFilters.nights;
  const total = (room.pricePerNight * nights).toFixed(2);
  const photoUrl = getRoomPhoto(room.roomType, room.roomNumber);

  const amenitiesHtml = room.amenities.map(a => `<span class="amenity-chip">${getSvgIcon("check", 11)} ${a}</span>`).join(" ");

  let bodyHtml = `
    <div style="border-radius: var(--radius-md); overflow: hidden; height: 160px; position: relative;">
      <img src="${photoUrl}" alt="Suite ${room.roomNumber}" style="width: 100%; height: 100%; object-fit: cover;">
      <div class="card-photo-scrim"></div>
      <span class="photo-badge-tier">${room.roomType}</span>
    </div>

    <div>
      <div style="font-size: 10.5px; font-weight: 700; text-transform: uppercase; color: var(--text-muted); margin-bottom: 6px;">Suite Specifications</div>
      <div style="display: grid; grid-template-columns: 1fr 1fr; gap: 8px; background: var(--bg-surface-subtle); padding: 12px; border-radius: var(--radius-md); border: 1px solid var(--border-subtle); font-size: 13px;">
        <div><strong>Floor:</strong> Level ${room.floor}</div>
        <div><strong>Bed:</strong> ${room.bedType}</div>
        <div><strong>Capacity:</strong> ${room.capacity} ${room.capacity === 1 ? 'Guest' : 'Guests'}</div>
        <div><strong>Rate:</strong> $${room.pricePerNight.toFixed(2)} / night</div>
      </div>
    </div>

    <div>
      <div style="font-size: 10.5px; font-weight: 700; text-transform: uppercase; color: var(--text-muted); margin-bottom: 6px;">Included Amenities</div>
      <div style="display: flex; flex-wrap: wrap; gap: 5px;">${amenitiesHtml}</div>
    </div>

    <div>
      <div style="font-size: 10.5px; font-weight: 700; text-transform: uppercase; color: var(--text-muted); margin-bottom: 6px;">Current Status</div>
      <div style="display: flex; gap: 6px;">
        <span class="status-pill ${room.status.toLowerCase()}">${room.status}</span>
        <span class="status-pill ${room.housekeepingStatus === 'READY' ? 'available' : 'cleaning'}">Housekeeping: ${room.housekeepingStatus}</span>
      </div>
    </div>
  `;

  if (room.status === "AVAILABLE" && room.housekeepingStatus === "READY") {
    bodyHtml += `
      <div>
        <div style="font-size: 10.5px; font-weight: 700; text-transform: uppercase; color: var(--text-muted); margin-bottom: 6px;">Reservation Details</div>
        <div style="display: flex; flex-direction: column; gap: 8px;">
          <div class="field-group">
            <label class="field-label" for="drawerGuestName">Guest Full Name</label>
            <input type="text" id="drawerGuestName" class="field-input" value="${engine.currentUser?.fullName || 'Johnathan Doe'}">
          </div>
          <div class="field-group">
            <label class="field-label" for="drawerStayNights">Number of Nights</label>
            <input type="number" id="drawerStayNights" class="field-input" min="1" max="30" value="${nights}">
          </div>
        </div>
      </div>

      <div class="bill-calc-card">
        <div class="bill-line"><span>Nightly Rate:</span><span>$${room.pricePerNight.toFixed(2)}</span></div>
        <div class="bill-line"><span>Length of Stay:</span><span id="drawerNightsLabel">${nights} ${nights === 1 ? 'Night' : 'Nights'}</span></div>
        <div class="bill-line grand-total"><span>Total Bill:</span><span id="drawerTotalLabel" style="color: var(--accent);">$${total}</span></div>
      </div>
    `;

    footer.innerHTML = `
      <button class="btn btn-luxury" onclick="window.confirmDrawerBooking(${room.roomNumber})">Confirm Reservation & Check-In</button>
    `;
  } else if (room.status === "OCCUPIED") {
    const accBill = (room.pricePerNight * room.bookedNights).toFixed(2);
    bodyHtml += `
      <div>
        <div style="font-size: 10.5px; font-weight: 700; text-transform: uppercase; color: var(--text-muted); margin-bottom: 6px;">Active Guest Stay</div>
        <div style="background: var(--bg-surface-subtle); padding: 12px; border-radius: var(--radius-md); border: 1px solid var(--border-subtle); font-size: 13px; display: flex; flex-direction: column; gap: 5px;">
          <div><strong>Guest:</strong> ${room.currentGuest}</div>
          <div><strong>Check-In:</strong> ${room.checkInDate || "Today"}</div>
          <div><strong>Duration:</strong> ${room.bookedNights} ${room.bookedNights === 1 ? 'Night' : 'Nights'}</div>
          <div style="margin-top: 4px; padding-top: 4px; border-top: 1px dashed var(--border-subtle);"><strong>Accumulated Bill:</strong> <strong style="color: var(--accent);">$${accBill}</strong></div>
        </div>
      </div>
    `;

    if (engine.currentUser?.role === "ADMIN" || engine.currentUser?.role === "STAFF") {
      footer.innerHTML = `
        <button class="btn btn-luxury" onclick="window.processStaffCheckout(${room.roomNumber})">Process Check-Out ($${accBill})</button>
      `;
    } else {
      footer.innerHTML = `<div style="text-align: center; font-size: 12px; color: var(--text-muted);">This suite is currently occupied by a guest.</div>`;
    }
  } else {
    bodyHtml += `
      <div>
        <div style="font-size: 10.5px; font-weight: 700; text-transform: uppercase; color: var(--text-muted); margin-bottom: 6px;">Staff Action Controls</div>
        <div style="display: flex; flex-direction: column; gap: 8px;">
          <button class="btn btn-outline btn-sm" onclick="window.staffMarkReady(${room.roomNumber}); window.closeDrawer();">
            ${getSvgIcon("check", 13)} Mark CLEAN & READY
          </button>
          <button class="btn btn-outline btn-sm" onclick="engine.setHousekeeping(${room.roomNumber}, 'CLEANING'); openDrawer(engine.getRoom(${room.roomNumber})); showToast('Set to cleaning', 'info');">
            ${getSvgIcon("broom", 13)} Set to CLEANING
          </button>
        </div>
      </div>
    `;
    footer.innerHTML = `<button class="btn btn-outline" onclick="window.closeDrawer()">Close Drawer</button>`;
  }

  body.innerHTML = bodyHtml;

  const nightsInp = document.getElementById("drawerStayNights");
  if (nightsInp) {
    nightsInp.addEventListener("input", (e) => {
      const n = Math.max(1, parseInt(e.target.value) || 1);
      const sub = (room.pricePerNight * n).toFixed(2);
      document.getElementById("drawerNightsLabel").textContent = `${n} ${n === 1 ? 'Night' : 'Nights'}`;
      document.getElementById("drawerTotalLabel").textContent = `$${sub}`;
    });
  }

  sideDrawer.classList.add("active");
  drawerBackdrop.classList.add("active");
}

function closeDrawer() {
  sideDrawer.classList.remove("active");
  drawerBackdrop.classList.remove("active");
  selectedRoomForDrawer = null;
}

window.confirmDrawerBooking = function(roomNumber) {
  const name = document.getElementById("drawerGuestName")?.value.trim() || "Guest";
  const nights = parseInt(document.getElementById("drawerStayNights")?.value) || 1;

  const res = engine.checkIn(roomNumber, name, nights);
  if (res && res.success) {
    showToast(`Suite ${roomNumber} confirmed for ${name}! Folio: ${res.txnId}`, "success");
    closeDrawer();
    renderCurrentPortal();
  } else {
    showToast("Unable to complete reservation.", "error");
  }
};

/* ==========================================================================
   6. BILL RECEIPT FOLIO MODAL
   ========================================================================== */
function showReceiptModal(folio) {
  receiptBody.innerHTML = `
    <div style="text-align: center; border-bottom: 1px dashed var(--border-subtle); padding-bottom: 14px;">
      <h4 class="font-serif" style="font-size: 19px;">Grand Horizon Resort</h4>
      <p style="font-size: 12px; color: var(--text-muted);">Official Guest Billing Statement</p>
    </div>
    <div style="display: flex; flex-direction: column; gap: 7px; font-size: 13px; margin: 14px 0;">
      <div style="display: flex; justify-content: space-between;"><span>Guest Name:</span><strong>${folio.guest}</strong></div>
      <div style="display: flex; justify-content: space-between;"><span>Suite Number:</span><strong>Suite ${folio.roomNumber}</strong></div>
      <div style="display: flex; justify-content: space-between;"><span>Stay Period:</span><span>${folio.checkInDate || 'Today'} to ${folio.checkOutDate}</span></div>
      <div style="display: flex; justify-content: space-between;"><span>Total Duration:</span><span>${folio.nights} ${folio.nights === 1 ? 'Night' : 'Nights'}</span></div>
      <div style="display: flex; justify-content: space-between;"><span>Nightly Rate:</span><span>$${folio.rate.toFixed(2)}</span></div>
      <div style="display: flex; justify-content: space-between; border-top: 1px solid var(--border-subtle); padding-top: 7px; font-size: 15px;">
        <strong>Total Settled:</strong>
        <strong style="color: var(--accent);">$${folio.total.toFixed(2)}</strong>
      </div>
    </div>
    <div style="font-size: 11px; text-align: center; color: var(--text-muted);">
      Payment settled via Front Desk. Thank you for staying with us!
    </div>
  `;
  receiptModal.classList.add("active");
}

function closeReceiptModal() {
  receiptModal.classList.remove("active");
}

window.printReceipt = function() {
  window.print();
};

/* ==========================================================================
   7. AUTH MODAL HELPERS
   ========================================================================== */
window.openAuthModal = function() {
  authModal.classList.add("active");
};

function closeAuthModal() {
  authModal.classList.remove("active");
}

/* ==========================================================================
   8. TOAST NOTIFICATIONS
   ========================================================================== */
function showToast(msg, type = "info") {
  const toast = document.createElement("div");
  toast.className = `toast-pill ${type}`;
  toast.innerHTML = `
    <span>${type === 'success' ? getSvgIcon("check", 14) : type === 'error' ? getSvgIcon("alert", 14) : getSvgIcon("sparkles", 14)}</span>
    <span>${msg}</span>
  `;
  toastsHub.appendChild(toast);

  setTimeout(() => {
    toast.style.opacity = "0";
    toast.style.transform = "translateX(30px)";
    setTimeout(() => toast.remove(), 300);
  }, 3500);
}
