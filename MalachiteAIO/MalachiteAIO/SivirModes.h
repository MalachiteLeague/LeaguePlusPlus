#pragma once
#include "SivirConfig.h"
#include <string>

inline void SivirModeOnSpellCast(CastedSpell const& Args)
{
	if (SivirAutoE->Enabled() )
	{
		if (Args.Caster_ != nullptr && Args.Caster_->IsEnemy(Player()) && Args.Caster_->IsHero() && GSpellData->GetTarget(Args.Data_) != nullptr
			&& GSpellData->GetTarget(Args.Data_)->GetNetworkId() == Player()->GetNetworkId())
		{
			vector<eSpellSlot> spells {kSlotQ, kSlotE, kSlotW, kSlotR};
			for (auto spell : spells)
			{
				if (GSpellData->GetSlot(Args.Data_) == spell)
				{
					E->CastOnPlayer();
				}
			}
		}
	}
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
		if (!GOrbwalking->CanMove())
			return;
		if (SivirComboQ->Enabled())
		{
			auto target = SelectTarget(PhysicalDamage, Q->Range());
			if (IsValidTarget(target))
			{
				Q->CastOnTarget(target, kHitChanceHigh);
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
		if (!GOrbwalking->CanMove())
			return;
		if (SivirHarassQ->Enabled())
		{
			auto target = SelectTarget(PhysicalDamage, Q->Range());
			if (IsValidTarget(target))
			{
				Q->CastOnTarget(target, kHitChanceHigh);
			}
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear && Player()->ManaPercent() >= SivirFarmMana->GetInteger())
	{
		if (!GOrbwalking->CanMove())
			return;
		if (SivirLaneClearQ->Enabled())
		{
			Vec3 CastPositionFrom;
			Vec3 CastPosition;
			int HitCount;
			FindBestLineCastPosition(vector<Vec3>{Player()->GetPosition()}, Q->Range(), Q->Radius(), true, false, CastPosition, HitCount, CastPositionFrom);
			if (HitCount >=3)
			{
				Q->CastOnPosition(CastPosition);
			}
		}
		if (SivirJungleClearQ->Enabled())
		{
			auto targets = NeutralMinions(Q->Range()).OrderBy<float>([&](IUnit* i) {return 1- i->GetMaxHealth(); });
			for (auto target : targets.ToVector())
			{
				Q->CastOnTarget(target, kHitChanceHigh);
			}
		}
	}
}