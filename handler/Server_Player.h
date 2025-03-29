#pragma once

#ifdef _WIN32
    #include <windows.h>
#else
    typedef uint32_t DWORD;  // Define DWORD as uint32_t for Linux
#endif

struct Friends {
	string name = "";
	bool mute = false, block_trade = false;
	long long last_seen = 0;
};
void to_json(json& j, const Friends& p) {
	j = json{
		{"name", p.name},
		{"mute", p.mute},
		{"block_trade", p.block_trade},
		{"last_seen", p.last_seen}
	};
}
void from_json(const json& j, Friends& p) {
	j["name"].get_to(p.name);
	j["mute"].get_to(p.mute);
	j["block_trade"].get_to(p.block_trade);
	j["last_seen"].get_to(p.last_seen);
}
struct PlayMods {
	uint16_t id = 0;
	long long time = 0;
	string user = "";
};
void to_json(json& j, const PlayMods& p) {
	j = json{
		{"id", p.id},
		{"time", p.time},
		{"user", p.user}
	};
}
void from_json(const json& j, PlayMods& p) {
	j["id"].get_to(p.id);
	j["time"].get_to(p.time);
	j["user"].get_to(p.user);
}
struct MarketPlace {
	string fg = "", storeName = "", whose = "";
	int notifications = 0;
};
struct Player {

	// Npc
	bool isNpcPromotionCalling = false, isNpcTipsCall = false, isNpcWelcomeLoad = false, isNpcTrading = false;

	// Warning System
	int Warning = 0;
	vector<string> Warning_Message{};
	vector<string> WM{};

	// Mod Setting
	bool npc_summon = false, effworld_ = false;
	int x_npc = 0, y_npc = 0, npc_netID = 0;
	int effworld = 0, cheat_bot_spam = 0, cheat_pull = 0, cheat_qq = 0, cheat_reme = 0, cheat_kick = 0, cheat_ban = 0, cheat_detect = 0, cheat_unacc = 0, cheat_hideother = 0, cheat_hidechat = 0, cheat_spam = 0;
	int Cheat_Spam_Delay = 1, Cheat_Last_Spam = 0;
	long long int Time_Spawn = 0;
	string Cheat_Spam_Text = "", npc_text = "", npc_name = "", npc_world = "";

	// Growch
	int staged = 0, s4tb = 0;

	// Kit
	int lvlKit = 0, xpKit = 0;
	bool startedKit = false, kit1 = false, kit2 = false, kit3 = false, kit4 = false, kit5 = false, kit6 = false, kit7 = false, kit8 = false, kit9 = false, kit10 = false;
	bool kit11 = false, kit12 = false, kit13 = false, kit14 = false, kit15 = false, kit16 = false, kit17 = false, kit18 = false, kit19 = false, kit20 = false;

	// Marketplace
	int buyp = 0, store_price = 0, store_id = 0;
	string store_pos = "", store_desc = "";

	// Spotify
	int spotify = 0;

	// battle pet
	pair<vector<uint16_t>, vector<uint16_t>> battle_pet{ {0, 0, 0, 1}, { 0,0,0,0 } };

	// Tutorial by Tianvan
	string last_tutorial_world = "";
	int Tutorial_Number = 1, Need_To_Required = 0, Requiring = 1;
	bool completed_tutorial = false, new_player = false, in_world_tutorial = false;

	// Pet Ai
	string pet_name = "";
	int pet_type = -1;
	float pet_move = 0.0f;
	long long int pet_xp = 0;
	int pet_netID = 0, pet_ID = 0, pet_level = 0, ability_xgems = 0, ability_xxp = 0;
	bool show_pets = false, pet_ClothesUpdated = false, master_pet = false, active_bluename = false, active_1hit = false, ChickenFlyTgt = false, GalaxyFly = false;
	
	// Gacha by Tianvan
	string gacha_type = "";
	int IntertSao_Fate = 0, Pity = 0;
	bool Pity_On = false, Has_In = true;
	vector<string> Gacha_History{};

	// Buy
	string last_name_item = "";
	int last_price_item = 0, last_id_item = 0;

	// Daily Login
	int is_day = 0;
	bool claimed_daily_today = false;
	long long int daily_login_day = 0;
	vector<uint8_t> daily_login;

	// Redeem Code by Tianvan
	long long last_redeem = 0;
	vector<string> Has_Claim{};
	vector<pair<int, int>> r_items{};

	struct { int lastActionSent = 0, totalActionSent = 0; } packetSent;

	// Role
	struct {
		bool Owner_Server = false, Staff = false, Developer = false, Administrator = false, Moderator = false, Vip = false, Cheats = false;
	} Role;

