#pragma once
#include "LucianConfig.h"
inline bool LucianIsShortEPrior (IUnit* target)
{
	if (IsGoingToWard(target, Player()) && target->IsMelee() && AngleBetween(target->GetPosition(), Player()->GetPosition(), GGame->CursorPosition()) > 130)
	{
		return false;
	}
	else if (!IsGoingToWard(target, Player()) && AngleBetween(target->GetPosition(), Player()->GetPosition(), GGame->CursorPosition()) < 50 && Distance(Player(), target) >= 300)
	{
		return false;
	}
	return true;
}
inline bool LucianCastEToGap(IUnit*  target)
{
	for (int i = 450; i >= 200; i = i - 25)
	{
		Vec3 pos = Extend(Player()->GetPosition(), GGame->CursorPosition(), i);
		if (Distance(target, pos) <= GetAutoAttackRange(target) - 200)
		{
			E->CastOnPosition(pos);
			return true;
		}
	}
	return false;
}
inline bool LucianCanUseE (IUnit* target, Vec3& Position )
{
	if (LucianIsShortEPrior(target))
	{
		for (int i = 200; i <= 425; i = i + 25)
		{
			Vec3 pos = Extend(Player()->GetPosition(), GGame->CursorPosition(), i);
			if (Distance(target, pos) <= GetAutoAttackRange(target))
			{
				Position = pos;
				//E->CastOnPosition(pos);
				return true;
			}
		}
		if (LucianComboEMode->GetInteger() == 1)
		{
			for (int i = 200; i <= 425; i = i + 25)
			{
				SArray<Vec3> Poses = GetCircleCircleIntersections(Player()->GetPosition(), target->GetPosition(), i, GetAutoAttackRange(target) - 100);
				Poses.OrderBy<float>([&](Vec3 x) {return Distance(x, GGame->CursorPosition()); });
				for (Vec3 position : Poses.ToVector())
				{
					if (Distance(target, position) <= GetAutoAttackRange(target) && !GNavMesh->IsPointWall(position))
					{
						Position = position;
						return true;
					}
				}
			}
		}
	}
	else if (!LucianIsShortEPrior(target))
	{
		for (int i = 450; i >= 200; i = i -25)
		{
			Vec3 pos = Extend(Player()->GetPosition(), GGame->CursorPosition(), i);
			if (Distance(target, pos) <= GetAutoAttackRange(target))
			{
				Position = pos;
				//E->CastOnPosition(pos);
				return true;
			}
		}
		if (LucianComboEMode->GetInteger() == 1)
		{
			for (int i = 200; i <= 425; i = i + 25)
			{
				SArray<Vec3> Poses = GetCircleCircleIntersections(Player()->GetPosition(), target->GetPosition(), i, GetAutoAttackRange(target) - 100);
				Poses.OrderBy<float>([&](Vec3 x) {return Distance(x, GGame->CursorPosition()); });
				for (Vec3 position : Poses.ToVector())
				{
					if (Distance(target, position) <= GetAutoAttackRange(target) && !GNavMesh->IsPointWall(position))
					{
						Position = position;
						return true;
					}
				}
			}
		}
	}
	return false;
}
inline bool LucianCastQExtend(bool OnlyforKS = false, SArray<IUnit*> IgnoredChampion = SArray<IUnit*>())
{
	auto extender = EnemyMinions(Q->Range()).AddRange(ValidEnemies(Q->Range()));
	auto extendee = ValidEnemies(900).Where([&](IUnit* i)
	{
		return !IgnoredChampion.Any([&](IUnit* i2) {return i2->GetNetworkId() == i->GetNetworkId(); });
	});
	for (IUnit* hero : extendee.ToVector())
	{
		Vec3 predhero = MalachitePredGetUnitPosition(hero, 
			vector<float>{0.4f, 0.39f, 0.38f, 0.37f, 0.36f, 0.36f, 0.35f, 0.34f, 
				0.33f, 0.32f, 0.31f, 0.30f, 0.29f, 0.29f, 0.28f, 0.27f, 0.26f, 0.25f}[Player()->GetLevel() - 1]);
		for (IUnit* minion : extender.ToVector())
		{
			Vec3 predminion = MalachitePredGetUnitPosition(minion, 0.f);
			Vec3 endpos = Extend(Player()->GetPosition(), predminion, 900);
			if (Distance(predhero, Player()->GetPosition(),endpos,true) <= hero->BoundingRadius())
			{
				if (!OnlyforKS || GetSpellDamage(hero, kSlotQ) > hero->GetHealth())
				{
					Q->CastOnUnit(minion);
					return true;
				}
			}
		}
	}
	return false;
}