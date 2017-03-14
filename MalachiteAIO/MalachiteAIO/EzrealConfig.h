#pragma once
#include "EzrealVariables.h"

//menu
IMenu* EzealMainMenu;
IMenu* EzealComboMenu;
IMenu* EzealHarassMenu;
IMenu* EzealFarmMenu;
IMenu* EzealAutoMenu;
IMenu* EzealDrawingsMenu;

//combo
IMenuOption* EzealComboQ;
IMenuOption* EzealComboW;
IMenuOption* EzealComboR;

//auto
IMenuOption* EzealAutoQ;
IMenuOption* EzealAutoW;
IMenuOption* EzealAutoStackTear;

//harass
IMenuOption* EzealHarassQ;
IMenuOption* EzealHarassW;
IMenuOption* EzealHarassMana;

//lasthit
IMenuOption* EzealLastHitQ;

//laneclear
IMenuOption* EzealLaneClearQ;

//jungleclear
IMenuOption* EzealJungleClearQ;
IMenuOption* EzealFarmMana;

inline void EzrealMenuAndSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, kCollidesWithYasuoWall | kCollidesWithMinions);
	Q->SetSkillshot(0.25f, 60, 2000, 1200);
	W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, false, kCollidesWithYasuoWall);
	W->SetSkillshot(0.25f, 80, 1600, 1050);
	E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, kCollidesWithNothing);
	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, kCollidesWithYasuoWall);
	R->SetSkillshot(1.f, 160, 2000, 20000);

	EzealMainMenu = GPluginSDK->AddMenu("MalaChiteAIO Ezreal");

	EzealComboMenu = EzealMainMenu->AddMenu("Combo Settings");
	EzealComboQ = EzealComboMenu->CheckBox("Q", true);
	EzealComboW = EzealComboMenu->CheckBox("W", true);
	EzealComboR = EzealComboMenu->CheckBox("R", true);

	EzealHarassMenu = EzealMainMenu->AddMenu("Harass Settings");
	EzealHarassQ = EzealHarassMenu->CheckBox("Q ", true);
	EzealHarassW = EzealHarassMenu->CheckBox("W ", true);
	EzealHarassMana = EzealHarassMenu->AddInteger("Mana %", 0, 100, 0);

	EzealFarmMenu = EzealMainMenu->AddMenu("Farm Settings");

	EzealLaneClearQ = EzealFarmMenu->CheckBox("LaneClear Q", true);
	EzealJungleClearQ = EzealFarmMenu->CheckBox("Jungle Q", true);
	EzealLastHitQ = EzealFarmMenu->CheckBox("LastHit Q", true);
	EzealFarmMana = EzealFarmMenu->AddInteger("Mana %", 0, 100, 50);

	EzealAutoMenu = EzealMainMenu->AddMenu("Auto Settings");
	EzealAutoQ = EzealAutoMenu->CheckBox("Q", true);
	EzealAutoW = EzealAutoMenu->CheckBox("W", false);
	EzealAutoStackTear = EzealAutoMenu->CheckBox("Stack Tear in Fountain", true);
}
