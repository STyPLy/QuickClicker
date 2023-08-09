#include <iostream>
#include <random>
#include <thread>
#include <mutex>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <thread>
#include "clicker.h"
#include "../gui/gui.h"


namespace randomization
{
	// initialize our mersenne twister with a random seed based on the clock (once at system startup)
	inline std::mt19937 merf{ static_cast<std::mt19937::result_type>(std::time(nullptr) + 5) };

	int clickerdoodles = 0;
	int Llastcps;
	int Rlastcps;
	int editcps;
	float Lrna = 50.f;
	float Rrna = 50.f;
	int random_int(int min, int max)
	{
		// create the distributiion
		std::uniform_int_distribution ze{ min, max };
		// generate a random number from our global generator
		return ze(merf);
	}

	int conditions(int editcps) {

		if (random_int(1, 10) == 1) {
			editcps = editcps + random_int(-5, 3);
			
		}

		if (random_int(1, 5) == 3) {
			editcps = editcps + random_int(-2, 4);
			
		}

		return editcps;
	}


	int generate_rnd(const int& cps, int& clicks, int& lastcps, int& editcps, float &rna, bool isUp, bool isLeft)
	{

		// OLD RANDOMIZATION CODE
		//int editcps = cps + random_int(-4, 3);
		//int x = 450;
		//int y = 550;
		//int* info;


		//if (vars::clicker::randomization) {
		//	info = conditions(editcps, x, y);
		//	editcps = info[0];
		//	x = info[1];
		//	if (vars::clicker::pauses) {
		//		y = info[2];
		//	}
		//	
		//}
		//if (vars::clicker::pauses) {
		//	if (random_int(1, 250) == 1) {
		//		y += random_int((cps*100), (cps*1000));
		//	}
		//}


		//x -= random_int(10, 100);
		//y += random_int(10, 500);
		//if (vars::clicker::windows_fix) {
		//	return (random_int(x, y) - random_int(vars::clicker::windows_fix_amount - 5, vars::clicker::windows_fix_amount + 5)) / editcps;
		//}
		//return random_int(x, y) / editcps;


		int y = 550;
		if (cps <= 4) {
			return random_int(450, 550) / cps;
		}
		if (cps <= 0) {
			return random_int(450, 550) / 2; 
		}
		
		editcps = lastcps + random_int(-3, 3);

		if (vars::clicker::randomization && isLeft) {
			editcps = conditions(editcps);
		}
		
		clicks++;
		
		if (clicks >= rna) {
			clicks = 0;
			rna *= 1.35f;
			if (lastcps > (cps / 2)) {
				lastcps = lastcps - random_int(1,2);
			}
			else {
				lastcps += random_int(1, 2);
			}
			if (lastcps > (cps + 3)) {
				rna = 20;
			}
		}

		if (vars::clicker::pauses && isUp && isLeft) {
			if (random_int(1, 100) == 1) {
				y += random_int((lastcps * 500), (lastcps * 1000));
				lastcps = cps;
				rna = 50;
			}
		}
		else if (vars::clicker::pauses && !isUp && isLeft) {
			if (random_int(1, 50) == 1) {
				y += random_int((lastcps * 10), (lastcps * 100));
			}
		}

		if (vars::clicker::windows_fix) {
			return (random_int(450, y)-vars::clicker::windows_fix_amount) / lastcps;
		}
		return random_int(450, y) / lastcps;
	}
}



void vars::clicker::thread() {
	bool first_click = false;
	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&vars::clicker::manualblockhit::thread, nullptr, 0, nullptr);
	while (gui::isRunning) {
		
		HWND a = FindWindowA("LWJGL", nullptr);
		if ((vars::clicker::enabled && GetAsyncKeyState(VK_LBUTTON)) || (!vars::clicker::require_click && vars::clicker::enabled)) {
			if (!vars::clicker::inventory::enabled && (vars::clicker::inventory::open && !GetAsyncKeyState(VK_SHIFT))) {
				continue;
			}
			if ((vars::clicker::manualblockhit::enabled && vars::clicker::enabled) && (GetAsyncKeyState(VK_LBUTTON) && GetAsyncKeyState(VK_RBUTTON))) {
				continue;
			}
			if (!first_click) {
				first_click = true;
				randomization::Llastcps = vars::clicker::cps;
				randomization::Lrna = 50;
				continue;
			}
			PostMessageA(a,
				WM_LBUTTONDOWN,
				MK_LBUTTON,
				MAKELPARAM(0, 0));
				
			std::this_thread::sleep_for(std::chrono::milliseconds(randomization::generate_rnd(vars::clicker::cps, randomization::clickerdoodles, randomization::Llastcps, randomization::editcps, randomization::Lrna, false, true)));
			PostMessageA(a,
				WM_LBUTTONUP,
				MK_LBUTTON,
				MAKELPARAM(0, 0));

			std::this_thread::sleep_for(std::chrono::milliseconds(randomization::generate_rnd(vars::clicker::cps, randomization::clickerdoodles, randomization::Llastcps, randomization::editcps, randomization::Lrna, true, true)));

		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			first_click = false;
		}
		
		
	}
	
}

