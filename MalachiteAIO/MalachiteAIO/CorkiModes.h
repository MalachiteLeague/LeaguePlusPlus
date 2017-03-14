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
	if (!GOrbwalking->CanMove())
		return;
	if (CorkiComboQ->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, Q->Range());
		if (IsValidTarget(target))
		{
			Q->CastOnTarget(target, kHitChanceMedium);
		}
	}
	if (CorkiComboE->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, Player()->GetRealAutoAttackRange(Player()));
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
			R->CastOnTarget(target, kHitChanceMedium);
		}
	}
}
inline void CorkiHarassOnUpdate()
{
	if (GOrbwalking->GetOrbwalkingMode() != kModeMixed)
		return;
	if (Player()->ManaPercent() <= CorkiHarassMana->GetInteger())
		return;
	if (!GOrbwalking->CanMove())
		return;
	if (CorkiHarassQ->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, Q->Range());
		if (IsValidTarget(target))
		{
			Q->CastOnTarget(target, kHitChanceMedium);
		}
	}
	if (CorkiHarassE->Enabled())
	{
		auto target = SelectTarget(PhysicalDamage, Player()->GetRealAutoAttackRange(Player()));
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
	if (!GOrbwalking->CanMove())
		return;
	if (CorkiLastHitQ->Enabled())
	{
		auto targets = EnemyMinions(Q->Range()).Where([&](IUnit* i) {return GetSpellDamage(i, kSlotQ) >= i->GetHealth(); }).ToVector();
		for (IUnit* target : targets)
		{
			Q->CastOnTarget(target, kHitChanceMedium);
		}
	}
}
inline void CorkiLaneJungOnUpdate()
{
	if (GOrbwalking->GetOrbwalkingMode() != kModeLaneClear)
		return;
	if (Player()->ManaPercent() <= CorkiFarmMana->GetInteger())
		return;
	if (!GOrbwalking->CanMove())
		return;
	if (CorkiJungleClearQ->Enabled())
	{
		auto targets = NeutralMinions(Q->Range()).ToVector();
		for (IUnit* target : targets)
		{
			Q->CastOnTarget(target, kHitChanceMedium);
		}
	}
	if (CorkiJungleClearE->Enabled())
	{
		auto targets = NeutralMinions(Player()->GetRealAutoAttackRange(Player())).ToVector();
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
			Q->CastOnTarget(target,kHitChanceMedium);
		}
	}
	if (CorkiLaneClearE->Enabled())
	{
		if (CountMinionsInRange(Player()->GetPosition(), Player()->GetRealAutoAttackRange(Player())) >= 3)
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
			Q->CastOnTarget(target, kHitChanceMedium);
		}
	}
	if (CorkiAutoR->Enabled() && Player()->GetSpellBook()->GetAmmo(kSlotR) >=  CorkiAutoRAtStack->GetInteger())
	{
		auto target = SelectTarget(PhysicalDamage, R->Range());
		if (IsValidTarget(target))
		{
			R->CastOnTarget(target, kHitChanceMedium);
		}
	}
}