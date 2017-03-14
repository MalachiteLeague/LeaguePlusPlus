#pragma once
#include "VayneModes.h"
PLUGIN_EVENT(void) VayneOnGameUpdate()
{
	VayneModeOnUpdate();
}
PLUGIN_EVENT(void) VayneOnOrbwalkAttack(IUnit* Source, IUnit* Target)
{
	VayneModeAfterAttack(Source, Target);
}
PLUGIN_EVENT(void) VayneOnInterruptible(InterruptibleSpell const& Args)
{
	VayneModeOnInterrupt(Args);
}
PLUGIN_EVENT(void) VayneOnGapCloser(GapCloserSpell const& Args)
{
	VayneModeOnGapClose(Args);
}
void VayneOnload()
{
	GEventManager->AddEventHandler(kEventOnGameUpdate, VayneOnGameUpdate);
	GEventManager->AddEventHandler(kEventOrbwalkAfterAttack, VayneOnOrbwalkAttack);
	GEventManager->AddEventHandler(kEventOnInterruptible, VayneOnInterruptible);
	GEventManager->AddEventHandler(kEventOnGapCloser, VayneOnGapCloser);
	VayneMenuAndSpells();
}
void VayneUnload()
{
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, VayneOnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOrbwalkAfterAttack, VayneOnOrbwalkAttack);
	GEventManager->RemoveEventHandler(kEventOnInterruptible, VayneOnInterruptible);
	GEventManager->RemoveEventHandler(kEventOnGapCloser, VayneOnGapCloser);
	VayneMainMenu->Remove();
}