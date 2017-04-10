#pragma once
#include "VelkozModes.h"

PLUGIN_EVENT(void) VelkozOnGameUpdate()
{
	VelkozModeOnUpdate();
}
PLUGIN_EVENT(void) VelkozOnInterruptible(InterruptibleSpell const& Args)
{
	VelkozModeOnInterrupt(Args);
}
PLUGIN_EVENT(void) VelkozOnGapCloser(GapCloserSpell const& Args)
{
	VelkozModeOnGapClose(Args);
}
PLUGIN_EVENT(void) VelkozOnCreateObject(IUnit* Source)
{
	if (Source == nullptr)
		return;
	if (Source->IsMissile() && GMissileData->GetCaster(Source)->GetNetworkId() == Player()->GetNetworkId())
	{
		auto data = GMissileData->GetName(Source);
		if (Equals(data, "VelkozQMissile"))
			VelkozQMissile = Source;
	}
}
PLUGIN_EVENT(void) VelkozOnDestroyObject(IUnit* Source)
{
	if (Source == nullptr)
		return;
	if (Source->IsMissile() && GMissileData->GetCaster(Source)->GetNetworkId() == Player()->GetNetworkId())
	{
		auto data = GMissileData->GetName(Source);
		if (Equals(data, "VelkozQMissile"))
			VelkozQMissile = nullptr;
	}
}
PLUGIN_EVENT(void) VelkozOnRender()
{
	//if (VelkozQMissile != nullptr)
	//{
	//	GRender->DrawOutlinedCircle(VelkozQMissile->GetPosition(), Pink(), 50);
	//}
	//for (int i = 130; i >= -130; i = i -20)
	//{
	//	Vec3 explode = RotateAround(GGame->CursorPosition(), Player()->GetPosition(), i);
	//	GRender->DrawOutlinedCircle(explode, Green(), 20);
	//}
}
void VelkozOnload()
{
	GEventManager->AddEventHandler(kEventOnGameUpdate, VelkozOnGameUpdate);
	GEventManager->AddEventHandler(kEventOnInterruptible, VelkozOnInterruptible);
	GEventManager->AddEventHandler(kEventOnGapCloser, VelkozOnGapCloser);
	GEventManager->AddEventHandler(kEventOnCreateObject, VelkozOnCreateObject);
	GEventManager->AddEventHandler(kEventOnDestroyObject, VelkozOnDestroyObject);
	GEventManager->AddEventHandler(kEventOnRender, VelkozOnRender);
	VelkozMenuAndSpells();
}
void VelkozUnload()
{
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, VelkozOnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnInterruptible, VelkozOnInterruptible);
	GEventManager->RemoveEventHandler(kEventOnGapCloser, VelkozOnGapCloser);
	GEventManager->RemoveEventHandler(kEventOnCreateObject, VelkozOnCreateObject);
	GEventManager->RemoveEventHandler(kEventOnDestroyObject, VelkozOnDestroyObject);
	GEventManager->RemoveEventHandler(kEventOnRender, VelkozOnRender);
	VelkozMainMenu->Remove();
}