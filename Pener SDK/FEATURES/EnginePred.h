#pragma once

class CEnginePred
{
public:
	void ExtrapolatePosition(SDK::CBaseEntity * pPlayer, SDK::CUserCmd * cmd, Vector & position, float & simtime, Vector velocity);
	void run_prediction(SDK::CUserCmd * cmd);
	void end_prediction(SDK::CUserCmd * cmd);
};

extern CEnginePred* prediction;