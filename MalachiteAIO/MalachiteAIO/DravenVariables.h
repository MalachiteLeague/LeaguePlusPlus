#pragma once
#include "MainVariables.h"

SArray<IUnit*> DravenAxesObject;

inline int DravenAxesOnHand()
{
	return Player()->GetBuffCount("DravenSpinningAttack");
}
inline bool DravenHasWMoveSpeed()
{
	return Player()->HasBuff("DravenFury");
}
inline bool DravenHasWAttackSpeed()
{
	return Player()->HasBuff("dravenfurybuff");
}
inline bool DravenIsR1()
{
	return Equals(Player()->GetSpellName(kSlotR), "DravenRCast");
}