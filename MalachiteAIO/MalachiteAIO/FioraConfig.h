#pragma once
#include "FioraVariables.h"

//menu
IMenu* FioraMainMenu;
IMenu* FioraComboMenu;
IMenu* FioraHarassMenu;
IMenu* FioraFarmMenu;
IMenu* FioraAutoMenu;
IMenu* FioraDrawingsMenu;

//combo
IMenuOption* FioraComboQ;
IMenuOption* FioraComboQGap;
IMenuOption* FioraComboRKillable;
IMenuOption* FioraComboRAlways;
IMenuOption* FioraComboOrbwalk;

////auto
//IMenuOption* FioraAutoQ;
//IMenuOption* FioraAutoR;
//IMenuOption* FioraAutoRAtStack;

//harass
IMenuOption* FioraHarassQ;
IMenuOption* FioraHarassE;
IMenuOption* FioraHarassMana;

IMenuOption* FioraLaneClearE;


//jungleclear
IMenuOption* FioraJungleClearE;
IMenuOption* FioraFarmMana;

//draw
IMenuOption* FioraDrawOrbWalkingPoint;

inline void FioraMenuAndSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, kCollidesWithNothing);
	Q->SetOverrideRange(400);
	W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, true, kCollidesWithYasuoWall);
	W->SetSkillshot(0.75f, 80, 200, 750);
	E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, kCollidesWithNothing);
	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, true, kCollidesWithNothing);
	R->SetOverrideRange(500);

	FioraMainMenu = GPluginSDK->AddMenu("MalaChiteAIO Fiora");

	FioraComboMenu = FioraMainMenu->AddMenu("Combo Settings");
	FioraComboQ = FioraComboMenu->CheckBox("Q", true);
	FioraComboQGap = FioraComboMenu->CheckBox("Q gap", true);
	FioraComboRKillable = FioraComboMenu->CheckBox("R Killable", true);
	FioraComboRAlways = FioraComboMenu->CheckBox("R Always", false);
	FioraComboOrbwalk = FioraComboMenu->CheckBox("Orbwalk to Passive", true);

	FioraHarassMenu = FioraMainMenu->AddMenu("Harass Settings");
	FioraHarassQ = FioraHarassMenu->CheckBox("Q ", true);
	FioraHarassE = FioraHarassMenu->CheckBox("E ", true);
	FioraHarassMana = FioraHarassMenu->AddInteger("Mana %", 0, 100, 0);

	FioraFarmMenu = FioraMainMenu->AddMenu("Farm Settings");

	FioraLaneClearE = FioraFarmMenu->CheckBox("LaneClear E", true);
	FioraJungleClearE = FioraFarmMenu->CheckBox("Jungle E", true);
	FioraFarmMana = FioraFarmMenu->AddInteger("Mana %", 0, 100, 0);

	FioraDrawingsMenu = FioraMainMenu->AddMenu("Draw Settings");
	FioraDrawOrbWalkingPoint = FioraDrawingsMenu->CheckBox("Draw OrbWalking Point", true);
	//FioraAutoMenu = FioraMainMenu->AddMenu("Auto Settings");
	//FioraAutoQ = FioraAutoMenu->CheckBox("Q", true);
	//FioraAutoR = FioraAutoMenu->CheckBox("R", true);
	//FioraAutoRAtStack = FioraAutoMenu->AddInteger("min R stacks", 0, 7, 3);
}
