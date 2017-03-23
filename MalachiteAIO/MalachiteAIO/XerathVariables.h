#pragma once
#include "MainVariables.h"

inline bool XerathIsRCharging()
{
	return Equals(Player()->GetSpellName(kSlotR), "XerathRMissileWrapper");
}
inline bool XerathIsQCharging()
{
	return Player()->HasBuff("XerathArcanopulseChargeUp");
}

int XerathLastCastedRTick;// XerathRMissileWrapper;