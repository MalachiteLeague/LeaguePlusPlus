#pragma once
#include "DravenModes.h"

PLUGIN_EVENT(void) DravenOnGameUpdate()
{
	DravenModeOnUpdate();
}
PLUGIN_EVENT(void) DravenOnRender()
{
	DravenModeOnRender();
}
PLUGIN_EVENT(void) DravenOnInterruptible(InterruptibleSpell const& Args)
{
	DravenModeOnInterrupt(Args);
}
PLUGIN_EVENT(void) DravenOnGapCloser(GapCloserSpell const& Args)
{
	DravenModeOnGapClose(Args);
}
PLUGIN_EVENT(void) DravenOnCreateObject(IUnit* Source)
{
	if (Source == nullptr)
		return;
	if (Source->IsMissile() && GMissileData->GetCaster(Source)->GetNetworkId() == Player()->GetNetworkId())
	{
		auto data = GMissileData->GetName(Source);
		if (Equals(data, "DravenSpinningReturn"))
			DravenAxesObject.Add(Source);
	}
}
PLUGIN_EVENT(void) DravenOnDestroyObject(IUnit* Source)
{
	if (Source == nullptr)
		return;
	if (Source->IsMissile() && GMissileData->GetCaster(Source)->GetNetworkId() == Player()->GetNetworkId())
	{
		auto data = GMissileData->GetName(Source);
		if (Equals(data, "DravenSpinningReturn"))
			DravenAxesObject.RemoveAll([&](IUnit* i) {return i->GetNetworkId() == Source->GetNetworkId(); });
	}
}
void DravenOnload()
{
	GEventManager->AddEventHandler(kEventOnGameUpdate, DravenOnGameUpdate);
	GEventManager->AddEventHandler(kEventOnRender, DravenOnRender);
	GEventManager->AddEventHandler(kEventOnInterruptible, DravenOnInterruptible);
	GEventManager->AddEventHandler(kEventOnGapCloser, DravenOnGapCloser);
	GEventManager->AddEventHandler(kEventOnCreateObject, DravenOnCreateObject);
	GEventManager->AddEventHandler(kEventOnDestroyObject, DravenOnDestroyObject);
	DravenMenuAndSpells();
}
void DravenUnload()
{
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, DravenOnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, DravenOnRender);
	GEventManager->RemoveEventHandler(kEventOnInterruptible, DravenOnInterruptible);
	GEventManager->RemoveEventHandler(kEventOnGapCloser, DravenOnGapCloser);
	GEventManager->RemoveEventHandler(kEventOnCreateObject, DravenOnCreateObject);
	GEventManager->RemoveEventHandler(kEventOnDestroyObject, DravenOnDestroyObject);
	DravenMainMenu->Remove();
}