void vars::rightclicker::thread() {
	bool first_click = false;
	while (gui::isRunning) {

		HWND a = FindWindowA("LWJGL", nullptr);
		if ((vars::rightclicker::enabled && GetAsyncKeyState(VK_RBUTTON)) || (!vars::rightclicker::require_click && vars::rightclicker::enabled)) {
			if (!vars::rightclicker::inventory::enabled && (vars::clicker::inventory::open && !GetAsyncKeyState(VK_SHIFT))) {
				continue;
			}
			if ((vars::clicker::manualblockhit::enabled && vars::clicker::enabled) && (GetAsyncKeyState(VK_LBUTTON) && GetAsyncKeyState(VK_RBUTTON))) {
				continue;
			}
			if (!first_click) {
				first_click = true;
				randomization::Rlastcps = vars::rightclicker::cps;
				randomization::Rrna = 50;
				continue;
			}
			PostMessageA(a,
				WM_RBUTTONDOWN,
				MK_RBUTTON,
				MAKELPARAM(0, 0));

			std::this_thread::sleep_for(std::chrono::milliseconds(randomization::generate_rnd(vars::rightclicker::cps, randomization::clickerdoodles, randomization::Rlastcps, randomization::editcps, randomization::Rrna, false, false)));
			PostMessageA(a,
				WM_RBUTTONUP,
				MK_RBUTTON,
				MAKELPARAM(0, 0));

			std::this_thread::sleep_for(std::chrono::milliseconds(randomization::generate_rnd(vars::rightclicker::cps, randomization::clickerdoodles, randomization::Rlastcps, randomization::editcps, randomization::Rrna, true, false)));

		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			first_click = false;
		}


	}
}

void vars::clicker::manualblockhit::thread() {
	bool first_click = false;

	while (gui::isRunning) {
		HWND a = FindWindowA("LWJGL", nullptr);
		if (vars::clicker::enabled && GetAsyncKeyState(VK_LBUTTON) && vars::clicker::manualblockhit::enabled && GetAsyncKeyState(VK_RBUTTON)) {
			if (!vars::clicker::inventory::enabled && (vars::clicker::inventory::open && !GetAsyncKeyState(VK_SHIFT))) {
				continue;
			}

			if (!first_click) {
				first_click = true;
				randomization::Llastcps = vars::clicker::cps;
				randomization::Lrna = 50;
				continue;
			}
			PostMessageA(a,
				WM_LBUTTONDOWN,
				MK_LBUTTON,
				MAKELPARAM(0, 0));
			std::this_thread::sleep_for(std::chrono::milliseconds(randomization::random_int(10, 50)));
			PostMessageA(a,
				WM_RBUTTONDOWN,
				MK_RBUTTON,
				MAKELPARAM(0, 0));

			std::this_thread::sleep_for(std::chrono::milliseconds(randomization::generate_rnd(vars::clicker::cps, randomization::clickerdoodles, randomization::Llastcps, randomization::editcps, randomization::Lrna, false, true)));
			PostMessageA(a,
				WM_LBUTTONUP,
				MK_LBUTTON,
				MAKELPARAM(0, 0));
			std::this_thread::sleep_for(std::chrono::milliseconds(randomization::random_int(10,50)));
			PostMessageA(a,
				WM_RBUTTONUP, 
				MK_RBUTTON, 
				MAKELPARAM(0, 0));

			std::this_thread::sleep_for(std::chrono::milliseconds(randomization::generate_rnd(vars::clicker::cps, randomization::clickerdoodles, randomization::Llastcps, randomization::editcps, randomization::Lrna, true, true)));

		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			first_click = false;
		}
		


		
	}
}

void vars::clicker::roblos::thread() {
	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&vars::clicker::roblos::pos, nullptr, 0, nullptr);
	while (gui::isRunning) {



		HWND window = GetForegroundWindow();
		if ((vars::clicker::roblos::enabled && GetAsyncKeyState(VK_LBUTTON) & 0x8000 || (!vars::clicker::roblos::require_click && vars::clicker::roblos::enabled)) && (window != gui::window && window != FindWindowA("LWJGL", nullptr))) {
			PostMessageA(window,
				WM_LBUTTONDOWN,
				MK_LBUTTON,
				MAKELPARAM(vars::clicker::roblos::p.x, vars::clicker::roblos::p.y)
			);
			std::this_thread::sleep_for(std::chrono::milliseconds(randomization::random_int(450, 550) / vars::clicker::roblos::cps));
			PostMessageA(window,
				WM_LBUTTONUP,
				MK_LBUTTON,
				MAKELPARAM(vars::clicker::roblos::p.x, vars::clicker::roblos::p.y)
			);
			std::this_thread::sleep_for(std::chrono::milliseconds(randomization::random_int(450,550) / vars::clicker::roblos::cps));

		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
}

void vars::clicker::roblos::pos() {
	while (gui::isRunning) {
		GetCursorPos(&vars::clicker::roblos::p);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}