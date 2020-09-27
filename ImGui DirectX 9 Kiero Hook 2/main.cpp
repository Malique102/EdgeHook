#include "includes.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

EndScene oEndScene = NULL;
WNDPROC oWndProc;
static HWND window = NULL;

void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(pDevice);
}
#define windowFlags ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse
bool init = false;
bool visible = true;
long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!init)
	{
		InitImGui(pDevice);
		init = true;
	}

	if (GetAsyncKeyState(open_menu) & 1) {
		visible = !visible;
	}

	if (visible) {
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("EdgeHook V1-V1.3", 0, windowFlags);

		// Offsets Define

		// Rage Define
		static int aimbotfov = 0;
		static int hitchance = 0;
		static int smooth = 0;
		static bool aimbotenabled = false;
		static const char* hitboxes[]{ "None", "Head", "Neck", "Upper Chest", "Chest", "Stomach", "Pelvis", "Legs", "Feet" };
		static int hitboxesItem;
		static bool silentaim = false;
		static int backtrack = 0;
		static const char* multipoint[]{ "None", "Head", "Neck", "Upper Chest", "Chest", "Stomach", "Pelvis", "Legs", "Feet" };
		static int multiItem = 0;
		static bool safepointenabled = false;
		static bool baimenabled = false;
		static bool fakedesyncenabled = false;
		static bool multipointenabled = false;

		// Anti Aim Define
		static const char* antiaim[]{ "None", "Static", "Jitter" };
		static int antiaimItem = 0;
		static bool antiaimenabled = false;
		static bool desyncenabled = false;
		static bool inverterenabled = false;

		// Visuals Define
		static int fov = 90;
		static int thirdpersonfov = 90;
		static bool thirdpersonenabled = false;
		static int nightmode = false;

		// ESP Define
		static bool glowenabled = false;
		static bool enemyhealthenabled = false;
		static bool teammatehealthenabled = false;
		static bool footstepsenabled = false;
		static bool nameenabled = false;
		static bool tracersenabled = false;
		static bool espenabled = false;

		// Other Define
		static const char* bhopmode[]{ "Off", "Legit", "Rage", "Directional" };
		static int bhopItem = 0;
		static bool bhopenabled = false;
		static bool namestealerenabled = false;
		static bool rccrosshairenabled = false;
		static bool clantagenabled = false;
		static bool spectatorsenabled = false;
		static bool killsayenabled = false;

		// Config Tab

		// Main

		ImGui::Text("EdgeHook V1-V1.3");

		ImGui::Spacing();

		// Rage Tab
		ImGui::Text("Rage");
		ImGui::Indent();
		ImGui::Checkbox("Enabled###Rage", &aimbotenabled);
		ImGui::Checkbox("Prefer BAIM", &baimenabled);
		ImGui::Checkbox("Prefer Safe Point", &safepointenabled);
		ImGui::Checkbox("Multi Point", &multipointenabled);
		ImGui::SliderInt("FOV", &aimbotfov, 0, 180);
		ImGui::SliderInt("Hit Chance", &hitchance, 0, 100);
		ImGui::SliderInt("Backtrack", &backtrack, 10, 200);
		ImGui::Combo("Hitboxes", &hitboxesItem, hitboxes, IM_ARRAYSIZE(hitboxes));
		ImGui::Combo("Multipoint Hitboxes", &multiItem, multipoint, IM_ARRAYSIZE(multipoint));
		ImGui::Unindent();

		// Spacing
		ImGui::Spacing();

		// Anti Aim Tab
		ImGui::Text("Anti Aim");
		ImGui::Indent();
		ImGui::Checkbox("Enabled###antiaim", &antiaimenabled);
		ImGui::Combo("Mode", &antiaimItem, antiaim, IM_ARRAYSIZE(antiaim));
		ImGui::Checkbox("Desync", &desyncenabled);
		ImGui::Checkbox("Desync Fake", &fakedesyncenabled);
		ImGui::Checkbox("Inverter", &inverterenabled);
		ImGui::Unindent();

		ImGui::Spacing();
		ImGui::Indent();
		ImGui::Text("Fake Angle");

		ImGui::Unindent();

		ImGui::Spacing();
		ImGui::Indent();
		ImGui::Text("Fake Lag");

		ImGui::Unindent();

		// Spacing
		ImGui::Spacing();

		// Visuals Tab
		ImGui::Text("Visuals");
		ImGui::Indent();
		ImGui::Checkbox("Recoil Crosshair", &rccrosshairenabled);
		ImGui::Checkbox("Third Person", &thirdpersonenabled);
		ImGui::SliderInt("Night Mode", &nightmode, 0, 100);
		ImGui::SliderInt("FOV", &fov, 20, 160);
		ImGui::SliderInt("Third Person FOV", &thirdpersonfov, 20, 160);
		ImGui::Unindent();

		// Spacing
		ImGui::Spacing();

		// ESP Tab
		ImGui::Text("ESP");
		ImGui::Indent();
		ImGui::Checkbox("Enabled###esp", &espenabled);
		ImGui::Checkbox("Glow", &glowenabled);
		ImGui::Checkbox("Name", &nameenabled);
		ImGui::Checkbox("Enemy Health", &enemyhealthenabled);
		ImGui::Checkbox("Teammate Health", &teammatehealthenabled);
		ImGui::Checkbox("Footsteps", &footstepsenabled);
		ImGui::Checkbox("Bullet Tracers", &tracersenabled);
		ImGui::Unindent();

		// Spacing
		ImGui::Spacing();

		// Other Tab
		ImGui::Text("Other");
		ImGui::Indent();
		ImGui::Combo("BHop", &bhopItem, bhopmode, IM_ARRAYSIZE(bhopmode));
		ImGui::Checkbox("Name Stealer", &namestealerenabled);
		ImGui::Checkbox("Clan Tag", &clantagenabled);
		ImGui::Checkbox("Spectators", &spectatorsenabled);
		ImGui::Checkbox("KillSay", &killsayenabled);
		ImGui::Unindent();

		// Spacing
		ImGui::Spacing();

		// Unhook
		ImGui::Text("Config");
		ImGui::Button("Unhook");
		ImGui::Spacing();
		ImGui::Text("Status: Undetected");
		ImGui::Text("https://discord.gg/zZYzRvn");
		ImGui::Unindent();

		ImGui::End();

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}
	return oEndScene(pDevice);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	DWORD wndProcId;
	GetWindowThreadProcessId(handle, &wndProcId);

	if (GetCurrentProcessId() != wndProcId)
		return TRUE; // skip to next window

	window = handle;
	return FALSE; // window found abort search
}

HWND GetProcessWindow()
{
	window = NULL;
	EnumWindows(EnumWindowsCallback, NULL);
	return window;
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool attached = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
		{
			kiero::bind(42, (void**)& oEndScene, hkEndScene);
			do
				window = GetProcessWindow();
			while (window == NULL);
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
			attached = true;
		}
	} while (!attached);
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}