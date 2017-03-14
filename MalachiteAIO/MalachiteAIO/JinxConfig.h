#pragma once
#include "JinxVariables.h"

//menu
IMenu* JinxMainMenu;
IMenu* JinxComboMenu;
IMenu* JinxHarassMenu;
IMenu* JinxFarmMenu;
IMenu* JinxAutoMenu;
IMenu* JinxDrawingsMenu;

//combo
IMenuOption* JinxComboQ;
IMenuOption* JinxComboW;
IMenuOption* JinxComboE;
IMenuOption* JinxComboR;

//auto
IMenuOption* JinxAutoE;

//harass
IMenuOption* JinxHarassQ;
IMenuOption* JinxHarassW;
IMenuOption* JinxHarassMana;

inline void JinxMenuAndSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, kCollidesWithNothing);
	W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, false, kCollidesWithYasuoWall | kCollidesWithMinions);
	W->SetSkillshot(0.60f, 60, 3300, 1500);
	E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, kCollidesWithYasuoWall);
	E->SetSkillshot(0.7f, 10 ,10000, 900);
	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, kCollidesWithYasuoWall | kCollidesWithHeroes);
	R->SetSkillshot(0.60f, 70, 1700, 20000);

	JinxMainMenu = GPluginSDK->AddMenu("MalaChiteAIO Jinx");

	JinxComboMenu = JinxMainMenu->AddMenu("Combo Settings");
	JinxComboQ = JinxComboMenu->CheckBox("Q", true);
	JinxComboW = JinxComboMenu->CheckBox("W", true);
	JinxComboE = JinxComboMenu->CheckBox("E", true);
	JinxComboR = JinxComboMenu->CheckBox("R", true);

	JinxHarassMenu = JinxMainMenu->AddMenu("Harass Settings");
	JinxHarassQ = JinxHarassMenu->CheckBox("Q ", true);
	JinxHarassW = JinxHarassMenu->CheckBox("W ", true);
	JinxHarassMana = JinxHarassMenu->AddInteger("Mana %", 0, 100, 0);

	JinxAutoMenu = JinxMainMenu->AddMenu("Auto Settings");
	JinxAutoE = JinxAutoMenu->CheckBox("Auto E on CC", true);
}
