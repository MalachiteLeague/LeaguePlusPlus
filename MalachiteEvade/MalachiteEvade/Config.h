#pragma once
#include "PluginSDK.h"
#include <map>

class SkillShotMenu
{
public :
	IMenu*  ParentMenu;
	IMenuOption* Enable;
	IMenuOption* PercentHP;
	IMenuOption* DangerLevel;
	IMenuOption* IsDangerous;
	IMenuOption* Draw;

};
IMenu* EvadeMenu;
IMenu* EvadeSkillMenu;
IMenu* EvadeSkillShotMenu;

IMenuOption* EvadeUsePercentHP;
IMenuOption* EvadeToogleKey;
IMenuOption* EvadeDodgeOnlyDangerousKey;
IMenuOption* EvadeEnable;
IMenuOption* EvadeDrawStatus;
//IMenuOption* EvadeDrawEnableColor;
//IMenuOption* EvadeDrawDisableColor;
IMenuOption* EvadeDrawTestOnAlly;

// evade spells
IMenuOption* EvadeWithWalking;
IMenuOption* EvadeWithWalkingDanger;
IMenuOption* EvadeWithFlash;
IMenuOption* EvadeWithFLashDanger;
IMenuOption* EvadeWithHourglass;
IMenuOption* EvadeWithHourglassDanger;

std::map<string, SkillShotMenu> EvadeSkillShotOptions;

inline void EvadeMenuInit()
{
	EvadeMenu = GPluginSDK->AddMenu("MalachiteEvade");
	EvadeUsePercentHP = EvadeMenu->CheckBox("Use % HP", false);
	EvadeToogleKey = EvadeMenu->AddKey("Toggle Key", 'K');
	EvadeDodgeOnlyDangerousKey = EvadeMenu->AddKey("Dodge Only Dangerous Key", 32);
	EvadeEnable = EvadeMenu->CheckBox("Enable", true);
	EvadeDrawStatus = EvadeMenu->CheckBox("Draw Evade Status", true);
	//EvadeDrawEnableColor = EvadeMenu->AddColor("Enable Color", DWORD(0xFFFFFF));
	//EvadeDrawDisableColor = EvadeMenu->AddColor("Disable Color", DWORD(0xFFFF00));
	EvadeDrawTestOnAlly = EvadeMenu->CheckBox("Draw Test On Ally", false);
	//
	EvadeSkillMenu = EvadeMenu->AddMenu("Evader");

	EvadeWithWalking = EvadeSkillMenu->CheckBox("Walking", true);
	EvadeWithWalkingDanger = EvadeSkillMenu->AddInteger("Min Walk Danger Level", 1,5,1);
	EvadeWithFlash = EvadeSkillMenu->CheckBox("Flash", true);
	EvadeWithFLashDanger = EvadeSkillMenu->AddInteger("Min Flash Danger Level", 1, 5, 5);
	EvadeWithHourglass = EvadeSkillMenu->CheckBox("Hourglass", true);
	EvadeWithHourglassDanger = EvadeSkillMenu->AddInteger("Min Hourglass Danger Level", 1, 5, 5);

	//
	EvadeSkillShotMenu = EvadeMenu->AddMenu("SkillShot setting");

	for (SpellData* spell : SpellsDB->Spells)
	{
		if (Enemies().Any([&](IUnit* i) {return string(i->ChampionName()) == spell->ChampName; }))
		{
			EvadeSkillShotOptions[spell->MenuName].ParentMenu = EvadeSkillShotMenu->AddMenu(spell->MenuName.c_str());
			EvadeSkillShotOptions[spell->MenuName].Enable = EvadeSkillShotOptions[spell->MenuName].ParentMenu->CheckBox("Enable", !spell->DisabledByDefault);
			EvadeSkillShotOptions[spell->MenuName].PercentHP = EvadeSkillShotOptions[spell->MenuName].ParentMenu->AddInteger("% HP", 0,101,101);
			EvadeSkillShotOptions[spell->MenuName].DangerLevel = EvadeSkillShotOptions[spell->MenuName].ParentMenu->AddInteger("Danger Level", 1,5, spell->DangerValue);
			EvadeSkillShotOptions[spell->MenuName].IsDangerous = EvadeSkillShotOptions[spell->MenuName].ParentMenu->CheckBox("Is Dangerous", spell->IsDangerous);
			EvadeSkillShotOptions[spell->MenuName].Draw = EvadeSkillShotOptions[spell->MenuName].ParentMenu->CheckBox("Draw", true);
		}
		//if (Allies().Any([&](IUnit* i) {return string(i->ChampionName()) == spell->ChampName; }))
		//{
		//	EvadeSkillShotOptions[spell->MenuName].ParentMenu = EvadeSkillShotMenu->AddMenu(spell->MenuName.c_str());
		//	EvadeSkillShotOptions[spell->MenuName].Enable = EvadeSkillShotOptions[spell->MenuName].ParentMenu->CheckBox("Enable", true);
		//	EvadeSkillShotOptions[spell->MenuName].PercentHP = EvadeSkillShotOptions[spell->MenuName].ParentMenu->AddInteger("% HP", 0, 101, 101);
		//	EvadeSkillShotOptions[spell->MenuName].DangerLevel = EvadeSkillShotOptions[spell->MenuName].ParentMenu->AddInteger("Danger Level", 1, 5, spell->DangerValue);
		//	EvadeSkillShotOptions[spell->MenuName].IsDangerous = EvadeSkillShotOptions[spell->MenuName].ParentMenu->CheckBox("Is Dangerous", spell->IsDangerous);
		//	EvadeSkillShotOptions[spell->MenuName].Draw = EvadeSkillShotOptions[spell->MenuName].ParentMenu->CheckBox("Draw", true);
		//}
	}
}

//
inline bool GetDodgeStage(DetectedSKillShot skillshot, int DangerousLevel)
{
	if (EvadeSkillShotOptions.find(skillshot.Data->MenuName) == EvadeSkillShotOptions.end())
		return false;
	if (!EvadeEnable->Enabled())
		return false;
	if (DangerousLevel > EvadeSkillShotOptions[skillshot.Data->MenuName].DangerLevel->GetInteger())
		return false;
	if (!EvadeSkillShotOptions[skillshot.Data->MenuName].Enable->Enabled())
		return false;
	if (EvadeUsePercentHP->Enabled() && Player()->HealthPercent() >= EvadeSkillShotOptions[skillshot.Data->MenuName].PercentHP->GetInteger())
		return false;
	if (IsKeyDown(EvadeDodgeOnlyDangerousKey) && !EvadeSkillShotOptions[skillshot.Data->MenuName].IsDangerous->Enabled())
		return false;
	return true;
}

