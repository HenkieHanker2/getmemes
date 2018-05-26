#include <d3d9.h>
#include <dinput.h>
#include "imgui\imgui.h"
#include "imgui\dx9\imgui_dx9.h"
#include <tchar.h>
#include <iostream>
#include "includes.h"

void DrawMenu()
{
	const char* KeyStrings[] = {
		"",
		"Mouse 1",
		"Mouse 2",
		"Cancel",
		"Middle Mouse",
		"Mouse 4",
		"Mouse 5",
		"",
		"Backspace",
		"Tab",
		"",
		"",
		"Clear",
		"Enter",
		"",
		"",
		"Shift",
		"Control",
		"Alt",
		"Pause",
		"Caps",
		"",
		"",
		"",
		"",
		"",
		"",
		"Escape",
		"",
		"",
		"",
		"",
		"Space",
		"Page Up",
		"Page Down",
		"End",
		"Home",
		"Left",
		"Up",
		"Right",
		"Down",
		"",
		"",
		"",
		"Print",
		"Insert",
		"Delete",
		"",
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"",
		"",
		"",
		"",
		"",
		"Numpad 0",
		"Numpad 1",
		"Numpad 2",
		"Numpad 3",
		"Numpad 4",
		"Numpad 5",
		"Numpad 6",
		"Numpad 7",
		"Numpad 8",
		"Numpad 9",
		"Multiply",
		"Add",
		"",
		"Subtract",
		"Decimal",
		"Divide",
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"F11",
		"F12",

	};
	const char* acc_mode[] = { "head", "body", "all" };
	const char* chams_mode[] = { "none", "visible", "invisible" };
	const char* pitchaa[] = { "none", "down", "jitter", "fake up", "zero" };
	const char* aaset[] = { "stand", "move", "air" };
	const char* aa_mode[] =
	{   "none",
		"static",
		"jitter",
		"spin",
		"fake lby",
		"relative"
	};
	const char* break_lby_mode[] =
	{ "none",
		"on bind",
		"freestanding"
	};
	const char* configs[] = { "mm hvh", "scar", "ssg", "pistols" };
	const char* box_style[] = { "none", "full", "debug" };

	static int tab_count = 0;
	//ImGui::BeginChild("##tabs", ImVec2(150, 0), true, 0);
	//{

		const char* tabs[] = { "     ragebot", "     visuals", "     misc", "     antiaim", "     config" };

		ImGui::PushItemWidth(140);
		ImGui::ListBox("##tablist", &tab_count, tabs, ARRAYSIZE(tabs), 30);
		ImGui::PopItemWidth();


	//}
	//ImGui::EndChild();
	ImGui::SameLine();
	ImGui::BeginChild("##tabs2", ImVec2(400, 0), true, 0);
	{
		switch (tab_count)
		{
		case 0:
		{
			const char* acc_mode[] = { "head", "body", "all" };
			ImGui::Checkbox("enable aimbot", &SETTINGS::settings.aim_bool);
			if (SETTINGS::settings.aim_bool) {
				ImGui::SliderFloat("hitchance", &SETTINGS::settings.chance_val, 0.1f, 100.f, ("%.1f"));
				ImGui::SliderFloat("minimum damage", &SETTINGS::settings.damage_val, 0.1f, 100.f, ("%.1f"));
				ImGui::Combo("aimbot hitbox", &SETTINGS::settings.acc_type, acc_mode, ARRAYSIZE(acc_mode));
				ImGui::Checkbox("smart tick resolver", &SETTINGS::settings.resolver_bool);
				ImGui::Checkbox("auto stop", &SETTINGS::settings.stop_bool);
				ImGui::Checkbox("auto scope", &SETTINGS::settings.scope_bool);
			}
		}
		break;
		case 1:
		{
			ImGui::Checkbox("enable visuals", &SETTINGS::settings.esp_bool);
			if (SETTINGS::settings.esp_bool)
			{
				ImGui::Checkbox("draw box", &SETTINGS::settings.box_bool);
				if (SETTINGS::settings.box_bool)
					ImGui::MyColorEdit4("box color", SETTINGS::settings.box_col, ImGuiColorEditFlags_Alpha | ImGuiColorEditFlags_NoSliders);
				ImGui::Checkbox("draw name", &SETTINGS::settings.name_bool);
				ImGui::Checkbox("draw weapon", &SETTINGS::settings.weap_bool);
				ImGui::Checkbox("draw info", &SETTINGS::settings.info_bool);
				ImGui::Checkbox("draw health", &SETTINGS::settings.health_bool);

				ImGui::Combo("colored models",  &SETTINGS::settings.chams_type ,chams_mode, ARRAYSIZE(chams_mode));
				if (SETTINGS::settings.chams_type > 0)
					ImGui::MyColorEdit4("visible model", SETTINGS::settings.vmodel_col, ImGuiColorEditFlags_Alpha | ImGuiColorEditFlags_NoSliders);
				if (SETTINGS::settings.chams_type > 1)
					ImGui::MyColorEdit4("invisible model", SETTINGS::settings.imodel_col, ImGuiColorEditFlags_Alpha | ImGuiColorEditFlags_NoSliders);

				ImGui::Checkbox("glow", &SETTINGS::settings.glow);
				if (SETTINGS::settings.glow) {
					ImGui::MyColorEdit4("glow enemy", SETTINGS::settings.glowc, ImGuiColorEditFlags_Alpha | ImGuiColorEditFlags_NoSliders);
					ImGui::Checkbox("glow on localplayer", &SETTINGS::settings.localplayer.glow);
					if (SETTINGS::settings.localplayer.glow)
					{
						ImGui::MyColorEdit4("glow local", SETTINGS::settings.localglow, ImGuiColorEditFlags_Alpha | ImGuiColorEditFlags_NoSliders);
						ImGui::Checkbox("pulse", &SETTINGS::settings.pulseglow);
					}
				}
				ImGui::Checkbox("radar", &SETTINGS::settings.radar);
				if (SETTINGS::settings.radar)
				{
					ImGui::MyColorEdit4("radar arrow", SETTINGS::settings.radar_col, ImGuiColorEditFlags_Alpha | ImGuiColorEditFlags_NoSliders);
				}
				ImGui::Checkbox("inaccuracy overlay", &SETTINGS::settings.spread_bool);
				if (SETTINGS::settings.spread_bool)
				{
					ImGui::MyColorEdit4("color", SETTINGS::settings.spread, ImGuiColorEditFlags_Alpha | ImGuiColorEditFlags_NoSliders);
				}
				ImGui::Checkbox("night mode", &SETTINGS::settings.night_bool);
				ImGui::Checkbox("hitmarker", &SETTINGS::settings.hitmarker);
				ImGui::Checkbox("bullet tracers", &SETTINGS::settings.beam_bool);
				if (SETTINGS::settings.beam_bool) {
					ImGui::MyColorEdit4("entity",SETTINGS::settings.beam2, ImGuiColorEditFlags_Alpha | ImGuiColorEditFlags_NoSliders);
					ImGui::MyColorEdit4("local", SETTINGS::settings.beam1, ImGuiColorEditFlags_Alpha | ImGuiColorEditFlags_NoSliders);
					ImGui::MyColorEdit4("team", SETTINGS::settings.beam3, ImGuiColorEditFlags_Alpha | ImGuiColorEditFlags_NoSliders);
				}
				ImGui::Checkbox("thirdperson", &SETTINGS::settings.tp_bool);
				if (SETTINGS::settings.tp_bool) {
					ImGui::Combo("key", &SETTINGS::settings.thirdkey, KeyStrings, ARRAYSIZE(KeyStrings));
				}
				ImGui::Checkbox("no flash", &SETTINGS::settings.noflash);
				ImGui::Checkbox("no visual recoil", &SETTINGS::settings.no_vis_recoil);
				ImGui::Checkbox("fov changer", &SETTINGS::settings.fov);
				if (SETTINGS::settings.fov) {
					ImGui::SliderFloat("value", &SETTINGS::settings.FOV, -50, 50, ("%.1f"));

				}
				ImGui::Checkbox("static zoom", &SETTINGS::settings.staticscope);
			}
		}
		break;
		case 2:
		{
			ImGui::Checkbox("enable misc", &SETTINGS::settings.misc_bool);
			if (SETTINGS::settings.misc_bool)
			{
				ImGui::Checkbox("auto bunnyhop", &SETTINGS::settings.bhop_bool);
				ImGui::Checkbox("auto strafer", &SETTINGS::settings.strafe_bool);
				ImGui::Checkbox("fakelag", &SETTINGS::settings.lag_bool);
				if (SETTINGS::settings.lag_bool) {
					ImGui::SliderFloat("standing lag", &SETTINGS::settings.stand_lag, 1, 15, ("%.1f"));
					ImGui::SliderFloat("moving lag", &SETTINGS::settings.move_lag, 1, 15, ("%.1f"));
					ImGui::SliderFloat("jumping lag", &SETTINGS::settings.jump_lag, 1, 15, ("%.1f"));
				}
			}
		}
		break;
		case 3:
		{
			ImGui::Checkbox("enable antiaim", &SETTINGS::settings.aa_bool);
			if (SETTINGS::settings.aa_bool)
			{
				ImGui::Combo("preset", &SETTINGS::settings.aatype, aaset, ARRAYSIZE(aaset));

				switch (SETTINGS::settings.aatype)
				{
				case 0:
				{
					ImGui::Combo("pitch", &SETTINGS::settings.antiaim.stand.pitch, pitchaa, ARRAYSIZE(pitchaa));
					ImGui::Combo("yaw", &SETTINGS::settings.antiaim.stand.yaw, aa_mode, ARRAYSIZE(aa_mode));
					ImGui::Combo("fake yaw", &SETTINGS::settings.antiaim.stand.fakeyaw, aa_mode, ARRAYSIZE(aa_mode));
				}
				break;
				case 1:
				{
					ImGui::Combo("move pitch", &SETTINGS::settings.antiaim.move.pitch, pitchaa, ARRAYSIZE(pitchaa));
					ImGui::Combo("move yaw", &SETTINGS::settings.antiaim.move.yaw, aa_mode, ARRAYSIZE(aa_mode));
					ImGui::Combo("move fake yaw", &SETTINGS::settings.antiaim.move.fakeyaw, aa_mode, ARRAYSIZE(aa_mode));
				}
				break;
				case 2:
				{
					ImGui::Combo("air pitch", &SETTINGS::settings.antiaim.air.pitch, pitchaa, ARRAYSIZE(pitchaa));
					ImGui::Combo("air yaw", &SETTINGS::settings.antiaim.air.yaw, aa_mode, ARRAYSIZE(aa_mode));
					ImGui::Combo("air fake yaw", &SETTINGS::settings.antiaim.air.fakeyaw, aa_mode, ARRAYSIZE(aa_mode));
				}
				break;


				}

				ImGui::SliderFloat("spin speed", &SETTINGS::settings.antiaim.spinspeed, -50, 50, ("%.1f"));
				ImGui::SliderFloat("jitter range", &SETTINGS::settings.antiaim.jitterrange, -360, 360, ("%.1f"));
				ImGui::Checkbox("break lby", &SETTINGS::settings.antiaim.breaklby.enable);
				if (SETTINGS::settings.antiaim.breaklby.enable) {
					ImGui::Combo("type", &SETTINGS::settings.antiaim.breaklby.type, break_lby_mode, ARRAYSIZE(break_lby_mode));
					if (SETTINGS::settings.antiaim.breaklby.type == 1) {
						ImGui::Combo("flip key", &SETTINGS::settings.antiaim.breaklby.flipkey, KeyStrings, ARRAYSIZE(KeyStrings));
					}
					ImGui::SliderFloat("lby delta", &SETTINGS::settings.antiaim.breaklby.delta, -180, 180, ("%.1f"));
				}

				ImGui::Checkbox("draw lines", &SETTINGS::settings.aa_lines);
				ImGui::Checkbox("draw indicators", &SETTINGS::settings.lby_indicator);
				ImGui::Checkbox("draw rifk arrows", &SETTINGS::settings.rifk_arrow);
			}
		}
		break;
		case 4:
		{
			std::string config;
			
			switch (ImGui::Combo("config", &SETTINGS::settings.config_sel, configs, ARRAYSIZE(configs)))
			{
			case 0: config = "default"; break;
			case 1: config = "auto"; break;
			case 2: config = "scout"; break;
			case 3: config = "pistol"; break;
			}

			if (ImGui::Button("Load Config", ImVec2(120, 30)))
			{
				SETTINGS::settings.Load(config);

				GLOBAL::Msg("[getmem.es] Configuration loaded.    \n");
			}

			if (ImGui::Button("Save Config", ImVec2(120, 30)))
			{
				SETTINGS::settings.Save(config);

				GLOBAL::Msg("[getmem.es] Configuration saved.    \n");
			}
		}
		break;
		}
	}
	ImGui::EndChild();
}