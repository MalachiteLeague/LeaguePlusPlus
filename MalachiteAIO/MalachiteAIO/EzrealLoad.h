#pragma once
//#include "MainVariables.h"
#include "EzrealModes.h"
PLUGIN_EVENT(void) EzrealOnGameUpdate()
{
	EzrealAutoOnUpdate();
	EzrealComboOnUpdate();
	EzrealHarassOnUpdate();
	EzrealLaneJungOnUpdate();
	EzrealLastHitOnUpdate();
}
PLUGIN_EVENT(void) EzrealOnRender()
{
	//auto targets = NeutralMinions(Q->Range()).ToVector();
	//for (IUnit* target : targets)
	//{
	//	GRender->DrawOutlinedCircle(target->GetPosition(), Pink(),100);
	//}
}
void EzrealOnLoad()
{
	GEventManager->AddEventHandler(kEventOnGameUpdate, EzrealOnGameUpdate);
	GEventManager->AddEventHandler(kEventOnRender, EzrealOnRender);
	EzrealMenuAndSpells();
}
void EzrealUnload()
{
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, EzrealOnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, EzrealOnRender);
	EzealMainMenu->Remove();
}