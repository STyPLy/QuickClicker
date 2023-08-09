#include "gui.h"
#include "font.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx9.h"
#include "../../imgui/imgui_impl_win32.h"
#include "../clicker/clicker.h"


using namespace gui;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter
);

long __stdcall WindowProcess(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter)
{
	if (ImGui_ImplWin32_WndProcHandler(window, message, wideParameter, longParameter))
		return true;

	switch (message)
	{
	case WM_SIZE: {
		if (gui::device && wideParameter != SIZE_MINIMIZED)
		{
			gui::presentParameters.BackBufferWidth = LOWORD(longParameter);
			gui::presentParameters.BackBufferHeight = HIWORD(longParameter);
			gui::ResetDevice();
		}
	}return 0;

	case WM_SYSCOMMAND: {
		if ((wideParameter & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
	}break;

	case WM_DESTROY: {
		PostQuitMessage(0);
	}return 0;

	case WM_LBUTTONDOWN: {
		gui::position = MAKEPOINTS(longParameter); // set click points
	}return 0;

	case WM_MOUSEMOVE: {
		if (wideParameter == MK_LBUTTON)
		{
			const auto points = MAKEPOINTS(longParameter);
			auto rect = ::RECT{ };

			GetWindowRect(gui::window, &rect);

			rect.left += points.x - gui::position.x;
			rect.top += points.y - gui::position.y;

			if (gui::position.x >= 0 &&
				gui::position.x <= gui::WIDTH &&
				gui::position.y >= 0 && gui::position.y <= 19)
				SetWindowPos(
					gui::window,
					HWND_TOPMOST,
					rect.left,
					rect.top,
					0, 0,
					SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER
				);
		}

	}return 0;

	}

	return DefWindowProc(window, message, wideParameter, longParameter);
}

void gui::CreateHWindow(const char* windowName) noexcept
{
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_CLASSDC;
	windowClass.lpfnWndProc = WindowProcess;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandleA(0);
	windowClass.hIcon = 0;
	windowClass.hCursor = 0;
	windowClass.hbrBackground = 0;
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = "class001";
	windowClass.hIconSm = 0;

	RegisterClassEx(&windowClass);

	gui::window = CreateWindowEx(
		0,
		"class001",
		windowName,
		WS_POPUP,
		100,
		100,
		gui::WIDTH,
		gui::HEIGHT,
		0,
		0,
		windowClass.hInstance,
		0
	);

	ShowWindow(window, SW_SHOWDEFAULT);
	UpdateWindow(window);
}

void gui::DestroyHWindow() noexcept
{
	DestroyWindow(window);
	UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
}

bool gui::CreateDevice() noexcept
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (!d3d)
		return false;

	ZeroMemory(&presentParameters, sizeof(presentParameters));

	presentParameters.Windowed = TRUE;
	presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParameters.BackBufferFormat = D3DFMT_UNKNOWN;
	presentParameters.EnableAutoDepthStencil = TRUE;
	presentParameters.AutoDepthStencilFormat = D3DFMT_D16;
	presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	if (d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&presentParameters,
		&device) < 0)
		return false;

	return true;
}

void gui::ResetDevice() noexcept
{
	ImGui_ImplDX9_InvalidateDeviceObjects();

	const auto result = gui::device->Reset(&gui::presentParameters);

	if (result == D3DERR_INVALIDCALL)
		IM_ASSERT(0);

	ImGui_ImplDX9_CreateDeviceObjects();
}

void gui::DestroyDevice() noexcept
{
	if (gui::device)
	{
		gui::device->Release();
		gui::device = nullptr;
	}

	if (gui::d3d)
	{
		gui::d3d->Release();
		gui::d3d = nullptr;
	}
}

void gui::CreateImGui() noexcept
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::GetIO().IniFilename = nullptr;
	
	ImFontConfig font;
	font.FontDataOwnedByAtlas = false;
	ImGui::GetIO().Fonts->AddFontFromMemoryTTF((void*)rawData, sizeof(rawData), 17.f, &font);


	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);      
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.48f, 0.64f, 0.43f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.48f, 0.64f, 0.43f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.48f, 0.64f, 0.43f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.09f, 0.12f, 0.12f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.09f, 0.12f, 0.12f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.48f, 0.64f, 0.43f, 1.0f);
	style.FrameRounding = 12.0f;
	// 0.46f, 0.61f, 0.39f, 1.0f
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);
}

void gui::DestroyImGui() noexcept
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void gui::BeginRender() noexcept
{
	MSG message;
	while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);

		if (message.message == WM_QUIT)
		{
			isRunning = !isRunning;
			return;
		}
	}

	// Start the Dear ImGui frame
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void gui::EndRender() noexcept
{
	
	ImGui::EndFrame();

	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(47, 79, 79, 255), 1.0f, 0);

	if (device->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		device->EndScene();
	}

	const auto result = device->Present(0, 0, 0, 0);

	// Handle loss of D3D9 device
	if (result == D3DERR_DEVICELOST && device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		ResetDevice();
}

