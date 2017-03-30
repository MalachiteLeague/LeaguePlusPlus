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
	if (!IsADCanCastSpell())
		return;
	if (EzealComboQ->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, Q->Range());
		if (IsValidTarget(target))
		{
			MalachiteCast(Q, target, kHitChanceHigh);
		}
	}
	if (EzealComboW->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, W->Range());
		if (IsValidTarget(target))
		{
			MalachiteCast(W, target, kHitChanceHigh);
		}
	}
	if (EzealComboR->Enabled() && CountEnemiesInRange(Player()->GetPosition(), 1000) == 0)
	{
		auto target = SelectTarget(PhysicalDamage,2000);
		if (IsValidTarget(target) && GetSpellDamage(target,kSlotR) >= target->GetHealth() / 1.5)
		{
			MalachiteCast(R, target, kHitChanceHigh);
		}
	}
}
inline void EzrealHarassOnUpdate()
{
	if (GOrbwalking->GetOrbwalkingMode() != kModeMixed)
		return;
	if (Player()->ManaPercent() <= EzealHarassMana->GetInteger())
		return;
	if (!IsADCanCastSpell())
		return;
	if (EzealHarassQ->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, Q->Range());
		if (IsValidTarget(target))
		{
			MalachiteCast(Q, target, kHitChanceHigh);
		}
	}
	if (EzealHarassW->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, W->Range());
		if (IsValidTarget(target))
		{
			MalachiteCast(W, target, kHitChanceHigh);
		}
	}
}
inline void EzrealLastHitOnUpdate()
{
	if (GOrbwalking->GetOrbwalkingMode() != kModeLastHit)
		return;
	if (Player()->ManaPercent() <= EzealFarmMana->GetInteger())
		return;
	if (!IsADCanCastSpell())
		return;
	if (EzealLastHitQ->Enabled())
	{
		auto targets = EnemyMinions(Q->Range()).Where([&](IUnit* i) {return GetSpellDamage(i, kSlotQ) >= i->GetHealth(); }).ToVector();
		for (IUnit* target : targets)
		{
			MalachiteCast(Q, target, kHitChanceHigh);
		}
	}
}
inline void EzrealLaneJungOnUpdate()
{
	if (GOrbwalking->GetOrbwalkingMode() != kModeLaneClear)
		return;
	if (Player()->ManaPercent() <= EzealFarmMana->GetInteger())
		return;
	if (!IsADCanCastSpell())
		return;
	if (EzealJungleClearQ->Enabled())
	{
		auto targets = NeutralMinions(Q->Range()).ToVector();
		for (IUnit* target : targets)
		{
			//Q->CastOnTarget(target, kHitChanceHigh);
			MalachiteCast(Q, target, kHitChanceHigh);
		}
	}	
	if (EzealLaneClearQ->Enabled())
	{
		auto targets = EnemyMinions(Q->Range()).ToVector();
		for (IUnit* target : targets)
		{
			MalachiteCast(Q, target, kHitChanceHigh);
		}
	}

}
inline void EzrealAutoOnUpdate()
{
	if (Player()->IsRecalling())
		return;
	if (!IsADCanCastSpell())
		return;
	if (EzealAutoQ->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, Q->Range());
		if (IsValidTarget(target))
		{
			MalachiteCast(Q, target, kHitChanceHigh);
		}
	}
	if (EzealAutoW->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, W->Range());
		if (IsValidTarget(target))
		{
			MalachiteCast(W, target, kHitChanceHigh);
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