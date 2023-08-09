#include "clicker.h"
#include "../gui/gui.h"

std::string getbindtext(size_t hex);

void vars::binds::thread() {
    
	while (gui::isRunning) {

		if (vars::clicker::bind_pressed) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			
            bool first_loop = false;
			
			for (size_t i = 3; i < 256; i++) {

				if (i != 13) {

					if (GetAsyncKeyState((i)&SHRT_MAX)) {

						if (!first_loop) {

							vars::clicker::bind_selected = i;
							vars::clicker::bindstr = getbindtext(i);

							if (i == 27) {
								vars::clicker::bindstr = "[NONE]";
								vars::clicker::bind_selected = 0;

							}
							std::this_thread::sleep_for(std::chrono::milliseconds(250));
							vars::clicker::bind_pressed = false;
						}
					}
				}
			}
			
            
		}
		if (vars::rightclicker::bind_pressed) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));

			bool first_loop = false;

			for (size_t i = 3; i < 256; i++) {

				if (i != 13) {

					if (GetAsyncKeyState((i)&SHRT_MAX)) {

						if (!first_loop) {

							vars::rightclicker::bind_selected = i;
							vars::rightclicker::bindstr = getbindtext(i);

							if (i == 27) {
								vars::rightclicker::bindstr = "[NONE]";
								vars::rightclicker::bind_selected = 0;

							}
							std::this_thread::sleep_for(std::chrono::milliseconds(250));
							vars::rightclicker::bind_pressed = false;
						}
					}
				}
			}


		}
		if (vars::hideUI::bind_pressed) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			
			bool first_loop = false;
			
			for (size_t i = 3; i < 256; i++) {

				if (i != 13) {

					if (GetAsyncKeyState((i)&SHRT_MAX)) {

						if (!first_loop) {

							vars::hideUI::bind_selected = i;
							vars::hideUI::bindstr = getbindtext(i);

							if (i == 27) {
								vars::hideUI::bindstr = "[NONE]";
								vars::hideUI::bind_selected = 0;

							}
							std::this_thread::sleep_for(std::chrono::milliseconds(250));
							vars::hideUI::bind_pressed = false;
						}
					}
				}
			}
			
			
		}
		if (vars::clicker::roblos::bind_pressed) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));

			bool first_loop = false;

			for (size_t i = 3; i < 256; i++) {

				if (i != 13) {

					if (GetAsyncKeyState((i)&SHRT_MAX)) {

						if (!first_loop) {

							vars::clicker::roblos::bind_selected = i;
							vars::clicker::roblos::bindstr = getbindtext(i);

							if (i == 27) {
								vars::clicker::roblos::bindstr = "[NONE]";
								vars::clicker::roblos::bind_selected = 0;

							}
							std::this_thread::sleep_for(std::chrono::milliseconds(250));
							vars::clicker::roblos::bind_pressed = false;
						}
					}
				}
			}


		}

		if (GetAsyncKeyState(vars::clicker::bind_selected) & 0x8000) {
			if (!vars::clicker::enabled) {
				while (GetAsyncKeyState(vars::clicker::bind_selected) & 0x8000) {
					std::this_thread::sleep_for(std::chrono::milliseconds(5));
				}vars::clicker::enabled = true;
			}
			else {
				while (GetAsyncKeyState(vars::clicker::bind_selected) & 0x8000) {
					std::this_thread::sleep_for(std::chrono::milliseconds(5));
				}vars::clicker::enabled = false;
			}
		}

		if (GetAsyncKeyState(vars::hideUI::bind_selected)) {
			if (!vars::binds::hide) {
				ShowWindow(gui::window, SW_HIDE);
				while (GetAsyncKeyState(vars::hideUI::bind_selected) & 0x8000) {
					std::this_thread::sleep_for(std::chrono::milliseconds(5));
				}vars::binds::hide = true;
			}
			else {
				ShowWindow(gui::window, SW_SHOW);
				while (GetAsyncKeyState(vars::hideUI::bind_selected) & 0x8000) {
					std::this_thread::sleep_for(std::chrono::milliseconds(5));
				}vars::binds::hide = false;
			}

		}
		if (GetAsyncKeyState(vars::rightclicker::bind_selected) & 0x8000) {
			if (!vars::rightclicker::enabled) {
				while (GetAsyncKeyState(vars::rightclicker::bind_selected) & 0x8000) {
					std::this_thread::sleep_for(std::chrono::milliseconds(5));
				}vars::rightclicker::enabled = true;
			}
			else {
				while (GetAsyncKeyState(vars::rightclicker::bind_selected) & 0x8000) {
					std::this_thread::sleep_for(std::chrono::milliseconds(5));
				}vars::rightclicker::enabled = false;
			}
		}
		if (GetAsyncKeyState(vars::clicker::roblos::bind_selected) & 0x8000) {
			if (!vars::clicker::roblos::enabled) {
				while (GetAsyncKeyState(vars::clicker::roblos::bind_selected) & 0x8000) {
					std::this_thread::sleep_for(std::chrono::milliseconds(5));
				}vars::clicker::roblos::enabled = true;
			}
			else {
				while (GetAsyncKeyState(vars::clicker::roblos::bind_selected) & 0x8000) {
					std::this_thread::sleep_for(std::chrono::milliseconds(5));
				}vars::clicker::roblos::enabled = false;
			}
		}
		

		std::this_thread::sleep_for(std::chrono::milliseconds(5));

	}
}


std::string getbindtext(size_t hex) {
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