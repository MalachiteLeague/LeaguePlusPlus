#pragma once
#include "XerathConfig.h"

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
		if (XerathComboE->Enabled())
		{
			auto target = SelectTarget(SpellDamage, E->Range());
			if (IsValidTarget(target))
				E->CastOnTarget(target, kHitChanceHigh);
		}
		if (XerathComboW->Enabled())
		{
			auto target = SelectTarget(SpellDamage, W->Range());
			if (IsValidTarget(target))
				W->CastOnTarget(target, kHitChanceHigh);
		}
		if (Q->IsReady() && XerathComboQ->Enabled())
		{
			if (Q->IsCharging())
			{
				auto target = SelectTarget(SpellDamage, Q->Range());
				if (IsValidTarget(target))
					Q->CastOnTarget(target, kHitChanceHigh);
			}
			if (!Q->IsCharging())
			{
				auto target = SelectTarget(SpellDamage, Q->Range());
				if (IsValidTarget(target))
					Q->StartCharging();
			}
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
	{
		if (Player()->ManaPercent() <= XerathHarassMana->GetInteger())
			return;
		if (XerathHarassW->Enabled())
		{
			auto target = SelectTarget(SpellDamage, W->Range());
			if (IsValidTarget(target))
				W->CastOnTarget(target, kHitChanceHigh);
		}
		if (Q->IsReady() && XerathHarassQ->Enabled())
		{
			if (Q->IsCharging())
			{
				auto target = SelectTarget(SpellDamage, Q->Range());
				if (IsValidTarget(target))
					Q->CastOnTarget(target, kHitChanceHigh);
			}
			if (!Q->IsCharging())
			{
				auto target = SelectTarget(SpellDamage, Q->Range());
				if (IsValidTarget(target))
					Q->StartCharging();
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
				R->CastOnTarget(target, kHitChanceHigh);
			}
		}
	}
}