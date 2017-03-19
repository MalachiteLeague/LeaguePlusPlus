#pragma once
#include "LucianConfig.h"

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
		if (Q->IsReady() && LucianComboQ->Enabled() && InSpellRange(Q, Target))
		{
			Q->CastOnUnit(Target);
		}
		else if (W->IsReady() && LucianComboW->Enabled() && InSpellRange(W, Target))
		{
			W->CastOnTarget(Target, kHitChanceHigh);
		}
	}
}