# 🏨 Hotel Management System (Demo Build)

A simple and lightweight Hotel Management System with both a **Terminal UI (Console)** and a **Modern Web UI**.

---

## 🚀 Quick Start Commands

Just open your terminal in this folder and use one of the simple commands below:

### 1. Run the Web Interface (Browser)
```bash
make web
```
- Opens a local web server automatically.
- Open your browser at: **`http://localhost:8000`**
- Press `Ctrl + C` in terminal to stop.

---

### 2. Run the Terminal Interface (Console TUI)
```bash
make run
```
- Compiles the C++ core and opens the interactive console application directly in your terminal.

---

### 3. Run Automated Tests
```bash
make test
```
- Compiles and runs all unit tests for Data Structures (`DynamicArray`), Sorting (`QuickSort`), and Search algorithms.

---

### 4. Clean Build Files
```bash
make clean
```
- Deletes temporary build files and binaries.

---

## 🔑 Demo Login Accounts

You can test different user roles using these accounts (or 1-click login on the web):

| Role | Username | Password | Permissions |
| :--- | :--- | :--- | :--- |
| **👑 Admin** | `admin` | `admin123` | Full control, view revenue KPI, edit rooms |
| **💼 Staff** | `staff` | `staff123` | Housekeeping queue, check-in, check-out |
| **👤 Guest** | `guest` | `guest123` | Browse suites, check availability, book rooms |
