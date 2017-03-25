#pragma once
#include "LucianModes.h"


PLUGIN_EVENT(void) LucianOnOrbwalkAttack(IUnit* Source, IUnit* Target)
{
	LucianModeAfterAttack(Source, Target);
}
PLUGIN_EVENT(void) LucianOnGameUpdate()
{
	LucianModeOnUpdate();
}
void LucianOnload()
{
	GEventManager->AddEventHandler(kEventOrbwalkAfterAttack, LucianOnOrbwalkAttack);
	GEventManager->AddEventHandler(kEventOnGameUpdate, LucianOnGameUpdate);
	LucianMenuAndSpells();
}
void LucianUnload()
{
	GEventManager->RemoveEventHandler(kEventOrbwalkAfterAttack, LucianOnOrbwalkAttack);
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, LucianOnGameUpdate);
	LucianMainMenu->Remove();
}