#pragma once
#include "MainVariables.h"

inline bool LucianCanUseE (IUnit* target, Vec3& Position )
{
	for (int i = 200; i <= 425 ; i = i + 25)
	{
		Vec3 pos = Extend(Player()->GetPosition(), GGame->CursorPosition(), i);
		if (Distance(target, pos) <= Player()->GetRealAutoAttackRange(target))
		{
			Position = pos;
			//E->CastOnPosition(pos);
			return true;
		}
	}
	return false;
}