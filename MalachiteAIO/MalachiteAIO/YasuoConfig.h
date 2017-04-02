#pragma once
#include "MainVariables.h"

//menu
IMenu* YasuoMainMenu;
IMenu* YasuoComboMenu;
IMenu* YasuoCustomModeMenu;
IMenu* YasuoHarassMenu;
IMenu* YasuoFarmMenu;
IMenu* YasuoAutoMenu;
IMenu* YasuoFleeMenu;
IMenu* YasuoDrawingsMenu;

//combo
IMenuOption* YasuoComboQ3Spin;
IMenuOption* YasuoComboQ3SpinMaxDist;
IMenuOption* YasuoComboFlashEQR;
IMenuOption* YasuoComboEMode;
IMenuOption* YasuoComboEUnderTurret;
IMenuOption* YasuoComboR;
IMenuOption* YasuoComboRHits;
std::map<string, IMenuOption*> YasuoComboRWhiteList;
std::map<string, IMenuOption*> YasuoComboRWhiteListHP;

//custom
IMenuOption* YasuoCustomKey;
IMenuOption* YasuoCustomQ3Spin;
IMenuOption* YasuoCustomQ3SpinMaxDist;
IMenuOption* YasuoCustomFlashEQR;
IMenuOption* YasuoCustomEMode;
IMenuOption* YasuoCustomEUnderTurret;
IMenuOption* YasuoCustomR;
IMenuOption* YasuoCustomRHits;
std::map<string, IMenuOption*> YasuoCustomRWhiteList;
std::map<string, IMenuOption*> YasuoCustomRWhiteListHP;

//auto
IMenuOption* YasuoAutoQ;
IMenuOption* YasuoAutoQ3;
IMenuOption* YasuoAutoQUnderTurret;

//harass
IMenuOption* YasuoHarassQ;
IMenuOption* YasuoHarassQ3;

//lasthit
IMenuOption* YasuoLastHitQ;
IMenuOption* YasuoLastHitE;
//laneclear
IMenuOption* YasuoLaneClearQ;
IMenuOption* YasuoLaneClearE;


//jungleclear
IMenuOption* YasuoJungleClearQ;
IMenuOption* YasuoJungleClearE;
IMenuOption* YasuoFarmUnderTurret;

//fleeoption
IMenuOption* YasuoFleeKey;
IMenuOption* YasuoFleeStackQ;

