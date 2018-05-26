#pragma once
namespace SDK
{
	class CUserCmd;
	class CBaseEntity;
}

class CAntiAim
{
public:
	void freestand(SDK::CUserCmd* cmd, float yawangs);
	void do_antiaim(SDK::CUserCmd* cmd);
	void fix_movement(SDK::CUserCmd* cmd);
private:
};

struct AntiaimData_t
{
	AntiaimData_t(int player, const float& dist, const bool& inair)
	{
		this->iPlayer = player;
		this->flDist = dist;
		this->bInAir = inair;
	}
	int				iPlayer;
	float			flDist;
	bool			bInAir;
};

extern CAntiAim* antiaim;