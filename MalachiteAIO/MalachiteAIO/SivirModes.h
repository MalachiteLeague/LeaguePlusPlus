#pragma once
#include "SivirConfig.h"
#include <string>

inline void SivirModeOnSpellCast(CastedSpell const& Args)
{
}

inline void SivirModeAfterAttack(IUnit* Source, IUnit* Target)
{
	if (Target == nullptr || Target->IsDead())
		return;
	if (!W->IsReady())
		return;
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		if (SivirComboW->Enabled())
		{
			W->CastOnPlayer();
			//GOrbwalking->ResetAA();
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed && Target->UnitFlags() == FL_HERO && Player()->ManaPercent() >= SivirHarassMana->GetInteger())
	{
		if (SivirHarassW->Enabled())
		{
			W->CastOnPlayer();
			//GOrbwalking->ResetAA();
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear && Player()->ManaPercent() >= SivirFarmMana->GetInteger())
	{
		if (SivirLaneClearW->Enabled() && Target->GetTeam() != kTeamNeutral)
		{
			W->CastOnPlayer();
			//GOrbwalking->ResetAA();
		}
		if (SivirJungleClearQ->Enabled() && Target->GetTeam() == kTeamNeutral)
		{
			W->CastOnPlayer();
			//GOrbwalking->ResetAA();
		}
	}
}
inline void SivirModeOnUpdate()
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		{

			IUnit* target = SelectTarget(SpellDamage, 700);

			CastItemOnUnit(3146, 700, target);

		}

		{

			IUnit* target = SelectTarget(SpellDamage, 550);

			CastItemOnUnit(3144, 550, target);

		}
		{

			IUnit* target = SelectTarget(SpellDamage, 650);

			CastItemOnUnit(3153, 650, target);

		}
		if (!IsADCanCastSpell())
			return;
		if (SivirComboQ->Enabled())
		{
			auto target = SelectTarget(PhysicalDamage, Q->Range());
			if (IsValidTarget(target))
			{
				MalachiteCast(Q, target, kHitChanceHigh);
			}
		}
		if (SivirComboR->Enabled())
		{
			if (CountEnemiesInRange(Player()->GetPosition(), 1000) >= 3 || (CountEnemiesInRange(Player()->GetPosition(), 1000) >= 1 && Player()->HealthPercent() <= 50))
			{
				R->CastOnPlayer();
			}
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed && Player()->ManaPercent() >= SivirHarassMana->GetInteger())
	{
		if (!IsADCanCastSpell())
			return;
		if (SivirHarassQ->Enabled())
		{
			auto target = SelectTarget(PhysicalDamage, Q->Range());
			if (IsValidTarget(target))
			{
				MalachiteCast(Q, target, kHitChanceHigh);
			}
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear && Player()->ManaPercent() >= SivirFarmMana->GetInteger())
	{
		if (!IsADCanCastSpell())
			return;
		if (SivirLaneClearQ->Enabled())
		{
			FarmLocation Location = FindBestLineCastPosition(vector<Vec3>{Player()->GetPosition()}, Q->Range(),Q->Range(), Q->Radius(), true, false);
			if (Location.HitCount >=3)
			{
				Q->CastOnPosition(Location.CastPosition);
			}
		}
		if (SivirJungleClearQ->Enabled())
		{
			auto targets = NeutralMinions(Q->Range()).OrderBy<float>([&](IUnit* i) {return 1- i->GetMaxHealth(); });
			for (auto target : targets.ToVector())
			{
				MalachiteCast(Q, target, kHitChanceHigh);
			}
		}
	}
}