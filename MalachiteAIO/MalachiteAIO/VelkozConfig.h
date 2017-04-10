#pragma once
#include "MainVariables.h"
//menu
IMenu* VelkozMainMenu;
IMenu* VelkozComboMenu;
IMenu* VelkozHarassMenu;
IMenu* VelkozFarmMenu;
IMenu* VelkozAutoMenu;
IMenu* VelkozDrawingsMenu;

//combo
IMenuOption* VelkozComboQ;
IMenuOption* VelkozComboQ2;
IMenuOption* VelkozComboW;
IMenuOption* VelkozComboE;
IMenuOption* VelkozComboR;

//auto
IMenuOption* VelkozAutoEGap;
IMenuOption* VelkozAutoEInterrupt;
IMenuOption* VelkozAutoQ2;
IMenuOption* VelkozAutoLockR;

//harass
IMenuOption* VelkozHarassQ;
IMenuOption* VelkozHarassQ2;
IMenuOption* VelkozHarassW;
IMenuOption* VelkozHarassE;
IMenuOption* VelkozHarassMana;

// farm 
IMenuOption* VelkozLaneClearQ;
IMenuOption* VelkozLaneClearW;
IMenuOption* VelkozJungClearQ;
IMenuOption* VelkozJungClearW;
IMenuOption* VelkozFarmMana;


inline void VelkozMenuAndSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, kCollidesWithYasuoWall | kCollidesWithMinions | kCollidesWithHeroes);
	Q->SetSkillshot(0.25f, 55, 1300, 1200);
	Q2 = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, kCollidesWithYasuoWall | kCollidesWithMinions | kCollidesWithHeroes);
	Q2->SetSkillshot(0.25f, 55, 2100, 1300);
	Q3 = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, kCollidesWithYasuoWall | kCollidesWithMinions | kCollidesWithHeroes);
	Q3->SetSkillshot(0.f, 55, numeric_limits<float>::infinity(), 1300);
	W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, false, kCollidesWithYasuoWall);
	W->SetSkillshot(0.25f, 85, 1700, 1200);
	E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, kCollidesWithYasuoWall);
	E->SetSkillshot(0.5f, 100, numeric_limits<float>::infinity(), 800);
	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, kCollidesWithYasuoWall);
	R->SetOverrideRange(1550);

	VelkozMainMenu = GPluginSDK->AddMenu("MalaChiteAIO Velkoz");

	VelkozComboMenu = VelkozMainMenu->AddMenu("Combo Settings");
	VelkozComboQ = VelkozComboMenu->CheckBox("Q1", true);
	VelkozComboQ2 = VelkozComboMenu->CheckBox("Q2", true);
	VelkozComboW = VelkozComboMenu->CheckBox("W", true);
	VelkozComboE = VelkozComboMenu->CheckBox("E", true);
	VelkozComboR = VelkozComboMenu->CheckBox("R", true);

	VelkozHarassMenu = VelkozMainMenu->AddMenu("Harass Settings");
	VelkozHarassQ = VelkozHarassMenu->CheckBox("Q1 ", true);
	VelkozHarassQ2 = VelkozHarassMenu->CheckBox("Q2", true);
	VelkozHarassW = VelkozHarassMenu->CheckBox("W ", true);
	VelkozHarassE = VelkozHarassMenu->CheckBox("E ", true);
	VelkozHarassMana = VelkozHarassMenu->AddInteger("Mana %", 0, 100, 0);

	VelkozFarmMenu = VelkozMainMenu->AddMenu("Farm Settings");
	VelkozLaneClearQ = VelkozFarmMenu->CheckBox("LaneClear Q ", true);
	VelkozLaneClearW = VelkozFarmMenu->CheckBox("LaneClear W ", true);
	VelkozJungClearQ = VelkozFarmMenu->CheckBox("Jungle Q ", true);
	VelkozJungClearW = VelkozFarmMenu->CheckBox("Jungle W ", true);
	VelkozFarmMana = VelkozFarmMenu->AddInteger("Mana %", 0, 100, 50);

	VelkozAutoMenu = VelkozMainMenu->AddMenu("Auto Settings");
	VelkozAutoEGap = VelkozAutoMenu->CheckBox("Auto E on GapCloser", true);
	VelkozAutoEInterrupt = VelkozAutoMenu->CheckBox("Auto E Interrupter", true);
	VelkozAutoQ2 = VelkozAutoMenu->CheckBox("Auto Q2", true);
	//VelkozAutoLockR = VelkozAutoMenu->CheckBox("Auto Lock R", true);
}
