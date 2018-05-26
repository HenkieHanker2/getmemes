#pragma once

#define BACKTRACKING_ENABLED

#define MAX_RECORDS 64
#define ACCELERATION_CALC_TIME 0.3f
#define ROTATION_CALC_TIME 0.5f
#define DIRECTION_CALC_TIME 0.5f
#define FLAG_CALC_TIME 0.9f

#define MAXSTUDIOBONES 128		// total bones actually used
#define MAX_PLAYERS 65

#include <deque>
#include <array>

namespace SDK
{
	class CUserCmd;
	class CBaseEntity;
	class ConVar;
}

struct legit_backtrackdata
{
	float simtime;
	Vector hitboxPos;
};

struct LayerRecord {
	int m_nSequence;
	float m_flCycle;
	float m_flWeight;
	int m_nOrder;

	LayerRecord() {
		m_nSequence = 0;
		m_flCycle = 0.f;
		m_flWeight = 0.f;
		m_nOrder = 0;
	}
};

struct LagRecord {
	LagRecord() {
		m_fFlags = 0;
		m_vecOrigin.Init(0, 0, 0);
		m_vecEyeAngles.Init(0, 0, 0);
		m_vecAbsAngles.Init(0, 0, 0);
		m_flSimulationTime = 0;
		m_flLowerBodyYawTarget = 0.f;
	}

	int						m_fFlags;
	Vector					m_vecOrigin;
	Vector					m_vecEyeAngles;
	Vector					m_vecAbsAngles;
	float					m_flLowerBodyYawTarget;

	float					m_flSimulationTime;
	float*					m_flPoseParameter;

	std::array<LayerRecord, 15>	m_layerRecords;

	VMatrix				m_bone_matrix[128];
};

struct resolver_info_t {
	int				flags_i;
	int				tick_count;
	LagRecord		lag_record;
	bool			resolved;
	int				sequence_activity;
	bool			valid;
};


struct resolver_player_t {
	int				index;
	SDK::CBaseEntity*	player;
	std::array<LayerRecord, 15> prevlayers;
	std::deque<resolver_info_t> storedTicks;

	bool			breakinglby = false;
	bool			breakinglbyu120 = false;
};

class VarMapEntry_t
{
public:
	unsigned short type;
	unsigned short m_bNeedsToInterpolate; // Set to false when this var doesn't
										  // need Interpolate() called on it anymore.
	void *data;
	void *watcher;
};

struct VarMapping_t
{
	VarMapping_t()
	{
		m_nInterpolatedEntries = 0;
	}

	VarMapEntry_t* m_Entries;
	int m_nInterpolatedEntries;
	float m_lastInterpolationTime;
};

class CBacktrack
{
public:
	void backtrack_player(SDK::CUserCmd * cmd);
	void run_legit(SDK::CUserCmd * cmd);
	void DisableInterpolation(SDK::CBaseEntity* pEntity)
	{
		VarMapping_t* map = GetVarMap(pEntity);
		if (!map) return;
		for (int i = 0; i < map->m_nInterpolatedEntries; i++)
		{
			VarMapEntry_t *e = &map->m_Entries[i];
			e->m_bNeedsToInterpolate = false;
		}
	}
private:
	VarMapping_t * GetVarMap(void* pBaseEntity)
	{
		return reinterpret_cast<VarMapping_t*>((DWORD)pBaseEntity + 0x24); 
	}
	int latest_tick;
	Vector angle_vector(Vector meme);
	float point_to_line(Vector Point, Vector LineOrigin, Vector Dir);
	bool IsValid(SDK::CBaseEntity * player);
	resolver_player_t players[MAX_PLAYERS];
};

extern legit_backtrackdata headPositions[64][12];
extern CBacktrack* backtracking;
