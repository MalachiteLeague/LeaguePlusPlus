#pragma once
#include "LucianModes.h"


PLUGIN_EVENT(void) LucianOnOrbwalkAttack(IUnit* Source, IUnit* Target)
{
	LucianModeAfterAttack(Source, Target);
}

void LucianOnload()
{
	GEventManager->AddEventHandler(kEventOrbwalkAfterAttack, LucianOnOrbwalkAttack);
	LucianMenuAndSpells();
}
void LucianUnload()
{
	GEventManager->RemoveEventHandler(kEventOrbwalkAfterAttack, LucianOnOrbwalkAttack);
	LucianMainMenu->Remove();
}