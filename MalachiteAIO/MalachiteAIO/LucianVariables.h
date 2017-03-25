#pragma once
#include "LucianConfig.h"
inline bool LucianIsShortEPrior (IUnit* target)
{
	if (IsGoingToWard(target, Player()) && target->IsMelee() && AngleBetween(target->GetPosition(), Player()->GetPosition(), GGame->CursorPosition()) > 130)
	{
		return false;
	}
	else if (!IsGoingToWard(target, Player()) && AngleBetween(target->GetPosition(), Player()->GetPosition(), GGame->CursorPosition()) < 50)
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
		if (Distance(target, pos) <= Player()->GetRealAutoAttackRange(target) - 200)
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
			if (Distance(target, pos) <= Player()->GetRealAutoAttackRange(target))
			{
				Position = pos;
				//E->CastOnPosition(pos);
				return true;
			}
		}
		if (LucianComboEMode->GetInteger() == 2)
		{
			for (int i = 200; i <= 425; i = i + 25)
			{
				SArray<Vec3> Poses = GetCircleCircleIntersections(Player()->GetPosition(), target->GetPosition(), i, Player()->GetRealAutoAttackRange(target) - 100);
				Poses.OrderBy<float>([&](Vec3 x) {return Distance(x, GGame->CursorPosition()); });
				for (Vec3 position : Poses.ToVector())
				{
					if (Distance(target, position) <= Player()->GetRealAutoAttackRange(target) && !GNavMesh->IsPointWall(position))
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
			if (Distance(target, pos) <= Player()->GetRealAutoAttackRange(target))
			{
				Position = pos;
				//E->CastOnPosition(pos);
				return true;
			}
		}
		if (LucianComboEMode->GetInteger() == 2)
		{
			for (int i = 200; i <= 425; i = i + 25)
			{
				SArray<Vec3> Poses = GetCircleCircleIntersections(Player()->GetPosition(), target->GetPosition(), i, Player()->GetRealAutoAttackRange(target) - 100);
				Poses.OrderBy<float>([&](Vec3 x) {return Distance(x, GGame->CursorPosition()); });
				for (Vec3 position : Poses.ToVector())
				{
					if (Distance(target, position) <= Player()->GetRealAutoAttackRange(target) && !GNavMesh->IsPointWall(position))
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