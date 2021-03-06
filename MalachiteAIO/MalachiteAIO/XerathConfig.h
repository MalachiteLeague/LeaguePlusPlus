#pragma once
#include "XerathVariables.h"

//menu
IMenu* XerathMainMenu;
IMenu* XerathComboMenu;
IMenu* XerathHarassMenu;
IMenu* XerathFarmMenu;
IMenu* XerathAutoMenu;
IMenu* XerathDrawingsMenu;

//combo
IMenuOption* XerathComboQ;
IMenuOption* XerathComboE;
IMenuOption* XerathComboW;

//auto
IMenuOption* XerathAutoQ;
IMenuOption* XerathAutoR;
IMenuOption* XerathAutoRTime;
IMenuOption* XerathAutoRDistance;

//harass
IMenuOption* XerathHarassQ;
IMenuOption* XerathHarassW;
IMenuOption* XerathHarassMana;

//lasthit
IMenuOption* XerathLastHitQ;

//laneclear
IMenuOption* XerathLaneClearW;


//jungleclear
IMenuOption* XerathJungleClearQ;
IMenuOption* XerathJungleClearE;
IMenuOption* XerathFarmMana;

//drawing
//jungleclear
IMenuOption* XerathDrawQ;
IMenuOption* XerathDrawW;
IMenuOption* XerathDrawE;
IMenuOption* XerathDrawR;
IMenuOption* XerathDrawRCast;

inline void XerathMenuAndSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, kCollidesWithNothing);
	Q->SetSkillshot(0.3f, 95, std::numeric_limits<float>::infinity(), 1550);
	Q->SetCharged(700, 1500, 1.5f);
	Q->SetChargedBuffName("XerathArcanopulseChargeUp");
	W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, false, kCollidesWithNothing);
	W->SetSkillshot(0.4f, 125, std::numeric_limits<float>::infinity(), 1100);
	E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, kCollidesWithYasuoWall | kCollidesWithMinions | kCollidesWithHeroes);
	E->SetSkillshot(0.25f, 60, 1400, 1050);
	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, kCollidesWithNothing);
	R->SetSkillshot(0.4f, 130, std::numeric_limits<float>::infinity(), 3520);// 4840 , 6160

	XerathMainMenu = GPluginSDK->AddMenu("MalaChiteAIO Xerath");

	XerathComboMenu = XerathMainMenu->AddMenu("Combo Settings");
	XerathComboQ = XerathComboMenu->CheckBox("Q", true);
	XerathComboW = XerathComboMenu->CheckBox("W", true);
	XerathComboE = XerathComboMenu->CheckBox("E", true);

	XerathHarassMenu = XerathMainMenu->AddMenu("Harass Settings");
	XerathHarassQ = XerathHarassMenu->CheckBox("Q ", true);
	XerathHarassW = XerathHarassMenu->CheckBox("W ", true);
	XerathHarassMana = XerathHarassMenu->AddInteger("Mana %", 0, 100, 0);

	XerathFarmMenu = XerathMainMenu->AddMenu("Farm Settings");
	XerathLaneClearW = XerathFarmMenu->CheckBox("LaneClear W", true);
	XerathFarmMana = XerathFarmMenu->AddInteger("Mana %", 0, 100, 0);

	XerathAutoMenu = XerathMainMenu->AddMenu("Auto Settings");
	XerathAutoR = XerathAutoMenu->CheckBox("Auto Shoot R", true);
	XerathAutoRTime = XerathAutoMenu->AddInteger("delay between R", 0, 1000, 300);
	XerathAutoRDistance = XerathAutoMenu->AddInteger("R max distance from cursor", 300, 10000, 1000);

	XerathDrawingsMenu = XerathMainMenu->AddMenu("Draw Settings");
	XerathDrawQ = XerathDrawingsMenu->CheckBox("Q", true);
	XerathDrawW = XerathDrawingsMenu->CheckBox("W", true);
	XerathDrawE = XerathDrawingsMenu->CheckBox("E", true);
	XerathDrawR = XerathDrawingsMenu->CheckBox("R", true);
	XerathDrawRCast = XerathDrawingsMenu->CheckBox("R Target Select Radius", true);
}