	// Title
	struct {
		bool Mentor = false, Grow4Good = false, Doctor = false, OfLegend = false, TiktokBadge = false, ContentCBadge = false, ThanksGiving = false, OldTimer = false, WinterSanta = false;
	} Title;

	// New Get
	vector<pair<int, int>> n_items{};

	bool autofarm = false, is_guest = false;
	bool Has_Login = false;
	int unlock_tgt = 0;
	bool tgt = false;
	string nm = "", ds = "", fg = "", last_name = "", last_pos = "", lastFind = "";
	bool savedd = false;
	string newname = "";
	string ip = "", fa_ip = "";
	vector<string> last_visited_worlds, worlds_owned, trade_history, crypto_history, ignored, last_rated;
	vector<map<int, int>> trade_items{};
	string name_color = "`0";
	long long int race_flag = 0, xp = 0;
	uint32_t hair_color = 0xFFFFFFFF, eye_drop = 0xFFFFFFFF, eye_lenses = 0xFFFFFFFF, xenonite = 0, cape_t = 2402849791, cape_c = 2402849791, cape_t2 = 723421695, cape_c2 = 1059267327, wings_t = 3356909055, wings_c = 4282965247, wings_t2 = 723421695, wings_c2 = 1059267327;
	int id = 0, netID = 0, state = 0, trading_with = -1;
	bool trade_accept = false, accept_the_offer = false;
	int x = -1, y = -1;
	int gems = 0, voucher = 0;
	bool growid = false;
	bool wiped_invalid_worlds = false;
	bool ttBadge = false, ccBadge = false;
	bool usedmegaphone = 0;
	map<int, int> access_offers{};
	bool hit1 = false;
	int skin = 0x8295C3FF;
	int exitwarn = 0;
	string last_world = "";
	uint16_t punched = 0;
	int enter_game = 0;
	int lock = 0;
	int flagmay = 256;
	vector<pair<string, int>> crypto;
	int lockeitem = 0;
	string last_online = "";
	bool ghost = false, invis = false;
	uint8_t n = 0; //newbie passed save
	string note = "";
	uint8_t supp = 0, hs = 0, m_h = 0, d_s = 0;
	string real_growtopia_name = "";
	string CapeStyleColor_1 = "147,56,143", CapeCollarColor_1 = "147,56,143", CapeStyleColor_2 = "137,30,43", CapeCollarColor_2 = "34,35,36", skin_c = "0,0,0";
	string _CapeStyleColor_1 = "93,22,200", _CapeCollarColor_1 = "220,72,255", _CapeStyleColor_2 = "137,30,43", _CapeCollarColor_2 = "34,35,63";
	int autofarm_slot = 1;
	int flags = 19451, TimeDilation = 30, _flags = 104912, _TimeDilation = 30;
	float strong_punch = 200, high_jump = 1000, player_speed = 250, water_speed = 125;
	int build_range = 128, punch_range = 128;
	int state_player = 0;
	int punch_effect = 0;
	int type_player = 0;
	int guild_role = -1;
	int flag_may_form = 0;
	int punch_modifier = 0;
	bool punch_decrease = false;
	string gender = "", temp_password = "";
	int rr_ = rand() % 6 + 1;
	int growpass_points = 0;
	vector<string> growpass_prizes, growpass_quests;
	int rr_used = 0;
	int wls = 0;
	uint8_t csn = -1;
	bool mini_you = false;
	long long int b_t = 0, b_s = 0; // ban seconds
	bool no_body = false, no_hands = false;
	int last_infected = 0;
	string b_r = "", b_b = ""; // ban reason ir banned by
	string m_b = "";
	uint16_t hair = 0, shirt = 0, pants = 0, feet = 0, face = 0, hand = 0, back = 0, mask = 0, necklace = 0, ances = 0, hiden_clothing = 0; /*clothes*/
	string temporary_tankIDName = "";
	string tankIDName = "", tankIDPass = "", requestedName = "", world = "", email = "", country = "", home_world = "", last_wrenched = "", last_msg_wrenched = "", info_new_ = "";
	string d_name = "";
	string temporary_vault = "";
	string Carnival_GameType = "None";
	vector<pair<int, int>>Carnival_Mirror_Maze;
	long long Carnival_GameTime = 0;
	bool DeathRaceBeaten = false;
	string DeathRaceWinner = "";
	bool BrutalBeaten = false;
	bool SpikyBeaten = false;
	bool NotSame = false;
	int Shooting_Punch = 0;
	int Shooting_Point = 0;
	int BrutalX = 0;
	int BrutalY = 0;
	int SpikyX = 0;
	int SpikyY = 0;
	int XCard_1 = 0;
	int YCard_1 = 0;
	int XCard_2 = 0;
	int YCard_2 = 0;
	int CardOpened = 0;
	int Card_1 = 0;
	int Card_2 = 0;
	int TotalCardSucces = 0;
	int Carnival_Games_Won = 0;
	int FunTimeRewards = 0;
	vector<Friends> friends;
	vector<int> last_friends_selection{};
	vector<string> pending_friends{};
	vector<string> bans{};
	string last_edit = "";
	int summer_surprise = 0, summer_total = 0;
	vector<int> summer_milestone;
	int pinata_day = 0;
	bool pinata_prize = false;
	bool pinata_claimed = false;
	bool pc_player = false;
	int pure_shadow = 0;
	int wrong2fa = 0;
	bool bypass = false, update_player = false, bypass2 = false;
	int new_packets = 0;
	bool hider = false, backwards = false;
	bool seeker = false;
	string world_owner = "";
	int random_geiger_time = 0;
	uint8_t i_11818_1 = 0, i_11818_2 = 0;
	int8_t random_fossil = rand() % 3 + 4;
	int page_number = 0;
	string page_item = "";
	int Aura_Season = 2, Trail_Season = 2;
	int Banner_Item = 0, CBanner_Item = 0, Banner_Flag = 0, CBanner_Flag = 0;
	bool Crown_Time_Change = true;
	int Crown_Cycle_Time = 15;
	int Base_R_0 = 255, Base_G_0 = 200, Base_B_0 = 37;
	int Gem_R_0 = 255, Gem_G_0 = 0, Gem_B_0 = 64;
	int Crystal_R_0 = 26, Crystal_G_0 = 45, Crystal_B_0 = 140;
	bool Crown_Floating_Effect_0 = false, Crown_Laser_Beam_0 = true, Crown_Crystals_0 = true, Crown_Rays_0 = true;
	long long World_Timed = 0;
	bool WorldTimed = false;
	int Base_R_1 = 255, Base_G_1 = 255, Base_B_1 = 255;
	int Gem_R_1 = 255, Gem_G_1 = 0, Gem_B_1 = 255;
	int Crystal_R_1 = 0, Crystal_G_1 = 45, Crystal_B_1 = 140;
	bool Crown_Floating_Effect_1 = true, Crown_Laser_Beam_1 = true, Crown_Crystals_1 = true, Crown_Rays_1 = true;
	int Crown_Value = 1768716607;
	long long int Crown_Value_0_0 = 4294967295, Crown_Value_0_1 = 4278255615, Crown_Value_0_2 = 4190961919;
	long long int Crown_Value_1_0 = 633929727, Crown_Value_1_1 = 1073807359, Crown_Value_1_2 = 2351766271;
	int transmute_item1 = 0, transmute_item2 = 0, remove_transmute = 0;
	string transmuted = "";
	bool temp_transmute = false;
	bool C_QuestActive = false, CQ = false;
	int C_QuestStep = 1, C_QuestProgress = 0, C_ProgressNeeded = 0, C_QuestKind = 0, C_DeliverID = 0;
	uint16_t opc = 0;
	int cc = 0;
	bool bb = false;
	uint8_t rb = 0;
	uint8_t gp = 0, glo = 0;
	uint8_t w_w = 0;
	int offergems = 0;
	bool show_location_ = true, show_friend_notifications_ = true;
	int confirm_reset = 0;
	int carnivalgameswon = 0;
	int level = 1;
	long long playtime = 0;
	vector<int> playtime_items;
	long long int account_created = 0, seconds = 0;
	int protocol = 0;
	string rid = "", mac = "", meta = "", vid = "", platformid = "", wk = "";
	int achievement_total = 0;
	map<string, int> achievements{};
	string lastmsg = "", lastmsgworld = "";
	long long int lastRESP = 0, lastPDOOR = 0, lastJOINWORLD = 0;
	int WarnPDoor = 0, WarnRespawn = 0;
	int gtwl = 0;
	uint16_t c_x = 0, c_y = 0;
	uint8_t lavaeffect = 0;
	long long int i240 = 0, i756 = 0, i758 = 0;
	bool tmod = 0;
	int b_i = 0, b_w = 0, b_p = 0;
	string b_bill = "0,0";
	int same_input = 0, not_same = 0, pickup_limits = 0, hack = 0;
	bool world_enter = false;
	string last_input_text = "";
	long long int pickup_time =0 , teleport_time = 0, last_inf = 0, last_spam_detection = 0, last_world_enter = 0, last_personal_update = 0, last_fish_catch = 0, respawn_time = 0, hand_torch = 0, punch_time = 0, lava_time = 0, world_time = 0, geiger_time = 0, valentine_time = 0, remind_time = 0, warp_time = 0, name_time = 0, anticheat_cooldown = 0, anticheat_cooldown2 = 0;
	int lastwrenchx = 0, lastwrenchy = 0, lastwrenchb = 0, lastchoosenitem = 0, lastchoosennr = 0;
	int spray_x = 0, spray_y = 0;
	int pps = 0;
	long long lpps = 0;
	long long int punch_count = 0;
	string personal_event = "", guild_event = "";
	int carnival_credit = 0;
	int total_credit_card = 0, credit_card = rand() % 10000000000000;
	int Magnet_Item = 0;
	int AncesID = 0, Upgradeto = 0, HowmuchSoulStone = 0, IDCeles = 0, JumlahCeles = 0, IDCrystalized = 0, JumlahCrystalized = 0;
	int DailyRiddles = 0;
	uint8_t  grow_air_ballon = 0;
	bool subscriber = false;
	int mailbox = 0;
	bool wiping_time = false;
	uint8_t geiger_ = 0;
	uint8_t all_in = 0;
	int fishing_used = 0, f_x = 0, f_y = 0, move_warning = 0, f_xy = 0, punch_warning = 0, fish_seconds = 0;
	vector<int> glo_p;
	vector<int> lvl_p;
	int geiger_x = -1, geiger_y = -1;
	int t_xp = 0, bb_xp = 0, g_xp = 0, p_xp = 0, ff_xp = 0, s_xp = 0;
	uint8_t t_lvl = 0, bb_lvl = 0, g_lvl = 0, p_lvl = 0, ff_lvl = 0, s_lvl = 0;
	vector<uint8_t> t_p, bb_p, p_p, g_p, ff_p, surg_p;
	int booty_broken = 0;
	bool ghc = false;
	uint8_t dd = 0;
	vector<PlayMods> playmods{};
	bool new_pass = false;
	uint16_t b_l = 1;
	vector<pair<uint16_t, uint8_t>> bp;
	vector<pair<int, int>> inv, transmute;
	bool auth_ = true;
	int choosenitem = 0;
	uint8_t radio = 0;
	bool radio2 = false;
	bool temp_radio = true;
	int b_ra = 0, b_lvl = 1;
	int magnetron_id = 0;
	int magnetron_x = 0;
	int magnetron_y = 0;
	string growmoji = "(wl)|ā|0&(oops)|ą|0&(sleep)|Ċ|0&(punch)|ċ|0&(bheart)|Ĕ|0&(grow)|Ė|0&(gems)|ė|0&(gtoken)|ę|0&(cry)|ĝ|0&(vend)|Ğ|0&(bunny)|ě|0&(cactus)|ğ|0&(pine)|Ĥ|0&(peace)|ģ|0&(terror)|ġ|0&(troll)|Ġ|0&(evil)|Ģ|0&(fireworks)|Ħ|0&(football)|ĥ|0&(alien)|ħ|0&(party)|Ĩ|0&(pizza)|ĩ|0&(clap)|Ī|0&(song)|ī|0&(ghost)|Ĭ|0&(nuke)|ĭ|0&(halo)|Į|0&(turkey)|į|0&(gift)|İ|0&(cake)|ı|0&(heartarrow)|Ĳ|0&(lucky)|ĳ|0&(shamrock)|Ĵ|0&(grin)|ĵ|0&(ill)|Ķ|0&(eyes)|ķ|0&(weary)|ĸ|0&(moyai)|ļ|0&(plead)|Ľ|0&";
	long long int save_time = 0, basher_time = 0;
	vector<vector<long long>> completed_blarneys{
		{1, 0},
		{2, 0},
		{3, 0},
		{4, 0},
		{5, 0},
		{6, 0},
		{7, 0},
		{8, 0},
		{9, 0},
	};
	bool block_trade = false;
	int p_x = 0;
	int p_y = 0;
	int guild_id = 0;
	int uid = 0;
	int pending_guild = 0;
	bool is_legend = false;
	bool ios_player = false;
	uint16_t pps23 = 0, all_packets = 0;
	int temp_x = 0, temp_y = 0;
	long long lpps2 = 0, all_packets_time = 0;
	uint8_t roleIcon = 6, roleSkin = 6;
	bool valentine = false;
	long long int ban_seconds = 0, last_exit = 0;
	string ban_reason = "";
	int autofarm_x = -1, autofarm_y = -1;
	uint8_t fires = 0;
	uint32_t total_pineapple = 0;
	uint16_t stage_pineapple = 0;
	uint8_t garuda = 0;
	uint16_t eq_aura = 0;
	int balloon_faction = rand() % 3 + 1, balloon_hit = 0, hit_by = 0, balloon_donated = 0, balloon_score = 0;
	int fruit_1 = 0, fruit_2 = 0, fruit_3 = 0;
	int fruit_1_c = 0, fruit_2_c = 0, fruit_3_c = 0;
	string chat_prefix = "";
	bool disable_cheater = 0;
	int egg_carton = 0;
	int magic_egg = 0;
	int egg_chance = 0;
	int p_status = 0;
	int participated = 0;
	int lwiz_quest = 0, lwiz_step = 1, lwiz_notification = 0;
	vector<vector<int>> legendary_quest, set = {{}};
	string player_device = "";
	int guild_fg = 0;
	int guild_bg = 0;
	int set_guild_bg = 0, set_guild_fg = 0;
	int cheater_settings = 0;
	int support101_ = 0;
	bool received_balloon_warz = false, black_color = false;
	string wolf_world = "";
	bool logger = 0;
	int last_used_block = 0;
	int search_page = 20;
	vector<uint16_t> available_surg_items;
	bool sounded = false;
	bool labworked = false;
	bool fixed = false;
	bool fixable = false;
	bool flu = false;
	int pulse = 40, site = 0, sleep = 0, dirt = 0, broken = 0, shattered = 0, incisions = 0, bleeding = 0, incneeded = 0, heart = 0;
	double temp = 98.6;
	double fever = 0.0;
	string pretext = "";
	string fixtext = "";
	string postext = "";
	string scantext = "";
	string tooltext = "The patient is prepped for surgery.";
	string endtext = "";
	bool update = true;
	bool s = true;
	// SURG
	uint8_t surgery_skill = 0, spongUsed = 0, scalpUsed = 0, stitcUsed = 0, antibUsed = 0, antisUsed = 0, ultraUsed = 0, labkiUsed = 0, anestUsed = 0, defibUsed = 0, splinUsed = 0, pinsUsed = 0, clampUsed = 0, transUsed = 0;
	uint16_t surgery_done = 0, su_8552_1 = 0, su_8552_2 = 0, su_8552_3 = 0;
	bool antibs = false, surgery_started = false;
	string surgery_world = "";
	string surged_person = "";
	string surged_display = "";
	string surgery_name = "";
	bool hospital_bed = false;
	int fa2 = 0;

