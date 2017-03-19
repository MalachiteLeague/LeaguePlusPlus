#pragma once
#include "TwitchConfig.h"
inline int TwitchGetESTack(IUnit * target)
{
	if (!target->HasBuff("TwitchDeadlyVenom"))
		return 0;
	return target->GetBuffCount("TwitchDeadlyVenom");
}
inline double TwitchGetEDamage(IUnit * target)
{
	if (!E->IsReady())
		return 0;
	int stack = TwitchGetESTack(target);
	if (stack == 0)
		return 0;
	float raw = vector<double>{ 20,35,50,65,80 }[Player()->GetSpellLevel(kSlotE) - 1]
		+ (vector<double>{15, 20, 25, 30, 35}[Player()->GetSpellLevel(kSlotE) - 1] + 0.25 * Player()->PhysicalDamageMod() + 0.2 *  Player()->TotalMagicDamage())* stack;
	return GDamage->CalcPhysicalDamage(Player(), target, raw);
}

inline  void TwitchModeOnUpdate()
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

		if (!GOrbwalking->CanMove())
			return;
		if (TwitchComboQ->Enabled())
		{
			if (CountEnemiesInRange(Player()->GetPosition(), 1000) > 0)
			{
				Q->CastOnPlayer();
			}
		}
		if (TwitchComboW->Enabled())
		{
			auto target = SelectTarget(PhysicalDamage, W->Range());
			if (IsValidTarget(target))
				W->CastOnTarget(target, kHitChanceHigh);
		}
		if (TwitchComboE->Enabled())
		{
			auto target = SelectTarget(PhysicalDamage, E->Range());
			if (IsValidTarget(target) && TwitchGetESTack(target) == 6)
			{
				E->CastOnPlayer();
			}
		}
		if (TwitchComboR->Enabled())
		{
			if (CountEnemiesInRange(Player()->GetPosition(), Player()->GetRealAutoAttackRange(Player()) + 300))
			{
				R->CastOnPlayer();
			}
		}

	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
	{
		if (Player()->ManaPercent() <= TwitchHarassMana->GetInteger())
			return;
		if (!GOrbwalking->CanMove())
			return;
		if (TwitchHarassW->Enabled())
		{
			auto target = SelectTarget(PhysicalDamage, W->Range());
			if (IsValidTarget(target))
				W->CastOnTarget(target, kHitChanceHigh);
		}
		if (TwitchHarassE->Enabled())
		{
			auto target = SelectTarget(PhysicalDamage, E->Range());
			if (IsValidTarget(target) && TwitchGetESTack(target) == 6)
			{
				E->CastOnPlayer();
			}
		}
	}
	//auto
	{
		if (!GOrbwalking->CanMove())
			return;
		for (auto hero : ValidEnemies(E->Range()).ToVector())
		{
			if (E->IsReady() && TwitchGetEDamage(hero) >= hero->GetHealth())
			{
				E->CastOnPlayer();
			}
		}
	}
}