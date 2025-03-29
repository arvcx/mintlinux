# 🚀 MintServer on Linux

A lightweight server solution built with performance in mind.  
This guide explains how to set up and run **MintServer** on a modern Linux system (we recommend using the latest Debian, Ubuntu, CentOS, or AlmaLinux).

---

## Prerequisites

- A clean installation of [Debian](https://www.debian.org/), [Ubuntu](https://ubuntu.com/), [CentOS](https://www.centos.org/), or [AlmaLinux](https://almalinux.org/)
- Sudo or root privileges
- Basic knowledge of using the terminal

---

## Description

MintServer is a high-performance, lightweight server solution designed for modern Linux systems. It is optimized for speed and efficiency, making it an ideal choice for developers and system administrators looking for a reliable server setup.

---

## Setup Instructions

### 🐧 Debian/Ubuntu

Follow these steps to install the required dependencies and run the application on Debian or Ubuntu:

1. **Update & Upgrade Your System**

   Open your terminal and update your package lists, then upgrade your installed packages:

   ```bash
   sudo apt update && sudo apt upgrade
   ```

2. **Install the Libraries**

   ```bash
   sudo apt install libenet-dev libfmt-dev nlohmann-json3-dev
   ```

3. **Run the App**

   ```bash
   cd Release
   ./MintServer
   ```

### 🐱‍💻 CentOS/AlmaLinux

Follow these steps to install the required dependencies and run the application on CentOS or AlmaLinux:

1. **Update & Upgrade Your System**

   Open your terminal and update your package lists, then upgrade your installed packages:

   ```bash
   sudo yum update && sudo yum upgrade
   ```

2. **Install the Libraries**

   ```bash
   sudo yum install epel-release
   sudo yum install enet-devel fmt-devel nlohmann-json-devel
   ```

3. **Run the App**

   ```bash
   cd Release
   ./MintServer
   ```

---

Enjoy your high-performance server setup with MintServer! 🎉
