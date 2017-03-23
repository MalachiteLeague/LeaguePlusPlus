#pragma once
#include "MainVariables.h"
#include "SpellBlockerConfig.h"

SArray<IUnit*> DetectedMissile;
PLUGIN_EVENT(void) SpellBlockerOnSpellCast(CastedSpell const& Args)
{
	if (Args.Caster_ == nullptr || Args.Caster_->UnitFlags() != FL_HERO || Args.Caster_->GetTeam() == Player()->GetTeam()
		|| !(Args.Target_ != nullptr && Args.Target_->GetNetworkId() == Player()->GetNetworkId()))
	{
		return;
	}
	SArray<TargetedSpellData> spelldata = SpellBlockerTargetedSpells.Where([&](TargetedSpellData i) {return !i.IsMissile; });
	if (spelldata.Any([&](TargetedSpellData i)
	{
		return Contains(Args.Caster_->ChampionName(), i.ChampionName) && i.UseSpellSlotNonMissile ? GSpellData->GetSlot(Args.Data_) == i.Slot :
			i.IsEqualSpellName(Args.Name_) && SpellBlockerOptions[i.ChampionName + SpellSlotToString(i.Slot)]->Enabled();
	}))
	{
		if (Contains(Player()->ChampionName(), "fiora") && SpellBlockerSpell1->Enabled() && W->IsReady())
		{
			auto target = SelectTarget(PhysicalDamage, W->Range());
			if (IsValidTarget(target))
			{
				auto pos = Extend(Player()->GetPosition(), target->GetPosition(), W->Range());
				W->CastOnPosition(pos);
			}
			else
			{
				auto pos = Extend(Player()->GetPosition(), Args.Caster_->GetPosition(), W->Range());
				W->CastOnPosition(pos);
			}
		}
		else if (Contains(Player()->ChampionName(), "sivir") && SpellBlockerSpell1->Enabled() && E->IsReady())
		{
			E->CastOnPlayer();
		}
	}
}

PLUGIN_EVENT(void) SpellBlockerOnGameUpdate()
{
	if (Contains(Player()->ChampionName(), "fiora") && SpellBlockerSpell1->Enabled() && W->IsReady())
	{
		SArray<TargetedSpellData> spelldata = SpellBlockerTargetedSpells.Where([&](TargetedSpellData i) {return i.IsMissile; });
		for (IUnit* missile : DetectedMissile.ToVector())
		{
			if (spelldata.Any([&](TargetedSpellData i)
				{return i.IsEqualSpellName(GMissileData->GetName(missile)) && SpellBlockerOptions[i.SpellNames[0]]->Enabled(); })
				&& Distance(missile, Player()) <= (0.5f +  GGame->Latency()/1000) * GMissileData->GetSpeed(missile))
			{
				auto target = SelectTarget(PhysicalDamage, W->Range());
				if (IsValidTarget(target))
				{
					auto pos = Extend(Player()->GetPosition(), target->GetPosition(), W->Range());
					W->CastOnPosition(pos);
				}
				else
				{
					auto pos = Extend(Player()->GetPosition(), GMissileData->GetStartPosition(missile), W->Range());
					W->CastOnPosition(pos);
				}
			}
		}
	}
	else if (Contains(Player()->ChampionName(), "sivir") && SpellBlockerSpell1->Enabled() && E->IsReady())
	{
		SArray<TargetedSpellData> spelldata = SpellBlockerTargetedSpells.Where([&](TargetedSpellData i) {return i.IsMissile; });
		for (IUnit* missile : DetectedMissile.ToVector())
		{
			if (spelldata.Any([&](TargetedSpellData i)
				{return i.IsEqualSpellName(GMissileData->GetName(missile)) && SpellBlockerOptions[i.SpellNames[0]]->Enabled(); })
				&& Distance(missile, Player()) <= (0.5f + GGame->Latency() / 1000) * GMissileData->GetSpeed(missile))
			{
				E->CastOnPlayer();
			}
		}
	}
}
PLUGIN_EVENT(void) SpellBlockerOnCreateObject(IUnit* Source)
{
	if (Source == nullptr)
		return;
	if (Source->IsMissile())
	{
		for (TargetedSpellData spell : SpellBlockerTargetedSpells.Where([&](TargetedSpellData i) {return i.IsMissile; }).ToVector())
		{
			for (string name : spell.SpellNames)
			{
				if (Contains(name, GMissileData->GetName(Source)))
				{
					DetectedMissile.Add(Source);
				}
			}
		}
	}
}
PLUGIN_EVENT(void) SpellBlockerOnDestroyObject(IUnit* Source)
{
	if (Source == nullptr)
		return;
	if (Source->IsMissile())
	{
		for (TargetedSpellData spell : SpellBlockerTargetedSpells.Where([&](TargetedSpellData i) {return i.IsMissile; }).ToVector())
		{
			for (string name : spell.SpellNames)
			{
				if (Contains(name, GMissileData->GetName(Source)))
				{
					DetectedMissile.RemoveAll([&](IUnit* i) {return i->GetNetworkId() == Source->GetNetworkId(); });
				}
			}
		}
	}
}
void SpellBlockerOnload()
{
	if (!Contains(Player()->ChampionName(), "Sivir") && !Contains(Player()->ChampionName(), "Fiora"))
		return;
	GEventManager->AddEventHandler(kEventOnGameUpdate, SpellBlockerOnGameUpdate);
	GEventManager->AddEventHandler(kEventOnSpellCast, SpellBlockerOnSpellCast);
	GEventManager->AddEventHandler(kEventOnCreateObject, SpellBlockerOnCreateObject);
	GEventManager->AddEventHandler(kEventOnDestroyObject, SpellBlockerOnDestroyObject);
	SpellBlockerMenu();
}
void SpellBlockerUnload()
{
	if (!Contains(Player()->ChampionName(), "Sivir") && !Contains(Player()->ChampionName(), "Fiora"))
		return;
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, SpellBlockerOnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnSpellCast, SpellBlockerOnSpellCast);
	GEventManager->RemoveEventHandler(kEventOnCreateObject, SpellBlockerOnCreateObject);
	GEventManager->RemoveEventHandler(kEventOnDestroyObject, SpellBlockerOnDestroyObject);
	SpellBlockerMainMenu->Remove();
}