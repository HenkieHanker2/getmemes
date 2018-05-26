#pragma once

namespace SDK
{
	class CUserCmd;
}

class CMovement
{
public:
	void bunnyhop(SDK::CUserCmd* cmd);
	void autostrafer(SDK::CUserCmd* cmd);
	void quick_stop(SDK::CBaseEntity * entity, SDK::CUserCmd * cmd);
};

extern CMovement* movement;