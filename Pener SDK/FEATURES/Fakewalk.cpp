#include "../includes.h"
#include "../Utils/Interfaces.h"
#include "../SDK/IEngine.h"
#include "../SDK/CUserCmd.h"
#include "../SDK/CBaseEntity.h"
#include "../SDK/CClientEntityList.h"
#include "../SDK/CTrace.h"
#include "../SDK/CBaseWeapon.h"
#include "../SDK/CGlobalVars.h"
#include "../SDK/NetChannel.h"
#include "../SDK/ConVar.h"
#include "../FEATURES/AutoWall.h"
#include "../FEATURES/Fakewalk.h"
#include "../FEATURES/Aimbot.h"

#include <time.h>
#include <iostream>
void CFakewalk::do_fakewalk(SDK::CUserCmd* cmd)
{
	if (GetAsyncKeyState(VK_SHIFT)) //make sure fakelag is set to max when u trigger fakewalk!
	{
		auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());

		if (!local_player || local_player->GetHealth() <= 0)
			return;

		static int choked = 0;
		choked = choked > 7 ? 0 : choked + 1;
		cmd->forwardmove = choked < 2 || choked > 5 ? 0 : cmd->forwardmove;
		cmd->sidemove = choked < 2 || choked > 5 ? 0 : cmd->sidemove;

		fake_walk = true;
		GLOBAL::should_send_packet = choked < 1;

	}
	else
		fake_walk = false;
}

CFakewalk* slidebitch = new CFakewalk();