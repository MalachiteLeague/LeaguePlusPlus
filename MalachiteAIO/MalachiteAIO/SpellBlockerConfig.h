#pragma once
#include "TargetedSpells.h"
#include "SpellBlockerSpells.h"
#include <map>

IMenu* SpellBlockerMainMenu;
IMenuOption* SpellBlockerSpell1;
std::map <string, IMenuOption*> SpellBlockerOptions;
inline void SpellBlockerMenu()
{
	SpellBlockerTargetedSpellOnLoad();
	SpellBlockerTargetedSpells.RemoveAll([&](TargetedSpellData i) { return !Enemies().Any([&](IUnit* hero) {return Contains(hero->ChampionName(), i.ChampionName); }); });


	SpellBlockerMainMenu = GPluginSDK->AddMenu("MalaChiteAIO SpellBlocker");
	if (Contains(Player()->ChampionName(), "Sivir"))
		SpellBlockerSpell1 = SpellBlockerMainMenu->CheckBox("Use Sivir E", true);
	else if (Contains(Player()->ChampionName(), "Fiora"))
		SpellBlockerSpell1 = SpellBlockerMainMenu->CheckBox("Use Fiora W", true);

	for (TargetedSpellData spell : SpellBlockerTargetedSpells.ToVector())
	{
		if (spell.IsMissile)
		{
			SpellBlockerOptions[spell.SpellNames[0]] = SpellBlockerMainMenu->CheckBox((spell.ChampionName + " " + SpellSlotToString(spell.Slot) + " " + spell.SpellNames[0]).c_str(), false);
		}
		else
		{
			SpellBlockerOptions[spell.ChampionName + SpellSlotToString(spell.Slot)] = SpellBlockerMainMenu->CheckBox((spell.ChampionName + " " + SpellSlotToString(spell.Slot)).c_str(), false);
		}
	}
	
}