void gui::Render() noexcept
{
	


	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::SetNextWindowSize({ WIDTH, HEIGHT });
	ImGui::Begin(
		"QuickClicker",
		&isRunning,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove
	);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.09f, 0.12f, 0.12f, 1.0f));
	if (vars::clicker::isSelected) {
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
	}

	ImGui::Button("LEFT CLICKER");
	if (ImGui::IsItemClicked()) {
		vars::clicker::isSelected = true;
		vars::rightclicker::isSelected = false;
		vars::hideUI::isSelected = false;
		vars::clicker::roblos::isSelected = false;
	}
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.09f, 0.12f, 0.12f, 1.0f));
	ImGui::SameLine(0.0F,5.0F);

	if (vars::rightclicker::isSelected) {
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
	}


	ImGui::Button("RIGHT CLICKER");
	if (ImGui::IsItemClicked()) {
		vars::clicker::isSelected = false;
		vars::rightclicker::isSelected = true;
		vars::hideUI::isSelected = false;
		vars::clicker::roblos::isSelected = false;
	}
	ImGui::SameLine(0.0F, 5.0F);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.09f, 0.12f, 0.12f, 1.0f));


	if (vars::clicker::roblos::isSelected) {
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
	}
	ImGui::Button("ROBLOS");
	if (ImGui::IsItemClicked()) {
		vars::hideUI::isSelected = false;
		vars::clicker::isSelected = false;
		vars::rightclicker::isSelected = false;
		vars::clicker::roblos::isSelected = true;
	}
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.09f, 0.12f, 0.12f, 1.0f));
	ImGui::SameLine(0.0f, 5.0f);




	if (vars::hideUI::isSelected) {
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
	}



	ImGui::Button("MENU");
	if (ImGui::IsItemClicked()) {
		vars::hideUI::isSelected = true;
		vars::clicker::isSelected = false;
		vars::rightclicker::isSelected = false;
		vars::clicker::roblos::isSelected = false;
	}
	

	if (vars::clicker::isSelected) {
		ImGui::Text("LEFT CPS");
		ImGui::SliderInt("", &vars::clicker::cps, 10, 24, "%d");

		ImGui::Checkbox(("ENABLED"), &vars::clicker::enabled);
		ImGui::SameLine();

		ImGui::TextDisabled(vars::clicker::bindstr.c_str());
		ImGui::NewLine();
		if (ImGui::IsItemClicked()) {
			vars::clicker::bind_pressed = true;
			vars::clicker::bindstr = "[PRESS ANY KEY]";
		}

		ImGui::Checkbox(("EXTRA RANDOMIZATION"), &vars::clicker::randomization);
		ImGui::SameLine();
		ImGui::Checkbox(("PAUSES"), &vars::clicker::pauses);


		ImGui::Checkbox(("REQUIRE CLICK"), &vars::clicker::require_click);
		ImGui::SameLine();
		ImGui::Checkbox(("IN INVENTORY"), &vars::clicker::inventory::enabled);
		ImGui::NewLine();
		ImGui::Checkbox(("MANUAL BLOCKHIT (EXPERIMENTAL)"), &vars::clicker::manualblockhit::enabled);
		ImGui::Checkbox(("WINDOWS FIX"), &vars::clicker::windows_fix);

		if (vars::clicker::windows_fix) {
			ImGui::SliderInt(" ", &vars::clicker::windows_fix_amount, 0, 200, "%d");
		}
		
	}
	else if (vars::rightclicker::isSelected) {
		ImGui::Text("RIGHT CPS");
		ImGui::SliderInt("", &vars::rightclicker::cps, 10, 24, "%d");

		ImGui::Checkbox(("ENABLED"), &vars::rightclicker::enabled);
		ImGui::SameLine();

		ImGui::TextDisabled(vars::rightclicker::bindstr.c_str());
		ImGui::NewLine();
		if (ImGui::IsItemClicked()) {
			vars::rightclicker::bind_pressed = true;
			vars::rightclicker::bindstr = "[PRESS ANY KEY]";
		}
	}
	else if (vars::hideUI::isSelected) {
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.09f, 0.12f, 0.12f, 1.0f));
		ImGui::NewLine();
		ImGui::NewLine();
		ImGui::Button("DESTRUCT");
		if (ImGui::IsItemClicked()) {
			vars::destruct::run();
		}

		ImGui::NewLine();
		ImGui::NewLine();
		ImGui::Text("HIDE UI");
		ImGui::SameLine();
		ImGui::TextDisabled(vars::hideUI::bindstr.c_str());
		if (ImGui::IsItemClicked()) {
			vars::hideUI::bind_pressed = true;
			vars::hideUI::bindstr = "[PRESS ANY KEY]";
		}
		
		ImGui::Button("Save Config");
		if (ImGui::IsItemClicked()) {
			vars::config::save();
		}
		if (vars::config::saved) {
			ImGui::Text("Saved Config Successfully");
		}

	}
	else if (vars::clicker::roblos::isSelected) {
		ImGui::Text("CPS");
		ImGui::SameLine();
		ImGui::SliderInt("", &vars::clicker::roblos::cps, 1, 100, "%d");

		ImGui::Checkbox(("ENABLED"), &vars::clicker::roblos::enabled);
		ImGui::SameLine();

		ImGui::TextDisabled(vars::clicker::roblos::bindstr.c_str());
		ImGui::NewLine();
		if (ImGui::IsItemClicked()) {
			vars::clicker::roblos::bind_pressed = true;
			vars::clicker::roblos::bindstr = "[PRESS ANY KEY]";
		}
		if (vars::clicker::roblos::cps > 50) {
			ImGui::TextDisabled("WARNING. CPS PAST 50 IS VERY BUGGY!!");
		}
		else {
			ImGui::NewLine();
		}
		ImGui::NewLine();
		ImGui::Checkbox(("REQUIRE CLICK"), &vars::clicker::roblos::require_click);

	}

	ImGui::End();
	
}
