#pragma once
#include "TwitchVariables.h"

//menu
IMenu* TwitchMainMenu;
IMenu* TwitchComboMenu;
IMenu* TwitchHarassMenu;
IMenu* TwitchFarmMenu;
IMenu* TwitchAutoMenu;
IMenu* TwitchDrawingsMenu;

//combo
IMenuOption* TwitchComboQ;
IMenuOption* TwitchComboW;
IMenuOption* TwitchComboE;
IMenuOption* TwitchComboR;

//harass
IMenuOption* TwitchHarassW;
IMenuOption* TwitchHarassE;
IMenuOption* TwitchHarassMana;

inline void TwitchMenuAndSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, kCollidesWithNothing);
	W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, false, kCollidesWithYasuoWall);
	W->SetSkillshot(0.25f, 80, 1400, 900);
	E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, kCollidesWithNothing);
	E->SetOverrideRange(1200);
	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, kCollidesWithNothing);
	R->SetOverrideRange(850);

	TwitchMainMenu = GPluginSDK->AddMenu("MalaChiteAIO Twitch");

	TwitchComboMenu = TwitchMainMenu->AddMenu("Combo Settings");
	TwitchComboQ = TwitchComboMenu->CheckBox("Q", true);
	TwitchComboW = TwitchComboMenu->CheckBox("W", true);
	TwitchComboE = TwitchComboMenu->CheckBox("E", true);
	TwitchComboR = TwitchComboMenu->CheckBox("R", true);

	TwitchHarassMenu = TwitchMainMenu->AddMenu("Harass Settings");
	TwitchHarassW = TwitchHarassMenu->CheckBox("W ", true);
	TwitchHarassE = TwitchHarassMenu->CheckBox("E ", true);
	TwitchHarassMana = TwitchHarassMenu->AddInteger("Mana %", 0, 100, 0);

}
