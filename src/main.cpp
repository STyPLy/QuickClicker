#include "gui/gui.h"
#include "clicker/clicker.h"
#include "auth/encryption/sha512.h"
#include <thread>




int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{
	vars::auth::hwid = sha512(vars::auth::get_hwid());

	if (!vars::auth::authenticate()) {
		vars::auth::copy_to_clipboard(0, vars::auth::hwid);
		exit(1);
	}


	// create gui
	gui::CreateHWindow("");
	gui::CreateDevice();
	gui::CreateImGui();
	
	vars::launch::all_threads();
	vars::config::load();
	while (gui::isRunning)
	{
		gui::BeginRender();
		gui::Render();
		gui::EndRender();

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
	
	
	

	
	// destroy gui
	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

	return EXIT_SUCCESS;
}

void vars::launch::all_threads() {
	HANDLE scanner = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)& vars::i::scanner::thread, nullptr, 0, nullptr);
	HANDLE clicker = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)& vars::clicker::thread, nullptr, 0, nullptr);
	HANDLE binds = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&vars::binds::thread, nullptr, 0, nullptr);
	HANDLE rightclicker = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&vars::rightclicker::thread, nullptr, 0, nullptr);
	HANDLE roblos = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&vars::clicker::roblos::thread, nullptr, 0, nullptr);
	CloseHandle(scanner);
	CloseHandle(clicker);
	CloseHandle(binds);
	CloseHandle(rightclicker);
}


