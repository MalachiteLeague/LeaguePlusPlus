#pragma once
#include "VayneVariables.h"

//menu
IMenu* VayneMainMenu;
IMenu* VayneComboMenu;
IMenu* VayneHarassMenu;
IMenu* VayneFarmMenu;
IMenu* VayneAutoMenu;
IMenu* VayneDrawingsMenu;

//combo
IMenuOption* VayneComboQ;
IMenuOption* VayneComboE;
IMenuOption* VayneComboR;

//auto
IMenuOption* VayneAutoEGapClose;
IMenuOption* VayneAutoEInterrupt;

//harass
IMenuOption* VayneHarassQ;
IMenuOption* VayneHarassMana;

//laneclear
IMenuOption* VayneLaneClearQ;
//jungleclear
IMenuOption* VayneJungleClearQ;
IMenuOption* VayneFarmMana;

inline void VayneMenuAndSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, kCollidesWithNothing);
	W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, false, kCollidesWithNothing);
	E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, kCollidesWithYasuoWall);
	E->SetSkillshot(0.3f, 10, 2000, 1000);
	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, kCollidesWithNothing);

	VayneMainMenu = GPluginSDK->AddMenu("MalaChiteAIO Vayne");

	VayneComboMenu = VayneMainMenu->AddMenu("Combo Settings");
	VayneComboQ = VayneComboMenu->CheckBox("Q", true);
	VayneComboE = VayneComboMenu->CheckBox("E", true);
	VayneComboR = VayneComboMenu->CheckBox("R", false);

	VayneHarassMenu = VayneMainMenu->AddMenu("Harass Settings");
	VayneHarassQ = VayneHarassMenu->CheckBox("Q ", true);
	VayneHarassMana = VayneHarassMenu->AddInteger("Mana %", 0, 100, 0);

	VayneFarmMenu = VayneMainMenu->AddMenu("Farm Settings");

	VayneLaneClearQ = VayneFarmMenu->CheckBox("LaneClear Q", false);
	VayneJungleClearQ = VayneFarmMenu->CheckBox("Jungle Q", false);
	VayneFarmMana = VayneFarmMenu->AddInteger("Mana %", 0, 100, 50);

	VayneAutoMenu = VayneMainMenu->AddMenu("Auto Settings");
	VayneAutoEGapClose = VayneAutoMenu->CheckBox("E on gapcloser", false);
	VayneAutoEInterrupt = VayneAutoMenu->CheckBox("E to interrupt", true);
}
