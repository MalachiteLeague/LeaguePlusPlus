#pragma once
#include "EvadeMath.h"
#include "EvaderDB.h"
#include <string>
Vec3 RenderPos1;
Vec3 RenderPos2;
int LastEvadeTick = 0;
Vec2 EvadeWalkingPoint;
extern int LastPolygonTick = 0;
PLUGIN_EVENT(bool) SSDetectorOnIssueOrder(IUnit* Source, DWORD OrderIdx, Vec3* Position, IUnit* Target)
{
	//if (GGame->TickCount() < LastEvadeTick + 150)
	//{
	//	return false;
	//}
	if (Source == Player() && EvadeWithWalking->Enabled())
	{
		if (EvadeWalkingPoint != Vec2(0, 0))
		{
			//GGame->PrintChat("blocked number 2");
			return false;
		}
	}
	if (Source == Player() && OrderIdx == kMoveTo && ShouldBlock(DetectedSkillShots, Player(), *Position, EvadeWithWalkingDanger->GetInteger()))
	{
		//GGame->PrintChat("blocked");
		return false;
	}
	return  true;
}
PLUGIN_EVENT(void) SSDetectorOnCast(CastedSpell const& Args)
{
	if (!Args.Caster_->IsHero())
		return;
	//
	for (SpellData* i : SpellsDB->Spells)
	{
		if (i->SpellName == string(Args.Name_)
			|| std::find(i->ExtraSpellNames.begin(), i->ExtraSpellNames.end(), string(Args.Name_)) != i->ExtraSpellNames.end())
		{
			if (!i->MissileOnly)
				GetDetectedSSOnCast(i, Args);
		}
	}
}
PLUGIN_EVENT(void) SSDetectorOnCreate(IUnit* Source)
{
	if (!Source->IsMissile())
		return;
	if (GMissileData->GetCaster(Source) == nullptr || !GMissileData->GetCaster(Source)->IsHero())
		return;
	//
	for (SpellData* i : SpellsDB->Spells)
	{
		if (i->MissileName == string(GMissileData->GetName(Source))
			|| std::find(i->ExtraMissileNames.begin(), i->ExtraMissileNames.end(), string(GMissileData->GetName(Source))) != i->ExtraMissileNames.end())
		{
			GetDetectedSSOnCreate(i, Source);
		}
	}
}
PLUGIN_EVENT(void) SSDetectorOnDestroy(IUnit* Source)
{
	if (!Source->IsMissile())
		return;
	if (GMissileData->GetCaster(Source) == nullptr || !GMissileData->GetCaster(Source)->IsHero())
		return;
	//
	std::vector<SpellData*>::iterator data = std::find_if(SpellsDB->Spells.begin(), SpellsDB->Spells.end(), [&](SpellData* i)
	{
		return i->MissileName == string(GMissileData->GetName(Source))
			|| std::find(i->ExtraMissileNames.begin(), i->ExtraMissileNames.end(), string(GMissileData->GetName(Source))) != i->ExtraMissileNames.end();
	});
	if (data != SpellsDB->Spells.end())
	{
		DetectedSkillShots.RemoveAll(
			[&](DetectedSKillShot i)
		{
			return i.MissileNWID == Source->GetNetworkId();
		});
		DetectedSkillShotsAlly.RemoveAll(
			[&](DetectedSKillShot i)
		{
			return i.MissileNWID == Source->GetNetworkId();
		});
	}
}
PLUGIN_EVENT(void) SSDetectorOnUpdate()
{
	// destroy process

	DetectedSkillShots.RemoveAll(
		[&](DetectedSKillShot i)
	{
		//GGame->PrintChat(string(i.Data->MissileName) == string("") ? "yes " : "no");
		
		if (i.Data->MissileName == "")
		{
			float distance = Distance(i.Start, i.End);
			return !i.IsMissile && GGame->TickCount() - i.DetectionTime >= i.Data->Delay + i.Data->ExtraDuration
				+ distance * 1000 / i.Data->MissileSpeed;
		}
		else
		{
			return  !i.IsMissile && GGame->TickCount() - i.DetectionTime >= i.Data->Delay + i.Data->ExtraDuration;
		}
	});
	DetectedSkillShotsAlly.RemoveAll(
		[&](DetectedSKillShot i)
	{
		//GGame->PrintChat(string(i.Data->MissileName) == string("") ? "yes " : "no");
		if (i.Data->MissileName == "")
		{
			float distance = Distance(i.Start, i.End);
			return !i.IsMissile && GGame->TickCount() - i.DetectionTime >= i.Data->Delay + i.Data->ExtraDuration
				+ distance * 1000 / i.Data->MissileSpeed;
		}
		else
		{
			return  !i.IsMissile && GGame->TickCount() - i.DetectionTime >= i.Data->Delay + i.Data->ExtraDuration;
		}
	});
	// 
    if (GGame->TickCount() - LastPolygonTick >= 100)
    {
		LastPolygonTick = GGame->TickCount();
		for (int i = 0; i < DetectedSkillShots.ToVector().size(); ++i)
		{
			DetectedSkillShots.elems[i].Polygon = GetPolygon(DetectedSkillShots.elems[i], DetectedSkillShots.elems[i].Data->AddHitbox);
		}
		for (int i = 0; i < DetectedSkillShotsAlly.ToVector().size(); ++i)
		{
			DetectedSkillShotsAlly.elems[i].Polygon = GetPolygon(DetectedSkillShotsAlly.elems[i], DetectedSkillShotsAlly.elems[i].Data->AddHitbox);
		}
    }

	//initialize evading point 
	EvadeWalkingPoint = GetEvadePosition(DetectedSkillShots, Player(), EvadeWithWalkingDanger->GetInteger());

	// evadeing
	if (EvadeWithWalking->Enabled() /*&& GGame->TickCount() >= LastEvadeTick + 150*/)
	{
		if (EvadeWalkingPoint != Vec2(0, 0))
		{
			GGame->IssueOrderEx(Player(), kMoveTo, ToVec3(EvadeWalkingPoint), false);
			LastEvadeTick = GGame->TickCount();
		}
		if (ShouldHoldOn(DetectedSkillShots, Player(),EvadeWithWalkingDanger->GetInteger()))
		{
			GGame->IssueOrderEx(Player(), kHoldPosition, Player()->GetPosition(), true);
		}
	}
	// HOURGLASS
	if (EvadeWithHourglass->Enabled())
	{
		SArray<DetectedSKillShot> detected = DetectedSkillShots.Where([&](DetectedSKillShot i) {return GetDodgeStage(i, EvadeWithHourglassDanger->GetInteger()); });
		for (DetectedSKillShot skillshot : detected.elems)
		{
			if (!IsAbleWalkEvade(EvadeWalkingPoint, skillshot, Player()) || !EvadeWithWalking->Enabled())
			{
				if (IsGettingHit(GGame->Latency() + 100, skillshot, Player()))
				{
					CastItemOnUnit(3157, 500, nullptr);
				}
			}
		}
	}
	//FLASH 
	if(EvadeWithFlash->Enabled() && Flash->IsReady())
	{
		SArray<DetectedSKillShot> detected = DetectedSkillShots.Where([&](DetectedSKillShot i) {return GetDodgeStage(i, EvadeWithFLashDanger->GetInteger()); });
		for (DetectedSKillShot skillshot : detected.elems)
		{
			if (!IsAbleWalkEvade(EvadeWalkingPoint, skillshot, Player()) || !EvadeWithWalking->Enabled())
			{
				if (IsGettingHit(GGame->Latency() + 100, skillshot, Player()))
				{
					Vec2 EvadePoint = GetEvadePosition(SArray<DetectedSKillShot>().Add(skillshot), Player(), EvadeWithFLashDanger->GetInteger());
					Vec2 Point = Extend(Player()->GetPosition().To2D(), EvadePoint, 424);
					Flash->CastOnPosition(ToVec3(Point));
				}
			}
		}
	}
	// EVADER
	for (Evader* evader : EvadersDB->EvadeSpells)
	{
		for (DetectedSKillShot skillshot : DetectedSkillShots.elems)
		{
			if (GetEvaderStage(evader, skillshot) && EvadeWalkingPoint != Vec2(0,0))
			{
				if (!IsAbleWalkEvade(Extend(EvadeWalkingPoint,Player()->GetPosition().To2D(),50),skillshot,Player()) || !EvadeWithWalking->Enabled())
				{
					if (IsGettingHit(evader->Delay + GGame->Latency(), skillshot, Player()))
					{
						TriggerEvader(evader, skillshot);
					}
				}
			}
		}
	}
}
PLUGIN_EVENT(void) SSDetectorOnRender()
{
	if (EvadeDrawTestOnAlly->Enabled())
	{
		for (DetectedSKillShot skillshot : DetectedSkillShotsAlly.elems)
		{
			skillshot.Polygon.Draw(Black());
		}
	}
	// draw skill shot
	for (DetectedSKillShot skillshot : DetectedSkillShots.elems)
	{
		if (EvadeSkillShotOptions.find(skillshot.Data->MenuName) == EvadeSkillShotOptions.end())
			continue;
		if (EvadeSkillShotOptions[skillshot.Data->MenuName].Draw->Enabled())
		{
			Vec4 Color;
			if (GetDodgeStage(skillshot, EvadeWithWalkingDanger->GetInteger()))
			{
				Color = White();
			}
			else
			{
				Color = Red();
			}
			skillshot.Polygon.Draw(Color);
		}
	}
	// draw status
	if (EvadeDrawStatus->Enabled())
	{
		Vec2 Position;
		GGame->Projection(Player()->GetPosition(), &Position);
		Position.x = Position.x - 25;
		Position.y = Position.y + 25;
		Vec4 Color =
			EvadeEnable->Enabled() ? White() : Red();
		string Text = EvadeEnable->Enabled() ? "Evade : ON" : "Evade : OFF"	;
		GRender->DrawTextW(Position, Color, Text.c_str());
	}
	//GRender->DrawOutlinedCircle(RenderPos1, Green(), 100);
	//GRender->DrawOutlinedCircle(RenderPos2, Red(), 100);
}
PLUGIN_EVENT(bool) SSDetectorOnWndProc(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	ToogleKeyChecker(EvadeToogleKey, EvadeEnable, Wnd, Message, wParam, lParam);
	return true;
}
inline void SkillshotDetectorLoad()
{
	SpellsDB = new SpellDB;
	EvadersDB = new EvaderDB;
	EvadeMenuInit();
	SpellsDB->Spells = SArray<SpellData*>(SpellsDB->Spells).Where([&](SpellData*  i){return SArray<IUnit*>(GEntityList->GetAllHeros(true,true)).Any([&](IUnit* hero)
	{
		return string(hero->ChampionName()) == i->ChampName;
	}); }).elems;
	GEventManager->AddEventHandler(kEventOnSpellCast, SSDetectorOnCast);
	GEventManager->AddEventHandler(kEventOnCreateObject, SSDetectorOnCreate);
	GEventManager->AddEventHandler(kEventOnDestroyObject, SSDetectorOnDestroy);
	GEventManager->AddEventHandler(kEventOnRender, SSDetectorOnRender);
	GEventManager->AddEventHandler(kEventOnGameUpdate, SSDetectorOnUpdate);
	GEventManager->AddEventHandler(kEventOnIssueOrder, SSDetectorOnIssueOrder);
	GEventManager->AddEventHandler(kEventOnWndProc, SSDetectorOnWndProc);
}
inline void SkillshotDetectorUnload()
{
	EvadeMenu->SaveSettings();
	EvadeMenu->Remove();
	GEventManager->RemoveEventHandler(kEventOnSpellCast, SSDetectorOnCast);
	GEventManager->RemoveEventHandler(kEventOnCreateObject, SSDetectorOnCreate);
	GEventManager->RemoveEventHandler(kEventOnDestroyObject, SSDetectorOnDestroy);
	GEventManager->RemoveEventHandler(kEventOnRender, SSDetectorOnRender);
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, SSDetectorOnUpdate);
	GEventManager->RemoveEventHandler(kEventOnIssueOrder, SSDetectorOnIssueOrder);
	GEventManager->RemoveEventHandler(kEventOnWndProc, SSDetectorOnWndProc);
}