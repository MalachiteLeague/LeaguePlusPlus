#pragma once
#include "JhinConfig.h"

inline void JhinModeOnUpdate()
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{

		if (Equals(Player()->GetSpellName(kSlotR),"JhinRShot"))
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
		if (JhinComboQ->Enabled())
		{
			auto target = SelectTarget(PhysicalDamage, Q->Range());
			if (IsValidTarget(target))
			{
				Q->CastOnUnit(target);
			}
		}
		if (JhinComboW->Enabled())
		{
			for (IUnit* hero : ValidEnemies(W->Range()).Where([&](IUnit* i) {return JhinTargetHasPassive(i); }).ToVector())
			{
				W->CastOnTarget(hero, kHitChanceMedium);
			}
		}
		if (JhinComboE->Enabled())
		{
			auto target = SelectTarget(PhysicalDamage, E->Range());
			if (IsValidTarget(target))
			{
				E->CastOnPosition(target->GetPosition());
			}
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
	{
		if (Equals(Player()->GetSpellName(kSlotR), "JhinRShot"))
			return;
		if (Player()->ManaPercent() <= JhinHarassMana->GetInteger())
			return;
		if (!GOrbwalking->CanMove())
			return;
		if (JhinHarassQ->Enabled())
		{
			auto target = SelectTarget(PhysicalDamage, Q->Range());
			if (IsValidTarget(target))
			{
				Q->CastOnUnit(target);
			}
		}
		if (JhinHarassW->Enabled())
		{
			for (IUnit* hero : ValidEnemies(W->Range()).Where([&](IUnit* i) {return JhinTargetHasPassive(i); }).ToVector())
			{
				W->CastOnTarget(hero, kHitChanceMedium);
			}
		}

	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
	{
		if (Equals(Player()->GetSpellName(kSlotR), "JhinRShot"))
			return;
		if (Player()->ManaPercent() <= JhinFarmMana->GetInteger())
			return;
		if (!GOrbwalking->CanMove())
			return;
		if (JhinLaneClearQ->Enabled())
		{
			for (auto minion : EnemyMinions(Q->Range()).Where([&](IUnit* i) {return CountMinionsInRange(i->GetPosition(), 500) >= 3; }).ToVector())
			{
				Q->CastOnUnit(minion);
			}
		}
		if (JhinJungleClearQ->Enabled())
		{
			for (auto minion : EnemyMinions(Q->Range()).ToVector())
			{
				Q->CastOnUnit(minion);
			}
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeLastHit)
	{
		if (Equals(Player()->GetSpellName(kSlotR), "JhinRShot"))
			return;
		if (Player()->ManaPercent() <= JhinFarmMana->GetInteger())
			return;
		if (!GOrbwalking->CanMove())
			return;
		if (JhinLaneClearQ->Enabled())
		{
			for (auto minion : EnemyMinions(Q->Range()).Where([&](IUnit* i) {return GetSpellDamage(i, kSlotQ) >= i->GetHealth(); }).ToVector())
			{
				Q->CastOnUnit(minion);
			}
		}
	}
	{
		if (JhinAutoR->Enabled() && Equals(Player()->GetSpellName(kSlotR), "JhinRShot"))
		{
			SArray<IUnit*> ignoredTarget;
			ignoredTarget.AddRange(ValidEnemies(R->Range()).Where([&](IUnit* i) {return !InTheCone(i->GetPosition(), Player()->GetPosition(), Player()->GetPosition() + Normalize(Player()->Direction())* R->Range(), 60); }));
			auto target = GTargetSelector->FindTargetEx(QuickestKill, PhysicalDamage, R->Range(), nullptr, true, &ignoredTarget.ToVector());
			if (IsValidTarget(target))
			{
				R->CastOnTarget(target, kHitChanceMedium);
			}
		}
		if (Equals(Player()->GetSpellName(kSlotR), "JhinRShot"))
			return;
		if (!GOrbwalking->CanMove())
			return;
		if (JhinAutoW->Enabled())
		{
			for (auto target : ValidEnemies(W->Range()).Where([&](IUnit* i) {return IsCCed(i); }).ToVector())
			{
				W->CastOnTarget(target, kHitChanceMedium);
			}
		}
	}
}