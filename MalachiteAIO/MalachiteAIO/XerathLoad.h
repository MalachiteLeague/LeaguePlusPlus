#pragma once
#include "XerathModes.h"

PLUGIN_EVENT(void) XerathOnGameUpdate()
{
	XerathModeOnUpdate();
}
PLUGIN_EVENT(void) XerathOnSpellCast(CastedSpell const& Args)
{
	if (Args.Caster_->GetNetworkId() == Player()->GetNetworkId())
	{
		if (Equals(GSpellData->GetSpellName(Args.Data_), "XerathRMissileWrapper"))
		{
			XerathLastCastedRTick = GGame->TickCount();
		}
	}
}
PLUGIN_EVENT(void) XerathOnRender()
{
	if (XerathDrawQ->Enabled())
	{
		GRender->DrawOutlinedCircle(Player()->GetPosition(), Green(), Q->Range());
	}
	if (XerathDrawW->Enabled())
	{
		GRender->DrawOutlinedCircle(Player()->GetPosition(), Green(), W->Range());
	}
	if (XerathDrawE->Enabled())
	{
		GRender->DrawOutlinedCircle(Player()->GetPosition(), Green(), E->Range());
	}
	if (XerathDrawR->Enabled())
	{
		GRender->DrawOutlinedCircle(Player()->GetPosition(), Green(), R->Range());
	}
	if (XerathDrawRCast->Enabled() && XerathIsRCharging())
	{
		GRender->DrawOutlinedCircle(GGame->CursorPosition(), Yellow(), XerathAutoRDistance->GetInteger());
	}
}

void XerathOnload()
{
	GEventManager->AddEventHandler(kEventOnGameUpdate, XerathOnGameUpdate);
	GEventManager->AddEventHandler(kEventOnSpellCast, XerathOnSpellCast);
	GEventManager->AddEventHandler(kEventOnRender, XerathOnRender);
	XerathMenuAndSpells();
}
void XerathUnload()
{
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, XerathOnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnSpellCast, XerathOnSpellCast);
	GEventManager->RemoveEventHandler(kEventOnRender, XerathOnRender);
	XerathMainMenu->Remove();
}