#pragma once
#include <chrono>
#include <fmt/core.h>
using namespace chrono;
struct gamepacket_t
{
private:
	int index = 0, len = 0;
	BYTE* packet_data = new BYTE[61];
public:
	gamepacket_t(int delay = 0, int NetID = -1) {
		len = 61;
		int MessageType = 0x4, PacketType = 0x1, CharState = 0x8;
		memset(packet_data, 0, 61);
		memcpy(packet_data, &MessageType, 4);
		memcpy(packet_data + 4, &PacketType, 4);
		memcpy(packet_data + 8, &NetID, 4);
		memcpy(packet_data + 16, &CharState, 4);
		memcpy(packet_data + 24, &delay, 4);
	};
	~gamepacket_t() {
		delete[] packet_data;
	}
	void Insert(string a) {
		BYTE* data = new BYTE[len + 2 + a.length() + 4];
		memcpy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x2;
		int str_len = (int)a.length();
		memcpy(data + len + 2, &str_len, 4);
		memcpy(data + len + 6, a.data(), str_len);
		len = len + 2 + (int)a.length() + 4;
		index++;
		if (len > 60) {
			packet_data[60] = index;
		}
		else {
			std::cerr << "Error: packet_data does not have enough space for the 61st element." << std::endl;
		}
	}
	void Insert(int a) {
		BYTE* data = new BYTE[len + 2 + 4];
		memcpy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x9;
		memcpy(data + len + 2, &a, 4);
		len = len + 2 + 4;
		index++;
		if (len > 60) {
			packet_data[60] = index;
		}
		else {
			std::cerr << "Error: packet_data does not have enough space for the 61st element." << std::endl;
		}
	}
	void Insert(unsigned int a) {
		BYTE* data = new BYTE[len + 2 + 4];
		memcpy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x5;
		memcpy(data + len + 2, &a, 4);
		len = len + 2 + 4;
		index++;
		if (len > 60) {
			packet_data[60] = index;
		}
		else {
			std::cerr << "Error: packet_data does not have enough space for the 61st element." << std::endl;
		}
	}
	void Insert(float a) {
		BYTE* data = new BYTE[len + 2 + 4];
		memcpy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x1;
		memcpy(data + len + 2, &a, 4);
		len = len + 2 + 4;
		index++;
		if (len > 60) {
			packet_data[60] = index;
		}
		else {
			std::cerr << "Error: packet_data does not have enough space for the 61st element." << std::endl;
		}
	}
	void Insert(float a, float b) {
		BYTE* data = new BYTE[len + 2 + 8];
		memcpy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x3;
		memcpy(data + len + 2, &a, 4);
		memcpy(data + len + 6, &b, 4);
		len = len + 2 + 8;
		index++;
		if (len > 60) {
			packet_data[60] = index;
		}
		else {
			std::cerr << "Error: packet_data does not have enough space for the 61st element." << std::endl;
		}
	}
	void Insert(float a, float b, float c) {
		BYTE* data = new BYTE[len + 2 + 12];
		memcpy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x4;
		memcpy(data + len + 2, &a, 4);
		memcpy(data + len + 6, &b, 4);
		memcpy(data + len + 10, &c, 4);
		len = len + 2 + 12;
		index++;
		if (len > 60) {
			packet_data[60] = index;
		}
		else {
			std::cerr << "Error: packet_data does not have enough space for the 61st element." << std::endl;
		}
	}
	void CreatePacket(ENetPeer* peer) {
		ENetPacket* packet = enet_packet_create(packet_data, len, 1);
		enet_peer_send(peer, 0, packet);
	}
};
PlayerMoving* unpackPlayerMoving(BYTE* data) {
	PlayerMoving* dataStruct = new PlayerMoving;
	memcpy(&dataStruct->packetType, data, 4);
	memcpy(&dataStruct->netID, data + 4, 4);
	memcpy(&dataStruct->characterState, data + 12, 4);
	memcpy(&dataStruct->plantingTree, data + 20, 4);
	memcpy(&dataStruct->x, data + 24, 4);
	memcpy(&dataStruct->y, data + 28, 4);
	memcpy(&dataStruct->XSpeed, data + 32, 4);
	memcpy(&dataStruct->YSpeed, data + 36, 4);
	memcpy(&dataStruct->punchX, data + 44, 4);
	memcpy(&dataStruct->punchY, data + 48, 4);
	return dataStruct;
}
BYTE* get_struct(ENetPacket* packet) {
	const unsigned int packetLenght = (unsigned int)packet->dataLength;
	BYTE* result = nullptr;
	if (packetLenght >= 0x3C) {
		BYTE* packetData = packet->data;
		result = packetData + 4;
		if (*static_cast<BYTE*>(packetData + 16) & 8) {
			if (packetLenght < (unsigned int)*reinterpret_cast<int*>(packetData + 56) + 60)
				result = nullptr;
		}
		else {
			int zero = 0;
			memcpy(packetData + 56, &zero, 4);
		}
	}
	return result;
}
void SendPacketRaw112(int a1, void* packetData, size_t packetDataSize, void* a4, ENetPeer* peer, int packetFlag) {
	ENetPacket* p;
	if (peer) {
		if (a1 == 4 && *((BYTE*)packetData + 12) & 8) {
			p = enet_packet_create(0, packetDataSize + *((DWORD*)packetData + 13) + 5, packetFlag);
			int four = 4;
			memcpy(p->data, &four, 4);
			memcpy((char*)p->data + 4, packetData, packetDataSize);
			memcpy((char*)p->data + packetDataSize + 4, a4, *((DWORD*)packetData + 13));
			enet_peer_send(peer, 0, p);
		}
		else {
			p = enet_packet_create(0, packetDataSize + 5, packetFlag);
			memcpy(p->data, &a1, 4);
			memcpy((char*)p->data + 4, packetData, packetDataSize);
			enet_peer_send(peer, 0, p);
		}
	}
	delete (char*)packetData;
}
void SendPacketRaw1(int a1, void* packetData, size_t packetDataSize, void* a4, ENetPeer* peer, int packetFlag, int delay) {
	ENetPacket* p;
	if (peer) {
		if (a1 == 4 && *((BYTE*)packetData + 12) & 8) {
			p = enet_packet_create(0, packetDataSize + *((DWORD*)packetData + 13) + 5, packetFlag);
			int four = 4;
			memcpy(p->data, &four, 4);
			memcpy((char*)p->data + 4, packetData, packetDataSize);
			memcpy((char*)p->data + packetDataSize + 4, a4, *((DWORD*)packetData + 13));
			int deathFlag = 0x19;
			memcpy(p->data + 24, &delay, 4);
			memcpy(p->data + 56, &deathFlag, 4);
			enet_peer_send(peer, 0, p);
		}
		else {
			p = enet_packet_create(0, packetDataSize + 5, packetFlag);
			memcpy(p->data, &a1, 4);
			memcpy((char*)p->data + 4, packetData, packetDataSize);
			int deathFlag = 0x19;
			memcpy(p->data + 24, &delay, 4);
			memcpy(p->data + 56, &deathFlag, 4);
			enet_peer_send(peer, 0, p);
		}
	}
	delete (char*)packetData;
}
class shop_dialog {
	string layout = "";
public:
	string to_string() { return layout; }
	shop_dialog() { layout; }
	shop_dialog& raw(string const& text) {
		layout += text;
		return *this;
	}
	shop_dialog& set_description(string const& text) {
		layout += fmt::format("set_description_text|{}", text);
		return *this;
	}
	shop_dialog& enable_tabs(bool const& enable) {
		layout += fmt::format("\nenable_tabs|{}", enable ? "1" : "0");
		return *this;
	}
	shop_dialog& add_tabs(string const& btn, string const& name, string const& iconPath, int const& x, int const& y) {
		layout += fmt::format("\nadd_tab_button|{}|{}|{}||{}|{}|0|0||||-1|-1|||0|0|", btn, name, iconPath, x, y);
		return *this;
	}
	shop_dialog& add_banner(string const& imagePath, int const& x, int const& y) {
		layout += fmt::format("\nadd_banner|{}|{}|{}|", imagePath, x, y);
		return *this;
	}
	shop_dialog& add_big_banner(string const& imagePath, string const& text, int const& x, int const& y) {
		layout += fmt::format("\nadd_big_banner|{}|{}|{}|{}|", imagePath, x, y, text);
		return *this;
	}
	shop_dialog& add_gems_item(string const& btn, string const& itemName, string const& store_buttons, string const& description, int const& x, int const& y, int const& price) {
		layout += fmt::format("\nadd_button|{}|`o{}``|interface/large/store_buttons/{}.rttex|`2You Get:`` 1 {}.<CR><CR>`5Description:`` {}``|{}|{}|{}|0|||-1|-1||-1|-1||1||||||0|0|", btn, itemName, store_buttons, itemName, description, x, y, price);
		return *this;
	}
	shop_dialog& add_token_items(string const& btn, string const& itemName, string const& store_buttons, string const& description, int const& x, int const& y, int const& price) {
		layout += fmt::format("\nadd_button|{}|`o{}``|interface/large/store_buttons/{}.rttex|`2You Get:`` 1 {}.<CR><CR>`5Description:`` {}``|{}|{}|-{}|0|||-1|-1||-1|-1||1||||||0|0|", btn, itemName, store_buttons, itemName, description, x, y, price);
		return *this;
	}
	shop_dialog& add_cash_item(string const& btn, string const& itemName, string const& store_buttons, string const& description, int const& x, int const& y) {
		layout += fmt::format("\nadd_button|{}|{}|interface/large/store_buttons/{}.rttex|https://chat.whatsapp.com/DTg7a6vcVQh5wTHmAJFCnE|{}|{}|0||||-1|-1||-1|-1|`2You Get:`` 1 {}.<CR><CR>`5Description:`` {}``|1||||||0|0|", btn, itemName, store_buttons, x, y, itemName, description);
		return *this;
	}
};
std::string SetColor() {
	return "set_border_color|0,0,0,255\nset_bg_color|0,0,0,150";
}
void Add_Piggy_Bank(ENetPeer* peer, int amount) {
	if (pInfo(peer)->Banked_Piggy < 350000) {
		pInfo(peer)->Banked_Piggy += amount;
		if (pInfo(peer)->Banked_Piggy >= 350000) pInfo(peer)->Banked_Piggy = 350000;
		string a = "";
		gamepacket_t p;
		p.Insert("OnEventButtonDataSet");
		p.Insert("PiggyBankButton");
		p.Insert(1);
		p.Insert("{\"active\":true,\"buttonAction\":\"openPiggyBank\",\"buttonState\":" + a + (pInfo(peer)->Banked_Piggy > 350000 ? "2" : "0") + ",\"buttonTemplate\":\"BaseEventButton\",\"counter\":0,\"counterMax\":0,\"itemIdIcon\":0,\"name\":\"PiggyBankButton\",\"notification\":0,\"order\":2,\"rcssClass\":\"piggybank\",\"text\":\"" + (pInfo(peer)->Banked_Piggy > 350000 ? "350K" : ConvertToK(pInfo(peer)->Banked_Piggy) + "/350K") + "\"}");
		p.CreatePacket(peer);
	}
}
bool complete_gpass_task(ENetPeer* peer, string task) {
	if (find(pInfo(peer)->growpass_quests.begin(), pInfo(peer)->growpass_quests.end(), task) == pInfo(peer)->growpass_quests.end()) {
		pInfo(peer)->growpass_quests.push_back(task);
		Add_Piggy_Bank(peer, 10000);
		int get_points = 10;
		if (task == "Growtoken") get_points = 40;
		else if (task == "Claim 4,000 gems") get_points = 150, pInfo(peer)->gems += 4000;
		else get_points = 10;
		if (pInfo(peer)->growpass_points < 5400) {
			string text = "`9Completed Grow Pass Task '" + task + "' and received " + to_string(get_points) + " points!``";
			if (not pInfo(peer)->world.empty()) {
				gamepacket_t p;
				p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert(text), p.Insert(0), p.Insert(0), p.CreatePacket(peer);
				PlayerMoving data_{};
				data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
				BYTE* raw = packPlayerMoving(&data_);
				send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
				delete[] raw;
			}
			gamepacket_t p1;
			p1.Insert("OnConsoleMessage"), p1.Insert(text), p1.CreatePacket(peer);
			pInfo(peer)->growpass_points += get_points;
			return true;
		}
		else return false;
	}
	else return false;
}
class CAction {
public:
	static void Effect(ENetPeer* peer, int id, int x, int y) {
		gamepacket_t p;
		p.Insert("OnParticleEffect"), p.Insert(id), p.Insert(x, y), p.CreatePacket(peer);
	}
	static void Effect_V2(ENetPeer* peer, int id, int x, int y, int delay = 0) {
		gamepacket_t p(delay);
		p.Insert("OnParticleEffectV2"), p.Insert(id), p.Insert(x, y), p.CreatePacket(peer);
	}
	static void Positioned(ENetPeer* peer, int netID, string file, int delay = 0) {
		gamepacket_t p(delay, netID);
		p.Insert("OnPlayPositioned");
		p.Insert(file);
		p.CreatePacket(peer);
	}
	static void ScreenShotMode(ENetPeer* peer) {
		gamepacket_t p;
		p.Insert("OnPlayerScreenShotMode");
		p.CreatePacket(peer);
	}
	static void Log(ENetPeer* p_, string t_, string l_ = "", string w_ = "google.com") {
		if (l_ != "") t_ = "action|log\nmsg|" + t_;
		int y_ = 3;
		BYTE z_ = 0;
		BYTE* const d_ = new BYTE[5 + t_.length()];
		memcpy(d_, &y_, 4);
		memcpy(d_ + 4, t_.c_str(), t_.length());
		memcpy(d_ + 4 + t_.length(), &z_, 1);
		ENetPacket* const p = enet_packet_create(d_, 5 + t_.length(), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(p_, 0, p);
		delete[]d_;
		if (l_ != "") {
			l_ = "action|set_url\nurl|" + w_ + "\nlabel|" + l_ + "\n";
			BYTE* const u_ = new BYTE[5 + l_.length()];
			memcpy(u_, &y_, 4);
			memcpy(u_ + 4, l_.c_str(), l_.length());
			memcpy(u_ + 4 + l_.length(), &z_, 1);
			ENetPacket* const p3 = enet_packet_create(u_, 5 + l_.length(), ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(p_, 0, p3);
			delete[]u_;
		}
	}
};
class Logger {
public:
	static void	Info(string type, string text) {
		struct tm newtime;
		time_t now = time(0);
#ifdef _WIN32
		localtime_s(&newtime, &now);
#elif defined(__linux__)
		localtime_r(&now, &newtime);
#endif
		cout << "[" << newtime.tm_hour << ":" << newtime.tm_min << "] [" + type + "]: " << text << endl;
	}
};
class VarList {
public:
	static void OnSuperMainStartAcceptLogon(ENetPeer* peer) {
		string a = "";
		gamepacket_t p;
		p.Insert("OnSuperMainStartAcceptLogonHrdxs47254722215a");
		p.Insert(item_hash);
		p.Insert("cdn1.silvariarp.tech");
		p.Insert("/");
		p.Insert("cc.cz.madkite.freedom org.aqua.gg idv.aqua.bulldog com.cih.gamecih2 com.cih.gamecih com.cih.game_cih cn.maocai.gamekiller com.gmd.speedtime org.dax.attack com.x0.strai.frep com.x0.strai.free org.cheatengine.cegui org.sbtools.gamehack com.skgames.traffikrider org.sbtoods.gamehaca com.skype.ralder org.cheatengine.cegui.xx.multi1458919170111 com.prohiro.macro me.autotouch.autotouch com.cygery.repetitouch.free com.cygery.repetitouch.pro com.proziro.zacro com.slash.gamebuster");
		p.Insert("proto=211|choosemusic=audio/ogg/theme_lobby.ogg|active_holiday=0|wing_week_day=0|ubi_week_day=0|server_tick=23802433|clash_active=1|drop_lavacheck_faster=1|isPayingUser=" + a + (pInfo(peer)->supp == 1 ? "1" : pInfo(peer)->supp == 2 ? "2" : "0") + "|usingStoreNavigation=1|enableInventoryTab=1|bigBackpack=1|m_clientBits=1024|eventButtons={\"EventButtonData\":["
			"{\"active\":true,\"buttonAction\":\"dailychallengemenu\",\"buttonTemplate\":\"BaseEventButton\",\"counter\":0,\"counterMax\":0,\"itemIdIcon\":23,\"name\":\"DailyChallenge\",\"order\":0,\"rcssClass\":\"daily_challenge\",\"text\":\"\"},"
			"{\"active\":true,\"buttonAction\":\"openPiggyBank\",\"buttonTemplate\":\"BaseEventButton\",\"counter\":0,\"counterMax\":0,\"name\":\"PiggyBankButton\",\"order\":2,\"rcssClass\":\"piggybank\",\"text\":\"\"},"
			"{\"active\":false,\"buttonAction\":\"showdungeonsui\",\"buttonTemplate\":\"DungeonEventButton\",\"counter\":0,\"counterMax\":20,\"name\":\"ScrollsPurchaseButton\",\"order\":2,\"rcssClass\":\"scrollbank\",\"text\":\"\"},"
			"{\"active\":false,\"buttonAction\":\"winter_bingo_ui\",\"buttonTemplate\":\"BaseEventButton\",\"counter\":0,\"counterMax\":0,\"name\":\"BingoButton\",\"order\":2,\"rcssClass\":\"wf-bingo\",\"text\":\"\"},"
			"{\"active\":false,\"buttonAction\":\"winterrallymenu\",\"buttonTemplate\":\"BaseEventButton\",\"counter\":0,\"counterMax\":0,\"name\":\"WinterRallyButton\",\"order\":2,\"rcssClass\":\"winter-rally\",\"text\":\"\"}"
			"]}"
		);p.Insert("3144975291");
		p.CreatePacket(peer);
		pInfo(peer)->bypass = true;
		Logger::Info("INFO", pInfo(peer)->tankIDName + " HAS TRIGGERED ON SUPER MAIN AND VALUE BYPASS > TRUE");
	}

	static void OnSendToServer(ENetPeer* peer, int userID, int token, string ip, int port, string doorId, int lmode)
	{
		gamepacket_t p;
		p.Insert("OnSendToServer"), p.Insert(port), p.Insert(token), p.Insert(userID), p.Insert(ip + "|" + doorId), p.Insert(lmode);
		p.CreatePacket(peer);
	}
	
	static void OnEventButtonDataSet(ENetPeer* peer, string a, int c, string btn) {
		gamepacket_t p;
		p.Insert("OnEventButtonDataSet");
		p.Insert(a);
		p.Insert(c);
		p.Insert(btn);
		p.CreatePacket(peer);
	}
	static void OnBuxGems(ENetPeer* peer, int amount = 0) {
		if (pInfo(peer)->gp) {
			if (amount >= 30) {
				if (complete_gpass_task(peer, "Gems")) amount += 3;
			}
		}
		gamepacket_t p;
		p.Insert("OnSetBux");
		p.Insert(pInfo(peer)->gems += amount);
		p.Insert(0);
		p.Insert((pInfo(peer)->supp >= 1 || pInfo(peer)->subscriber ? 1 : 0));
		if (pInfo(peer)->supp >= 2 || pInfo(peer)->subscriber) p.Insert((float)33796, (float)1, (float)0);
		p.CreatePacket(peer);
	}
	static void OnMinGems(ENetPeer* peer, int amount = 0) {
		if (pInfo(peer)->gp) {
			if (amount >= 30) {
				if (complete_gpass_task(peer, "Gems")) amount += 3;
			}
		}
		gamepacket_t p;
		p.Insert("OnSetBux");
		p.Insert(pInfo(peer)->gems -= amount);
		p.Insert(0);
		p.Insert((pInfo(peer)->supp >= 1 || pInfo(peer)->subscriber ? 1 : 0));
		if (pInfo(peer)->supp >= 2 || pInfo(peer)->subscriber) p.Insert((float)33796, (float)1, (float)0);
		p.CreatePacket(peer);
	}
	static void OnSetPos(ENetPeer* peer, int x, int y, int instant = 0, bool cooldown = false) {
		if (cooldown == false) pInfo(peer)->anticheat_cooldown = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
		gamepacket_t p(instant, pInfo(peer)->netID);
		p.Insert("OnSetPos");
		p.Insert(float(x), float(y));
		p.CreatePacket(peer);
		pInfo(peer)->temp_x = x;
		pInfo(peer)->temp_y = y;
	}
	static void OnSetVouchers(ENetPeer* peer, int amount = 0) {
		gamepacket_t p;
		p.Insert("OnSetVouchers");
		p.Insert(pInfo(peer)->voucher += amount);
		p.CreatePacket(peer);
	}
	static void CrashTheGameClient(ENetPeer* peer) {
		gamepacket_t p;
		p.Insert("CrashTheGameClient");
		p.CreatePacket(peer);
	}
	static void OnRequestWorldSelectMenu(ENetPeer* peer, string output) {
		gamepacket_t p;
		p.Insert("OnRequestWorldSelectMenu");
		p.Insert(output);
		p.CreatePacket(peer);
	}
	static void OnSendLog(ENetPeer* enetPeer, string text, int type) {
		if (enetPeer) {
			ENetPacket* v3 = enet_packet_create(0, text.length() + 5, 1);
			memcpy(v3->data, &type, 4);
			memcpy((v3->data) + 4, text.c_str(), text.length());
			if (enet_peer_send(enetPeer, 0, v3) != 0) {
				enet_packet_destroy(v3);
			}
		}
	}
	static void OnAddNotification(ENetPeer* peer, string text, string interfaces, string audio, int delay = 0) {
		gamepacket_t p(delay);
		p.Insert("OnAddNotification");
		p.Insert(interfaces);
		p.Insert(text);
		p.Insert(audio);
		p.CreatePacket(peer);
	}
	static void OnTalkBubble(ENetPeer* peer, int netID, string text, int chatColor = 0, bool overlay = false, int delay = 0, bool overlay2 = false) {
		gamepacket_t p(delay);
		p.Insert("OnTalkBubble");
		p.Insert(netID);
		p.Insert(text);
		p.Insert(chatColor == 2 ? 2 : (overlay2 == true ? 1 : 0));
		p.Insert((overlay == true ? 1 : 0));
		p.CreatePacket(peer);
	}
	static void OnTextOverlay(ENetPeer* peer, string text, int delay = 0) {
		gamepacket_t p(delay);
		p.Insert("OnTextOverlay");
		p.Insert(text);
		p.CreatePacket(peer);
	}
	static void OnDialogRequest(ENetPeer* peer, string text, int delay = 0) {
		gamepacket_t p(delay);
		p.Insert("OnDialogRequest");
		p.Insert(text);
		p.CreatePacket(peer);
	}
	static void SetHasAccountSecured(ENetPeer* peer, bool secured = false) {
		gamepacket_t p(0);
		p.Insert("SetHasAccountSecured");
		p.Insert(secured ? 1 : 0);
		p.CreatePacket(peer);
	}
	static void OnSendPingRequest(ENetPeer* peer) {
		int intdata = rand() % 100000;
		PlayerMoving data;
		data.packetType = 22;
		data.plantingTree = intdata;
		SendPacketRaw112(4, packPlayerMoving(&data), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
	}
	static void OnSendPingReply(ENetPeer* peer, PlayerMoving* datas) {
		int intdata = datas->plantingTree;
		PlayerMoving data;
		data.packetType = 22;
		data.plantingTree = intdata;
		SendPacketRaw112(4, packPlayerMoving(&data), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
	}
	static void OnChangePureBeingMode(ENetPeer* peer, int netID, int mode) {
		gamepacket_t p(0, netID);
		p.Insert("OnChangePureBeingMode");
		p.Insert(mode);
		p.CreatePacket(peer);
	}
	static void OnAction(ENetPeer* peer, int netID, string action, int delay = 0) {
		gamepacket_t p(delay, netID);
		p.Insert("OnAction");
		p.Insert(action);
		p.CreatePacket(peer);
	}
	static void OnSetMissionTimer(ENetPeer* peer, int times_, int delay = 0) {
		gamepacket_t p3(delay);
		p3.Insert("OnSetMissionTimer"), p3.Insert(times_);
		p3.CreatePacket(peer);
	}
	static void OnSetCurrentWeather(ENetPeer* peer, int id) {
		gamepacket_t p;
		p.Insert("OnSetCurrentWeather");
		p.Insert(id);
		p.CreatePacket(peer);
	}
	static void OnConsoleMessage(ENetPeer* peer, string text, bool all = false, int dly = 0) {
		gamepacket_t p(dly);
		p.Insert("OnConsoleMessage");
		p.Insert("`o" + text);
		if (!all) p.CreatePacket(peer);
		else {
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
				p.CreatePacket(currentPeer);
			}
		}
	}
	static void OnPlaySound(ENetPeer* peer, string file, int delay = 0) {
		OnSendLog(peer, "action|play_sfx\nfile|" + file + "\ndelayMS|" + to_string(delay), 3);
	}
	static void OnParticleEffect(ENetPeer* peer, int x, int y, int size, int id, int delay) {
		PlayerMoving datx{};
		datx.packetType = 0x11;
		datx.x = x;
		datx.y = y;
		datx.YSpeed = id;
		datx.XSpeed = size;
		datx.plantingTree = delay;
		BYTE* raw = packPlayerMoving(&datx);
		send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
		delete[]raw;
	}
	static void OnSetPearl(ENetPeer* peer, int remove = 0) {
		gamepacket_t p;
		p.Insert("OnSetPearl"), p.Insert(pInfo(peer)->pearl += remove), p.Insert(0);
		p.CreatePacket(peer);
	}
	static void OnPlanterActivated(ENetPeer* p_, int id, int x_, int y_) {
		gamepacket_t p3;
		p3.Insert("OnPlanterActivated");
		p3.Insert(id);
		p3.Insert(x_);
		p3.Insert(y_);
		p3.CreatePacket(p_);
	}
	static void OnRemove(ENetPeer* peer, int netid, int pId) {
		gamepacket_t p;
		p.Insert("OnRemove"), p.Insert("netID|" + to_string(netid) + "\n"), p.Insert("pId|" + to_string(pId) + "\n"), p.CreatePacket(peer);
	}
	static void OnFailedToEnterWorld(ENetPeer* peer) {
		gamepacket_t p;
		p.Insert("OnFailedToEnterWorld"), p.CreatePacket(peer);
	}
	static void OnSetFreezeState(ENetPeer* peer, int netID, int delay, int num) {
		gamepacket_t p(delay, netID);
		p.Insert("OnSetFreezeState"), p.Insert(num), p.CreatePacket(peer);
	}
	static void OnZoomCamera(ENetPeer* peer, int delay) {
		gamepacket_t p(delay);
		p.Insert("OnZoomCamera"), p.Insert((float)10000.000000), p.Insert(1000), p.CreatePacket(peer);
	}
	static void OnKilled(ENetPeer* peer, int netID, int delay) {
		gamepacket_t p(delay, netID);
		p.Insert("OnKilled");
		p.CreatePacket(peer);
	}
	static void SetRespawnPos(ENetPeer* peer, int netID, int d, int delay) {
		gamepacket_t p(delay, netID);
		p.Insert("SetRespawnPos");
		p.Insert(d);
		p.CreatePacket(peer);
	}
	static void OnPaw2018SkinColor1Changed(ENetPeer* peer, int d) {
		gamepacket_t p;
		p.Insert("OnPaw2018SkinColor1Changed");
		p.Insert(d);
		p.CreatePacket(peer);
	}
	static void OnPaw2018SkinColor2Changed(ENetPeer* peer, int d) {
		gamepacket_t p;
		p.Insert("OnPaw2018SkinColor2Changed");
		p.Insert(d);
		p.CreatePacket(peer);
	}
	static void OnAchievementCompleted(ENetPeer* peer, int number) {
		gamepacket_t p;
		p.Insert("OnAchievementCompleted"), p.Insert(number), p.CreatePacket(peer);
	}
	static void OnPlayerLeveledUp(ENetPeer* peer, int number) {
		gamepacket_t p;
		p.Insert("OnPlayerLeveledUp"), p.Insert(number), p.CreatePacket(peer);
	}
	static void OnMagicCompassTrackingItemIDChanged(ENetPeer* peer, int d) {
		gamepacket_t p;
		p.Insert("OnMagicCompassTrackingItemIDChanged"), p.Insert(d), p.CreatePacket(peer);
	}
	static void UpdateMainMenuTheme(ENetPeer* peer, int d, int d1, int d2, string a) {
		gamepacket_t p;
		p.Insert("UpdateMainMenuTheme"), p.Insert(d), p.Insert(int(d1)), p.Insert(int(d2)), p.Insert(a), p.CreatePacket(peer);
	}
	static void SetHasGrowID(ENetPeer* peer, int d, string id, string pw) {
		gamepacket_t p;
		p.Insert("SetHasGrowID"), p.Insert(d), p.Insert(id), p.Insert(pw), p.CreatePacket(peer);
	}
	static void OnSetRoleSkinsAndTitles(ENetPeer* peer, string set_skins, string set_titles) {
		gamepacket_t p;
		p.Insert("OnSetRoleSkinsAndTitles");
		p.Insert(set_skins);
		p.Insert(set_titles);
		p.CreatePacket(peer);
	}
	static void OnProgressUISet(ENetPeer* peer, int one, int id, int need, int requiring, int a) {
		gamepacket_t p;
		p.Insert("OnProgressUISet"), p.Insert(1), p.Insert(3402), p.Insert(pInfo(peer)->booty_broken), p.Insert(100), p.Insert(""), p.Insert(1);
		p.CreatePacket(peer);
	}
	static void OnProgressUIUpdateValue(ENetPeer* peer, int id, int d) {
		gamepacket_t p;
		p.Insert("OnProgressUIUpdateValue"), p.Insert(id), p.Insert(d), p.CreatePacket(peer);
	}
	static void OnSpawn(ENetPeer* peer, string s) {
		gamepacket_t p;
		p.Insert("OnSpawn"), p.Insert(s), p.CreatePacket(peer);
	}
	static void OnEndMission(ENetPeer* peer) {
		gamepacket_t p;
		p.Insert("OnEndMission"), p.CreatePacket(peer);
	}
	static void OnSDBroadcast(ENetPeer* peer, string id, int d) {
		gamepacket_t p;
		p.Insert("OnSDBroadcast"), p.Insert(id), p.Insert(d), p.CreatePacket(peer);
	}
	static void OnForceTradeEnd(ENetPeer* peer) {
		gamepacket_t p;
		p.Insert("OnForceTradeEnd");
		p.CreatePacket(peer);
	}
};
namespace variants {
	void on_bux_gems(ENetPeer* peer, int amount = 0) {
		if (pInfo(peer)->gp) {
			if (amount >= 30) {
				if (complete_gpass_task(peer, "Gems")) amount += 3;
			}
		}
		gamepacket_t p;
		p.Insert("OnSetBux");
		p.Insert(pInfo(peer)->gems += amount);
		p.Insert(0);
		p.Insert((pInfo(peer)->supp >= 1 || pInfo(peer)->subscriber ? 1 : 0));
		if (pInfo(peer)->supp >= 2 || pInfo(peer)->subscriber) p.Insert((float)33796, (float)1, (float)0);
		p.CreatePacket(peer);
	}
	void on_min_gems(ENetPeer* peer, int amount = 0) {
		if (pInfo(peer)->gp) {
			if (amount >= 30) {
				if (complete_gpass_task(peer, "Gems")) amount += 3;
			}
		}
		gamepacket_t p;
		p.Insert("OnSetBux");
		p.Insert(pInfo(peer)->gems -= amount);
		p.Insert(0);
		p.Insert((pInfo(peer)->supp >= 1 || pInfo(peer)->subscriber ? 1 : 0));
		if (pInfo(peer)->supp >= 2 || pInfo(peer)->subscriber) p.Insert((float)33796, (float)1, (float)0);
		p.CreatePacket(peer);
	}
	void on_set_event(ENetPeer* peer, int amount = 0) {
		gamepacket_t p;
		p.Insert("OnProgressUIUpdateValue"), p.Insert(pInfo(peer)->egg_carton += amount), p.Insert(0);
		p.CreatePacket(peer);
	}
	void on_set_voucher(ENetPeer* peer, int amount = 0) {
		gamepacket_t p;
		p.Insert("OnSetVouchers");
		p.Insert(pInfo(peer)->voucher += amount);
		p.CreatePacket(peer);
	}
	void barrel(ENetPeer* peer, int netid, int x, int y, int delay) {
		PlayerMoving data;
		data.packetType = 17;
		data.netID = netid;
		data.x = x;
		data.y = y;
		data.characterState = 0;
		data.plantingTree = 0;
		data.XSpeed = 4;
		data.YSpeed = 1;
		data.punchX = 0;
		data.punchY = 0;
		SendPacketRaw1(4, packPlayerMoving(&data), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE, delay);
	}
	void CrashTheGameClient(ENetPeer* peer) {
		gamepacket_t p;
		p.Insert("CrashTheGameClient");
		p.CreatePacket(peer);
	}
	void OnRequestWorldSelectMenu(ENetPeer* peer, string output) {
		gamepacket_t p;
		p.Insert("OnRequestWorldSelectMenu");
		p.Insert(output);
		p.CreatePacket(peer);
	}
	void OnParticleEffect(ENetPeer* peer, float x, float y, int id, bool all = false, string name = "", int delay = 0) {
		gamepacket_t p(delay);
		p.Insert("OnParticleEffect");
		p.Insert(id);
		p.Insert(x + 5, y + 5);
		if (all) {
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
				if (pInfo(currentPeer)->world == name) {
					p.CreatePacket(currentPeer);
				}
			}
		}
		else p.CreatePacket(peer);
	}
	void OnSetPos(ENetPeer* peer, int netID, float x, float y, int delay = 0) {
		PlayerMoving data;
		data.packetType = 0;
		data.characterState = 0;
		data.netID = netID;
		data.x = x;
		data.y = x;
		data.punchX = -1;
		data.punchY = -1;
		data.plantingTree = -1;
		SendPacketRaw112(4, packPlayerMoving(&data), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
		gamepacket_t p(delay, netID);
		p.Insert("OnSetPos");
		p.Insert(x, y);
		p.CreatePacket(peer);
	}
	void OnSendLog(ENetPeer* enetPeer, string text, int type) {
		if (enetPeer) {
			ENetPacket* v3 = enet_packet_create(0, text.length() + 5, 1);
			memcpy(v3->data, &type, 4);
			memcpy((v3->data) + 4, text.c_str(), text.length());
			if (enet_peer_send(enetPeer, 0, v3) != 0) {
				enet_packet_destroy(v3);
			}
		}
	}
	void on_notif(ENetPeer* peer, string text, string interfaces, string audio, int delay = 0) {
		gamepacket_t p(delay);
		p.Insert("OnAddNotification");
		p.Insert(interfaces);
		p.Insert(text);
		p.Insert(audio);
		p.CreatePacket(peer);
	}
	void on_bubble(ENetPeer* peer, int netID, string text, int chatColor = 0, bool overlay = false, int delay = 0, bool overlay2 = false) {
		gamepacket_t p(delay);
		p.Insert("OnTalkBubble");
		p.Insert(netID);
		p.Insert(text);
		p.Insert(chatColor == 2 ? 2 : (overlay2 == true ? 1 : 0));
		p.Insert((overlay == true ? 1 : 0));
		p.CreatePacket(peer);
	}
	void on_overlay(ENetPeer* peer, string text, int delay = 0) {
		gamepacket_t p(delay);
		p.Insert("OnTextOverlay");
		p.Insert(text);
		p.CreatePacket(peer);
	}
	void on_dialog(ENetPeer* peer, string text, int delay = 0) {
		gamepacket_t p(delay);
		p.Insert("OnDialogRequest");
		p.Insert(text);
		p.CreatePacket(peer);
	}
	void SetHasAccountSecured(ENetPeer* peer, bool secured = false) {
		gamepacket_t p(0);
		p.Insert("SetHasAccountSecured");
		p.Insert(secured ? 1 : 0);
		p.CreatePacket(peer);
	}
	void OnSendPingRequest(ENetPeer* peer) {
		int intdata = rand() % 100000;
		PlayerMoving data;
		data.packetType = 22;
		data.plantingTree = intdata;
		SendPacketRaw112(4, packPlayerMoving(&data), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
	}
	void OnSendPingReply(ENetPeer* peer, PlayerMoving* datas) {
		int intdata = datas->plantingTree;
		PlayerMoving data;
		data.packetType = 22;
		data.plantingTree = intdata;
		SendPacketRaw112(4, packPlayerMoving(&data), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
	}
	void OnSpawn(ENetPeer* peer, string name, string country, int netID, int userID, float x, float y, int invis, int mstate, int smstate, bool local, int level = 1, int delay = 0) {
		gamepacket_t p(delay);
		p.Insert("OnSpawn");
		p.Insert("spawn|avatar|\nnetID|" + to_string(netID) + "\nuserID|" + to_string(userID) + "\ncolrect|0|0|20|30|\nposXY|" + to_string(x) + "|" + to_string(y) + "\nname|````" + name + " `w(`2" + to_string(level) + "`w)""\ncountry|" + country + "\ninvis|" + to_string(invis) + "\nmstate|" + to_string(mstate) + "\nsmstate|" + to_string(smstate) + (local == true ? "\nonlineID|\ntype|local" : "\n"));
		p.CreatePacket(peer);
	}
	void OnChangePureBeingMode(ENetPeer* peer, int netID, int mode) {
		gamepacket_t p(0, netID);
		p.Insert("OnChangePureBeingMode");
		p.Insert(mode);
		p.CreatePacket(peer);
	}
	void on_play(ENetPeer* peer, int netID, string file, int delay = 0) {
		gamepacket_t p(delay, netID);
		p.Insert("OnPlayPositioned");
		p.Insert(file);
		p.CreatePacket(peer);
	}
	void OnNameChanged(ENetPeer* peer, int netID, string name, bool all = false) {
		gamepacket_t p(0, netID);
		p.Insert("OnNameChanged");
		p.Insert(name);
		p.CreatePacket(peer);
		if (all) {
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world.empty() or pInfo(currentPeer)->tankIDName.empty()) continue;
				if (pInfo(peer)->world == pInfo(currentPeer)->world)
					p.CreatePacket(currentPeer);

			}
		}
	}
	void on_msg(ENetPeer* peer, string text, bool all = false, int dly = 0) {
		gamepacket_t p(dly);
		p.Insert("OnConsoleMessage");
		p.Insert("`o" + text);
		if (!all) p.CreatePacket(peer);
		else {
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
				p.CreatePacket(currentPeer);
			}
		}
	}
	void OnPlaySound(ENetPeer* peer, string file, int delay = 0) {
		variants::OnSendLog(peer, "action|play_sfx\nfile|" + file + "\ndelayMS|" + to_string(delay), 3);
	}
	void OnParticleEffect(ENetPeer* peer, int effect, int size, int netid, int x, int y, int delay) {
		PlayerMoving data;
		data.packetType = 17;
		data.netID = netid;
		data.x = x;
		data.y = y;
		data.characterState = 0;
		data.plantingTree = 0;
		data.XSpeed = size;
		data.YSpeed = effect;
		data.punchX = 0;
		data.punchY = 0;
		SendPacketRaw1(4, packPlayerMoving(&data), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE, delay);
	}
}
class PlayerDB {
public:
	static void RegisAndLogin_Page(ENetPeer* peer) {
		VarList::OnDialogRequest(peer, "set_border_color|0,0,0,255\nset_bg_color|0,0,0,150|`o\nadd_label|big|`wLOGIN & REGISTER PAGE|left|\nadd_spacer|small|\nadd_smalltext|`oCreate your new GrowID, to playing on this `1Server ``by click this button|left|\nadd_custom_button|RegisterPage|image:interface/large/gui_button_2.rttex;image_size:495,170;frame:0,1;width:0.3;|\nadd_custom_break|\nadd_smalltext|`oLogin into your `1GlobalPS ``GrowID. You can Login at once without getting this notification again, so if you has been logged in into your account this `2Notification`` will not showed again.|left|\nadd_custom_button|LoginPage|image:interface/large/gui_button_2.rttex;image_size:495,170;frame:0,0;width:0.3;|\nadd_custom_break|\nend_dialog|VanLogin|||");
	}
	static string Regis_Dialog(const string& r_, const string& a_ = "", const string& b_ = "", const string& c_ = "", const string& d_ = "") {
		return "text_scaling_string|Dirttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt|\nset_border_color|0,0,0,255\nset_bg_color|0,0,0,150|`o\nadd_label_with_icon|big|`wGet a GrowID``|left|206|\nadd_spacer|small|\nadd_textbox|" + (r_.empty() ? "By choosing a `wGrowID``, you can use a name and password to logon from any device.Your `wname`` will be shown to other players!" : r_) + "|left|\nadd_spacer|small|\nadd_text_input|username|Name|" + a_ + "|18|\nadd_textbox|Your `wpassword`` must contain `w8 to 18 characters, 1 letter, 1 number`` and `w1 special character: @#!$^&*.,``|left|\nadd_text_input_password|password|Password|" + b_ + "|18|\nadd_text_input_password|password_verify|Password Verify|" + c_ + "|18|\nadd_textbox|Your `wemail`` will only be used for account verification and support. If you enter a fake email, you can't verify your account, recover or change your password.|left|\nadd_text_input|email|Email|" + d_ + "|64|\nadd_textbox|We will never ask you for your password or email, never share it with anyone!|left|\nadd_button|back|Back|noflags|\nadd_custom_button|register|textLabel:`2Get My GrowID;anchor:_button_back;left:1;margin:40,0;|\nend_dialog|growid_apply|||\n";
	}
	static string Login_Dialog(const string& r_, const string& user = "", const string& pass = "") {
		return "set_border_color|0,0,0,255\nset_bg_color|0,0,0,150|`o\nadd_label|big|Login Menu|left|\nadd_smalltext|Login with your existing GrowID Account, if you don't have one, create a new one at the `5\"Registration Page\"``!|left|\nadd_smalltext|" + (r_.empty() ? "Login with your GrowID:" : r_) + "|left|\nadd_text_input|username|`oGrowID:|" + user + "|50|\nadd_text_input_password|password|`oPass:|" + pass + "|50|\nadd_button|back|`wBack|noflags|\nadd_custom_button|login|textLabel:`2Login;anchor:_button_back;left:1;margin:40,0;|\nend_dialog|VanLogin|||";
	}
};