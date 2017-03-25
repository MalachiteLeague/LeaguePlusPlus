#pragma once
#include "LucianVariables.h"

inline void LucianModeAfterAttack(IUnit* Source, IUnit* Target)
{
	if (Target == nullptr || Target->IsDead())
		return;
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		Vec3 Position;
		if (E->IsReady() && LucianComboE->Enabled() && LucianCanUseE(Target, Position))
		{
			E->CastOnPosition(Position);
			GOrbwalking->ResetAA();
		}
		else if (Q->IsReady() && LucianComboQ->Enabled() && InSpellRange(Q, Target))
		{
			Q->CastOnUnit(Target);
			//GOrbwalking->ResetAA();
		}
		else if (W->IsReady() && LucianComboW->Enabled() && InSpellRange(W, Target))
		{
			W->CastOnTarget(Target, kHitChanceHigh);
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed && Player()->ManaPercent() >= LucianHarassMana->GetInteger())
	{
		if (Q->IsReady() && LucianHarassQ->Enabled() && InSpellRange(Q, Target))
		{
			auto target = SelectTarget(PhysicalDamage, Q->Range());
			if (IsValidTarget(target))
			{
				Q->CastOnUnit(Target);
			}
		}
		else if (W->IsReady() && LucianHarassW->Enabled() && InSpellRange(W, Target))
		{
			auto target = SelectTarget(PhysicalDamage, Q->Range());
			if (IsValidTarget(target))
			{
				W->CastOnTarget(Target, kHitChanceHigh);
			}
		}
	}
}
inline void LucianModeOnUpdate()
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
		if (E->IsReady() && LucianComboEGap->Enabled() 
			&& CountEnemiesInRange(Player()->GetPosition(),Player()->GetRealAutoAttackRange(Player())) == 0)
		{
			SArray<IUnit*> Ignored = ValidEnemies().Where([&](IUnit* i) {return Distance(i, GGame->CursorPosition()) > 500; });
			auto target = GTargetSelector->FindTargetEx(QuickestKill, PhysicalDamage, Q->Range() + E->Range(), nullptr, true, &Ignored.ToVector());
			if (IsValidTarget(target))
			{
				LucianCastEToGap(target);
			}
		}
	}
}