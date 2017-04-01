#pragma once
#include "YasuoVariables.h"

inline bool YasuoIsDashing()
{
	return GGame->TickCount() - YasuoLastETick <= 420 - GGame->Latency();
}

inline bool YasuoNotDashing()
{
	return GGame->TickCount() - YasuoLastETick > 500 - GGame->Latency();
}

inline int YasuoQStage()
{
	if (Player()->GetSpellBook()->GetLevel(kSlotQ) == 0) return 1;
	string name = Player()->GetSpellBook()->GetName(kSlotQ);
	string Q1 = "YasuoQW";
	string Q2 = "YasuoQ2W";
	return name == Q1 ? 1 : name == Q2 ? 2 : 3;
}
inline bool YasuoCastQ(IUnit* target)
{
	if (YasuoIsDashing())
		return false;
	if (YasuoQStage() == 3)
	{
		return MalachiteCast(Q2, target, kHitChanceHigh);
	}
	return MalachiteCast(Q, target);
}
inline bool YasuoCastQ()
{
	if (YasuoIsDashing())
		return false;
	auto enemies = ValidEnemies().OrderBy<float>([](IUnit* i) {return i->GetHealth(); });
	for (auto target : enemies.ToVector())
	{
		if (YasuoQStage() == 3)
		{
			if (MalachiteCast(Q2, target, kHitChanceHigh)) return true;
		}
		if (MalachiteCast(Q, target)) return true;
	}
	return false;
}
inline bool YasuoCastQCircle (IUnit* target)
{
	if (!YasuoIsDashing())
		return false;
	auto pred = MalachitePredGetUnitPosition(target, (YasuoDashData->EndTick - GGame->TickCount() - GGame->Latency())/1000.f);
	if (Distance(pred, YasuoDashData->EndPosition) <= 150 + target->BoundingRadius())
	{
		return Q->CastOnPosition(Player()->GetPosition());
	}
	return false;
}
inline float YasuoGetQRange()
{
	return YasuoQStage() == 3 ? Q2->Range() : Q->Range();
}
inline SArray<IUnit*> YasuoAllETargets(bool checkbuff = true)
{
	SArray<IUnit*> targets;
	targets.AddRange(ValidEnemies());
	targets.AddRange(EnemyMinions()).AddRange(NeutralMinions());
	targets.RemoveAll([&](IUnit* i) {return !IsValidTarget(i, E->Range()); });
	if (checkbuff)
	{
		targets.RemoveAll([&](IUnit* i) {return i->HasBuff("YasuoDashWrapper"); });
	}
	return targets;
}
inline Vec3 YasuoGetDashEnd (IUnit* target)
{
	auto pred = MalachitePredGetUnitPosition(target,0.f);
	return Extend(Player()->GetPosition(), pred, 475);
}

inline void YasuoCastETarget(bool Underturret)
{
	if (!IsADCanCastSpell())
		return;
	auto target = SelectTarget(PhysicalDamage,E->Range() + 200);
	if (IsValidTarget(target))
	{
		SArray<IUnit*> Etargets = YasuoAllETargets().Where([&](IUnit*  i) {return Underturret ? true : !GUtility->IsPositionUnderTurret(YasuoGetDashEnd(i)); })
		.Where([&](IUnit* i2 )
		{
			float range = Player()->AttackRange() + Player()->BoundingRadius()  + target->BoundingRadius();
			return Distance(MalachitePredGetUnitPosition(target, 0.45f), YasuoGetDashEnd(i2)) <= range
				|| Distance(target, YasuoGetDashEnd(i2)) <= range;
		});
		if (Etargets.Any())
		{
			IUnit* Etarget = Etargets.FirstOrDefault();
			E->CastOnUnit(Etarget);
		}
	}
}
inline void YasuoCastEFly(bool Underturret)
{
	if (!IsADCanCastSpell())
		return;
	for (IUnit* target : ValidEnemies().ToVector())
	{
		SArray<IUnit*> Etargets = YasuoAllETargets().Where([&](IUnit*  i) {return Underturret ? true : !GUtility->IsPositionUnderTurret(YasuoGetDashEnd(i)); })
			.Where([&](IUnit* i2)
		{
			float range = Player()->AttackRange() + Player()->BoundingRadius() + target->BoundingRadius();
			return Distance(MalachitePredGetUnitPosition(target, 0.45f), YasuoGetDashEnd(i2)) <= range
				|| Distance(target, YasuoGetDashEnd(i2)) <= range;
		});
		if (Etargets.Any())
		{
			IUnit* Etarget = Etargets.FirstOrDefault();
			E->CastOnUnit(Etarget);
		}
	}
}
inline void YasuoCastEMouse (bool Underturret)
{
	if (!IsADCanCastSpell())
		return;
	SArray<IUnit*> Etargets = YasuoAllETargets().Where([&](IUnit*  i) {return Underturret ? true : !GUtility->IsPositionUnderTurret(YasuoGetDashEnd(i)); })
	.Where([&](IUnit* i2)
	{
		return Distance(YasuoGetDashEnd(i2), GGame->CursorPosition()) < Distance(Player(), GGame->CursorPosition()) - 100;
	});
	Etargets.OrderBy<float>([&](IUnit* i) {return Distance(YasuoGetDashEnd(i), GGame->CursorPosition()); });
	if (Etargets.Any())
	{
		IUnit* Etarget = Etargets.FirstOrDefault();
		E->CastOnUnit(Etarget);
	}
}
inline void YasuoCastEFlee ()
{
	SArray<IUnit*> Etargets = YasuoAllETargets()
		.Where([&](IUnit* i2)
	{
		return Distance(YasuoGetDashEnd(i2), GGame->CursorPosition()) < Distance(Player(), GGame->CursorPosition()) - 100;
	});
	Etargets.OrderBy<float>([&](IUnit* i) {return Distance(YasuoGetDashEnd(i), GGame->CursorPosition()); });
	if (Etargets.Any())
	{
		IUnit* Etarget = Etargets.FirstOrDefault();
		E->CastOnUnit(Etarget);
	}
}
inline bool YasuoCastEOnUnit(IUnit* target,bool Underturret)
{
	if (!GUtility->IsPositionUnderTurret(YasuoGetDashEnd(target)) || Underturret)
	{
		E->CastOnUnit(target);
		return true;
	}
	return false;
}
inline void YasuoStackQ()
{
	if (CountEnemiesInRange(Player()->GetPosition(),E->Range()) == 0 && YasuoQStage() != 3)
	{
		for (IUnit* target : YasuoAllETargets(false).ToVector())
		{
			if (MalachiteCast(Q, target))
				return;
		}
	}
}
inline bool YasuoTargetIsOnAir(IUnit* target)
{
	return target->HasBuffOfType(BUFF_Knockback) || target->HasBuffOfType(BUFF_Knockup);
}
inline int YasuoGEtRcount(IUnit* target)
{
	return ValidEnemies().Where([&](IUnit* i )
	{
		return
			Distance(i, target) <= 400 && YasuoTargetIsOnAir(i);
	}).Count();
}
inline double YasuoGetEDamage(IUnit* target)
{
	return GetSpellDamage(target, kSlotE) * (1 + Player()->GetBuffCount("YasuoDashScalar") * 0.25f);
}
