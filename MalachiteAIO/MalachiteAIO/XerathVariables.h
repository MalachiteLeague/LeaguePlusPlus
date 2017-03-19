#pragma once
#include "MainVariables.h"

inline bool XerathIsRCharging()
{
	return Equals(Player()->GetSpellName(kSlotR), "XerathRMissileWrapper");
}

int XerathLastCastedRTick;// XerathRMissileWrapper;