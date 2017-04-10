#pragma once
#include "VelkozConfig.h"

IUnit* VelkozQMissile;

inline double VelkozGetRDamage(IUnit* target)
{
	if (Player()->GetSpellLevel(kSlotR) == 0)
		return 0;
	double rawdamage = vector<double>{ 450, 625 , 800 }[Player()->GetSpellLevel(kSlotR) - 1] + 1.25 * Player()->MagicDamage();
	return GDamage->CalcMagicDamage(Player(), target, rawdamage);
}