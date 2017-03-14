#pragma once
#include "JinxConfig.h"

inline void JinxModeOnUpdate()
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
		
		if (JinxComboQ->Enabled() && !Player()->HasBuff("JinxQ") && Q->IsReady())
		{
			auto target = SelectTarget(PhysicalDamage, Player()->GetRealAutoAttackRange(Player()) + vector<int>{75,100,125,150,175} [Player()->GetSpellLevel(kSlotQ) - 1]);
			if (IsValidTarget(target) && !IsInAutoAttackRange(target))
			{
				Q->CastOnPlayer();
			}
		}
		if (JinxComboQ->Enabled() && Player()->HasBuff("JinxQ") && Q->IsReady())
		{
			auto target = SelectTarget(PhysicalDamage, Player()->GetRealAutoAttackRange(Player()) + vector<int>{75, 100, 125, 150, 175}[Player()->GetSpellLevel(kSlotQ) - 1]);
			if (IsValidTarget(target) && Distance(Player(), target) <= 525 + Player()->BoundingRadius() + target->BoundingRadius())
			{
				Q->CastOnPlayer();
			}
		}
		if (JinxComboW->Enabled())
		{
			auto target = SelectTarget(PhysicalDamage, W->Range());
			if (IsValidTarget(target) && !IsInAutoAttackRange(target))
			{
				W->CastOnTarget(target, kHitChanceMedium);
			}
		}
		if (JinxComboE->Enabled())
		{
			auto target = SelectTarget(PhysicalDamage, E->Range());
			if (IsValidTarget(target))
			{
				E->CastOnTarget(target, kHitChanceMedium);
			}
		}
		if (JinxComboR->Enabled())
		{
			auto target = SelectTarget(PhysicalDamage, 2000);
			if(IsValidTarget(target) && Distance(Player(), target) >= 900 && target->GetHealth() <= GetSpellDamage(target,kSlotR))
			{
				R->CastOnUnit(target);
			}
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
	{
		if (!GOrbwalking->CanMove())
			return;
		if (JinxHarassQ->Enabled() && !Player()->HasBuff("JinxQ") && Q->IsReady())
		{
			auto target = SelectTarget(PhysicalDamage, Player()->GetRealAutoAttackRange(Player()) + vector<int>{75, 100, 125, 150, 175}[Player()->GetSpellLevel(kSlotQ) - 1]);
			if (IsValidTarget(target) && !IsInAutoAttackRange(target))
			{
				Q->CastOnPlayer();
			}
		}
		if (JinxHarassQ->Enabled() && Player()->HasBuff("JinxQ") && Q->IsReady())
		{
			auto target = SelectTarget(PhysicalDamage, Player()->GetRealAutoAttackRange(Player()) + vector<int>{75, 100, 125, 150, 175}[Player()->GetSpellLevel(kSlotQ) - 1]);
			if (IsValidTarget(target) && Distance(Player(), target) <= 525 + Player()->BoundingRadius() + target->BoundingRadius())
			{
				Q->CastOnPlayer();
			}
		}
		if (Player()->ManaPercent() <= JinxHarassMana->GetInteger())
			return;
		if (JinxHarassW->Enabled())
		{
			auto target = SelectTarget(PhysicalDamage, W->Range());
			if (IsValidTarget(target) && !IsInAutoAttackRange(target))
			{
				W->CastOnTarget(target, kHitChanceMedium);
			}
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
	{
		if (!GOrbwalking->CanMove())
			return;
		if (Player()->HasBuff("JinxQ") && Q->IsReady())
		{
			Q->CastOnPlayer();
		}
	}
	//auto
	{
		if (JinxAutoE->Enabled())
		{
			for (auto hero : ValidEnemies(E->Range()).ToVector())
			{
				if (hero->HasBuffOfType(BUFF_Stun) || hero->HasBuffOfType(BUFF_Snare) || hero->HasBuffOfType(BUFF_Suppression) || hero->HasBuffOfType(BUFF_Charm) || hero->HasBuffOfType(BUFF_Snare))
				{
					E->CastOnTarget(hero);
				}
			}
		}
	}

}