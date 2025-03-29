#pragma once
#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace NetworkUtils {
    size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
        size_t totalSize = size * nmemb;
        output->append((char*)contents, totalSize);
        return totalSize;
    }

    std::string getClientLocation(const std::string& ipAddress) {
        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            std::string url = "http://ip-api.com/json/" + ipAddress;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res == CURLE_OK) {
                try {
                    json data = json::parse(readBuffer);
                    if (data["status"] == "success") {
                        return "IP: " + ipAddress + " | Country: " + data["country"].get<std::string>() +
                               " | City: " + data["city"].get<std::string>() +
                               " | ISP: " + data["isp"].get<std::string>();
                    } else {
                        return "Failed to get location for IP: " + ipAddress;
                    }
                } catch (const std::exception& e) {
                    return "[ERROR] JSON Parsing Error";
                }
            } else {
                return "[ERROR] Failed to fetch data from API";
            }
        }
        return "[ERROR] cURL initialization failed";
    }
    std::string getLoc(const std::string& ipAddress) {
        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            std::string url = "http://ip-api.com/json/" + ipAddress;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res == CURLE_OK) {
                try {
                    json data = json::parse(readBuffer);
                    if (data["status"] == "success") {
                        return "Country: " + data["country"].get<std::string>() + " - City: " + data["city"].get<std::string>();
                    } else {
                        return "Failed to get location for IP: " + ipAddress;
                    }
                } catch (const std::exception& e) {
                    return "[ERROR] JSON Parsing Error";
                }
            } else {
                return "[ERROR] Failed to fetch data from API";
            }
        }
        return "[ERROR] cURL initialization failed";
    }
}