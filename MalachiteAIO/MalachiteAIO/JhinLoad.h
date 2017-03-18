#pragma once
#include "JhinModes.h"
PLUGIN_EVENT(void) JhinOnGameUpdate()
{
	JhinModeOnUpdate();
}
PLUGIN_EVENT(void) JhinOnCreateObject(IUnit* Source)
{
	if(Source == nullptr)
		return;
	if (Contains(Source->GetObjectName(),  "Jhin_Base_E_passive_mark.troy"))
	{
		JhinPassives.Add(Source);
	}
}
PLUGIN_EVENT(void) JhinOnDestroyObject(IUnit* Source)
{
	if (Source == nullptr)
		return;
	if (Contains(Source->GetObjectName(), "Jhin_Base_E_passive_mark.troy"))
	{
		JhinPassives.RemoveAll([&](IUnit* i) {return i->GetNetworkId() == Source->GetNetworkId(); });
	}
}
PLUGIN_EVENT(void) JhinOnRender()
{
}
void JhinOnload()
{
	GEventManager->AddEventHandler(kEventOnGameUpdate, JhinOnGameUpdate);
	GEventManager->AddEventHandler(kEventOnCreateObject, JhinOnCreateObject);
	GEventManager->AddEventHandler(kEventOnDestroyObject, JhinOnDestroyObject);
	GEventManager->AddEventHandler(kEventOnRender, JhinOnRender);
	JhinMenuAndSpells();
}
void JhinUnload()
{
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, JhinOnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnCreateObject, JhinOnCreateObject);
	GEventManager->RemoveEventHandler(kEventOnDestroyObject, JhinOnDestroyObject);
	GEventManager->RemoveEventHandler(kEventOnRender, JhinOnRender);
	JhinMainMenu->Remove();
}