#include "../clicker/clicker.h"
#include "json.h"
std::string getbindtexts(size_t hex);


void vars::config::save() {
	Json::Value d;
	std::string res;

	d["hwid"] = vars::auth::hwid;
	d["LEFT_CPS"] = vars::clicker::cps;
	
	d["WINDOWS_FIX"] = vars::clicker::windows_fix_amount;
	
	d["randomization"] = vars::clicker::randomization;
	d["pauses"] = vars::clicker::pauses;
	d["require_click"] = vars::clicker::require_click;
	d["inventory"] = vars::clicker::inventory::enabled;


	d["RIGHT_CPS"] = vars::rightclicker::cps;
	
	d["LEFT_BIND"] = vars::clicker::bind_selected;
	d["RIGHT_BIND"] = vars::rightclicker::bind_selected;
	d["HIDE_MENU_BIND"] = vars::hideUI::bind_selected;

	vars::auth::getf(d.toStyledString(), "config/save");

	


	

}


void vars::config::load() {
	try {
		Json::Reader reader;
		Json::Value d;
		std::string response;
		d["hwid"] = vars::auth::hwid;
		std::vector<char>* buf = vars::auth::getf(d.toStyledString(), "config/load");

		for (const auto& i : *buf) {
			response.push_back(i);
		}
		delete buf;

		bool success = reader.parse(response, d);
		if (!success) {
			return;
		}

		vars::clicker::cps = d["LEFT_CPS"].asInt();
		vars::rightclicker::cps = d["RIGHT_CPS"].asInt();
		vars::clicker::windows_fix_amount = d["WINDOWS_FIX"].asInt();
		vars::clicker::randomization = d["randomization"].asBool();
		vars::clicker::pauses = d["pauses"].asBool();
		vars::clicker::require_click = d["require_click"].asBool();
		vars::clicker::inventory::enabled = d["inventory"].asBool();
		

		vars::clicker::bind_selected = d["LEFT_BIND"].asInt();
		vars::rightclicker::bind_selected = d["RIGHT_BIND"].asInt();
		vars::hideUI::bind_selected = d["HIDE_MENU_BIND"].asInt();

		if (vars::clicker::bind_selected != 0) {
			vars::clicker::bindstr = getbindtexts(d["LEFT_BIND"].asInt());

		}
		if (vars::rightclicker::bind_selected != 0) {
			vars::rightclicker::bindstr = getbindtexts(d["RIGHT_BIND"].asInt());

		}
		if (vars::hideUI::bind_selected != 0) {
			vars::hideUI::bindstr = getbindtexts(d["HIDE_MENU_BIND"].asInt());
		}

	}
	catch (std::string& ex) {
		return;
	}
	
	

}

std::string getbindtexts(size_t hex) {
	const char* const key_string[] = {
		"Unknown",
		"LButton",
		"RButton",
		"CANCEL",
		"MButton",
		"MButton2",
		"MButton3",
		"Unknown",
		"Back",
		"Tab",
		"Unknown",
		"Unknown",
		"Clear",
		"Return",
		"Unknown",
		"Unknown",
		"Shift",
		"Control",
		"Menu",
		"Pause",
		"Capital",
		"Unknown",
		"Unknown",
		"Unknown",
		"Final",
		"Unknown",
		"Unknown",
		"Escape",
		"Convert",
		"NonConvert",
		"Accept",
		"ModeChange",
		"Space",
		"Prior",
		"Next",
		"End",
		"Home",
		"Left",
		"Up",
		"Right",
		"Down",
		"Select",
		"Print",
		"Execute",
		"SnpShot",
		"Insert",
		"Delete",
		"Help",
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"Lwin",
		"Rwin",
		"Apps",
		"Unknown",
		"Sleep",
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"*",
		"+",
		"Separator",
		"-",
		"Decimal",
		"/",
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"F11",
		"F12",
		"F13",
		"F14",
		"F15",
		"F16",
		"F17",
		"F18",
		"F19",
		"F20",
		"F21",
		"F22",
		"F23",
		"F24",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Numlock",
		"Scroll",
		"Equal",
		"Masshou",
		"Touroku",
		"Loya",
		"Roya",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"LShift",
		"RShift",
		"Control",
		"Control",
		"Menu",
		"RMenu",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
	};
	return "[BIND: " + std::string(key_string[hex]) + "]";
}