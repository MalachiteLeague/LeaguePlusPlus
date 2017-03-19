#pragma once
#include "DravenVariables.h"

//menu
IMenu* DravenMainMenu;
IMenu* DravenComboMenu;
IMenu* DravenHarassMenu;
IMenu* DravenFarmMenu;
IMenu* DravenAutoMenu;
IMenu* DravenDrawingsMenu;

//combo
IMenuOption* DravenComboQ;
IMenuOption* DravenComboW;
IMenuOption* DravenComboE;
IMenuOption* DravenComboR;

//auto
IMenuOption* DravenAutoEGap;
IMenuOption* DravenAutoEInterrupt;

IMenuOption* DravenFarmQ;
IMenuOption* DravenFarmMana;

//draw
IMenuOption* DravenDrawAxe;

//axe range
IMenuOption* DravenAxePickRange;
inline void DravenMenuAndSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, true, false, kCollidesWithYasuoWall);
	W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, true, kCollidesWithNothing);
	E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, kCollidesWithYasuoWall);
	E->SetSkillshot(0.25f, 130, 1400, 1100);
	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, kCollidesWithYasuoWall);
	R->SetSkillshot(0.4f, 160, 2000, 20000);

	DravenMainMenu = GPluginSDK->AddMenu("MalaChiteAIO Draven");

	DravenAxePickRange = DravenMainMenu->AddInteger("Axes Pick Range", 0, 1000, 700);

	DravenComboMenu = DravenMainMenu->AddMenu("Combo Settings");
	DravenComboQ = DravenComboMenu->CheckBox("Q", true);
	DravenComboW = DravenComboMenu->CheckBox("W", true);
	DravenComboE = DravenComboMenu->CheckBox("E", true);
	DravenComboR = DravenComboMenu->CheckBox("R", true);

	DravenFarmMenu = DravenMainMenu->AddMenu("Farm Settings");
	DravenFarmQ = DravenFarmMenu->CheckBox("Q", true);
	DravenFarmMana = DravenFarmMenu->AddInteger("Mana %", 0, 100, 0);

	DravenAutoMenu = DravenMainMenu->AddMenu("Auto Settings");
	DravenAutoEGap = DravenAutoMenu->CheckBox("E anti gap", true);
	DravenAutoEInterrupt = DravenAutoMenu->CheckBox("E interrupt spells", true);

	DravenDrawingsMenu = DravenMainMenu->AddMenu("Drawing Settings");
	DravenDrawAxe = DravenDrawingsMenu->CheckBox("Draw Axe Catch Range", true);
}