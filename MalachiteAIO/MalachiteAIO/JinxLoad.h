#pragma once
#include "JinxModes.h"

PLUGIN_EVENT(void) JinxOnGameUpdate()
{
	JinxModeOnUpdate();
}
void JinxOnload()
{
	GEventManager->AddEventHandler(kEventOnGameUpdate, JinxOnGameUpdate);
	JinxMenuAndSpells();
}
void JinxUnload()
{
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, JinxOnGameUpdate);
	JinxMainMenu->Remove();
}