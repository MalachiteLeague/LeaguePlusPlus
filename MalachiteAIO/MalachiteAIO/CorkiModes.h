#pragma once
#include "CorkiConfig.h"

inline void CorkiComboOnUpdate()
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
	if (CorkiComboQ->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, Q->Range());
		if (IsValidTarget(target))
		{
			MalachiteCast(Q, target, kHitChanceHigh);
		}
	}
	if (CorkiComboE->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, GetAutoAttackRange(Player()));
		if (IsValidTarget(target))
		{
			E->CastOnPlayer();
		}
	}
	if (CorkiComboR->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, R->Range());
		if (IsValidTarget(target))
		{
			MalachiteCast(R, target, kHitChanceHigh);
		}
	}
}
inline void CorkiHarassOnUpdate()
{
	if (GOrbwalking->GetOrbwalkingMode() != kModeMixed)
		return;
	if (Player()->ManaPercent() <= CorkiHarassMana->GetInteger())
		return;
	if (!IsADCanCastSpell())
		return;
	if (CorkiHarassQ->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, Q->Range());
		if (IsValidTarget(target))
		{
			MalachiteCast(Q, target, kHitChanceHigh);
		}
	}
	if (CorkiHarassE->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, GetAutoAttackRange(Player()));
		if (IsValidTarget(target))
		{
			E->CastOnPlayer();
		}
	}
}
inline void CorkiLastHitOnUpdate()
{
	if (GOrbwalking->GetOrbwalkingMode() != kModeLastHit)
		return;
	if (Player()->ManaPercent() <= CorkiFarmMana->GetInteger())
		return;
	if (!IsADCanCastSpell())
		return;
	if (CorkiLastHitQ->Enabled())
	{
		auto targets = EnemyMinions(Q->Range()).Where([&](IUnit* i) {return GetSpellDamage(i, kSlotQ) >= i->GetHealth(); }).ToVector();
		for (IUnit* target : targets)
		{
			MalachiteCast(Q, target, kHitChanceHigh);
		}
	}
}
inline void CorkiLaneJungOnUpdate()
{
	if (GOrbwalking->GetOrbwalkingMode() != kModeLaneClear)
		return;
	if (Player()->ManaPercent() <= CorkiFarmMana->GetInteger())
		return;
	if (!IsADCanCastSpell())
		return;
	if (CorkiJungleClearQ->Enabled())
	{
		auto targets = NeutralMinions(Q->Range()).ToVector();
		for (IUnit* target : targets)
		{
			MalachiteCast(Q, target, kHitChanceHigh);
		}
	}
	if (CorkiJungleClearE->Enabled())
	{
		auto targets = NeutralMinions(GetAutoAttackRange(Player())).ToVector();
		for (IUnit* target : targets)
		{
			E->CastOnPlayer();
		}
	}
	if (CorkiLaneClearQ->Enabled())
	{
		auto targets = EnemyMinions(Q->Range()).Where([&](IUnit* i) {return CountMinionsInRange(i->GetPosition(), 250) >= 3; }).ToVector();
		for (IUnit* target : targets)
		{
			MalachiteCast(Q, target, kHitChanceHigh);
		}
	}
	if (CorkiLaneClearE->Enabled())
	{
		if (CountMinionsInRange(Player()->GetPosition(), GetAutoAttackRange(Player())) >= 3)
		{
			E->CastOnPlayer();
		}
	}
}
inline void CorkiAutoOnUpdate()
{
	if (Player()->IsRecalling())
		return;
	if (!GOrbwalking->CanMove())
		return;
	if (CorkiAutoQ->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, Q->Range());
		if (IsValidTarget(target))
		{
			MalachiteCast(Q, target, kHitChanceHigh);
		}
	}
	if (CorkiAutoR->Enabled() && Player()->GetSpellBook()->GetAmmo(kSlotR) >=  CorkiAutoRAtStack->GetInteger())
	{
		auto target = SelectTarget(PhysicalDamage, R->Range());
		if (IsValidTarget(target))
		{
			MalachiteCast(R, target, kHitChanceHigh);
		}
	}
}