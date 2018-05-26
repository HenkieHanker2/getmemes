#pragma once

namespace SDK
{
	class CUserCmd;
	class CBaseEntity;
	class CBaseWeapon;
}

class CAimbot
{
public:
	void AutoZeus(SDK::CUserCmd * cmd);
	int zeus_hitbox(SDK::CBaseEntity * entity);
	void shoot_enemy(SDK::CUserCmd* cmd);
	bool good_backtrack_tick(int tick);
	void lby_backtrack(SDK::CUserCmd * pCmd, SDK::CBaseEntity * pLocal, SDK::CBaseEntity * pEntity);
	void auto_revolver(SDK::CUserCmd * cmd);
	//bool ValidTick(LagRecord * targetRecord, LagRecord * prevRecord);
	//void GetBestTarget(SDK::CBaseEntity *& targetPlayer, Vector & targetVector, LagRecord *& targetRecord);
	float accepted_inaccuracy(SDK::CBaseWeapon * weapon);
	Vector smart_baimpoint(SDK::CBaseEntity * entity);
	bool CAimbot::can_shoot(SDK::CUserCmd* cmd);
	void fix_recoil(SDK::CUserCmd* cmd);
	void rotate_movement(float yaw, SDK::CUserCmd * cmd);
	int scan_hitbox(SDK::CBaseEntity * entity); //int
	Vector get_hitbox_pos(SDK::CBaseEntity* entity, int hitbox_id);
private:
	int select_target();
	void quick_stop(SDK::CUserCmd * cmd);
	Vector scan_hitpoint(SDK::CBaseEntity * entity);
	int smart_baim(SDK::CBaseEntity * entity);
	SDK::mstudiobbox_t* get_hitbox(SDK::CBaseEntity* entity, int hitbox_index);
	bool meets_requirements(SDK::CBaseEntity* entity);
	int get_damage(Vector position);
	bool spread_limit(SDK::CBaseWeapon* weapon);
	float seedchance(Vector Point);
};

extern CAimbot* aimbot;