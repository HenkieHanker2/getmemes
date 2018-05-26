//#include "../includes.h"
//#include "../UTILS/interfaces.h"
//#include "../SDK/IEngine.h"
//#include "../SDK/CClientEntityList.h"
//#include "../SDK/CInputSystem.h"
//#include "../UTILS/render.h"
//#include "Components.h"
//#include "../SDK/ConVar.h"
//#include "menu_framework.h"
//
//namespace MENU
//{
//	void InitColors()
//	{
//		using namespace PPGUI_PP_GUI;
//
//		
//		colors[WINDOW_BODY] = CColor(40, 40, 40);
//		colors[WINDOW_TITLE_BAR] = SETTINGS::settings.menu_col; //255, 75, 0
//		colors[WINDOW_TEXT] = WHITE;
//
//		colors[GROUPBOX_BODY] = CColor(50, 50, 50);
//		colors[GROUPBOX_OUTLINE] = GREY;
//		colors[GROUPBOX_TEXT] = WHITE;
//
//		colors[SCROLLBAR_BODY] = CColor(90, 90, 90, 255);
//
//		colors[SEPARATOR_TEXT] = WHITE;
//		colors[SEPARATOR_LINE] = CColor(90, 90, 90, 255);
//
//		colors[CHECKBOX_CLICKED] = CColor(4, 94, 21); //HOTPINK
//		colors[CHECKBOX_NOT_CLICKED] = CColor(90, 90, 90, 255);
//		colors[CHECKBOX_TEXT] = WHITE;
//
//		colors[BUTTON_BODY] = CColor(90, 90, 90, 255);
//		colors[BUTTON_TEXT] = WHITE;
//
//		colors[COMBOBOX_TEXT] = WHITE;
//		colors[COMBOBOX_SELECTED] = CColor(90, 90, 90, 255);
//		colors[COMBOBOX_SELECTED_TEXT] = WHITE;
//		colors[COMBOBOX_ITEM] = CColor(70, 70, 70, 255);
//		colors[COMBOBOX_ITEM_TEXT] = WHITE;
//
//		colors[SLIDER_BODY] = CColor(90, 90, 90, 255);
//		colors[SLIDER_VALUE] = CColor(255, 75, 0); //HOTPINK
//		colors[SLIDER_TEXT] = WHITE;
//
//		colors[TAB_BODY] = CColor(90, 90, 90, 255);
//		colors[TAB_TEXT] = WHITE;
//		colors[TAB_BODY_SELECTED] = CColor(112, 112, 112); //HOTPINK
//		colors[TAB_TEXT_SELECTED] = WHITE;
//
//		colors[VERTICAL_TAB_BODY] = CColor(70, 70, 70, 255);
//		colors[VERTICAL_TAB_TEXT] = WHITE;
//		colors[VERTICAL_TAB_OUTLINE] = CColor(0, 0, 0, 100);
//		colors[VERTICAL_TAB_BODY_SELECTED] = CColor(100, 100, 100, 255);
//
//		colors[COLOR_PICKER_BODY] = CColor(70, 70, 70, 255);
//		colors[COLOR_PICKER_TEXT] = WHITE;
//		colors[COLOR_PICKER_OUTLINE] = CColor(0, 0, 0, 100);
//	}
//	void Do()
//	{
//		//all of this cool gui stuff made by bolbi, but i decide to just render text and make binds for every feature. sorry bolbi!
//
//		static bool menu_open = false;
//
//		if (UTILS::INPUT::input_handler.GetKeyState(VK_INSERT) & 1)
//		{
//			menu_open = !menu_open;
//			INTERFACES::Engine->ClientCmd(menu_open ? "cl_mouseenable 0" :
//				"cl_mouseenable 1");
//			INTERFACES::InputSystem->EnableInput(!menu_open);
//		}
//
//		if (UTILS::INPUT::input_handler.GetKeyState(VK_END) & 1)
//		{
//			menu_hide = !menu_hide;
//		}
//
//		//--- Flip Bool Stuff ---//

