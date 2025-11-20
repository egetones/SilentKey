<div align="center">

# 🕷️ SilentKey

![C++](https://img.shields.io/badge/C++-Linux_Kernel-blue?style=flat&logo=c%2B%2B)
![License](https://img.shields.io/badge/License-MIT-green)
![Type](https://img.shields.io/badge/Type-Spyware_Analysis-red)

<p>
  <strong>A Proof-of-Concept Linux Keylogger interacting directly with Kernel Input Subsystem.</strong>
</p>

[Report Bug](https://github.com/your-username/silentkey/issues) · [Request Feature](https://github.com/your-username/silentkey/issues)

</div>

---

## 📖 Description

**SilentKey** is a cybersecurity research tool designed to demonstrate how input capturing works on Linux systems at the kernel level.

Instead of hooking into high-level GUI libraries (like X11 or Wayland), SilentKey reads raw `input_event` structures directly from the device files located in `/dev/input/`. This makes it independent of the desktop environment.

### Key Features

  **Kernel Level Access:** Intercepts keystrokes directly from the hardware driver.
  **File Logging:** Saves captured data to `keylog.txt`.
  **Live Monitoring:** Displays keystrokes in the terminal in real-time.
  **Device Agnostic:** Works with internal laptop keyboards and external USB keyboards.

---

## Usage

**Requirement:** You must have `root` (sudo) privileges to read from `/dev/input/`.

1. **Compile the tool:**
   ```bash
   make
   ```

2. **Find your keyboard Event ID:**
   Use the following command to list input devices:
   ```bash
   grep -E 'Name=|Handlers=' /proc/bus/input/devices
   ```
   *Look for "sysrq kbd" handlers. Common IDs are `event3` or `event4`.*

3. **Run SilentKey:**
   Replace `eventX` with your specific ID.
   ```bash
   sudo ./silentkey /dev/input/event3
   ```

4. **Check the logs:**
   The captured keystrokes are saved in the current directory:
   ```bash
   cat keylog.txt
   ```

---

## ⚠️ Disclaimer

This software is developed for **educational purposes only**. It is intended to help security researchers and students understand input handling and spyware mechanics. 
**Unauthorized use of this tool on systems you do not own is illegal.** The author is not responsible for any misuse.

---

## License

Distributed under the MIT License. See `LICENSE` for more information.
