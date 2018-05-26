#include "../includes.h"
#include "../UTILS/interfaces.h"
#include "../SDK/IEngine.h"
#include "../SDK/CUserCmd.h"
#include "../SDK/CBaseEntity.h"
#include "../SDK/CClientEntityList.h"
#include "../SDK/CTrace.h"
#include "../SDK/CBaseWeapon.h"
#include "../SDK/CGlobalVars.h"
#include "../SDK/NetChannel.h"
#include "../SDK/CBaseAnimState.h"
#include "../SDK/ConVar.h"
#include "../FEATURES/Fakewalk.h"
#include "../FEATURES/AutoWall.h"
#include "../FEATURES/FakeLag.h"

void CFakeLag::do_fakelag(SDK::CUserCmd* cmd)
{
	GLOBAL::should_send_packet = true;
	int choke_amount;

	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
	if (!local_player || local_player->GetHealth() <= 0)
		return;

	auto net_channel = INTERFACES::Engine->GetNetChannel();
	if (!net_channel)
		return;

	if (!SETTINGS::settings.aa_bool)
		return;

	//if u dont remember, 1 = no fakelag (no fucking shit)
	if (SETTINGS::settings.lag_bool)
	{
		static int choke;

		if (choke < 14)
			choke++;
		else if (choke >= 14)
			choke--;

		Vector local_position = local_player->GetVecOrigin();

		if (local_update - INTERFACES::Globals->curtime < 0.1 && local_player->GetVelocity().Length2D() < 0.1 || INTERFACES::Engine->IsVoiceRecording())
			choke_amount = 1;
		else if (fake_walk)
		{
			if (local_update - INTERFACES::Globals->curtime < 0.1)
				choke_amount = 1;
			else
				choke_amount = slidebitch->choked < 1;
		}
		else
		{
			choke_amount = rand() % 2 ? choke  : SETTINGS::settings.stand_lag; // standing flag (1)
			if (!(local_player->GetFlags() & FL_ONGROUND))
			{
				choke_amount = rand() % 2 ? choke : SETTINGS::settings.jump_lag; // jumping flag (6)
			}
			else if (local_player->GetVelocity().Length2D() > 0.1)
			{
				choke_amount = rand() % 2 ? choke : SETTINGS::settings.move_lag; // moving flag (3)
			}
		}
	}
	else
		choke_amount = 1;

	if (net_channel->m_nChokedPackets >= min(15, choke_amount))
		GLOBAL::should_send_packet = true;
	else
		GLOBAL::should_send_packet = false;
}

CFakeLag* fakelag = new CFakeLag();