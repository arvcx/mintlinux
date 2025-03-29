# 🚀 CrossMint on Linux

A lightweight Growtopia Private Server solution built with performance in mind.
This guide explains how to set up and run **CrossMint** on a modern Linux system (we recommend using the latest Debian, Ubuntu, CentOS, or AlmaLinux).

## Prerequisites
- 🧹 A clean installation of [Debian](https://www.debian.org/), [Ubuntu](https://ubuntu.com/), [CentOS](https://www.centos.org/), or [AlmaLinux](https://almalinux.org/)
- 🔑 Sudo or root privileges
- 🧠 Basic knowledge of using the terminal

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
   ./CrossMint
   ```

### 🐱‍💻 CentOS/AlmaLinux

Follow these steps to install the required dependencies and run the application on CentOS or AlmaLinux:

1. **Update & Upgrade Your System**

   Open your terminal and update your package lists, then upgrade your installed packages:

   ```bash
   sudo yum update && sudo yum upgrade
   ```

2. **Install the Library**

   ```bash
   sudo yum install epel-release
   sudo yum install enet-devel fmt-devel nlohmann-json-devel
   ```

3. **Run the app**

   ```bash
   cd Release
   ./MintServer
   ```

--- 

Enjoy your high-performance server setup with CrossMint! 🎉
