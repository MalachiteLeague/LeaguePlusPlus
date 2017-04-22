#pragma once
#include "EvadeMath.h"
#include <string>
Vec3 RenderPos1;
Vec3 RenderPos2;
int LastEvadeTick = 0;
PLUGIN_EVENT(bool) SSDetectorOnIssueOrder(IUnit* Source, DWORD OrderIdx, Vec3* Position, IUnit* Target)
{
	if (GGame->TickCount() < LastEvadeTick + 100)
	{
		return false;
	}
	if (Source == Player() && OrderIdx == kMoveTo && ShouldBlock(DetectedSkillShots,Player(),*Position,EvadeWithWalkingDanger->GetInteger()))
	{
		//GGame->PrintChat("blocked");
		return false;
	}
	if (Source == Player())
	{
		Vec2 EvadePoint = GetEvadePosition(DetectedSkillShots, Player(), EvadeWithWalkingDanger->GetInteger());
		if (EvadePoint != Vec2(0, 0))
		{
			//GGame->PrintChat("blocked number 2");
			return false;
		}
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
PLUGIN_EVENT(void) SSDetectorOnRender()
{
	if (EvadeDrawTestOnAlly->Enabled())
	{
		for (DetectedSKillShot skillshot : DetectedSkillShotsAlly.ToVector())
		{
			Geometry::IPolygon Poly = GetPolygon(skillshot);
			Poly.Draw(Black());
			//Geometry::IPolygon Poly = GetPolygon(skillshot);
			//Vec4 Color;
			//if (GetDodgeStage(skillshot, EvadeWithWalkingDanger->GetInteger()))
			//{
			//	Color = White();
			//}
			//else
			//{
			//	Color = Yellow();
			//}
			//Poly.Draw(Color);
		}
		//{
		//	auto target = SelectTarget(PhysicalDamage, 2000);
		//	if (target != nullptr)
		//	{
		//		GRender->DrawOutlinedCircle(ToVec3(GetEvadePosition(DetectedSkillShotsAlly, target)), Pink(), 50);
		//	}
		//}
	}
	// draw skill shot
	for (DetectedSKillShot skillshot : DetectedSkillShots.ToVector())
	{
		if (EvadeSkillShotOptions[skillshot.Data->MenuName].Draw->Enabled())
		{
			Geometry::IPolygon Poly = GetPolygon(skillshot);
			Vec4 Color;
			if (GetDodgeStage(skillshot, EvadeWithWalkingDanger->GetInteger()))
			{
				Color = White();
			}
			else
			{
				Color = Red();
			}
			Poly.Draw(Color);
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
		string Text = EvadeEnable->Enabled() ? "Evade : ON" : "Evade : OFF";
		GRender->DrawTextW(Position, Color, Text.c_str());
	}
	/*GRender->DrawOutlinedCircle(RenderPos1, Green(), 100);
	GRender->DrawOutlinedCircle(RenderPos2, Red(), 100);*/
}
PLUGIN_EVENT(void) SSDetectorOnUpdate()
{
	// destroy process

	DetectedSkillShots.RemoveAll(
		[&](DetectedSKillShot i)
	{
		//GGame->PrintChat(string(i.Data->MissileName) == string("") ? "yes " : "no");
		return !i.IsMissile && GGame->TickCount() - i.DetectionTime >= i.Data->Delay +  i.Data->ExtraDuration
		+ (string(i.Data->MissileName) == string("") ?  (Distance(i.Start, i.End)*1000/i.Data->MissileSpeed) : 0);
	});
	DetectedSkillShotsAlly.RemoveAll(
		[&](DetectedSKillShot i)
	{
		//GGame->PrintChat(string(i.Data->MissileName) == string("") ? "yes " : "no");
		return !i.IsMissile && GGame->TickCount() - i.DetectionTime >= i.Data->Delay + i.Data->ExtraDuration
			+ (string(i.Data->MissileName) == string("") ? (Distance(i.Start, i.End) * 1000 / i.Data->MissileSpeed): 0);
	});


	// evadeing
	if (EvadeWithWalking->Enabled() && GGame->TickCount() >= LastEvadeTick + 100)
	{
		Vec2 EvadePoint = GetEvadePosition(DetectedSkillShots, Player(), EvadeWithWalkingDanger->GetInteger());
		if (EvadePoint != Vec2(0, 0))
		{
			GGame->IssueOrderEx(Player(), kMoveTo, ToVec3(EvadePoint), false);
			LastEvadeTick = GGame->TickCount();
		}
		if (ShouldHoldOn(DetectedSkillShots, Player(),EvadeWithWalkingDanger->GetInteger()))
		{
			GGame->IssueOrderEx(Player(), kHoldPosition, Player()->GetPosition(), true);
		}
	}
	if(EvadeWithFlash->Enabled() && Flash->IsReady())
	{
		Vec2 EvadePoint = GetEvadePosition(DetectedSkillShots, Player(), EvadeWithFLashDanger->GetInteger());
		SArray<DetectedSKillShot> detected = DetectedSkillShots.Where([&](DetectedSKillShot i) {return GetDodgeStage(i, EvadeWithFLashDanger->GetInteger()); });
		for (DetectedSKillShot skillshot : detected.ToVector())
		{
			if (IsGettingHit(GGame->Latency() + 100, skillshot, Player()))
			{
				Vec2 Point = Extend(Player()->GetPosition().To2D(), EvadePoint, 424);
				Flash->CastOnPosition(ToVec3(Point));
			}
		}
	}
	if (EvadeWithHourglass->Enabled())
	{
		Vec2 EvadePoint = GetEvadePosition(DetectedSkillShots, Player(), EvadeWithHourglassDanger->GetInteger());
		SArray<DetectedSKillShot> detected = DetectedSkillShots.Where([&](DetectedSKillShot i) {return GetDodgeStage(i, EvadeWithHourglassDanger->GetInteger()); });
		for (DetectedSKillShot skillshot : detected.ToVector())
		{
			if (IsGettingHit(GGame->Latency() + 100, skillshot, Player()))
			{
				CastItemOnUnit(3157, 500, nullptr);
				//if (string(Player()->ChampionName()) == string("Xayah") )
				//{
				//	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, false, false, kCollidesWithNothing);
				//	R->SetOverrideRange(10000);
				//	auto target = SelectTarget(PhysicalDamage, 1000);
				//	if (target != nullptr)
				//		R->CastOnPosition(target->GetPosition());
				//	else
				//		R->CastOnPosition(ToVec3(skillshot.Start));
				//}
			}
		}
	}
}
PLUGIN_EVENT(bool) SSDetectorOnWndProc(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	ToogleKeyChecker(EvadeToogleKey, EvadeEnable, Wnd, Message, wParam, lParam);
	return true;
}
inline void SkillshotDetectorLoad()
{
	SpellsDB = new SpellDB;
	EvadeMenuInit();
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