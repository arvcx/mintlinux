# CrossMint on Linux

A lightweight server solution built with performance in mind.  
This guide explains how to set up and run **CrossMint** on a modern Linux system
(we recommend using the latest Debian or Ubuntu).

---

## Prerequisites

- A clean installation of [Debian](https://www.debian.org/) or [Ubuntu](https://ubuntu.com/)
- Sudo or root privileges
- Basic knowledge of using the terminal

---

## Linux Setup

Follow these steps to install the required dependencies and run the application:

1. **Update & Upgrade Your System**

   Open your terminal and update your package lists, then upgrade your installed packages:

   ```bash
   sudo apt update && sudo apt upgrade
   ```
2. **Install the Library***

   ```bash
   sudo apt install libenet-dev libfmt-dev nlohmann-json3-dev
   ```
   
3. **Run the app**

   ```bash
   cd Release
   ./CrossMint
   ```
   
