#pragma once
#include "YasuoHelper.h"
inline void YasuoModeOnUpdate()
{
	//// COMBO COMBO COMBO COMBO COMBO COMBO COMBO COMBO COMBO COMBO COMBO COMBO COMBO COMBO COMBO COMBO COMBO COMBO COMBO COMBO COMBO 
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		// R
		if (YasuoComboR->Enabled())
		{
			SArray<IUnit*> targets = ValidEnemies(R->Range()).Where([&](IUnit* i) {return YasuoTargetIsOnAir(i); });
			for (IUnit* target : targets.ToVector())
			{
				if (YasuoGEtRcount(target) >= YasuoComboRHits->GetInteger())
				{
					R->CastOnPosition(target->GetPosition());
				}
				if (YasuoComboRWhiteList[string("combo") + std::to_string(target->GetNetworkId())]->Enabled()
					&& YasuoComboRWhiteListHP[string("combohp") + std::to_string(target->GetNetworkId())]->GetInteger() > target->HealthPercent())
				{
					R->CastOnPosition(target->GetPosition());
				}
			}
		}
		if (!IsADCanCastSpell())
			return;
		// Q
		if (YasuoQStage() != 3 && YasuoNotDashing())
		{
			YasuoCastQ();
		}
		else
		{
			auto target = SelectTarget(PhysicalDamage, Q2->Range());
			if (IsValidTarget(target))
			{
				if (!YasuoComboQ3Spin->Enabled() || target->HasBuff("YasuoDashWrapper") || Distance(target, Player()->GetPosition()) > YasuoComboQ3SpinMaxDist->GetInteger())
				{
					YasuoCastQ(target);
				}
			}
			for (IUnit* hero : ValidEnemies().ToVector())
			{
				YasuoCastQCircle(hero);
			}
		}
		// E
		bool underturret = YasuoComboEUnderTurret->Enabled();
		{
			switch (YasuoComboEMode->GetInteger())
			{
			case 0:
				YasuoCastEFly(underturret);
				break;
			case 1:
				YasuoCastETarget(underturret);
				break;
			default:
				YasuoCastEMouse(underturret);
				break;
			}
		}
		// gapE + Qstack
		if (CountEnemiesInRange(Player()->GetPosition(),E->Range()) == 0)
		{
			YasuoCastEMouse(underturret);
		}
		YasuoStackQ();

	}
	//// CUSTOM CUSTOM CUSTOM CUSTOM CUSTOM CUSTOM CUSTOM CUSTOM CUSTOM CUSTOM CUSTOM CUSTOM CUSTOM CUSTOM CUSTOM CUSTOM CUSTOM 
	if (IsKeyDown(YasuoCustomKey))
	{
		GOrbwalking->Orbwalk(GetOrbwalkTarget(), GGame->CursorPosition());
		// R
		if (YasuoCustomR->Enabled())
		{
			SArray<IUnit*> targets = ValidEnemies(R->Range()).Where([&](IUnit* i) {return YasuoTargetIsOnAir(i); });
			for (IUnit* target : targets.ToVector())
			{
				if (YasuoGEtRcount(target) >= YasuoCustomRHits->GetInteger())
				{
					R->CastOnUnit(target);
				}
				if (YasuoCustomRWhiteList[string("custom") + std::to_string(target->GetNetworkId())]->Enabled()
					&& YasuoCustomRWhiteListHP[string("customhp") + std::to_string(target->GetNetworkId())]->GetInteger() > target->HealthPercent())
				{
					R->CastOnUnit(target);
				}
			}
		}
		if (!IsADCanCastSpell(true))
			return;
		// Q
		if (YasuoQStage() != 3 && YasuoNotDashing())
		{
			YasuoCastQ();
		}
		else
		{
			auto target = SelectTarget(PhysicalDamage, Q2->Range());
			if (IsValidTarget(target))
			{
				if (!YasuoCustomQ3Spin->Enabled() || target->HasBuff("YasuoDashWrapper") || Distance(target, Player()->GetPosition()) > YasuoCustomQ3SpinMaxDist->GetInteger())
				{
					YasuoCastQ(target);
				}
			}
			for (IUnit* hero : ValidEnemies().ToVector())
			{
				YasuoCastQCircle(hero);
			}
		}
		// E
		bool underturret = YasuoCustomEUnderTurret->Enabled();
		{
			switch (YasuoCustomEMode->GetInteger())
			{
			case 0:
				YasuoCastEFly(underturret);
				break;
			case 1:
				YasuoCastETarget(underturret);
				break;
			default:
				YasuoCastEMouse(underturret);
				break;
			}
		}
		// gapE + Qstack
		if (CountEnemiesInRange(Player()->GetPosition(), E->Range()) == 0)
		{
			YasuoCastEMouse(underturret);
		}
		YasuoStackQ();
	}
	//// HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS HARASS
	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
	{
		if (!IsADCanCastSpell())
			return;
		// Q
		if (YasuoQStage() != 3 && YasuoNotDashing() && YasuoHarassQ->Enabled())
		{
			YasuoCastQ();
		}
		else if (YasuoQStage() != 3 && YasuoNotDashing() && YasuoHarassQ3->Enabled())
		{
			auto target = SelectTarget(PhysicalDamage, Q2->Range());
			if (IsValidTarget(target))
			{
				YasuoCastQ(target);
			}
		}
	}
	//// FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM FARM 
	if (GOrbwalking->GetOrbwalkingMode() == kModeLastHit)
	{
		bool underturret = YasuoFarmUnderTurret->Enabled();
		SArray<IUnit*> Minions = EnemyMinions(E->Range());
		for (IUnit* minion : Minions.ToVector())
		{
			if (YasuoLastHitQ->Enabled() && GetSpellDamage(minion, kSlotQ) > minion->GetHealth())
			{
				YasuoCastQ(minion);
			}
			if (YasuoLastHitE->Enabled() && YasuoGetEDamage(minion) > minion->GetHealth())
			{
				YasuoCastEOnUnit(minion, underturret);
			}
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
	{
		bool underturret = YasuoFarmUnderTurret->Enabled();
		//lane
		if (YasuoLaneClearQ->Enabled() && YasuoLaneClearE->Enabled())
		{
			SArray<IUnit*>  Minions = EnemyMinions(E->Range());
			for (IUnit* minion : Minions.ToVector())
			{
				if (CountMinionsInRange(YasuoGetDashEnd(minion), 250) >=3)
				{
					if (YasuoCastEOnUnit(minion, underturret))
						pDelay->Add(100, []() {Q->CastOnPosition(Player()->GetPosition()); });
				}
			}

		}
		if (YasuoLaneClearQ->Enabled())
		{
			FarmLocation location = FindBestLineCastPosition({ Player()->GetPosition() }, YasuoGetQRange(), YasuoGetQRange(), 10, true, true);
			if (location.HitCount >= 1)
			{
				YasuoCastQ(location.CastOnUnit);
			}
		}
		if (YasuoLaneClearE->Enabled())
		{
			SArray<IUnit*> Minions = EnemyMinions(E->Range());
			for (IUnit* minion : Minions.ToVector())
			{
				if (YasuoGetEDamage(minion) > minion->GetHealth())
				{
					YasuoCastEOnUnit(minion, underturret);
				}
			}
		}
		// jungle
		if (YasuoJungleClearQ->Enabled() || YasuoJungleClearE->Enabled())
		{
			SArray<IUnit*> Minions = NeutralMinions(YasuoGetQRange());
			for (IUnit* minion : Minions.ToVector())
			{
				if (YasuoJungleClearQ->Enabled())
				{
					YasuoCastQ(minion);
				}
				if (YasuoJungleClearE->Enabled())
				{
					YasuoCastEOnUnit(minion, underturret);
				}
			}
		}
	}
	//// FLEE FLEE FLEE FLEE FLEE FLEE FLEE FLEE FLEE FLEE FLEE FLEE FLEE FLEE FLEE FLEE FLEE FLEE FLEE FLEE FLEE FLEE FLEE FLEE FLEE FLEE
	if (IsKeyDown(YasuoFleeKey))
	{
		GOrbwalking->Orbwalk(nullptr, GGame->CursorPosition());
		YasuoCastEFlee();
		if (YasuoFleeStackQ)
			YasuoStackQ();
	}
	//// AUTO AUTO AUTO AUTO AUTO AUTO AUTO AUTO AUTO AUTO AUTO AUTO AUTO AUTO AUTO AUTO AUTO AUTO AUTO AUTO AUTO AUTO AUTO AUTO AUTO AUTO AUTO AUTO
	{
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo || IsKeyDown(YasuoCustomKey) || IsKeyDown(YasuoFleeKey))
			return;
		if (YasuoAutoQUnderTurret->Enabled() || !GUtility->IsPositionUnderTurret(Player()->GetPosition()))
		{
			if (YasuoQStage() != 3 && YasuoAutoQ->Enabled())
			{
				YasuoCastQ();
			}
			if (YasuoQStage() == 3 && YasuoAutoQ3->Enabled())
			{
				YasuoCastQ();
			}
		}
	}
}
