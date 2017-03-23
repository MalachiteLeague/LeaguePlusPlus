#pragma once
#include "FioraModes.h"
PLUGIN_EVENT(void) FioraOnCreateObject(IUnit* Source)
{
	if (Source == nullptr)
		return;
	SArray<string> passivename;
	passivename.AddRange(FioraPassiveName);
	if (passivename.Any([&](string a) {return  Contains(a, Source->GetObjectName()); }))
	{
		FioraPassiveObjects.Add(Source);
	}
	SArray<string> prepassivename;
	prepassivename.AddRange(FioraPrePassiveName);
	if (prepassivename.Any([&](string a) {return  Contains(a, Source->GetObjectName()); }))
	{
		FioraPrePassiveObjects.Add(Source);
	}
	if (Contains(Source->GetObjectName(), "Fiora_Base_R_Mark") || Contains(Source->GetObjectName(), "Fiora_Base_R") && Contains(Source->GetObjectName(), "Timeout_FioraOnly.troy"))
	{
		FioraUltiPassiveObjects.Add(Source);
	}
}
PLUGIN_EVENT(void) FioraOnDestroyObject(IUnit* Source)
{
	if (Source == nullptr)
		return;
	SArray<string> passivename;
	passivename.AddRange(FioraPassiveName);
	if (passivename.Any([&](string a) {return  Contains(a, Source->GetObjectName()); }))
	{
		FioraPassiveObjects.RemoveAll([&](IUnit* i) {return Source->GetNetworkId() == i->GetNetworkId(); });
	}
	SArray<string> prepassivename;
	prepassivename.AddRange(FioraPrePassiveName);
	if (prepassivename.Any([&](string a) {return  Contains(a, Source->GetObjectName()); }))
	{
		FioraPrePassiveObjects.RemoveAll([&](IUnit* i) {return Source->GetNetworkId() == i->GetNetworkId(); });
	}
	if (Contains(Source->GetObjectName(), "Fiora_Base_R_Mark") || Contains(Source->GetObjectName(), "Fiora_Base_R") && Contains(Source->GetObjectName(), "Timeout_FioraOnly.troy"))
	{
		FioraUltiPassiveObjects.RemoveAll([&](IUnit* i) {return Source->GetNetworkId() == i->GetNetworkId(); });
	}
}
PLUGIN_EVENT(void) FioraOnGameUpdate()
{
	FioraModeOnUpdate();
}
PLUGIN_EVENT(void) FioraOnOrbwalkAttack(IUnit* Source, IUnit* Target)
{
	FioraModeAfterAttack(Source, Target);
}
PLUGIN_EVENT(void) FioraOnRender()
{
	if (FioraDrawOrbWalkingPoint->Enabled() && GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		Vec2 PlayerPos;
		Vec2 OrbwalkPos;
		GGame->Projection(Player()->GetPosition(), &PlayerPos);
		GGame->Projection(GOrbwalking->GetLastPosition(), &OrbwalkPos);
		GRender->DrawLine(PlayerPos, OrbwalkPos, Yellow());
	}
}
void FioraOnload()
{
	GEventManager->AddEventHandler(kEventOnGameUpdate, FioraOnGameUpdate);
	GEventManager->AddEventHandler(kEventOrbwalkAfterAttack, FioraOnOrbwalkAttack);
	GEventManager->AddEventHandler(kEventOnCreateObject, FioraOnCreateObject);
	GEventManager->AddEventHandler(kEventOnDestroyObject, FioraOnDestroyObject);
	GEventManager->AddEventHandler(kEventOnRender, FioraOnRender);
	FioraMenuAndSpells();
}
void FioraUnload()
{
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, FioraOnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOrbwalkAfterAttack, FioraOnOrbwalkAttack);
	GEventManager->RemoveEventHandler(kEventOnCreateObject, FioraOnCreateObject);
	GEventManager->RemoveEventHandler(kEventOnDestroyObject, FioraOnDestroyObject);
	GEventManager->RemoveEventHandler(kEventOnRender, FioraOnRender);
	FioraMainMenu->Remove();
}