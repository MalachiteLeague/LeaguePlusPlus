#pragma once
#include "CorkiModes.h"

PLUGIN_EVENT(void) CorkiOnGameUpdate()
{
	CorkiComboOnUpdate();
	CorkiHarassOnUpdate();
	CorkiLastHitOnUpdate();
	CorkiLaneJungOnUpdate();
	CorkiAutoOnUpdate();
}
PLUGIN_EVENT(void)  CorkiOnRender()
{
}
void  CorkiOnLoad()
{
	GEventManager->AddEventHandler(kEventOnGameUpdate, CorkiOnGameUpdate);
	GEventManager->AddEventHandler(kEventOnRender, CorkiOnRender);
	CorkiMenuAndSpells();
}
void CorkiUnload()
{
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, CorkiOnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, CorkiOnRender);
	CorkiMainMenu->Remove();
}