#pragma once
#include "EzrealConfig.h"
#include <string>

inline void EzrealComboOnUpdate()
{
	if (GOrbwalking->GetOrbwalkingMode() != kModeCombo)
		return;

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
	if (EzealComboQ->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, Q->Range());
		if (IsValidTarget(target))
		{
			Q->CastOnTarget(target, kHitChanceMedium);
		}
	}
	if (EzealComboW->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, W->Range());
		if (IsValidTarget(target))
		{
			W->CastOnTarget(target, kHitChanceMedium);
		}
	}
	if (EzealComboR->Enabled() && CountEnemiesInRange(Player()->GetPosition(), 1000) == 0)
	{
		auto target = SelectTarget(PhysicalDamage,2000);
		if (IsValidTarget(target) && GetSpellDamage(target,kSlotR) >= target->GetHealth() / 1.5)
		{
			R->CastOnTarget(target, kHitChanceMedium);
		}
	}
}
inline void EzrealHarassOnUpdate()
{
	if (GOrbwalking->GetOrbwalkingMode() != kModeMixed)
		return;
	if (Player()->ManaPercent() <= EzealHarassMana->GetInteger())
		return;
	if (!GOrbwalking->CanMove())
		return;
	if (EzealHarassQ->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, Q->Range());
		if (IsValidTarget(target))
		{
			Q->CastOnTarget(target, kHitChanceMedium);
		}
	}
	if (EzealHarassW->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, W->Range());
		if (IsValidTarget(target))
		{
			W->CastOnTarget(target, kHitChanceMedium);
		}
	}
}
inline void EzrealLastHitOnUpdate()
{
	if (GOrbwalking->GetOrbwalkingMode() != kModeLastHit)
		return;
	if (Player()->ManaPercent() <= EzealFarmMana->GetInteger())
		return;
	if (!GOrbwalking->CanMove())
		return;
	if (EzealLastHitQ->Enabled())
	{
		auto targets = EnemyMinions(Q->Range()).Where([&](IUnit* i) {return GetSpellDamage(i, kSlotQ) >= i->GetHealth(); }).ToVector();
		for (IUnit* target : targets)
		{
			Q->CastOnTarget(target, kHitChanceMedium);
		}
	}
}
inline void EzrealLaneJungOnUpdate()
{
	if (GOrbwalking->GetOrbwalkingMode() != kModeLaneClear)
		return;
	if (Player()->ManaPercent() <= EzealFarmMana->GetInteger())
		return;
	if (!GOrbwalking->CanMove())
		return;
	if (EzealJungleClearQ->Enabled())
	{
		auto targets = NeutralMinions(Q->Range()).ToVector();
		for (IUnit* target : targets)
		{
			Q->CastOnTarget(target, kHitChanceMedium);
		}
	}	
	if (EzealLaneClearQ->Enabled())
	{
		auto targets = EnemyMinions(Q->Range()).ToVector();
		for (IUnit* target : targets)
		{
			Q->CastOnTarget(target, kHitChanceMedium);
		}
	}

}
inline void EzrealAutoOnUpdate()
{
	if (Player()->IsRecalling())
		return;
	if (!GOrbwalking->CanMove())
		return;
	if (EzealAutoQ->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, Q->Range());
		if (IsValidTarget(target))
		{
			Q->CastOnTarget(target, kHitChanceMedium);
		}
	}
	if (EzealAutoW->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, W->Range());
		if (IsValidTarget(target))
		{
			W->CastOnTarget(target, kHitChanceMedium);
		}
	}
	if (Player()->HasItemId(3070) || Player()->HasItemId(3004) || Player()->HasItemId(3003))
	{
		if (EzealAutoStackTear->Enabled() && GUtility->IsPositionInFountain(Player()->GetPosition()))
		{
			Q->CastOnPosition(Player()->GetPosition());
			W->CastOnPosition(Player()->GetPosition());
		}
	}
}