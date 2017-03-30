#pragma once
#include "MainVariables.h"

//menu
IMenu* LucianMainMenu;
IMenu* LucianComboMenu;
IMenu* LucianHarassMenu;
IMenu* LucianFarmMenu;
IMenu* LucianAutoMenu;
IMenu* LucianDrawingsMenu;

//combo
IMenuOption* LucianComboQ;
IMenuOption* LucianComboQExtend;
IMenuOption* LucianComboQExtendMana;
IMenuOption* LucianComboW;
IMenuOption* LucianComboE;
IMenuOption* LucianComboEMode;
IMenuOption* LucianComboEGap;

//auto
IMenuOption* LucianAutoQ;
IMenuOption* LucianAutoW;
IMenuOption* LucianAutoMana;
IMenuOption* LucianAutoQKS;

//harass
IMenuOption* LucianHarassQ;
IMenuOption* LucianHarassQExtend;
IMenuOption* LucianHarassW;
IMenuOption* LucianHarassMana;
// farm 
IMenuOption* LucianLaneClearQ;
IMenuOption* LucianLaneClearQMinionHitCount;
IMenuOption* LucianJungClearQ;
IMenuOption* LucianLaneClearW;
IMenuOption* LucianJungClearW;
IMenuOption* LucianFarmMana;


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
	LucianComboQExtend = LucianComboMenu->CheckBox("Q extend", false);
	LucianComboQExtendMana = LucianComboMenu->AddInteger("Q extend mana", 0,100,50);
	LucianComboW = LucianComboMenu->CheckBox("W", true);
	LucianComboE = LucianComboMenu->CheckBox("E", true);
	//LucianComboEMode = LucianComboMenu->AddInteger("E Mode : (Mouse = 1, Auto = 2)", 1, 2, 1);
	LucianComboEMode = LucianComboMenu->AddSelection("E Mode", 1, {"Mouse","Smart"});
	LucianComboEGap = LucianComboMenu->CheckBox("E to gap close", false);

	LucianHarassMenu = LucianMainMenu->AddMenu("Harass Settings");
	LucianHarassQ = LucianHarassMenu->CheckBox("Q ", true);
	LucianHarassQExtend = LucianHarassMenu->CheckBox("Q extend", true);
	LucianHarassW = LucianHarassMenu->CheckBox("W ", true);
	LucianHarassMana = LucianHarassMenu->AddInteger("Mana %", 0, 100, 50);

	LucianFarmMenu = LucianMainMenu->AddMenu("Farm Settings");
	LucianLaneClearQ = LucianFarmMenu->CheckBox("LaneClear Q ", true);
	LucianLaneClearQMinionHitCount = LucianFarmMenu->AddInteger("if hit X minion", 1,3,2);
	LucianLaneClearW = LucianFarmMenu->CheckBox("LaneClear W ", true);
	LucianJungClearQ = LucianFarmMenu->CheckBox("Jungle Q ", true);
	LucianJungClearW = LucianFarmMenu->CheckBox("Jungle W ", true);
	LucianFarmMana = LucianFarmMenu->AddInteger("Mana %", 0, 100, 50);

	LucianAutoMenu = LucianMainMenu->AddMenu("Auto Settings");
	LucianAutoQ = LucianAutoMenu->CheckBox("Auto Q Harass", true);
	LucianAutoMana = LucianAutoMenu->AddInteger("Auto Q Harass if %Mana >", 0, 100, 50);
	LucianAutoQKS = LucianAutoMenu->CheckBox("Auto Q KS", true);
}
