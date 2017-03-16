#pragma once
#include "LucianVariables.h"

//menu
IMenu* LucianMainMenu;
IMenu* LucianComboMenu;
IMenu* LucianHarassMenu;
IMenu* LucianFarmMenu;
IMenu* LucianAutoMenu;
IMenu* LucianDrawingsMenu;

//combo
IMenuOption* LucianComboQ;
IMenuOption* LucianComboW;
IMenuOption* LucianComboE;

//auto
IMenuOption* LucianAutoQ;
IMenuOption* LucianAutoW;
IMenuOption* LucianAutoStackTear;

//harass
IMenuOption* LucianHarassQ;
IMenuOption* LucianHarassW;
IMenuOption* LucianHarassMana;


inline void LucianMenuAndSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, kCollidesWithNothing);
	Q->SetOverrideRange(640);
	W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, false, kCollidesWithYasuoWall);
	W->SetSkillshot(0.25f, 55, 1600, 1000);
	E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, kCollidesWithNothing); // 200 / 425
	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, kCollidesWithYasuoWall);

	LucianMainMenu = GPluginSDK->AddMenu("MalaChiteAIO Lucian");

	LucianComboMenu = LucianMainMenu->AddMenu("Combo Settings");
	LucianComboQ = LucianComboMenu->CheckBox("Q", true);
	LucianComboW = LucianComboMenu->CheckBox("W", true);
	LucianComboE = LucianComboMenu->CheckBox("E", true);

	LucianHarassMenu = LucianMainMenu->AddMenu("Harass Settings");
	LucianHarassQ = LucianHarassMenu->CheckBox("Q ", true);
	LucianHarassW = LucianHarassMenu->CheckBox("W ", true);
	LucianHarassMana = LucianHarassMenu->AddInteger("Mana %", 0, 100, 0);
}
