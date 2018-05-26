#pragma once

/*
global variables and other stuff that is probably too small to put in another 
file (and i'm too lazy to make files for all of them) would go in here.
Stuff like fonts and shit
*/

namespace SDK
{
	class CBaseEntity;
}

namespace GLOBAL
{
	extern HWND csgo_hwnd;

	extern bool should_send_packet;
	extern bool is_fakewalking;
	extern int choke_amount;
	extern 	float	flHurtTime;
	extern Vector real_angles;
	extern Vector fake_angles;
	using msg_t = void(__cdecl*)(const char*, ...);
	extern msg_t		Msg;
	extern bool hurtcalled;
	extern SDK::CUserCmd* cmd;
	extern SDK::CBaseEntity* LocalPlayer;
}
namespace FONTS
{
	extern unsigned int menu_tab_font;
	extern unsigned int menu_checkbox_font;
	extern unsigned int menu_slider_font;
	extern unsigned int menu_groupbox_font;
	extern unsigned int menu_combobox_font;
	extern unsigned int menu_window_font;
	extern unsigned int numpad_menu_font;
	extern unsigned int visuals_esp_font;
	extern unsigned int visuals_xhair_font;
	extern unsigned int visuals_side_font;
	extern unsigned int visuals_name_font;
	extern unsigned int visuals_lby_font;
	
	bool ShouldReloadFonts();
	void InitFonts();
}
namespace SETTINGS
{
	class CSettings
	{
	public:
		// returns true/false whether the function succeeds, usually returns false if file doesn't exist
		bool Save(std::string file_name);
		bool Load(std::string file_name);

		void CreateConfig(); // creates a blank config

		std::vector<std::string> GetConfigs();

		bool bhop_bool;
		bool strafe_bool;
		bool rifk_arrow;

		bool esp_bool;
		int chams_type;
		int xhair_type;
		bool tp_bool;
		bool aim_bool;
		int aim_type;
		bool aa_bool;
		int aatype;
		bool resolver_bool;

		bool fov;
		bool staticscope;
		float FOV;

		int thirdkey;


		char configname[128] = "default";
		struct
		{
			struct
			{
				int pitch;
				int yaw;
				int fakeyaw;
			}stand;
			struct
			{
				int pitch;
				int yaw;
				int fakeyaw;
			}move;
			struct
			{
				int pitch;
				int yaw;
				int fakeyaw;
			}air;

			float spinspeed;
			float jitterrange;
			struct
			{
				float delta;
				bool enable;
				int type;
				int flipkey;
			}breaklby;
			struct
			{
				float range;
				float speed;
			}switch_aa;
		}antiaim;

		bool spread_bool;
		bool aa_lines;
		bool lby_indicator;


		bool radar;


		int acc_type;
		bool up_bool;
		bool misc_bool;
		int config_sel;
		bool beam_bool;
		bool no_vis_recoil;
		bool scope_bool;
		bool stop_bool;
		bool night_bool;
		bool box_bool;
		bool hitmarker;
		bool name_bool;
		bool weap_bool;
		bool health_bool;
		bool info_bool;
		bool back_bool;
		bool lag_bool;
		int box_type;
		bool reverse_bool;
		bool multi_bool;
		bool fakefix_bool;

		float stand_lag;
		float move_lag;
		float jump_lag;

		bool debug_bool;

		bool noflash;

		bool glow;

		 float spread[4];

		 float beam1[4];
		 float beam2[4];
		 float beam3[4];
		 float radar_col[4];
		 float vmodel_col[4];
		 float imodel_col[4];
		 float box_col[4];

		 float menu_col[4];
		 float localglow[4];
		 float glowc[4];


		bool pulseglow;

		struct
		{
			bool esp;
			bool chams;
			bool glow;
			bool pulseglow;
		}localplayer;

		float chance_val;
		float damage_val;
		float delta_val;
		float point_val;
		float body_val;

		bool flip_bool;
		int aa_side;

	private:
	}; extern CSettings settings;
}


extern float local_update;
extern bool using_fake_angles[65];

extern bool in_tp;
extern bool fake_walk;

extern int resolve_type[65];

extern int shots_fired[65];
extern int shots_hit[65];
extern int shots_missed[65];

extern bool bLowerBodyYawUpdated;

extern float tick_to_back[65];
extern float lby_to_back[65];
extern bool backtrack_tick[65];

extern float lby_delta;
extern float update_time[65];

extern int hitmarker_time;

extern bool menu_hide;
extern bool hurtcalled;
extern int oldest_tick[65];
extern float compensate[65][12];
extern Vector backtrack_hitbox[65][20][12];
extern float backtrack_simtime[65][12];