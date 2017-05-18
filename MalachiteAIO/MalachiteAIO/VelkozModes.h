#pragma once
#include "VelkozVariables.h"

inline void VelkozModeOnUpdate()
{
	float EndTime;
	if (VelkozQMissile != nullptr)
	{
		Q2->SetRangeCheckFrom(Extend(VelkozQMissile->GetPosition(), Player()->GetPosition(), -Q->Speed()* GGame->Latency() / 1000));
		Q3->SetRangeCheckFrom(Extend(VelkozQMissile->GetPosition(), Player()->GetPosition(), -Q->Speed()* GGame->Latency() / 1000));
	}
	if (Player()->IsCastingImportantSpell(&EndTime))
		return;
	// COMBO COMBO COMBO COMBO COMBO COMBO  COMBO COMBO COMBO COMBO COMBO COMBO COMBO COMBO COMBOCOMBO COMBO COMBO COMBO COMBO COMBO COMBO COMBO COMBO 
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		if (VelkozComboQ->Enabled() && VelkozQMissile == nullptr)
		{
			auto target = SelectTarget(SpellDamage, Q->Range());
			if (target != nullptr)
			{
				MalachiteCast(Q, target);
			}
			target = SelectTarget(SpellDamage, Q->Range()*1.4);
			if (target != nullptr && VelkozComboQ2->Enabled())
			{
				Vec3 giua = (target->GetPosition() + Player()->GetPosition()) / 2;
				for (int i = 90; i >= -90; i = i - 5)
				{
					Vec3 explode = RotateAround(target->GetPosition(), giua, i);
					if (Distance(explode, Player()->GetPosition()) <= Q->Range() && Distance(explode, target->GetPosition()) <= Q2->Range()
						&& Distance(explode, Player()->GetPosition()) >= 300
						&& MalachitePredGetCollisions(Player()->GetPosition(), explode, Q->GetCollisionFlags(), target, Q).size() == 0
						&& MalachitePredGetCollisions(explode, target->GetPosition(), Q3->GetCollisionFlags(), target, Q3).size() == 0)
					{
						Q->CastOnPosition(explode);
						break;
					}
				}
			}
		}
		if (VelkozComboQ2->Enabled() && VelkozQMissile != nullptr)
		{
			for (IUnit* hero : ValidEnemies(Q2->Range(), VelkozQMissile->GetPosition()).ToVector())
			{
				auto pred = MalachitePredGetPrediction(Q2, hero);
				auto pred1 = MalachitePredGetPrediction(Q3, hero);
				if (pred1.HitChance >= kHitChanceHigh  && abs(AngleBetween(pred.CastPosition, Q2->GetRangeCheckFrom(), GMissileData->GetStartPosition(VelkozQMissile)) - 90) <= 3)
				{
					Q2->CastOnPlayer();
				}
			}
		}
		if (VelkozComboW->Enabled())
		{
			auto target = SelectTarget(SpellDamage, W->Range());
			if (target != nullptr)
				MalachiteCast(W, target);
		}
		if (VelkozComboE->Enabled())
		{
			auto target = SelectTarget(SpellDamage, E->Range());
			if (target != nullptr)
				MalachiteCast(E, target);
		}
		if (VelkozComboR->Enabled() && R->IsReady())
		{
			for (IUnit* hero : ValidEnemies(R->Range() - 200).ToVector())
			{
				if (VelkozGetRDamage(hero)*0.7 >= hero->GetHealth())
				{
					R->CastOnPosition(hero->GetPosition());
				}
			}
		}
	}
	// HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS 
	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed && Player()->ManaPercent() >= VelkozHarassMana->GetInteger())
	{
		if (VelkozHarassQ->Enabled() && VelkozQMissile == nullptr)
		{
			auto target = SelectTarget(SpellDamage, Q->Range());
			if (target != nullptr)
			{
				MalachiteCast(Q, target);
			}
			target = SelectTarget(SpellDamage, Q->Range()*1.4);
			if (target != nullptr && VelkozHarassQ2->Enabled())
			{
				Vec3 giua = (target->GetPosition() + Player()->GetPosition()) / 2;
				for (int i = 90; i >= -90; i = i - 5)
				{
					Vec3 explode = RotateAround(target->GetPosition(), giua, i);
					if (Distance(explode, Player()->GetPosition()) <= Q->Range() && Distance(explode, target->GetPosition()) <= Q2->Range() 
						&& Distance(explode, Player()->GetPosition()) >= 300
						&& MalachitePredGetCollisions(Player()->GetPosition(), explode, Q->GetCollisionFlags(), target, Q).size() == 0
						&& MalachitePredGetCollisions(explode, target->GetPosition(), Q2->GetCollisionFlags(), target, Q2).size() == 0)
					{
						Q->CastOnPosition(explode);
						break;
					}
				}
			}
		}
		if (VelkozHarassQ2->Enabled() && VelkozQMissile != nullptr)
		{
			for (IUnit* hero : ValidEnemies(Q2->Range(), VelkozQMissile->GetPosition()).ToVector())
			{
				auto pred = MalachitePredGetPrediction(Q2, hero);
				auto pred1 = MalachitePredGetPrediction(Q3, hero);
				if (pred1.HitChance >= kHitChanceHigh  && abs(AngleBetween(pred.CastPosition, Q2->GetRangeCheckFrom(), GMissileData->GetStartPosition(VelkozQMissile)) - 90) <= 3)
				{
					Q2->CastOnPlayer();
				}
			}
		}
		if (VelkozHarassW->Enabled())
		{
			auto target = SelectTarget(SpellDamage, W->Range());
			if (target != nullptr)
				MalachiteCast(W, target);
		}
		if (VelkozHarassE->Enabled())
		{
			auto target = SelectTarget(SpellDamage, E->Range());
			if (target != nullptr)
				MalachiteCast(E, target);
		}
	}
	// FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear && Player()->ManaPercent() >= VelkozFarmMana->GetInteger())
	{
		if (VelkozLaneClearQ->Enabled() && VelkozQMissile == nullptr)
		{
			for (IUnit* minion : EnemyMinions(Q->Range()).ToVector())
			{
				MalachiteCast(Q, minion);
			}	
		}
		if (VelkozLaneClearW->Enabled())
		{
			auto Location = FindBestLineCastPosition({ Player()->GetPosition() }, W->Range(), W->Range(), W->Radius(), true, true);
			if (Location.HitCount >= 2)
			{
				W->CastOnPosition(Location.CastPosition);
			}
		}
		if (VelkozJungClearQ->Enabled() && VelkozQMissile == nullptr)
		{
			for (IUnit* minion : NeutralMinions(Q->Range()).ToVector())
			{
				MalachiteCast(Q, minion);
			}
		}
		if (VelkozJungClearW->Enabled())
		{
			for (IUnit* minion : NeutralMinions(W->Range()).ToVector())
			{
				MalachiteCast(W, minion);
			}
		}
	}
	//auto auto auto auto auto auto  auto auto auto  auto auto auto auto auto auto  auto auto auto  auto auto auto  auto auto auto  
	{
		if (VelkozAutoQ2->Enabled() && VelkozQMissile != nullptr)
		{
			for (IUnit* hero : ValidEnemies(Q2->Range(), VelkozQMissile->GetPosition()).ToVector())
			{
				auto pred = MalachitePredGetPrediction(Q2, hero);
				auto pred1 = MalachitePredGetPrediction(Q3, hero);
				if (pred1.HitChance >= kHitChanceHigh  && abs(AngleBetween(pred.CastPosition, Q2->GetRangeCheckFrom(), GMissileData->GetStartPosition(VelkozQMissile)) - 90) <= 3)
				{
					Q2->CastOnPlayer();
				}
			}
		}
	}

}
inline void VelkozModeOnGapClose(GapCloserSpell const& Args)
{
	if (!VelkozAutoEGap->Enabled())
		return;
	if (Args.Source == nullptr)
		return;
	MalachiteCast(E, Args.Source);
}
inline void VelkozModeOnInterrupt(InterruptibleSpell const& Args)
{
	if (!VelkozAutoEInterrupt->Enabled())
		return;
	if (Args.Source == nullptr)
		return;
	MalachiteCast(E, Args.Source);
}