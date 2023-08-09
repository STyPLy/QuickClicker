#pragma once
#include <iostream>
#include <random>
#include <thread>
#include <mutex>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <thread>
#include <ostream>
#include <sstream>
#include <TlHelp32.h>
#include "../auth/xorstr.h"
namespace vars
{	

	namespace config {
		extern void save();
		extern void load();
		inline bool saved = false;
		inline std::string config;

	}


	namespace auth {

		extern std::string ze();
		inline std::string hwid;
		inline std::string user;
		extern std::vector<char>* getf(std::string params, std::string path);
		extern bool authenticate();
		inline std::string version = xorstr("1.3.0");
		inline void copy_to_clipboard(HWND hwnd, const std::string& s) {

			OpenClipboard(hwnd);
			EmptyClipboard();
			HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
			if (!hg) {

				CloseClipboard();
				return;
			}
			memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
			GlobalUnlock(hg);
			SetClipboardData(CF_TEXT, hg);
			CloseClipboard();
			GlobalFree(hg);
		}
		inline std::string get_hwid() {
			char* drive_name;
			size_t len;
			std::string hwid;

			errno_t err = _dupenv_s(&drive_name, &len, xorstr("SystemDrive"));

			if (err == 0 && drive_name != NULL) {
				hwid = std::string(drive_name);
				hwid.append(xorstr("\\"));
				DWORD drive_serial = 0;
				GetVolumeInformationA(hwid.c_str(), nullptr, NULL, &drive_serial,
					nullptr, nullptr, nullptr, NULL);

				std::ostringstream o;
				o << std::hex << HIWORD(drive_serial) << LOWORD(drive_serial);
				hwid = o.str();


				free(drive_name);

			}
			

			return hwid;
		}
	}
	
	namespace destruct {
		extern void run();
		inline DWORD get_pid(const std::string& process_name) {
			PROCESSENTRY32 process_info;
			process_info.dwSize = sizeof(process_info);

			HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
			if (snapshot == INVALID_HANDLE_VALUE)
				return 0;

			Process32First(snapshot, &process_info);
			if (!process_name.compare(process_info.szExeFile)) {
				CloseHandle(snapshot);
				return process_info.th32ProcessID;
			}

			while (Process32Next(snapshot, &process_info)) {
				if (!process_name.compare(process_info.szExeFile)) {
					CloseHandle(snapshot);
					return process_info.th32ProcessID;
				}
			}

			CloseHandle(snapshot);

			return 0;
		}
		inline DWORD get_service_pid(const std::string& service_name) {
			SC_HANDLE scm = OpenSCManager(nullptr, nullptr, NULL);
			SC_HANDLE sc = OpenService(scm, service_name.c_str(), SERVICE_QUERY_STATUS);

			SERVICE_STATUS_PROCESS ssp = { 0 };
			DWORD bytes_needed = 0;
			QueryServiceStatusEx(sc, SC_STATUS_PROCESS_INFO, reinterpret_cast<LPBYTE>(&ssp), sizeof(ssp),
				&bytes_needed);

			CloseServiceHandle(sc);
			CloseServiceHandle(scm);

			return ssp.dwProcessId;
		}
		inline void terminate_process(DWORD pid) {
			if (HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, false, pid)) {
				BOOL result = TerminateProcess(hProcess, 1);
				CloseHandle(hProcess);
			}
		}
	}

	namespace hideUI {
		inline size_t bind_selected;
		inline std::string bindstr = "[NONE]";
		inline bool bind_pressed = false;
		inline bool isSelected = false;
	}


	namespace i {
		inline HANDLE minecraft_handle;
		inline HWND minecraft_window;
		namespace scanner {
			
			extern void thread();

		}
	}
	namespace clicker {
		extern void thread();

		namespace roblos {
			extern void thread();
			inline int cps = 50;
			inline bool enabled = false;
			inline bool require_click = false;
			inline bool isSelected = false;

			inline bool bind_pressed = false;
			inline size_t bind_selected;
			inline std::string bindstr = "[NONE]";
			inline POINT p;
			extern void pos();
		}
		

		namespace manualblockhit {
			extern void thread();
			inline bool enabled = false;
		}
		namespace inventory {
			inline bool enabled = false;
			inline bool open = false;
		}
		inline bool isSelected = true;

		inline int key{};
		inline bool randomization = true;
		inline int cps = 14;
		inline bool enabled = false;
		inline bool bind_pressed = false;
		inline size_t bind_selected;
		inline std::string bindstr = "[NONE]";
		inline int windows_fix_amount = 100;
		inline bool windows_fix = false;

		inline bool require_click = true;
		inline bool pauses = true;
	}
	
	namespace rightclicker {
		
		extern void thread();
		namespace inventory {
			inline bool enabled = false;
			inline bool open = false;
		}
		inline bool isSelected = false;

		inline int key{};
		inline bool randomization = true;
		inline int cps = 17;
		inline bool enabled = false;
		inline bool bind_pressed = false;
		inline size_t bind_selected;
		inline std::string bindstr = "[NONE]";
		inline int windows_fix_amount = 100;
		inline bool windows_fix = false;

		inline bool require_click = true;
		inline bool pauses = true;
	}

	namespace binds {
		extern void thread();
		
		inline bool hide = false;
	}


	namespace launch {
		extern void all_threads();
	}
	
}