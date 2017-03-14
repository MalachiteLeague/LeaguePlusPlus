#pragma once
#include "MainVariables.h"
#include "EzrealLoad.h"
#include "CorkiLoad.h"
#include "VayneLoad.h"
#include "JinxLoad.h"

PluginSetup("MalachiteAIO");

PLUGIN_EVENT(void) OnOrbwalkBeforeAttack(IUnit* Target)
{
}
PLUGIN_EVENT(void) OnOrbwalkAttack(IUnit* Source, IUnit* Target)
{
}
PLUGIN_EVENT(void) OnOrbwalkAfterAttack(IUnit* Source, IUnit* Target)
{
}
// Return an IUnit object here to force the orbwalker to select it for this tick
PLUGIN_EVENT(IUnit*) OnOrbwalkingFindTarget()
{
	return nullptr;
}
PLUGIN_EVENT(void) OnOrbwalkTargetChange(IUnit* OldTarget, IUnit* NewTarget)
{
}
PLUGIN_EVENT(void) OnOrbwalkNonKillableMinion(IUnit* NonKillableMinion)
{
}
PLUGIN_EVENT(void) OnRender()
{
}
PLUGIN_EVENT(void) OnSpellCast(CastedSpell const& Args)
{
}
PLUGIN_EVENT(void) OnUnitDeath(IUnit* Source)
{
}
PLUGIN_EVENT(void) OnCreateObject(IUnit* Source)
{
}
PLUGIN_EVENT(void) OnDestroyObject(IUnit* Source)
{
}
PLUGIN_EVENT(void) OnDoCast(CastedSpell const& Args)
{
}
PLUGIN_EVENT(void) OnInterruptible(InterruptibleSpell const& Args)
{
}
PLUGIN_EVENT(void) OnGapCloser(GapCloserSpell const& Args)
{
}
// Called when issuing an order (e.g move, attack, etc.)
// Return false to stop order from executing
PLUGIN_EVENT(bool) OnIssueOrder(IUnit* Source, DWORD OrderIdx, Vec3* Position, IUnit* Target)
{
	return true;
}
PLUGIN_EVENT(void) OnBuffAdd(IUnit* Source, void* BuffData)
{
}
PLUGIN_EVENT(void) OnBuffRemove(IUnit* Source, void* BuffData)
{
}
PLUGIN_EVENT(void) OnGameEnd()
{
}
PLUGIN_EVENT(void) OnLevelUp(IUnit* Source, int NewLevel)
{
}
// Only called for local player, before the spell packet is sent
PLUGIN_EVENT(void) OnPreCast(int Slot, IUnit* Target, Vec3* StartPosition, Vec3* EndPosition)
{
}
PLUGIN_EVENT(void) OnDash(UnitDash* Args)
{
}
PLUGIN_EVENT(void) OnD3DPresent(void* Direct3D9DevicePtr)
{
}
PLUGIN_EVENT(void) OnD3DPreReset(void* Direct3D9DevicePtr)
{
}
PLUGIN_EVENT(void) OnD3DPostReset(void* Direct3D9DevicePtr)
{
}
PLUGIN_EVENT(void) OnRenderBehindHUD()
{
}
// Return false to set this message as handled
PLUGIN_EVENT(bool) OnWndProc(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	return true;
}
PLUGIN_EVENT(void) OnEnterVisible(IUnit* Source)
{
}
PLUGIN_EVENT(void) OnExitVisible(IUnit* Source)
{
}

PLUGIN_EVENT(void) OnGameUpdate()
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && (Player()->HasItemId(3140) || Player()->HasItemId(3139)))
	{
		vector<void*> buffs;
		Player()->GetAllBuffsData(buffs);
		for (void* buff : buffs)
		{
			if (buff != nullptr && GBuffData->GetBuffName(buff) != nullptr)
			{
				if(GBuffData->GetBuffType(buff) == BUFF_Stun || GBuffData->GetBuffType(buff) == BUFF_Snare || GBuffData->GetBuffType(buff) == BUFF_Charm || GBuffData->GetBuffType(buff) == BUFF_Fear || GBuffData->GetBuffType(buff) == BUFF_Suppression)
				{
					if ((GBuffData->GetEndTime(buff) - GGame->Time()) * 1000 >= 500)
					{
						CastItemOnUnit(3140, 500, nullptr);
						CastItemOnUnit(3139, 500, nullptr);
					}
				}
			}
		}
	}
}
SArray <string> ChampionList;
PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	ChampionList.AddRange(vector<string>{"ezreal","corki","vayne", "jinx"});
	// Initializes global interfaces for core access
	PluginSDKSetup(PluginSDK);
	if (!ChampionList.Any([&](string i) {return  Contains(GEntityList->Player()->ChampionName(), i); }))
	{
		return;
	}
	string noti = "MalachiteAIO ";
	noti += GEntityList->Player()->ChampionName();
	noti += " loaded!";
	GRender->Notification(Pink(), 10, noti.c_str());
	InitOnLoad();

	GEventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);

	if (Contains(GEntityList->Player()->ChampionName(), "ezreal"))
	{
		EzrealOnLoad();
	}
	else if (Contains(GEntityList->Player()->ChampionName(), "corki"))
	{
		CorkiOnLoad();
	}
	else if (Contains(GEntityList->Player()->ChampionName(), "vayne"))
	{
		VayneOnload();
	}
	else if (Contains(GEntityList->Player()->ChampionName(), "jinx"))
	{
		JinxOnload();
	}
}



// Called when plugin is unloaded

PLUGIN_API void OnUnload()
{
	if (!ChampionList.Any([&](string i) {return  Contains(GEntityList->Player()->ChampionName(), i); }))
	{
		return;
	}

	InitUnload();

	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);

	if (Contains(GEntityList->Player()->ChampionName(), "ezreal"))
	{
		EzrealUnload();
	}
	else if (Contains(GEntityList->Player()->ChampionName(), "corki"))
	{
		CorkiUnload();
	}
	else if (Contains(GEntityList->Player()->ChampionName(), "vayne"))
	{
		VayneUnload();
	}
	else if (Contains(GEntityList->Player()->ChampionName(), "jinx"))
	{
		JinxUnload();
	}
}