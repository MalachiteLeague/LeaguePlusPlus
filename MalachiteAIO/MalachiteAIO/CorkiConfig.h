#pragma once
#include "CorkiVariables.h"

//menu
IMenu* CorkiMainMenu;
IMenu* CorkiComboMenu;
IMenu* CorkiHarassMenu;
IMenu* CorkiFarmMenu;
IMenu* CorkiAutoMenu;
IMenu* CorkiDrawingsMenu;

//combo
IMenuOption* CorkiComboQ;
IMenuOption* CorkiComboE;
IMenuOption* CorkiComboR;

//auto
IMenuOption* CorkiAutoQ;
IMenuOption* CorkiAutoR;
IMenuOption* CorkiAutoRAtStack;

//harass
IMenuOption* CorkiHarassQ;
IMenuOption* CorkiHarassE;
IMenuOption* CorkiHarassMana;

//lasthit
IMenuOption* CorkiLastHitQ;

//laneclear
IMenuOption* CorkiLaneClearQ;
IMenuOption* CorkiLaneClearE;


//jungleclear
IMenuOption* CorkiJungleClearQ;
IMenuOption* CorkiJungleClearE;
IMenuOption* CorkiFarmMana;

inline void CorkiMenuAndSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, true, false, kCollidesWithYasuoWall);
	Q->SetSkillshot(0.3f, 250, 1000, 825);
	W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, true, kCollidesWithNothing);
	E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, kCollidesWithNothing);
	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, true, kCollidesWithYasuoWall | kCollidesWithMinions);
	R->SetSkillshot(0.2f, 40, 2000, 1300);

	CorkiMainMenu = GPluginSDK->AddMenu("MalaChiteAIO Corki");

	CorkiComboMenu = CorkiMainMenu->AddMenu("Combo Settings");
	CorkiComboQ = CorkiComboMenu->CheckBox("Q", true);
	CorkiComboE = CorkiComboMenu->CheckBox("E", true);
	CorkiComboR = CorkiComboMenu->CheckBox("R", true);

	CorkiHarassMenu = CorkiMainMenu->AddMenu("Harass Settings");
	CorkiHarassQ = CorkiHarassMenu->CheckBox("Q ", true);
	CorkiHarassE = CorkiHarassMenu->CheckBox("E ", true);
	CorkiHarassMana = CorkiHarassMenu->AddInteger("Mana %", 0, 100, 0);

	CorkiFarmMenu = CorkiMainMenu->AddMenu("Farm Settings");

	CorkiLaneClearQ = CorkiFarmMenu->CheckBox("LaneClear Q", true);
	CorkiLaneClearE = CorkiFarmMenu->CheckBox("LaneClear E", true);
	CorkiJungleClearQ = CorkiFarmMenu->CheckBox("Jungle Q", true);
	CorkiJungleClearE = CorkiFarmMenu->CheckBox("Jungle E", true);
	CorkiLastHitQ = CorkiFarmMenu->CheckBox("LastHit Q", true);
	CorkiFarmMana = CorkiFarmMenu->AddInteger("Mana %", 0, 100, 0);

	CorkiAutoMenu = CorkiMainMenu->AddMenu("Auto Settings");
	CorkiAutoQ = CorkiAutoMenu->CheckBox("Q", true);
	CorkiAutoR = CorkiAutoMenu->CheckBox("R", true);
	CorkiAutoRAtStack= CorkiAutoMenu->AddInteger("min R stacks", 0, 7, 3);
}
