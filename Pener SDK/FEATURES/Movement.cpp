#include "../includes.h"
#include "../UTILS/interfaces.h"
#include "../SDK/IEngine.h"
#include "../SDK/CTrace.h"
#include "../SDK/CBaseWeapon.h"
#include "../SDK/CUserCmd.h"
#include "../SDK/CBaseEntity.h"
#include "../SDK/CClientEntityList.h"
#include "../FEATURES/AutoWall.h"
#include "../FEATURES/Aimbot.h"
#include "../FEATURES/Movement.h"

void CMovement::bunnyhop(SDK::CUserCmd* cmd)
{
	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());

	if (!local_player)
		return;

	if (cmd->buttons & IN_JUMP)
	{
		int local_flags = local_player->GetFlags();
		if (!(local_flags & FL_ONGROUND))
			cmd->buttons &= ~IN_JUMP;

		if (local_player->GetVelocity().Length() <= 50)
			cmd->forwardmove = 450.f;
	}
}

void CMovement::autostrafer(SDK::CUserCmd* cmd) //thanks toast
{
	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());

	if (!local_player)
		return;

	bool bKeysPressed = true;
	if ((GetAsyncKeyState(VK_SPACE) && !(local_player->GetFlags() & FL_ONGROUND)) && bKeysPressed)
	{
		cmd->forwardmove = (1550.f * 5) / local_player->GetVelocity().Length2D();
		cmd->sidemove = (cmd->command_number % 2) == 0 ? -450.f : 450.f;
		if (cmd->forwardmove > 450.f)
			cmd->forwardmove = 450.f;
	}

}

void CMovement::quick_stop(SDK::CBaseEntity* entity, SDK::CUserCmd* cmd)
{
	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer()); //initialize local player

	if (!local_player) //make sure this nigga aint null
		return;

	Vector local_position = local_player->GetVecOrigin() + local_player->GetViewOffset(); //get eye position

	if (entity->GetImmunity()) //make sure u dont stop when they in spawn protect
		return;

	if (entity->GetIsDormant()) //fuck dormant niggas
		return;

	auto weapon = reinterpret_cast<SDK::CBaseWeapon*>(INTERFACES::ClientEntityList->GetClientEntity(local_player->GetActiveWeaponIndex())); //initialize weapon

	if (!weapon) //make sure u aint holdin aiR niGGa
		return;

	if (weapon->is_knife() || weapon->is_grenade() || weapon->GetItemDefenitionIndex() == SDK::WEAPON_TASER) //we dont wanna stop if we holdin a knife, grenade or zeus
		return;

	if (!aimbot->can_shoot(cmd)) //so it doesn't just fully freeze us while reloading or cocking
		return;

	if (autowall->CalculateDamage(local_position, aimbot->get_hitbox_pos(entity, aimbot->scan_hitbox(entity)), local_player, entity).damage > SETTINGS::settings.damage_val) //autowall to the enemies position and see if they meet minimum damage
	{
		cmd->forwardmove = 450; //because fuck you
		aimbot->rotate_movement(UTILS::CalcAngle(Vector(0, 0, 0), local_player->GetVelocity()).y + 180.f, cmd); //negate direction to fully stop
	}
}

CMovement* movement = new CMovement();