//
//		//--- New Menu Rendering System --//
//		if (menu_hide)
//		{
//			//menu is hidden entirely, you can do anything here i guess
//		}
//		else
//		{
//			if (menu_open)
//			{
//				using namespace PPGUI_PP_GUI;
//
//				// if menu not open
//				if (!menu_open)
//					return;
//
//				DrawMouse();
//
//				SetFont(FONTS::menu_window_font);
//				WindowBegin("ascendancy", Vector2D(200, 200), Vector2D(700, 500));
//
//				std::vector<std::string> tabs = { "aimbot", "visuals", "misc", "antiaim", "config" };
//				std::vector<std::string> aim_mode = { "rage", "legit" };
//				std::vector<std::string> acc_mode = { "head", "body", "all" };
//				std::vector<std::string> chams_mode = { "none", "visible", "invisible" };
//				std::vector<std::string> pitchaa = { "none", "down", "jitter", "fake up", "zero" };
//				std::vector<std::string> aaset = { "stand", "move", "air" };
//				std::vector<std::string> aa_mode =
//				{ "none",
//					"static",
//					"jitter",
//					"spin",
//					"fake lby",
//					"relative"
//				};
//				std::vector<std::string> break_lby_mode =
//				{ "none",
//					"on bind [v]",
//					"freestanding"
//				};
//				std::vector<std::string> configs = { "mm hvh", "scar", "ssg", "pistols" };
//				std::vector<std::string> box_style = { "none", "full", "debug" };
//				std::string config;
//
//				switch (Tab("main", tabs, OBJECT_FLAGS::FLAG_NONE))
//				{
//				case 0:
//				{
//					Checkbox("enable aimbot", SETTINGS::settings.aim_bool);
//					if (SETTINGS::settings.aim_bool)
//					{
//						Slider("hitchance", 0, 100, SETTINGS::settings.chance_val);
//						Slider("minimum damage", 1, 100, SETTINGS::settings.damage_val);
//						Combobox("aimbot hitbox", acc_mode, SETTINGS::settings.acc_type);
//						Checkbox("smart tick resolver", SETTINGS::settings.resolver_bool);
//						Checkbox("auto stop", SETTINGS::settings.stop_bool);
//						Checkbox("auto scope", SETTINGS::settings.scope_bool);
//					}
//				}
//				break;
//				case 1:
//				{
//					Checkbox("enable visuals", SETTINGS::settings.esp_bool);
//					if (SETTINGS::settings.esp_bool)
//					{
//						Checkbox("draw box", SETTINGS::settings.box_bool);
//						if (SETTINGS::settings.box_bool)
//							ColorPicker("box color", SETTINGS::settings.box_col);
//						Checkbox("draw name", SETTINGS::settings.name_bool);
//						Checkbox("draw weapon", SETTINGS::settings.weap_bool);
//						Checkbox("draw info", SETTINGS::settings.info_bool);
//						Checkbox("draw health", SETTINGS::settings.health_bool);
//
//						Combobox("colored models", chams_mode, SETTINGS::settings.chams_type);
//						if (SETTINGS::settings.chams_type > 0)
//							ColorPicker("visible model", SETTINGS::settings.vmodel_col);
//						if (SETTINGS::settings.chams_type > 1)
//							ColorPicker("invisible model", SETTINGS::settings.imodel_col);
//
//						Checkbox("glow", SETTINGS::settings.glow);
//						if (SETTINGS::settings.glow) {
//							ColorPicker("glow enemy", SETTINGS::settings.glowc);
//							Checkbox("glow on localplayer", SETTINGS::settings.localplayer.glow);
//							if (SETTINGS::settings.localplayer.glow)
//							{
//								ColorPicker("glow local", SETTINGS::settings.localglow);
//								Checkbox("pulse", SETTINGS::settings.pulseglow);
//							}
//						}
//						Checkbox("radar", SETTINGS::settings.radar);
//						if (SETTINGS::settings.radar)
//						{
//							ColorPicker("radar arrow", SETTINGS::settings.radar_col);
//						}
//						Checkbox("inaccuracy overlay", SETTINGS::settings.spread_bool);
//						if (SETTINGS::settings.spread_bool)
//						{
//							ColorPicker("color", SETTINGS::settings.spread);
//						}
//						Checkbox("night mode", SETTINGS::settings.night_bool);
//						Checkbox("bullet tracers", SETTINGS::settings.beam_bool);
//						if (SETTINGS::settings.beam_bool) {
//							ColorPicker("entity", SETTINGS::settings.beam2);
//							ColorPicker("local", SETTINGS::settings.beam1);
//							ColorPicker("team", SETTINGS::settings.beam3);
//						}
//						Checkbox("thirdperson", SETTINGS::settings.tp_bool);
//						Checkbox("no flash", SETTINGS::settings.noflash);
//						Checkbox("no visual recoil", SETTINGS::settings.no_vis_recoil);
//						Checkbox("fov changer", SETTINGS::settings.fov);
//						if (SETTINGS::settings.fov) {
//							Slider("value", -50, 50, SETTINGS::settings.FOV);
//
//						}
//						Checkbox("static zoom", SETTINGS::settings.staticscope);
//					}
//				}
//				break;
//				case 2:
//				{
//					Checkbox("enable misc", SETTINGS::settings.misc_bool);
//					if (SETTINGS::settings.misc_bool)
//					{
//						Checkbox("auto bunnyhop", SETTINGS::settings.bhop_bool);
//						Checkbox("auto strafer", SETTINGS::settings.strafe_bool);
//						Checkbox("fakelag", SETTINGS::settings.lag_bool);
//						Slider("standing lag", 1, 15, SETTINGS::settings.stand_lag);
//						Slider("moving lag", 1, 15, SETTINGS::settings.move_lag);
//						Slider("jumping lag", 1, 15, SETTINGS::settings.jump_lag);
//					}
//				}
//				break;
//				case 3:
//				{
//					Checkbox("enable antiaim", SETTINGS::settings.aa_bool);
//					if (SETTINGS::settings.aa_bool)
//					{
//						Combobox("preset", aaset, SETTINGS::settings.aatype);
//
//						switch (SETTINGS::settings.aatype)
//						{
//						case 0:
//						{
//							Combobox("pitch", pitchaa, SETTINGS::settings.antiaim.stand.pitch);
//							Combobox("yaw", aa_mode, SETTINGS::settings.antiaim.stand.yaw);
//							Combobox("fake yaw", aa_mode, SETTINGS::settings.antiaim.stand.fakeyaw);
//						}
//						break;
//						case 1:
//						{
//							Combobox("move pitch", pitchaa, SETTINGS::settings.antiaim.move.pitch);
//							Combobox("move yaw", aa_mode, SETTINGS::settings.antiaim.move.yaw);
//							Combobox("move fake yaw", aa_mode, SETTINGS::settings.antiaim.move.fakeyaw);
//						}
//						break;
//						case 2:
//						{
//							Combobox("air pitch", pitchaa, SETTINGS::settings.antiaim.air.pitch);
//							Combobox("air yaw", aa_mode, SETTINGS::settings.antiaim.air.yaw);
//							Combobox("air fake yaw", aa_mode, SETTINGS::settings.antiaim.air.fakeyaw);
//						}
//						break;
//
//
//						}
//
//						Slider("spin speed", -50, 50, SETTINGS::settings.antiaim.spinspeed);
//						Slider("jitter range", -180, 180, SETTINGS::settings.antiaim.jitterrange);
//						if (Checkbox("break lby", SETTINGS::settings.antiaim.breaklby.enable)) {
//							Combobox("type", break_lby_mode, SETTINGS::settings.antiaim.breaklby.type);
//							Slider("lby delta", -180, 180, SETTINGS::settings.antiaim.breaklby.delta);
//						}
//						Checkbox("draw lines", SETTINGS::settings.aa_lines);
//						Checkbox("draw indicators", SETTINGS::settings.lby_indicator);
//						Checkbox("draw rifk arrows", SETTINGS::settings.rifk_arrow);
//					}
//				}
//				break;
//				case 4:
//				{
//					switch (Combobox("config", configs, SETTINGS::settings.config_sel))
//					{
//					case 0: config = "default"; break;
//					case 1: config = "auto"; break;
//					case 2: config = "scout"; break;
//					case 3: config = "pistol"; break;
//					}
//
//					if (Button("Load Config"))
//					{
//						SETTINGS::settings.Load(config);
//
//						GLOBAL::Msg("[getmem.es] Configuration loaded.    \n");
//					}
//
//					if (Button("Save Config"))
//					{
//						SETTINGS::settings.Save(config);
//
//						GLOBAL::Msg("[getmem.es] Configuration saved.    \n");
//					}
//				}
//				break;
//				}
//
//				WindowEnd();
//			}
//			else
//			{
//
//			}
//		}
//
//	}
//}