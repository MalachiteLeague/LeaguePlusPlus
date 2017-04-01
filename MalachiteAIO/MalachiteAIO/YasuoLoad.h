#pragma once
#include "YasuoModes.h"
PLUGIN_EVENT(void) YasuoOnGameUpdate()
{
	YasuoModeOnUpdate();
	//if (YasuoIsDashing() && GGame->TickCount() - YasuoLastETick > 420 - GGame->Latency())
	//	Q->CastOnPosition(Player()->GetPosition());
	//GGame->PrintChat(std::to_string(YasuoQStage()).c_str());
}
PLUGIN_EVENT(void) YasuoOnSpellCast(CastedSpell const& Args)
{
	YasuoVariableOnSpellCast(Args);
}
PLUGIN_EVENT(void) YasuoOnDash(UnitDash* Args)
{
	YasuoVariableOnDash(Args);
}
PLUGIN_EVENT(void) YasuoOnPlayAnimation(IUnit* Source, std::string const Args)
{
	YasuoVariableOnPlayAnimation(Source, Args);
}
PLUGIN_EVENT(void) YasuoOnRender()
{
	//for (IUnit* target : YasuoAllETargets().ToVector())
	//{
	//	GRender->DrawOutlinedCircle(target->GetPosition(), Pink(), 100);
	//}
}
void YasuoOnload()
{
	GEventManager->AddEventHandler(kEventOnGameUpdate, YasuoOnGameUpdate);
	GEventManager->AddEventHandler(kEventOnSpellCast, YasuoOnSpellCast);
	GEventManager->AddEventHandler(kEventOnDash, YasuoOnDash);
	GEventManager->AddEventHandler(kEventOnPlayAnimation, YasuoOnPlayAnimation);
	GEventManager->AddEventHandler(kEventOnRender, YasuoOnRender);
	YasuoMenuAndSpells();
}
void YasuoUnload()
{
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, YasuoOnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnSpellCast, YasuoOnSpellCast);
	GEventManager->RemoveEventHandler(kEventOnDash, YasuoOnDash);
	GEventManager->RemoveEventHandler(kEventOnPlayAnimation, YasuoOnPlayAnimation);
	GEventManager->RemoveEventHandler(kEventOnRender, YasuoOnRender);
	YasuoMainMenu->Remove();
}