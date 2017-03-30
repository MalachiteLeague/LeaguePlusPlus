#pragma once
#include "VayneConfig.h"
inline Vec3 VayneCondemnPos() {return Extend(Player()->GetPosition(), GGame->CursorPosition(), 300);}
inline void VayneModeAfterAttack(IUnit* Source, IUnit* Target)
{
	if (Target == nullptr || Target->IsDead())
		return;
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		if (VayneComboQ->Enabled())
		{
			if (Distance(VayneCondemnPos(), Target->GetPosition()) <= Player()->GetRealAutoAttackRange(Target))
			{
				Q->CastOnPosition(GGame->CursorPosition());
			}
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed && Player()->ManaPercent() >= VayneHarassMana->GetInteger())
	{
		if (Target->UnitFlags() == FL_HERO && VayneHarassQ->Enabled())
		{
			if (Distance(VayneCondemnPos(), Target->GetPosition()) <= Player()->GetRealAutoAttackRange(Target))
			{
				Q->CastOnPosition(GGame->CursorPosition());
			}
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear && Player()->ManaPercent() >= VayneFarmMana->GetInteger())
	{
		if ((Target->GetTeam() == kTeamNeutral && VayneJungleClearQ->Enabled()) || (Target->GetTeam() != kTeamNeutral && Player()->IsEnemy(Target) && VayneLaneClearQ->Enabled()))
		{
			if (Distance(VayneCondemnPos(), Target->GetPosition()) <= Player()->GetRealAutoAttackRange(Target))
			{
				Q->CastOnPosition(GGame->CursorPosition());
			}
		}
	}
}
inline void VayneModeOnUpdate()
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
		if (!IsADCanCastSpell())
			return;
		if (VayneComboE->Enabled())
		{
			for (IUnit* hero : Enemies().Where([&](IUnit* i) {return IsValidTarget(i) && IsInAutoAttackRange(i); }).ToVector())
			{
				AdvPredictionOutput pred;
				E->RunPrediction(hero, false, kCollidesWithYasuoWall, &pred);
				if (pred.HitChance != kHitChanceCollision)
				{
					auto pos1 = hero->GetPosition();
					auto pos2 = pred.TargetPosition;
					auto pos11 = Extend(pos1, Player()->GetPosition(), -450);
					auto pos21 = Extend(pos2, Player()->GetPosition(), -450);
					if (IsWallBetween(pos1, pos11) && IsWallBetween(pos2, pos21))
					{
						E->CastOnUnit(hero);
					}
				}
			}
		}
		if (VayneComboR->Enabled())
		{
			if (CountEnemiesInRange(Player()->GetPosition(), 700) > 0)
			{
				R->CastOnPlayer();
			}
		}
	}
}
inline void VayneModeOnGapClose (GapCloserSpell const& Args)
{
	if (!VayneAutoEGapClose->Enabled())
		return;
	if (Args.Sender == nullptr || !IsInAutoAttackRange(Args.Sender))
		return;
	E->CastOnUnit(Args.Sender);
}
inline void VayneModeOnInterrupt (InterruptibleSpell const& Args)
{
	if (!VayneAutoEInterrupt->Enabled())
		return;
	if (Args.Target == nullptr || !IsInAutoAttackRange(Args.Target))
		return;
	E->CastOnUnit(Args.Target);
}