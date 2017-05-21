#pragma once
#include "Polygons.h"
#include "SkillShotDB.h"

inline Vec2 GetFirstCollision (Vec2 From, Vec2 To, int ColiFlag, float speed, float radius)
{
	Vec2 CollideVec(0,0);
	vector<IUnit *> Collisons;
	if (ColiFlag&kCollidesWithHeroes || ColiFlag&kCollidesWithMinions)
	{
		//GGame->PrintChat("a");
		SArray<IUnit*> Heroes;
		SArray<IUnit*> Minions;
		SArray<IUnit*> AllUnits;
		if (ColiFlag&kCollidesWithHeroes)
		{
			Heroes.AddRange(GEntityList->GetAllHeros(true, false));
			Heroes = Heroes.Where([&](IUnit* i) {return i != nullptr && !i->IsDead() && i->GetNetworkId() != Player()->GetNetworkId(); });
		}
		if (ColiFlag&kCollidesWithMinions)
		{
			//GGame->PrintChat("b");
			Minions.AddRange(AllyMinions(Distance(From, To) + 500, ToVec3(From)));
			Minions.AddRange(NeutralMinions(Distance(From, To) + 500, ToVec3(From)));
			//GGame->PrintChat(std::to_string(Minions.Count()).c_str());
		}
		AllUnits.AddRange(Heroes);
		AllUnits.AddRange(Minions);
		for (IUnit* hero : AllUnits.elems)
		{
			float delay = Distance(ToVec3(From), hero->GetPosition()) / speed;
			Vec3 pred = MalachitePredGetUnitPosition(hero, delay);
			float mindistance = hero->BoundingRadius() + radius / 2;
			if (/*Distance(hero->GetPosition(), ToVec3(From), ToVec3(To), true) < mindistance
				||*/ Distance(pred, ToVec3(From), ToVec3(To), true) < mindistance
/*				|| GetSegmentSegmentIntersections(From, To, hero->GetPosition(), pred)*/)
			{
				Collisons.push_back(hero);
			}
		}
	}
	if (ColiFlag&kCollidesWithYasuoWall)
	{
		IUnit* Wall;
		SArray<IUnit*> AllUnits;
		AllUnits.AddRange(GEntityList->GetAllUnits());
		AllUnits = AllUnits.Where([&](IUnit* i) {return i != nullptr &&  Contains(i->GetObjectName(), "w_windwall_enemy_"); });
		if (AllUnits.Any())
		{
			Wall = AllUnits.FirstOrDefault();
			float length = 300 /*+ 5 * 5*/;
			Vec3 direction = Pendicular(Normalize((Wall->GetPosition() - MalachitePredLastYasuoWallCastPos)));
			Vec3 WallStart = ToVec3((ToVec2(Wall->GetPosition()) + length * ToVec2(direction) / 2));
			Vec3 WallEnd = ToVec3((ToVec2(Wall->GetPosition()) - length * ToVec2(direction) / 2));
			float mindistance = 50 + radius / 2 + 50;
			if (Distance(WallStart, ToVec3(From), ToVec3(To), true) < mindistance
				|| Distance(WallEnd, ToVec3(From), ToVec3(To), true) < mindistance
				|| GetSegmentSegmentIntersections(ToVec3(From), ToVec3(To), WallStart, WallEnd))
			{
				Collisons.push_back(Wall);
			}
		}
	}
	if (Collisons.size() == 0)
		return CollideVec;
	std :: sort (Collisons.begin(), Collisons.end(), [&](IUnit* a, IUnit* b) { return Distance(a, ToVec3(From)) < Distance(b, ToVec3(From)); });
	CollideVec = Extend(From, To, Distance(From, Collisons.front()->GetPosition().To2D()));
	return CollideVec;
}
inline Geometry::IPolygon GetPolygon(DetectedSKillShot skillshot, bool useBoundingRadius = false, int extraRad = 0)
{
	// fast calculation
	{
		//Vec2 NewStart = Extend(skillshot.Start, skillshot.End, -skillshot.Data->BehindStart);
		//Vec2 NewEnd = Extend(skillshot.End, skillshot.Start, skillshot.Data->BehindStart);
		//skillshot.Start = NewStart;
		//skillshot.End = NewEnd;
		//NewStart = Extend(skillshot.Start, skillshot.End, skillshot.Data->InfrontStart);
		//NewEnd = Extend(skillshot.End, skillshot.Start, -skillshot.Data->InfrontStart);
		//skillshot.Start = NewStart;
		//skillshot.End = NewEnd;

		//
		if (skillshot.Data->MissileFromUnit)
		{
			Vec2 dir = (skillshot.End - skillshot.Start).VectorNormalize();
			if (skillshot.IsProcess && skillshot.Caster != nullptr)
			{
				skillshot.Start = skillshot.Caster->GetPosition().To2D();
				skillshot.End = skillshot.Start + dir*skillshot.Data->RawRange;
			}
			if (skillshot.IsMissile &&  GMissileData->GetCaster(skillshot.MissileObject) != nullptr)
			{
				skillshot.Start = GMissileData->GetCaster(skillshot.MissileObject)->GetPosition().To2D();
				skillshot.End = skillshot.Start + dir*skillshot.Data->RawRange;
			}
		}
		//
		if (skillshot.Data->MissileToUnit)
		{

			if (skillshot.IsProcess && skillshot.Caster != nullptr)
			{
				skillshot.End = skillshot.Caster->GetPosition().To2D();
			}
			if (skillshot.IsMissile &&  GMissileData->GetCaster(skillshot.MissileObject) != nullptr)
			{
				skillshot.End = GMissileData->GetCaster(skillshot.MissileObject)->GetPosition().To2D();
			}
		}
	}

	int ExtraRadius = (useBoundingRadius ? (skillshot.Data->AddHitbox ? Player()->BoundingRadius() : 0) : 0);
	ExtraRadius = ExtraRadius + extraRad;
	if (!skillshot.IsMissile || skillshot.MissileObject == nullptr)
	{
		Vec2 CollisionPos = GetFirstCollision(skillshot.Start, skillshot.End, skillshot.Data->CollisionObjects, skillshot.Data->MissileSpeed, skillshot.Data->RawRadius);
		
		switch (skillshot.Data->Type)
		{
		case ST_Ring:
			return Polygons::Ring(skillshot.End, skillshot.Data->RadiusEx ,skillshot.Data->RawRadius ).ToPolygon(ExtraRadius);
		case ST_Arc:
			return Polygons::Arc(skillshot.Start,skillshot.End, skillshot.Data->RawRadius ).ToPolygon(ExtraRadius);
		case ST_Box:
		{
			Vec2 dir = (skillshot.Start - skillshot.End).VectorNormalize().Perpendicular();
			Vec2 start = skillshot.End - (dir * skillshot.Data->RadiusEx / 2);
			Vec2 end = skillshot.End + (dir * skillshot.Data->RadiusEx / 2);
			return Polygons::Line(start, end, skillshot.Data->RawRadius/2).ToPolygon(ExtraRadius);
		}
		case ST_Line:
			return CollisionPos == Vec2(0, 0) ?
				Polygons::Line(skillshot.Start, skillshot.End, skillshot.Data->RawRadius/2).ToPolygon(ExtraRadius) :
				Polygons::Line(skillshot.Start, CollisionPos, skillshot.Data->RawRadius/2).ToPolygon(ExtraRadius);
		case ST_MissileLine:
			return CollisionPos == Vec2(0, 0) ?
				Polygons::Line(skillshot.Start, skillshot.End, skillshot.Data->RawRadius/2 ).ToPolygon(ExtraRadius) :
				Polygons::Line(skillshot.Start, CollisionPos, skillshot.Data->RawRadius/2 ).ToPolygon(ExtraRadius);
		case ST_Circle:
			return Polygons::Circle(skillshot.End, skillshot.Data->RawRadius ).ToPolygon(ExtraRadius);
		case ST_Ellipse:
			return Polygons::Ellipse(skillshot.Start,skillshot.End,skillshot.End,skillshot.Data->RawRadius,skillshot.Data->RadiusEx).ToPolygon(ExtraRadius);
		case ST_MissileCone:
			return  Polygons::Cone(skillshot.Start, (skillshot.End - skillshot.Start).VectorNormalize(), skillshot.Data->RawRadius, skillshot.Data->RawRange).ToPolygon(ExtraRadius);
		default :
			return Polygons::Cone(skillshot.Start, (skillshot.End - skillshot.Start).VectorNormalize(),skillshot.Data->RawRadius,skillshot.Data->RawRange).ToPolygon(ExtraRadius);
		}
	}
	else
	{
		Vec2 CollisionPos = GetFirstCollision(skillshot.MissileObject->GetPosition().To2D(), skillshot.End, skillshot.Data->CollisionObjects, skillshot.Data->MissileSpeed, skillshot.Data->RawRadius);
		switch (skillshot.Data->Type)
		{
		case ST_Ring:
			return Polygons::Ring(skillshot.End, skillshot.Data->RadiusEx , skillshot.Data->RawRadius ).ToPolygon(ExtraRadius);
		case ST_Arc:
			return Polygons::Arc(skillshot.Start, skillshot.End, skillshot.Data->RawRadius ).ToPolygon(ExtraRadius);
		case ST_Box:
		{
			Vec2 dir = (skillshot.Start - skillshot.End).VectorNormalize().Perpendicular();
			Vec2 start = skillshot.End - (dir * skillshot.Data->RadiusEx / 2);
			Vec2 end = skillshot.End + (dir * skillshot.Data->RadiusEx / 2);
			return Polygons::Line(start, end, skillshot.Data->RawRadius/2 ).ToPolygon(ExtraRadius);
		}
		case ST_Line:
			return CollisionPos == Vec2(0, 0) ?
				Polygons::Line(skillshot.Start, skillshot.End, skillshot.Data->RawRadius/2).ToPolygon(ExtraRadius) :
				Polygons::Line(skillshot.Start, CollisionPos, skillshot.Data->RawRadius/2).ToPolygon(ExtraRadius);
		case ST_MissileLine:
		{	
			return CollisionPos == Vec2(0, 0) ?
				Polygons::Line(skillshot.MissileObject->GetPosition().To2D(), skillshot.End, skillshot.Data->RawRadius/2).ToPolygon(ExtraRadius) :
				Polygons::Line(skillshot.MissileObject->GetPosition().To2D(), CollisionPos, skillshot.Data->RawRadius/2).ToPolygon(ExtraRadius);
		}
		case ST_Circle:
			return Polygons::Circle(skillshot.End, skillshot.Data->RawRadius ).ToPolygon(ExtraRadius);
		case ST_Ellipse:
			return Polygons::Ellipse(skillshot.Start, skillshot.End, skillshot.End, skillshot.Data->RawRadius, skillshot.Data->RadiusEx).ToPolygon(ExtraRadius);
		case ST_MissileCone:
			return  Polygons::Cone(skillshot.Start, (skillshot.End - skillshot.Start).VectorNormalize(), skillshot.Data->RawRadius, skillshot.Data->RawRange).ToPolygon(ExtraRadius);
		default:
			return Polygons::Cone(skillshot.Start, (skillshot.End - skillshot.Start).VectorNormalize(), skillshot.Data->RawRadius, skillshot.Data->RawRange).ToPolygon(ExtraRadius);
		}
	}
}
inline bool GetDetectedSSOnCast(SpellData* spelldata, CastedSpell const& Args)
{
	Vec2 StartPos = /*Args.Position_.To2D();*/ GSpellData->GetStartPosition(Args.Data_).To2D();
	if (spelldata->MissileFromUnit)
		StartPos = GSpellData->GetCaster(Args.Data_)->GetPosition().To2D();
	Vec2 EndPos = /*Args.EndPosition_.To2D();*/ GSpellData->GetEndPosition(Args.Data_).To2D();
	if (spelldata->MissileToUnit)
		EndPos = GSpellData->GetCaster(Args.Data_)->GetPosition().To2D();
	if (spelldata->FixedRange || DistanceSqr(ToVec3(StartPos), Args.EndPosition_) > pow(spelldata->RawRange, 2))
		EndPos = Extend(Args.Position_, Args.EndPosition_, spelldata->RawRange).To2D();
	// fast calculation
	{
		Vec2 NewStart = Extend(StartPos, EndPos, - spelldata->BehindStart);
		Vec2 NewEnd = Extend(EndPos, StartPos, spelldata->BehindStart);
		StartPos = NewStart;
		EndPos = NewEnd;
		NewStart = Extend(StartPos, EndPos, spelldata->InfrontStart);
		NewEnd = Extend(EndPos, StartPos, - spelldata->InfrontStart);
		StartPos = NewStart;
		EndPos = NewEnd;
		if (spelldata->IsSpecial)
		{
			// oriana
			if (spelldata->IsOriana)
			{
				vector<IUnit*> AllUnit = GEntityList->GetAllUnits();
				vector<IUnit*>::iterator objectIterator = std::find_if(AllUnit.begin(), AllUnit.end(), [&](IUnit* i)
				{
					return i != nullptr && string(i->GetObjectName()) == string("Orianna_Base_Z_ball_glow_red.troy");
					/*&& i->GetTeam() == Args.Caster_->GetTeam()*/;
				});
				if (objectIterator != AllUnit.end())
				{
					IUnit* object = *objectIterator;
					StartPos = ToVec2(object->GetPosition());
					EndPos = ToVec2(object->GetPosition());
				}
				else
				{
					bool found = false;
					for (IUnit* i : GEntityList->GetAllHeros(false, true))
					{
						if (i != nullptr && i->IsVisible() && (i->HasBuff("OrianaGhost") || i->HasBuff("OrianaGhostSelf")))
						{
							StartPos = i->GetPosition().To2D();
							EndPos = i->GetPosition().To2D();
							found = true;
						}
					}
					if (!found)
					{
						return false;
					}
				}
			}
			// galio
			if (spelldata->IsGalio)
			{
				EndPos = Args.EndPosition_.To2D();
				if (DistanceSqr(ToVec3(StartPos), ToVec3(EndPos)) > pow(spelldata->RawRange,2))
				{
					EndPos = Extend(StartPos, EndPos, spelldata->RawRange);
				}
			}
		}
	}

	if (Args.Caster_->IsEnemy(Player()))
	{
		DetectedSKillShot a = DetectedSKillShot(
			spelldata,
			StartPos,
			EndPos,
			GGame->TickCount()
			, true, false, nullptr, 0, Args.Caster_);
		a.Polygon = GetPolygon(a, a.Data->AddHitbox);
		a.DetectionTime = GGame->TickCount();
		DetectedSkillShots.Add(a);
	}
	else
	{
		DetectedSKillShot a = DetectedSKillShot(
			spelldata,
			StartPos,
			EndPos,
			GGame->TickCount()
			, true, false, nullptr, 0, Args.Caster_);
		a.Polygon = GetPolygon(a, a.Data->AddHitbox);
		a.DetectionTime = GGame->TickCount();
		DetectedSkillShotsAlly.Add(a);
	}
	return true;
}
inline bool GetDetectedSSOnCreate(SpellData* spelldata, IUnit* Source)
{
	Vec2 StartPos = GMissileData->GetStartPosition(Source).To2D();
	Vec2 EndPos = GMissileData->GetEndPosition(Source).To2D();
	if (spelldata->FixedRange)
		EndPos = Extend(GMissileData->GetStartPosition(Source), GMissileData->GetEndPosition(Source), spelldata->RawRange).To2D();
	// fast calculation
	{

	}

	if (GMissileData->GetCaster(Source)->IsEnemy(Player()))
	{
		DetectedSKillShot a = DetectedSKillShot(
			spelldata,
			GMissileData->GetStartPosition(Source).To2D(),
			EndPos
			, GGame->TickCount()
			, false, true, Source, Source->GetNetworkId());
		a.Polygon = GetPolygon(a, a.Data->AddHitbox);
		a.DetectionTime = GGame->TickCount();
		DetectedSkillShots.Add(a);
	}
	else
	{
		DetectedSKillShot a = DetectedSKillShot(
			spelldata,
			GMissileData->GetStartPosition(Source).To2D(),
			EndPos
			, GGame->TickCount()
			, false, true, Source, Source->GetNetworkId());
		a.Polygon = GetPolygon(a, a.Data->AddHitbox);
		a.DetectionTime = GGame->TickCount();
		DetectedSkillShotsAlly.Add(a);
	}
	return true;
}