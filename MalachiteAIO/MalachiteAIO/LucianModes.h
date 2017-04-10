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
			auto target = SelectTarget(PhysicalDamage, Q->Range());
			if (IsValidTarget(target))
			{
				Q->CastOnUnit(target);
			}
			//GOrbwalking->ResetAA();
		}
		else if (Q->IsReady() && LucianComboQ->Enabled() && LucianCastQExtend())
		{
			
		}
		else if (W->IsReady() && LucianComboW->Enabled() && InSpellRange(W, Target))
		{
			MalachiteCast(W, Target, kHitChanceHigh);
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed && Player()->ManaPercent() >= LucianHarassMana->GetInteger())
	{
		if (Q->IsReady() && LucianHarassQ->Enabled() && InSpellRange(Q, Target))
		{
			auto target = SelectTarget(PhysicalDamage, Q->Range());
			if (IsValidTarget(target))
			{
				Q->CastOnUnit(target);
			}
		}
		else if (W->IsReady() && LucianHarassW->Enabled() && InSpellRange(W, Target))
		{
			auto target = SelectTarget(PhysicalDamage, Q->Range());
			if (IsValidTarget(target))
			{
				MalachiteCast(W, target, kHitChanceHigh);
			}
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear && Player()->ManaPercent() >= LucianFarmMana->GetInteger())
	{
		//GGame->PrintChat(std::to_string(Target->GetTeam()).c_str());
		if (Target->GetTeam() != kNeutral)
		{
			if (LucianLaneClearW->Enabled() && CountMinionsInRange(Player()->GetPosition(), 700) >= 2)
			{
				MalachiteCast(W, Target, kHitChanceHigh);
			}
		}
		if (Target->IsJungleCreep())
		{
			//GGame->PrintChat("a");
			if (Q->IsReady() && LucianJungClearQ->Enabled() && InSpellRange(Q, Target))
			{
				Q->CastOnUnit(Target);
			}
			else if (W->IsReady() && LucianJungClearW->Enabled() && InSpellRange(W, Target))
			{
				MalachiteCast(W, Target, kHitChanceHigh);
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
		if (!IsADCanCastSpell())
			return;
		if (E->IsReady() && LucianComboEGap->Enabled() 
			&& CountEnemiesInRange(Player()->GetPosition(),Player()->AttackRange() + Player()->BoundingRadius() * 3) == 0)
		{
			SArray<IUnit*> Ignored = ValidEnemies().Where([&](IUnit* i) {return Distance(i, GGame->CursorPosition()) > 500; });
			auto target = GTargetSelector->FindTargetEx(QuickestKill, PhysicalDamage, Q->Range() + E->Range(), nullptr, true, &Ignored.ToVector());
			if (IsValidTarget(target))
			{
				LucianCastEToGap(target);
			}
		}
		if (LucianComboQExtend->Enabled() && Player()->ManaPercent() > LucianComboQExtendMana->GetInteger() 
			&& CountEnemiesInRange(Player()->GetPosition(), Player()->AttackRange() + Player()->BoundingRadius() * 3) == 0)
		{
			LucianCastQExtend();
		}
	}

	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed && Player()->ManaPercent() >= LucianHarassMana->GetInteger())
	{
		if (!IsADCanCastSpell())
			return;
		if (LucianHarassQ ->Enabled())
		{
			LucianCastQExtend();
		}
	}

	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear && Player()->ManaPercent() >= LucianFarmMana->GetInteger())
	{
		if (!IsADCanCastSpell())
			return;
		if (Player()->HasBuff("LucianPassiveBuff"))
			return;
		//GGame->PrintChat("a");
		//lane
		if (LucianLaneClearQ->Enabled())
		{
			//GGame->PrintChat("a");
			auto pred = FindBestLineCastPosition(vector<Vec3>{ Player()->GetPosition() }, 900, Q->Range(), 70, true, true);
			//GGame->PrintChat(std::to_string(pred.HitCount).c_str());
			if (pred.HitCount >= LucianLaneClearQMinionHitCount->GetInteger() && pred.CastOnUnit != nullptr)
			{
				Q->CastOnUnit(pred.CastOnUnit);
			}
		}
	}
	//auto
	{
		if (LucianAutoQKS->Enabled())
		{
			LucianCastQExtend(true);
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
			return;
		if (!IsADCanCastSpell())
			return;
		if(LucianAutoQ->Enabled() && Player()->ManaPercent() >= LucianAutoMana->GetInteger() && !GUtility->IsPositionUnderTurret(Player()->GetPosition()))
		{
			LucianCastQExtend();
		}
	}
}