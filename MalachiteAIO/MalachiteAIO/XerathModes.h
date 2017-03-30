#pragma once
#include "XerathConfig.h"
float XerathLastChargeTick;
inline void XerathModeOnUpdate()
{
	if (Player()->GetSpellLevel(kSlotR) == 1)
		R->SetOverrideRange(3300);
	else if (Player()->GetSpellLevel(kSlotR) == 2)
		R->SetOverrideRange(4550);
	else if (Player()->GetSpellLevel(kSlotR) == 3)
		R->SetOverrideRange(5800);

	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		if (Q->IsReady() && XerathComboQ->Enabled())
		{
			if (XerathIsQCharging())
			{
				auto target = SelectTarget(SpellDamage, 1550);
				if (IsValidTarget(target))
				{
					//Vec3 pred;
					//GPrediction->GetFutureUnitPosition(target, 0.2f, true, pred);
					//if (InSpellRange(Q, pred))
					//	Q->CastOnPosition(pred);
					//Q->CastOnTarget(target, kHitChanceHigh);
					MalachiteCast(Q, target, kHitChanceVeryHigh);
				}
			}
			if (!XerathIsQCharging())
			{
				auto target = SelectTarget(SpellDamage, 1550);
				if (IsValidTarget(target))
					Q->StartCharging();
			}
		}
		if (XerathComboE->Enabled())
		{
			auto target = SelectTarget(SpellDamage, E->Range());
			if (IsValidTarget(target))
				//E->CastOnTarget(target, kHitChanceHigh);
				MalachiteCast(E, target, kHitChanceVeryHigh);
		}
		if (XerathComboW->Enabled())
		{
			auto target = SelectTarget(SpellDamage, W->Range());
			if (IsValidTarget(target))
				//W->CastOnTarget(target, kHitChanceHigh);
				MalachiteCast(W, target, kHitChanceVeryHigh);
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
	{
		if (Q->IsReady() && XerathHarassQ->Enabled())
		{
			if (XerathIsQCharging())
			{
				auto target = SelectTarget(SpellDamage, 1550);
				if (IsValidTarget(target))
				{
					//Vec3 pred;
					//GPrediction->GetFutureUnitPosition(target, 0.2f, true, pred);
					//if (InSpellRange(Q, pred))
					//	Q->CastOnPosition(pred);
					//Q->CastOnTarget(target, kHitChanceHigh);
					MalachiteCast(Q, target, kHitChanceVeryHigh);
				}
			}
			if (!XerathIsQCharging())
			{
				auto target = SelectTarget(SpellDamage, 1550);
				if (IsValidTarget(target))
					Q->StartCharging();
			}
		}
		if (Player()->ManaPercent() <= XerathHarassMana->GetInteger())
			return;
		if (XerathHarassW->Enabled())
		{
			auto target = SelectTarget(SpellDamage, W->Range());
			if (IsValidTarget(target))
			{
				//Vec3 pred;
				//GPrediction->GetFutureUnitPosition(target, 0.3f, true, pred);
				//W->CastOnPosition(pred);
				//W->CastOnTarget(target, kHitChanceHigh);
				MalachiteCast(W, target, kHitChanceVeryHigh);
			}

		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear && Player()->ManaPercent() >= XerathFarmMana->GetInteger())
	{
		if (!GOrbwalking->CanMove())
			return;
		if (XerathLaneClearW->Enabled())
		{
			Vec3 CastPosition;
			int HitCount;
			GPrediction->FindBestCastPosition(W->Range(), W->Radius(), false, true, true, CastPosition, HitCount);
			if (HitCount >= 3)
			{
				W->CastOnPosition(CastPosition);
			}
		}
	}
	// auto
	{
		if (XerathAutoR->Enabled() && XerathIsRCharging() && abs(GGame->TickCount() - XerathLastCastedRTick) >= XerathAutoRTime->GetInteger())
		{
			auto target = GTargetSelector->FindTargetEx(QuickestKill, SpellDamage, R->Range(), nullptr, true, 
				&ValidEnemies().Where([&](IUnit* i) {return Distance(i, GGame->CursorPosition()) > XerathAutoRDistance->GetInteger(); }).ToVector());
			if (IsValidTarget(target))
			{
				//Vec3 pred;
				//GPrediction->GetFutureUnitPosition(target, 0.3f, true, pred);
				//R->CastOnPosition(pred);
				//R->CastOnTarget(target, kHitChanceHigh);
				MalachiteCast(R, target, kHitChanceVeryHigh);
			}
		}
	}
}