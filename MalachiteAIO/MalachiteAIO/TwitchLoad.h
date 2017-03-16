#pragma once
#include "TwitchModes.h"

PLUGIN_EVENT(void) TwitchOnGameUpdate()
{
	TwitchModeOnUpdate();
}
void TwitchOnload()
{
	GEventManager->AddEventHandler(kEventOnGameUpdate, TwitchOnGameUpdate);
	TwitchMenuAndSpells();
}
void TwitchUnload()
{
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, TwitchOnGameUpdate);
	TwitchMainMenu->Remove();
}