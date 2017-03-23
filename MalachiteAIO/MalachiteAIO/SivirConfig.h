#pragma once
#include "SivirVariables.h"

//menu
IMenu* SivirMainMenu;
IMenu* SivirComboMenu;
IMenu* SivirHarassMenu;
IMenu* SivirFarmMenu;
IMenu* SivirAutoMenu;
IMenu* SivirDrawingsMenu;

//combo
IMenuOption* SivirComboQ;
IMenuOption* SivirComboW;
IMenuOption* SivirComboR;

//auto
IMenuOption* SivirAutoRAtStack;

//harass
IMenuOption* SivirHarassQ;
IMenuOption* SivirHarassW;
IMenuOption* SivirHarassMana;

//laneclear
IMenuOption* SivirLaneClearQ;
IMenuOption* SivirLaneClearW;


//jungleclear
IMenuOption* SivirJungleClearQ;
IMenuOption* SivirJungleClearW;
IMenuOption* SivirFarmMana;

inline void SivirMenuAndSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, kCollidesWithYasuoWall);
	Q->SetSkillshot(0.f, 100, 1350, 1250);
	W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, true, kCollidesWithNothing);
	E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, kCollidesWithNothing);
	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, true, kCollidesWithNothing);

	SivirMainMenu = GPluginSDK->AddMenu("MalaChiteAIO Sivir");

	SivirComboMenu = SivirMainMenu->AddMenu("Combo Settings");
	SivirComboQ = SivirComboMenu->CheckBox("Q", true);
	SivirComboW = SivirComboMenu->CheckBox("W", true);
	SivirComboR = SivirComboMenu->CheckBox("R", true);

	SivirHarassMenu = SivirMainMenu->AddMenu("Harass Settings");
	SivirHarassQ = SivirHarassMenu->CheckBox("Q ", true);
	SivirHarassW = SivirHarassMenu->CheckBox("W ", true);
	SivirHarassMana = SivirHarassMenu->AddInteger("Mana %", 0, 100, 0);

	SivirFarmMenu = SivirMainMenu->AddMenu("Farm Settings");

	SivirLaneClearQ = SivirFarmMenu->CheckBox("LaneClear Q", true);
	SivirLaneClearW = SivirFarmMenu->CheckBox("LaneClear W", true);
	SivirJungleClearQ = SivirFarmMenu->CheckBox("Jungle Q", true);
	SivirJungleClearW = SivirFarmMenu->CheckBox("Jungle W", true);
	SivirFarmMana = SivirFarmMenu->AddInteger("Mana %", 0, 100, 0);

	SivirAutoMenu = SivirMainMenu->AddMenu("Auto Settings");
}