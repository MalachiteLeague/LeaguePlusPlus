#pragma once
#include "KalistaVariables.h"

////menu
//IMenu* KalistaMainMenu;
//IMenu* KalistaQSettings;
//IMenu* KalistaWSettings;
//IMenu* KalistaESettings;
//IMenu* KalistaRSettings;
//IMenu* KalistaAdvanceSettings;
//IMenu* KalistaDrawingsMenu;
//
////Qsettings
//IMenuOption* KalistaQCombo;
//IMenuOption* KalistaQComboMana;
//IMenuOption* KalistaQHarass;
//IMenuOption* KalistaQHarassMana;
//
////Wsettings
//IMenuOption* KalistaWDragonBaron;
//
//
////ESettings
//IMenuOption* KalistaEFarmSlider;
//IMenuOption* KalistaEKillsteal;// should be auto ? 
//IMenuOption* KalistaEStealBaronDragon;//
//IMenuOption* KalistaECanonMinion;
//IMenuOption* KalistaEAutoHarass;
//
//
////RSettings
//IMenuOption* KalistaRSaveSoulBound;
//
//inline void KalistaMenuAndSpells()
//{
//	Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, true, false, kCollidesWithYasuoWall);
//	Q->SetSkillshot(0.3f, 250, 1000, 825);
//	W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, true, kCollidesWithNothing);
//	E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, kCollidesWithNothing);
//	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, true, kCollidesWithYasuoWall | kCollidesWithMinions);
//	R->SetSkillshot(0.2f, 40, 2000, 1300);
//
//	KalistaMainMenu = GPluginSDK->AddMenu("MalaChiteAIO Kalista");
//
//	KalistaQSettings = KalistaMainMenu->AddMenu("Q Settings");
//	//Qsettings
//	KalistaQCombo = KalistaQSettings->CheckBox("Q Combo",true);
//	KalistaQComboMana = KalistaQSettings->AddInteger("Q Combo Mana", 0 , 100, 40);
//	KalistaQHarass = KalistaQSettings->CheckBox("Q harass", true);
//	KalistaQHarassMana = KalistaQSettings->AddInteger("Q harass mana", 0,100,60);
//
//	//Wsettings
//	KalistaWSettings = KalistaMainMenu->AddMenu("W Settings");
//	KalistaWDragonBaron;
//
//	//ESettings
//	KalistaESettings = KalistaMainMenu->AddMenu("E Settings");
//	KalistaEFarmSlider;
//	KalistaEKillsteal;// should be auto ? 
//	KalistaEStealBaronDragon;//
//	KalistaECanonMinion;
//	KalistaEAutoHarass;
//
//
//	//RSettings
//	KalistaRSettings = KalistaMainMenu->AddMenu("R Settings");
//	IMenuOption* KalistaRSaveSoulBound;
//}