inline void YasuoMenuAndSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, true, false, kCollidesWithNothing);
	Q->SetSkillshot(0.3f, 10, numeric_limits<float>::infinity(), 450);
	Q2 = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, kCollidesWithYasuoWall);
	Q2->SetSkillshot(0.5f, 10, 1200, 1050);
	W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, false, false, kCollidesWithNothing);
	E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, kCollidesWithNothing);
	E->SetOverrideRange(475);
	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, false, false, kCollidesWithNothing);
	R->SetOverrideRange(1200);

	YasuoMainMenu = GPluginSDK->AddMenu("MalaChiteAIO Yasuo");

	YasuoComboMenu = YasuoMainMenu->AddMenu("Combo Settings");
	YasuoComboQ3Spin = YasuoComboMenu->CheckBox("Q3 circle", true);
	//YasuoComboFlashEQR = YasuoComboMenu->CheckBox("Flash-E-Q3-R", true);
	YasuoComboQ3SpinMaxDist = YasuoComboMenu->AddInteger("Force Q3 circle at distance",500,1150,500 );
	YasuoComboEMode = YasuoComboMenu->AddSelection("E Mode",0 ,{"Fly","Stick","Mouse"});
	YasuoComboEUnderTurret = YasuoComboMenu->CheckBox("E Under Turret", true);
	YasuoComboR = YasuoComboMenu->CheckBox("R", true);
	YasuoComboRHits = YasuoComboMenu->AddInteger("R if will hit", 1,3,2);
	for (IUnit* hero : GEntityList->GetAllHeros(false, true))
	{
		string checkboxname = string("R on ") + hero->ChampionName() + "(" + hero->GetObjectName() +")";
		YasuoComboRWhiteList[string("combo") + std::to_string(hero->GetNetworkId())] = YasuoComboMenu->CheckBox(checkboxname.c_str(), true);
		YasuoComboRWhiteListHP[string("combohp") + std::to_string(hero->GetNetworkId())] = YasuoComboMenu->AddInteger("if %hp <", 0,101,101);
	}
	//

	YasuoHarassMenu = YasuoMainMenu->AddMenu("Harass Settings");
	YasuoHarassQ = YasuoHarassMenu->CheckBox("Q ", true);
	YasuoHarassQ3 = YasuoHarassMenu->CheckBox("Q3 ", true);

	YasuoFarmMenu = YasuoMainMenu->AddMenu("Farm Settings");

	YasuoLaneClearQ = YasuoFarmMenu->CheckBox("LaneClear Q", true);
	YasuoLaneClearE = YasuoFarmMenu->CheckBox("LaneClear E", true);
	YasuoJungleClearQ = YasuoFarmMenu->CheckBox("Jungle Q", true);
	YasuoJungleClearE = YasuoFarmMenu->CheckBox("Jungle E", true);
	YasuoLastHitQ = YasuoFarmMenu->CheckBox("LastHit Q", true);
	YasuoLastHitE = YasuoFarmMenu->CheckBox("LastHit E", true);
	YasuoFarmUnderTurret = YasuoFarmMenu->CheckBox("E Under Turret", true);

	YasuoAutoMenu = YasuoMainMenu->AddMenu("Auto Settings");
	YasuoAutoQ = YasuoAutoMenu->CheckBox("Q", true);
	YasuoAutoQ3 = YasuoAutoMenu->CheckBox("Q3", true);
	YasuoAutoQUnderTurret = YasuoAutoMenu->CheckBox("Under Turret", true);
	//
	YasuoCustomModeMenu = YasuoMainMenu->AddMenu("Custom Mode Settings");
	YasuoCustomKey = YasuoCustomModeMenu->AddKey("Custom Key", 'G');
	YasuoCustomQ3Spin = YasuoCustomModeMenu->CheckBox("Q3 circle", true);
	YasuoCustomQ3SpinMaxDist = YasuoCustomModeMenu->AddInteger("Force Q3 circle at distance", 500, 1150, 500);
	//YasuoCustomFlashEQR = YasuoCustomModeMenu->CheckBox("Flash-E-Q3-R", true);
	YasuoCustomEMode = YasuoCustomModeMenu->AddSelection("E Mode", 0, { "Fly","Stick","Mouse" });
	YasuoCustomEUnderTurret = YasuoCustomModeMenu->CheckBox("E Under Turret", true);
	YasuoCustomR = YasuoCustomModeMenu->CheckBox("R", true);
	YasuoCustomRHits = YasuoCustomModeMenu->AddInteger("R if will hit", 1, 3, 2);
	for (IUnit* hero : GEntityList->GetAllHeros(false, true))
	{
		string checkboxname = string("R on ") + hero->ChampionName() + "(" + hero->GetObjectName() + ")";
		YasuoCustomRWhiteList[string("custom") + std::to_string(hero->GetNetworkId())] = YasuoCustomModeMenu->CheckBox(checkboxname.c_str(), true);
		YasuoCustomRWhiteListHP[string("customhp") + std::to_string(hero->GetNetworkId())] = YasuoCustomModeMenu->AddInteger("if %hp <", 0, 101, 101);
	}

	YasuoFleeMenu = YasuoMainMenu->AddMenu("Dash Mode Settings");
	YasuoFleeKey = YasuoFleeMenu->AddKey("Dash Key", 'T');
	YasuoFleeStackQ = YasuoFleeMenu->CheckBox("Stack Q",true);
}