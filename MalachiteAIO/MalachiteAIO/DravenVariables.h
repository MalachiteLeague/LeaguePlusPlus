#pragma once
#include "MainVariables.h"

SArray<IUnit*> DravenAxesObject;
SArray<IUnit*> DravenAxesMissileOne;
inline int DravenAxesOnHand()
{
	return Player()->GetBuffCount("DravenSpinningAttack");
}
inline int DravenAxesCount()
{
	return DravenAxesOnHand() + DravenAxesObject.Count() + DravenAxesMissileOne.Count();
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