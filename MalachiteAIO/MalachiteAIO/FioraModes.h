#pragma once
#include "FioraConfig.h"
inline bool FioraEIsReady()
{
	return E->IsReady() && !Player()->HasBuff("FioraE") && !Player()->HasBuff("fiorae2");
}
inline void FioraModeOnUpdate()
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && FioraComboOrbwalk->Enabled())
	{
		auto target = FioraGetTarget(700);
		if (IsValidTarget(target))
		{
			auto status = FioraGetPassiveStatus(target, 0);
			if (status.HasPassive)
			{
				SArray<Vec3> points = status.PassivePredictedPositions.OrderBy<float>([&](Vec3 i) {return Distance(i, Player()->GetPosition()); });
				if (points.Any())
				{
					auto point = points.FirstOrDefault();
					GOrbwalking->SetOverridePosition(point);
				}
				else GOrbwalking->SetOverridePosition(GGame->CursorPosition());
			}
			else GOrbwalking->SetOverridePosition(GGame->CursorPosition());
		}
		else GOrbwalking->SetOverridePosition(GGame->CursorPosition());
	}
	else
	{
		GOrbwalking->SetOverridePosition(GGame->CursorPosition());
	}
	//
	{   IUnit* Ultedtarget = FioraGetUltedTarget();
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && Ultedtarget != nullptr && Distance(Ultedtarget, Player()) <= 700)
		{
			GOrbwalking->SetOverrideTarget(Ultedtarget);
			if (IsInAutoAttackRange(Ultedtarget))
			{
				GOrbwalking->SetAttacksAllowed(true);
			}
			else
			{
				GOrbwalking->SetAttacksAllowed(false);
			}
		}
		else
		{
			GOrbwalking->SetAttacksAllowed(true);
			GOrbwalking->SetOverrideTarget(nullptr);
		}
	}
	//

	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		if (!GOrbwalking->CanMove())
			return;
		if (Q->IsReady() && FioraComboQ->Enabled())
		{
			auto hero = FioraGetTarget(700);
			if (IsValidTarget(hero))
			{
				auto status = FioraGetPassiveStatus(hero ,0);
				if (status.HasPassive
					&& !(IsInAutoAttackRange(hero)
						&& status.PassivePredictedPositions.Any([&](Vec3 x)
				{return InTheCone(Player()->GetPosition(), status.TargetPredictedPosition, x, 90); })))
				{
					if (status.PassiveType == FioraUltiPassive
						&& FioraCastQtoUltPassive(hero, FioraGetQPassivedelay(hero)))
					{
						
					}
					else if (status.PassiveType == FioraNormalPassive
						&& FioraCastQtoPassive(hero, FioraGetQPassivedelay(hero)))
					{
						
					}
					else if (status.PassiveType == FioraPrePassive
						&& FioraCastQtoPrePassive(hero, FioraGetQPassivedelay(hero)))
					{
						
					}
					else if (FioraComboQGap->Enabled())
					{
						FioraCastQtoGapClose(hero);
					}
				}
			}
		}
		if (R->IsReady())
		{
			if (FioraComboRAlways->Enabled())
			{
				auto target = SelectTarget(PhysicalDamage, R->Range());
				if (IsValidTarget(target))
				{
					R->CastOnUnit(target);
				}
			}
			if (FioraComboRKillable->Enabled())
			{
				auto target = SelectTarget(PhysicalDamage, R->Range());
				if (IsValidTarget(target) && FioraGetFastDamage(target) >= target->GetHealth() && target->GetHealth() >= FioraGetFastDamage(target) / 3)
				{
					R->CastOnUnit(target);
				}
			}
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
	{
		if (Player()->ManaPercent() <= FioraHarassMana->GetInteger())
			return;
		if (!GOrbwalking->CanMove())
			return;
		if (Q->IsReady() && FioraHarassQ->Enabled())
		{
			auto hero = FioraGetTarget(700);
			if (IsValidTarget(hero))
			{
				auto status = FioraGetPassiveStatus(hero, 0);
				if (status.HasPassive
					&& !(IsInAutoAttackRange(hero)
						&& status.PassivePredictedPositions.Any([&](Vec3 x)
				{return InTheCone(Player()->GetPosition(), status.TargetPredictedPosition, x, 90); })))
				{
					if (status.PassiveType == FioraUltiPassive
						&& FioraCastQtoUltPassive(hero, FioraGetQPassivedelay(hero)))
					{

					}
					else if (status.PassiveType == FioraNormalPassive
						&& FioraCastQtoPassive(hero, FioraGetQPassivedelay(hero)))
					{

					}
				}
			}
		}
	}
}
inline void FioraModeAfterAttack(IUnit* Source, IUnit* Target)
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		if (FioraEIsReady())
		{
			E->CastOnPlayer();
			GOrbwalking->ResetAA();
		}
		else
		{
			CastItemOnUnit(3074, 500, nullptr);
			CastItemOnUnit(3077, 500, nullptr);
			CastItemOnUnit(3748, 500, nullptr);
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed && Target->UnitFlags() == FL_HERO)
	{
		if (FioraEIsReady() && FioraHarassE->Enabled() && Player()->ManaPercent() > FioraHarassMana->GetInteger())
		{
			E->CastOnPlayer();
			GOrbwalking->ResetAA();
		}
		else
		{
			CastItemOnUnit(3074, 500, nullptr);
			CastItemOnUnit(3077, 500, nullptr);
			CastItemOnUnit(3748, 500, nullptr);
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear && Target->UnitFlags() == FL_CREEP)
	{
		if (FioraEIsReady() && Player()->ManaPercent() > FioraHarassMana->GetInteger()
			&& ((FioraLaneClearE->Enabled() && Target->GetTeam() != kTeamNeutral) || (FioraJungleClearE->Enabled() && Target->GetTeam() == kTeamNeutral)))
		{
			E->CastOnPlayer();
			GOrbwalking->ResetAA();
		}
		else
		{
			CastItemOnUnit(3074, 500, nullptr);
			CastItemOnUnit(3077, 500, nullptr);
			CastItemOnUnit(3748, 500, nullptr);
		}
	}
}