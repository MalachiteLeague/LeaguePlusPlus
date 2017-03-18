#pragma once
#include "MainVariables.h"

SArray<IUnit *> JhinPassives;

inline bool JhinTargetHasPassive(IUnit * target)
{
	return JhinPassives.Any([&](IUnit* i) {return Distance(i, target) <= 50; });
}