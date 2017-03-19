#pragma once
#include "DravenConfig.h"

inline void DravenModeOnUpdate()
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeNone)
	{
		GOrbwalking->SetOverridePosition(GGame->CursorPosition());
	}
	else
	{
		SArray<IUnit *> Axes =  DravenAxesObject.OrderBy<float>([&](IUnit* i) { return Distance(GMissileData->GetEndPosition(i), GGame->CursorPosition()); });
		Axes = Axes.Where([&](IUnit* i) {return Distance(GMissileData->GetEndPosition(i), GGame->CursorPosition()) <= DravenAxePickRange->GetInteger(); });
		if (Axes.Any())
		{
			GOrbwalking->SetOverridePosition(GMissileData->GetEndPosition(Axes.ToVector().front()));
		}
		else
		{
			GOrbwalking->SetOverridePosition(GGame->CursorPosition());
		}
	}
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
		if (!GOrbwalking->CanMove())
			return;
		if (DravenComboQ->Enabled() && DravenAxesOnHand() + DravenAxesObject.Count() < 2)
		{
			if (CountEnemiesInRange(Player()->GetPosition(), 900) > 0)
			{
				Q->CastOnPlayer();
			}
		}
		if (DravenComboW->Enabled())
		{
			if (!DravenHasWAttackSpeed() && CountEnemiesInRange(Player()->GetPosition() ,Player()->GetRealAutoAttackRange(Player())) > 0)
			{
				W->CastOnPlayer();
			}
			if (!DravenHasWMoveSpeed() && CountEnemiesInRange(Player()->GetPosition(), Player()->GetRealAutoAttackRange(Player())) == 0
				&& CountEnemiesInRange(Player()->GetPosition(), 900) > 0)
			{
				W->CastOnPlayer();
			}
		}
		if (DravenComboE->Enabled())
		{
			auto target = SelectTarget(PhysicalDamage, E->Range());
			if (IsValidTarget(target))
			{
				E->CastOnTarget(target, kHitChanceHigh);
			}
		}
		if (DravenComboR->Enabled() && DravenIsR1())
		{
			auto target = SelectTarget(PhysicalDamage, 2000);
			if (IsValidTarget(target) && GetSpellDamage(target, kSlotR) >= target->GetHealth())
			{
				R->CastOnTarget(target, kHitChanceHigh);
			}
			Vec3 CastPosition;
			Vec3 CastPositionFrom;
			int HitCounts;
			FindBestLineCastPosition(vector<Vec3>{Player()->GetPosition()}, 1500, R->Radius(), false, true, CastPosition, HitCounts, CastPositionFrom);
			if (HitCounts >= 3)
			{
				R->CastOnPosition(CastPosition);
			}
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear || GOrbwalking->GetOrbwalkingMode() == kModeLastHit)
	{
		if (!GOrbwalking->CanMove())
			return;
		if (Player()->ManaPercent() <= DravenFarmMana->GetInteger())
			return;
		if (DravenFarmQ->Enabled() && DravenAxesOnHand() + DravenAxesObject.Count() < 2)
		{
			auto Minions = EnemyMinions(700).AddRange(NeutralMinions(700));
			if (Minions.Count() > 0)
			{
				Q->CastOnPlayer();
			}
		}
	}
}
inline void DravenModeOnGapClose(GapCloserSpell const& Args)
{
	if (!DravenAutoEGap->Enabled())
		return;
	if (Args.Sender == nullptr || !InSpellRange(E, Args.Sender))
		return;
	E->CastOnTarget(Args.Sender, kHitChanceHigh);
}
inline void DravenModeOnInterrupt(InterruptibleSpell const& Args)
{
	if (!DravenAutoEInterrupt->Enabled())
		return;
	if (Args.Target == nullptr || !InSpellRange(E, Args.Target))
		return;
	E->CastOnTarget(Args.Target, kHitChanceHigh);
}
inline void DravenModeOnRender ()
{
	if (DravenDrawAxe->Enabled())
	{
		GRender->DrawOutlinedCircle(GGame->CursorPosition(), Yellow(), DravenAxePickRange->GetInteger());
		for (auto axe : DravenAxesObject.ToVector())
		{
			GRender->DrawOutlinedCircle(GMissileData->GetEndPosition(axe), Distance(GMissileData->GetEndPosition(axe), GGame->CursorPosition()) < DravenAxePickRange->GetInteger() ? Green() : Red(), 150);
		}
	}
}