	// Proxy
	struct Proxys {
		bool reme = false;
		bool qeme = false;
		bool fastspin = false;
	} proxy;

	// Bank
	int bank_password = 0, Banked_Piggy = 0;
	bool Has_Enter_Bank = false;
	std::vector<std::string> Bank_History{};
	long long int Gems_Storage = 0;
	int32_t wl_bank_amount = 0, dl_bank_amount = 0, bgl_bank_amount = 0;

	string TitleTexture = "", TitleCoordinate = "";
	vector<int> Wrench_Style, Wrench_Decoration;
	int wrench_foreground_custom = 0, wrench_custom = 0;

	uint8_t surgery_type = -1, started_type = 0, mercy = 0, drtitle = 0, drlegend = 0, drt = 0, lvl125 = 0, donor = 0, master = 0, tgiv = 0, anni_old = 0, santa = 0;
	bool spotlight = false;
	bool mentor = false;
	uint8_t minokawa_wings = 0, panda_spirit = 0, mask_dragon = 0, growformer = 0;
	int won_seeker = 0, won_hider = 0;
	bool emoji_gg = false;
	int musical_volume = 100;
	string musical_note = "C-F-G#G-F-B#A#G-F-G#G-D#G-C-";
	vector<string> growtoken_worlds;
	uint8_t grow4good_seed2 = 0, grow4good_combine = 0, grow4good_crystal = 0, grow4good_honors = 0;
	uint16_t grow4good_seed = 0;
	bool new_version = false;
	bool grow4good_email = 0;
	bool wls_participated = false;
	long long int  grow_reset_day = 0, grow_reset_week = 0, grow_reset_month = 0;
	string last_home_world = "";
	string spectate_person = "";
	int grow4good_gems = 0;
	int grow4good_surgery = 0;
	int grow4good_fish = 0;
	int grow4good_points = 0;
	uint8_t grow4good_30mins = 0;
	int grow4good_break = 0;
	int grow4good_place = 0;
	int grow4good_trade = 0;
	int grow4good_sb = 0;
	bool grow4good_enter = false;
	int grow4good_provider = 0;
	int grow4good_provider2 = rand() % 450 + 1;
	int grow4good_geiger = 0;
	int grow4good_geiger2 = 0;
	bool punch_aura = false;
	int punch_aura_id = 0;
	bool halloween_prize_receive = false;
	string game_version = "";
	bool updated_clothes = false;
	bool adventure_begins = false, adventure_ends = false, display_age = false, display_home = false;
	vector<int>Fav_Items;
	uint8_t sprite = 0, wild = 6, golem = 6;
	bool Respawning = false;
	bool ONGame = false, Carried_A_Flag = false;
	int Game_Goal_Egg = 0, Game_Player_Hits = 0, Game_Live = 0, Game_Flag = 0;
	string Game_Team = "";
	int Flag_X = 0, Flag_Y = 0;
	string login_pass = "";
	int pearl = 0, rubble = 0;
	bool received_recycle_prize = false;
	int last_state = 0;
	int automatic_bot = 0;
	bool collect_allowed = false;
	int collect_total = 0;
	bool onetimecollect = false;
	bool load_item2 = false;
};
#define pInfo(peer) ((Player*)(peer->data))
struct PlayerMoving {
	int32_t netID, effect_flags_check;
	int packetType, characterState, plantingTree, punchX, punchY, secondnetID;
	float x{}, y, XSpeed{}, YSpeed;
	int packet_3, packet_int_40 = 0;
};
BYTE* packBlockType(int packetType, int plantingTree, int x, int y, int state = 0) {
	BYTE* data = new BYTE[56];
	memset(data, 0, 56);
	memcpy(data + 0, &packetType, 4);
	memcpy(data + 12, &state, 4);
	memcpy(data + 20, &plantingTree, 4);
	memcpy(data + 44, &x, 4);
	memcpy(data + 48, &y, 4);
	return data;
}
class kranken_pattern {
public:
	enum : uint8_t {
		NONE,
		PT1,
		PT2,
		PT3,
		PT4,
		PT5,
		PT6,
		PT7,
		PT8,
		PT9,
		PT10,
		PT11,
		PT12,
	};
	static std::pair<uint32_t, uint32_t> get_pattern(const uint8_t& pattern) {
		switch (pattern) {
		case NONE:
			return { (uint32_t)0, (uint32_t)10962 };
		case PT1:
			return { (uint32_t)1, (uint32_t)10964 };
		case PT2:
			return { (uint32_t)2, (uint32_t)10966 };
		case PT3:
			return { (uint32_t)3, (uint32_t)10968 };
		case PT4:
			return { (uint32_t)4, (uint32_t)10970 };
		case PT5:
			return { (uint32_t)5, (uint32_t)10972 };
		case PT6:
			return { (uint32_t)6, (uint32_t)10974 };
		case PT7:
			return { (uint32_t)7, (uint32_t)10976 };
		case PT8:
			return { (uint32_t)8, (uint32_t)10978 };
		case PT9:
			return { (uint32_t)9, (uint32_t)10980 };
		case PT10:
			return { (uint32_t)10, (uint32_t)10982 };
		case PT11:
			return { (uint32_t)11, (uint32_t)10984 };
		case PT12:
			return { (uint32_t)12, (uint32_t)10986 };
		default:
			return { (uint32_t)0, (uint32_t)10962 };
		}
	}
};
BYTE* PackBlockUpdate(int packetType, int characterState, float x, float y, float XSpeed, float YSpeed, float rotation, int netID, int plantingTree, int punchX, int punchY, int packet_1, int packet_2, int packet_3) {
	BYTE* data = new BYTE[56];
	memset(data, 0, 56);
	memcpy(data + 0, &packetType, 4);
	if (packet_1 != 0) memcpy(data + 1, &packet_1, 4);
	if (packet_2 != 0) memcpy(data + 2, &packet_2, 4);
	if (packet_3 != 0) memcpy(data + 3, &packet_3, 4);
	if (netID !=0 )memcpy(data + 4, &netID, 4);
	if (characterState != 0)memcpy(data + 12, &characterState, 4);
	if (plantingTree != 0)memcpy(data + 20, &plantingTree, 4);
	memcpy(data + 24, &x, 4);
	memcpy(data + 28, &y, 4);
	if (XSpeed != 0) memcpy(data + 32, &XSpeed, 4);
	if (YSpeed !=0)memcpy(data + 36, &YSpeed, 4);
	memcpy(data + 40, &rotation, 4);
	if (punchX != 0)memcpy(data + 44, &punchX, 4);
	if (punchY != 0)memcpy(data + 48, &punchY, 4);
	return data;
}
BYTE* packPlayerMoving(PlayerMoving* dataStruct, int size_ = 56, int some_extra = 0) {
	BYTE* data = new BYTE[size_];
	memset(data, 0, size_);
	memcpy(data + 0, &dataStruct->packetType, 4);
	memcpy(data + 3, &some_extra, 4);
	memcpy(data + 4, &dataStruct->netID, 4);
	memcpy(data + 12, &dataStruct->characterState, 4);
	memcpy(data + 20, &dataStruct->plantingTree, 4);
	memcpy(data + 24, &dataStruct->x, 4);
	memcpy(data + 28, &dataStruct->y, 4);
	memcpy(data + 32, &dataStruct->XSpeed, 4);
	memcpy(data + 36, &dataStruct->YSpeed, 4);
	memcpy(data + 40, &dataStruct->packet_int_40, 4);
	memcpy(data + 44, &dataStruct->punchX, 4);
	memcpy(data + 48, &dataStruct->punchY, 4);
	return data;
}
BYTE* packFishMoving(PlayerMoving* dataStruct, int size_ = 56) {
	BYTE* data = new BYTE[size_];
	memset(data, 0, size_);
	*(__int8*)(data + 0) = 31;
	*(__int8*)(data + 3) = dataStruct->packet_3;
	*(__int16*)(data + 4) = dataStruct->netID;
	*(__int16*)(data + 44) = dataStruct->x;
	*(__int16*)(data + 48) = dataStruct->y;
	return data;
}
void send_raw(ENetPeer* peer, int a1, void* packetData, int packetDataSize, int packetFlag, int delay = 0) {
	ENetPacket* p;
	if (peer) {
		if (a1 == 4 && *((BYTE*)packetData + 12) & 8) {
			p = enet_packet_create(0, packetDataSize + *((DWORD*)packetData + 13) + 5, packetFlag);
			int four = 4;
			memcpy(p->data, &four, 4);
			memcpy((char*)p->data + 4, packetData, packetDataSize);
			memcpy((char*)p->data + packetDataSize + 4, 0, *((DWORD*)packetData + 13));
			if (delay != 0) {
				int deathFlag = 0x19;
				memcpy(p->data + 24, &delay, 4);
				memcpy(p->data + 56, &deathFlag, 4);
			}
		}
		else {
			p = enet_packet_create(0, packetDataSize + 5, packetFlag);
			memcpy(p->data, &a1, 4);
			memcpy((char*)p->data + 4, packetData, packetDataSize);
			if (delay != 0) {
				int deathFlag = 0x19;
				memcpy(p->data + 24, &delay, 4);
				memcpy(p->data + 56, &deathFlag, 4);
			}
		}
		enet_peer_send(peer, 0, p);
	}
}
void send_raw2(ENetPeer* peer, int a1, void* packetData, int packetDataSize, int packetFlag, int delay = 0) {
	ENetPacket* p;
	if (peer) {
		if (a1 == 4 && *((BYTE*)packetData + 12) & 8) {
			p = enet_packet_create(0, packetDataSize + *((DWORD*)packetData + 13) + 5, packetFlag);
			int four = 4;
			memcpy(p->data, &four, 4);
			memcpy(p->data + 24, &delay, 4);
			memcpy((char*)p->data + 4, packetData, packetDataSize);
			memcpy((char*)p->data + packetDataSize + 4, 0, *((DWORD*)packetData + 13));
		}
		else {
			p = enet_packet_create(0, packetDataSize + 5, packetFlag);
			memcpy(p->data, &a1, 4);
			memcpy((char*)p->data + 4, packetData, packetDataSize);
		}
		enet_peer_send(peer, 0, p);
	}
}
void send_inventory(ENetPeer* peer) {
	size_t inv_size = (pInfo(peer)->inv.size() > 476 ? 476 : pInfo(peer)->inv.size());
	int packetLen = 66 + (inv_size * 4) + 4, MessageType = 0x4, PacketType = 0x9, NetID = -1, CharState = 0x8, state56 = 6 + (inv_size * 4) + 4, bruh = 1;
	BYTE* d_ = new BYTE[packetLen];
	memset(d_, 0, packetLen);
	memcpy(d_, &MessageType, 1);
	memcpy(d_ + 4, &PacketType, 4);
	memcpy(d_ + 8, &NetID, 4);
	memcpy(d_ + 16, &CharState, 4);
	memcpy(d_ + 56, &state56, 4);
	memcpy(d_ + 60, &bruh, 4);
	memcpy(d_ + 61, &inv_size, 4);
	memcpy(d_ + 65, &inv_size, 4);
	vector<pair<uint16_t, uint8_t>> send_later;
	int offset = 67;
	for (int i_ = 0; i_ < inv_size; ++i_) {
		if (pInfo(peer)->inv[i_].first == 9850 || pInfo(peer)->inv[i_].first == 9812 || pInfo(peer)->inv[i_].first == 7782 || pInfo(peer)->inv[i_].first == 9902 || pInfo(peer)->inv[i_].first == 9636 || pInfo(peer)->inv[i_].first == 9726 || pInfo(peer)->inv[i_].first == 9500 || pInfo(peer)->inv[i_].first == 9584 || pInfo(peer)->inv[i_].first == 9586 || pInfo(peer)->inv[i_].first == 9588 || pInfo(peer)->inv[i_].first == 9590 || pInfo(peer)->inv[i_].first == 9550 || pInfo(peer)->inv[i_].first == 9582 || pInfo(peer)->inv[i_].first == 9580 || pInfo(peer)->inv[i_].first == 9578 || pInfo(peer)->inv[i_].first == 9572 || pInfo(peer)->inv[i_].first == 9570 || pInfo(peer)->inv[i_].first == 9568 || pInfo(peer)->inv[i_].first == 9566 || pInfo(peer)->inv[i_].first == 9564 || pInfo(peer)->inv[i_].first == 9562 || pInfo(peer)->inv[i_].first == 9560 || pInfo(peer)->inv[i_].first == 9558 || pInfo(peer)->inv[i_].first == 9490 || pInfo(peer)->inv[i_].first == 9492 || pInfo(peer)->inv[i_].first == 9490 || pInfo(peer)->inv[i_].first == 9492 || pInfo(peer)->inv[i_].first == 9516 || pInfo(peer)->inv[i_].first == 9540) send_later.push_back(make_pair(pInfo(peer)->inv[i_].first, pInfo(peer)->inv[i_].second));
		else {
			*(__int16*)(d_ + offset) = pInfo(peer)->inv[i_].first; offset += 2;
			*(__int8*)(d_ + offset) = pInfo(peer)->inv[i_].second; offset += 2;
		}
	}
	ENetPacket* const p_ = enet_packet_create(d_, packetLen, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, p_);
	delete[] d_;
	if (send_later.size() > 0) {
		PlayerMoving data_{};
		data_.packetType = 13;
		for (int i = 0; i < send_later.size(); i++) {
			data_.plantingTree = send_later[i].first;
			BYTE* raw = packPlayerMoving(&data_);
			raw[3] = send_later[i].second;
			send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
			delete[]raw;
		}
	}
}
void send_packet(ENetPeer* peer, const void* data, uintmax_t data_size, uint32_t flags) {
	ENetPacket* packet = enet_packet_create(data, data_size, flags);
	if (!packet) return;
	if (enet_peer_send(peer, 0, packet) != 0) enet_packet_destroy(packet);
}
void send_packet(ENetPeer* peer, uint32_t type, const void* data, uintmax_t data_size, uint32_t flags) {
	ENetPacket* packet = enet_packet_create(nullptr, 5 + data_size, flags);
	if (!packet) return;
	memcpy(packet->data, &type, 4);
	packet->data[data_size + 4] = 0;
	if (data) memcpy(packet->data + 4, data, data_size);
	if (enet_peer_send(peer, 0, packet) != 0) enet_packet_destroy(packet);
}
string CooldownText(int seconds) {
	string x;
	int day = seconds / (24 * 3600);
	if (day != 0) x.append(to_string(day) + " days, ");
	seconds = seconds % (24 * 3600);
	int hour = seconds / 3600;
	if (hour != 0) x.append(to_string(hour) + " hours, ");
	seconds %= 3600;
	int minutes = seconds / 60;
	if (minutes != 0) x.append(to_string(minutes) + " mins, ");
	seconds %= 60;
	int secondsz = seconds;
	if (secondsz != 0) x.append(to_string(secondsz) + " secs ");
	return x;
}
std::string get_player_custom_wrench(ENetPeer* peer) {
	return "{\"PlayerWorldID\":" + to_string(pInfo(peer)->netID) + ",\"TitleTexture\":\"" + pInfo(peer)->TitleTexture + "\",\"TitleTextureCoordinates\":\"" + pInfo(peer)->TitleCoordinate + "\",\"WrenchCustomization\":{\"WrenchForegroundCanRotate\":true,\"WrenchForegroundID\":" + to_string(pInfo(peer)->wrench_foreground_custom) + ",\"WrenchIconID\":" + to_string(pInfo(peer)->wrench_custom) + "}}";
}