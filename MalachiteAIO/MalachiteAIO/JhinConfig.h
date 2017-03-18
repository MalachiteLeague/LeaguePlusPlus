#pragma once
#include "JhinVariables.h"

//menu
IMenu* JhinMainMenu;
IMenu* JhinComboMenu;
IMenu* JhinHarassMenu;
IMenu* JhinFarmMenu;
IMenu* JhinAutoMenu;
IMenu* JhinDrawingsMenu;

//combo
IMenuOption* JhinComboQ;
IMenuOption* JhinComboE;
IMenuOption* JhinComboW;

//auto
IMenuOption* JhinAutoW;
IMenuOption* JhinAutoR;

//harass
IMenuOption* JhinHarassQ;
IMenuOption* JhinHarassW;
IMenuOption* JhinHarassMana;

//lasthit
IMenuOption* JhinLastHitQ;

//laneclear
IMenuOption* JhinLaneClearQ;


//jungleclear
IMenuOption* JhinJungleClearQ;
IMenuOption* JhinFarmMana;

inline void JhinMenuAndSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, kCollidesWithYasuoWall);
	Q->SetOverrideRange(600);
	W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, true, kCollidesWithYasuoWall | kCollidesWithHeroes);
	W->SetSkillshot(1.0f, 100, 10000, 2500);
	E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, kCollidesWithNothing);
	E->SetOverrideRange(750);
	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, true, kCollidesWithYasuoWall);
	R->SetSkillshot(0.45f, 100, 5000, 3500);

	JhinMainMenu = GPluginSDK->AddMenu("MalaChiteAIO Jhin");

	JhinComboMenu = JhinMainMenu->AddMenu("Combo Settings");
	JhinComboQ = JhinComboMenu->CheckBox("Q", true);
	JhinComboW = JhinComboMenu->CheckBox("W", true);
	JhinComboE = JhinComboMenu->CheckBox("E", true);

	JhinHarassMenu = JhinMainMenu->AddMenu("Harass Settings");
	JhinHarassQ = JhinHarassMenu->CheckBox("Q ", true);
	JhinHarassW = JhinHarassMenu->CheckBox("W ", true);
	JhinHarassMana = JhinHarassMenu->AddInteger("Mana %", 0, 100, 0);

	JhinFarmMenu = JhinMainMenu->AddMenu("Farm Settings");

	JhinLaneClearQ = JhinFarmMenu->CheckBox("LaneClear Q", true);
	JhinJungleClearQ = JhinFarmMenu->CheckBox("Jungle Q", true);
	JhinLastHitQ = JhinFarmMenu->CheckBox("LastHit Q", true);
	JhinFarmMana = JhinFarmMenu->AddInteger("Mana %", 0, 100, 0);

	JhinAutoMenu = JhinMainMenu->AddMenu("Auto Settings");
	JhinAutoW = JhinAutoMenu->CheckBox("W on CC", true);
	JhinAutoR = JhinAutoMenu->CheckBox("Auto Shoot R", true);
}
