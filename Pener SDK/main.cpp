#include "includes.h"

#include "UTILS\interfaces.h"
#include "HOOKS\hooks.h"
#include "UTILS\offsets.h"
#include "FEATURES\EventListener.h"
#include "SDK\ConVar.h"
#include "SDK\IEngine.h"

#include "MENU\menu_framework.h"

#include <chrono>
#include <thread>

bool using_fake_angles[65];

int target;
bool in_tp;
bool fake_walk;

int resolve_type[65];

int shots_fired[65];
int shots_hit[65];

int shots_missed[65];
float local_update;
float tick_to_back[65];
float lby_to_back[65];
bool backtrack_tick[65];

float lby_delta;
float update_time[65];

int hitmarker_time;

bool menu_hide;

int oldest_tick[65];
float compensate[65][12];
Vector backtrack_hitbox[65][20][12];
float backtrack_simtime[65][12];

DWORD GetFuncSize(DWORD* Function, DWORD* StubFunction)
{
	DWORD dwFunctionSize = 0, dwOldProtect;
	DWORD *fnA = NULL, *fnB = NULL;

	fnA = (DWORD *)Function;
	fnB = (DWORD *)StubFunction;
	dwFunctionSize = (fnB - fnA);
	VirtualProtect(fnA, dwFunctionSize, PAGE_EXECUTE_READWRITE, &dwOldProtect); // Need to modify our privileges to the memory
	return dwFunctionSize;
}

void Start()
{
	INTERFACES::InitInterfaces();
	OFFSETS::InitOffsets();




	SDK::ConVar* Developer = INTERFACES::cvar->FindVar("developer");
	*(float*)((DWORD)&Developer->fnChangeCallback + 0xC) = NULL;
	Developer->SetValue("1");


	SDK::ConVar* con_filter_enable = INTERFACES::cvar->FindVar("con_filter_enable");
	*(float*)((DWORD)&con_filter_enable->fnChangeCallback + 0xC) = NULL;
	con_filter_enable->SetValue("2");

	SDK::ConVar* con_filter_text = INTERFACES::cvar->FindVar("con_filter_text");
	*(float*)((DWORD)&con_filter_text->fnChangeCallback + 0xC) = NULL;

	con_filter_text->SetValue("[getmem.es] ");

	UTILS::INPUT::input_handler.Init();
	FONTS::InitFonts();
	//MENU::InitColors();

	HOOKS::InitHooks();
	HOOKS::InitNetvarHooks();
	CGameEvents::InitializeEventListeners();
}

__declspec(noinline) void start_end()
{
	return;
}

void wait_nigger()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	memset(&Start, 0, GetFuncSize((DWORD*)&Start, (DWORD*)&start_end));
}



void gay()
{
	while (0 < 1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}

BOOL WINAPI DllMain(HINSTANCE Instance, DWORD Reason, LPVOID Reserved)
{
	if (Reason == DLL_PROCESS_ATTACH)
	{
		//AllocConsole();
		auto hwnd = GetConsoleWindow();
		auto hMenu = GetSystemMenu(hwnd, FALSE);
		if (hMenu)
			DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);

		//SetConsoleTitle("Console:");
		//freopen("CONIN$", "r", stdin);
		//freopen("CONOUT$", "w", stdout);

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Start, NULL, NULL, NULL);
		//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)wait_nigger, NULL, NULL, NULL);
		//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)gay, NULL, NULL, NULL);
	}
	return true;
}

