#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <array>
#include <sstream>
#include <cctype>
//#include <format>
#include "../include/base64.hpp"
const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

bool isValidBase64(const std::string& input) {
    if (input.length() % 4 != 0) return false;
    for (char c : input) {
        if (!isalnum(c) && c != '+' && c != '/' && c != '=') {
            return false;
        }
    }
    return true;
}
namespace GrowTopia {
	class Parser {
		std::vector<std::pair<std::string, std::string>> contents;
	public:
		Parser(std::string const& str) {
			for (std::string const& line : explode("\n", str)) {
				std::vector<std::string> lineContents = explode("|", line);
				if (lineContents.size() < 2) continue;
				contents.emplace_back(lineContents[0], lineContents[1]);
			}
		}
		std::pair<std::string, std::string> get_value_starts_with(std::string const& key) {
			for (auto const& [contentKey, value] : contents) {
				if (contentKey.starts_with(key)) return { contentKey, value };
			}
			return {};
		}
		std::string get_value(std::string const& key) {
			for (auto const& [contentKey, value] : contents) {
				if (contentKey == key) return value;
			}
			return "";
		}
	};
	class HandleReturnParser {
		std::vector<std::pair<std::string, std::string>> contents;
	public:
		HandleReturnParser(std::string const& str) {
			for (std::string const& line : explode("\\n", str)) {
				std::vector<std::string> lineContents = explode("|", line);
				if (lineContents.size() < 2) continue;
				contents.emplace_back(lineContents[0], lineContents[1]);
			}
		}
		std::pair<std::string, std::string> get_value_starts_with(std::string const& key) {
			for (auto const& [contentKey, value] : contents) {
				if (contentKey.starts_with(key)) return { contentKey, value };
			}
			return {};
		}
		std::string get_value(std::string const& key) {
			for (auto const& [contentKey, value] : contents) {
				if (contentKey == key) return value;
			}
			return "";
		}
	};
	std::string getValue(const std::string& str, const std::string& key) {
		std::string searchKey = key + "=";
		size_t startPos = str.find(searchKey);
		if (startPos != std::string::npos) {
			startPos += searchKey.length(); 
			size_t endPos = str.find('&', startPos); 
			if (endPos == std::string::npos) {
				endPos = str.length(); 
			}
			return str.substr(startPos, endPos - startPos); 
		}
		return ""; 
	}
	std::string GetContents(ENetPeer* peer, std::string const& cch) {
		std::string content = "";
		vector<string> result_token = explode("|", cch);
		vector<string> line_parts = explode("\n", result_token[2]);
		string token = line_parts[0];
		if (isValidBase64(token)) {
			auto const decoded_token = base64::from_base64(token);
			std::string token_ = getValue(decoded_token, "_token");
			std::string user = getValue(decoded_token, "growId");
			std::string pass = getValue(decoded_token, "password");
			//Logger::Info("INFO", "Encode 'ltoken': [" + decoded_token + "] GrowID: [" + user + "] Password: [" + pass + "]");
			//Logger::Info("INFO", "Encode '_token' from 'ltoken': [" + token_ + "]");
			if (user == "Netro" and pass == "Netro") {
				pInfo(peer)->is_guest = true;
			}
			if (decoded_token.empty()) return "";
			try {
				content.append("tankIDName|" + user + "|\n");
				content.append("tankIDPass|" + pass + "|\n");
				content.append(token_ + "|\n");
			}
			catch (std::exception&) { return ""; }
			return content;
		}
		else return "";
	}
}