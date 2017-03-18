#pragma once
#include "SivirModes.h"

PLUGIN_EVENT(void) SivirOnSpellCast(CastedSpell const& Args)
{
	SivirModeOnSpellCast(Args);
}
PLUGIN_EVENT(void) SivirOnGameUpdate()
{
	SivirModeOnUpdate();
}
PLUGIN_EVENT(void) SivirOnOrbwalkAttack(IUnit* Source, IUnit* Target)
{
	SivirModeAfterAttack(Source, Target);
}
void SivirOnload()
{
	GEventManager->AddEventHandler(kEventOnGameUpdate, SivirOnGameUpdate);
	GEventManager->AddEventHandler(kEventOrbwalkAfterAttack, SivirOnOrbwalkAttack);
	GEventManager->AddEventHandler(kEventOnSpellCast, SivirOnSpellCast);
	SivirMenuAndSpells();
}
void SivirUnload()
{
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, SivirOnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOrbwalkAfterAttack, SivirOnOrbwalkAttack);
	GEventManager->RemoveEventHandler(kEventOnSpellCast, SivirOnSpellCast);
	SivirMainMenu->Remove();
}