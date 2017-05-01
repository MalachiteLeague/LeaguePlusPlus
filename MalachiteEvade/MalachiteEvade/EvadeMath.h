#pragma once
#include "FastMath.h"
#include "Config.h"
inline int GetDangerousLevel (Vec2 Position, SArray<DetectedSKillShot> Detected, DetectedSKillShot& SkillShot)
{
	int danger = 0;
	for (DetectedSKillShot skillshot : Detected.ToVector())
	{
		if (GetPolygon(skillshot, skillshot.Data->AddHitbox).IsInside(Position) && EvadeSkillShotOptions[skillshot.Data->MenuName].DangerLevel->GetInteger() > danger)
		{
			danger = EvadeSkillShotOptions[skillshot.Data->MenuName].DangerLevel->GetInteger();
			SkillShot = skillshot;
		}
	}
	return danger;
}
inline bool IsAbleWalkEvade(Vec2 Point, DetectedSKillShot skillshot, IUnit* target)
{
	if (skillshot.IsProcess)
	{
		float distance = Distance(target->GetPosition(), ToVec3(skillshot.Start));
		int time = skillshot.Data->Delay + distance * 1000 / skillshot.Data->MissileSpeed;
		int time2 = Distance(target, ToVec3(Point)) * 1000 / target->MovementSpeed();
		return time2 + GGame->Latency() + 100 < time ;
	}
	if (skillshot.IsMissile && skillshot.MissileObject != nullptr)
	{
		float distance = Distance(skillshot.MissileObject, target);
		int time = distance * 100 / skillshot.Data->MissileSpeed;
		int time2 = Distance(target, ToVec3(Point)) * 1000 / target->MovementSpeed();
		return time2 + GGame->Latency() + 100 < time ;
	}
	return false;
}
inline Vec2 GetEvadePosition(SArray<DetectedSKillShot> Detected, IUnit* target,int Dangerouslevel)
{
	SArray<DetectedSKillShot> detected = Detected.Where([&](DetectedSKillShot i) {return GetDodgeStage(i, Dangerouslevel); });
	DetectedSKillShot skillshot;
	int dangerouslevel = GetDangerousLevel(target->GetPosition().To2D(), detected, skillshot);
	// an toan ne
	if (dangerouslevel == 0)
		return Vec2(0, 0);
	// nguy hiem ne
	//float distance = 10000000000000000;
	Vec2 EvadePoint = Vec2(0, 0);
	Geometry::IPolygon Polygon = GetPolygon(skillshot, skillshot.Data->AddHitbox, 50);

	// tim tat ca cac diem quen thuoc
	SArray<Vec2> Points;
	//if (skillshot.Data->Type == ST_Line || skillshot.Data->Type == ST_MissileLine || skillshot.Data->Type == ST_Box)
	//{
	//	for (int i = 1; i < Polygon.Points.size(); i = i + 1)
	//	{
	//		Points.Add(Polygon.Points[i]);
	//		float dists = Distance(target->GetPosition(), ToVec3(Polygon.Points[i - 1]), ToVec3(Polygon.Points[i]));
	//		Vec2 middle = Extend(target->GetPosition().To2D(), GetLineLineIntersections(target->GetPosition().To2D(), target->GetPosition().To2D() + Pendicular(ToVec3((Polygon.Points[i - 1] - Polygon.Points[i]))).To2D(),
	//			Polygon.Points[i - 1], Polygon.Points[i]), dists + 50);
	//		Points.Add(middle);
	//		float dist = Distance(ToVec3(Polygon.Points[i - 1]), ToVec3(Polygon.Points[i]));
	//		// more maybe no need ?
	//		if (Polygon.Points.size() < 6)
	//		{
	//			for (int j = -4; j < 5; j = j + 1)
	//			{
	//				Points.Add(Extend(Polygon.Points[i - 1], middle, j * 25));
	//			}
	//		}

	//	}
	//	Points.Add(Polygon.Points[0]);
	//	float dists = Distance(target->GetPosition(), ToVec3(Polygon.Points.back()), ToVec3(Polygon.Points[0]));
	//	Vec2 middle = Extend(target->GetPosition().To2D(), GetLineLineIntersections(target->GetPosition().To2D(), target->GetPosition().To2D() + Pendicular(ToVec3((Polygon.Points.front() - Polygon.Points.back()))).To2D(),
	//		Polygon.Points.front(), Polygon.Points.back()), dists + 50);
	//	Points.Add(middle);
	//	float dist = Distance(ToVec3(Polygon.Points.back()), ToVec3(Polygon.Points[0]));
	//	// more maybe no need ?
	//	if (Polygon.Points.size() < 6)
	//	{
	//		for (int j = -4; j < 5; j = j + 1)
	//		{
	//			Points.Add(Extend(Polygon.Points.back(), middle, j * 25));
	//		}
	//	}
	//}
	//else
	//{
		for (int i = 1; i < Polygon.Points.size(); i = i + 1)
		{
			float dists = Distance(target->GetPosition(), ToVec3(Polygon.Points[i - 1]), ToVec3(Polygon.Points[i]));
			Vec2 middle = Extend(target->GetPosition().To2D(), GetLineLineIntersections(target->GetPosition().To2D(), target->GetPosition().To2D() + Pendicular(ToVec3((Polygon.Points[i - 1] - Polygon.Points[i]))).To2D(),
				Polygon.Points[i - 1], Polygon.Points[i]), dists + 50);
			Points.Add(middle);
		}
		float dists = Distance(target->GetPosition(), ToVec3(Polygon.Points.back()), ToVec3(Polygon.Points[0]));
		Vec2 middle = Extend(target->GetPosition().To2D(), GetLineLineIntersections(target->GetPosition().To2D(), target->GetPosition().To2D() + Pendicular(ToVec3((Polygon.Points.front() - Polygon.Points.back()))).To2D(),
			Polygon.Points.front(), Polygon.Points.back()), dists + 50);
		Points.Add(middle);
	//}
	if (Points.Any())
		EvadePoint = Points.MinOrDefault<float>([&](Vec2 i) {return DistanceSqr(ToVec3(i), target->GetPosition()); });
	//kiem diem di bo ne phu hop
	DetectedSKillShot SShot;
	Points = Points.Where([&](Vec2 i) {return !GNavMesh->IsPointWall(ToVec3(i)) && GetDangerousLevel(i, detected, SShot) < dangerouslevel; });
	if (Points.Any())
	{
		Points = Points.OrderBy<float>([&](Vec2 i) {return Distance(i, target->GetPosition().To2D()); });
		EvadePoint = Points.FirstOrDefault();
		//Points = Points.Where([&](Vec2 i) {return IsAbleWalkEvade(i, skillshot, target); });
		//if (Points.Any())
		//{
		//	Points = Points.OrderBy<float>([&](Vec2 i) {return Distance(i, GGame->CursorPosition().To2D()); });
		//	EvadePoint = Points.FirstOrDefault();
		//}
	}
	return  EvadePoint;
	return Vec2(0, 0);
}
inline bool IsGettingHit (int milisecond, DetectedSKillShot skillshot , IUnit* target)
{
	if (!GetPolygon(skillshot, skillshot.Data->AddHitbox).IsInside(target->GetPosition().To2D()))
		return false;
    if (skillshot.IsProcess)
    {
		float distance = Distance(target->GetPosition(), ToVec3(skillshot.Start));
		int time = skillshot.Data->Delay + distance * 1000 / skillshot.Data->MissileSpeed;
		return GGame->TickCount() + milisecond >= time + skillshot.DetectionTime;
    }
	if (skillshot.IsMissile && skillshot.MissileObject != nullptr)
	{
		float distance = Distance(skillshot.MissileObject, target);
		int time = distance * 100 / skillshot.Data->MissileSpeed;
		return milisecond >= time;
	}
	return false;
}
inline bool ShouldHoldOn (SArray<DetectedSKillShot> Detected, IUnit* target, int Dangerouslevel)
{
	vector<Vec3> waypoint = target->GetWaypointList();
	if (waypoint.size() <= 1)
		return false;
	SArray<DetectedSKillShot> detected = Detected.Where([&](DetectedSKillShot i) {return GetDodgeStage(i, Dangerouslevel); });
	DetectedSKillShot skillshot;
	if (GetDangerousLevel(ToVec2(waypoint[0]), detected, skillshot) != 0)
		return false;
	if (GetDangerousLevel(ToVec2(Extend(waypoint[0], waypoint[1], 50)), detected, skillshot) != 0)
		return true;
	return false;
}
inline bool ShouldBlock (SArray<DetectedSKillShot> Detected, IUnit* target, Vec3 Position, int Dangerouslevel)
{
	SArray<DetectedSKillShot> detected = Detected.Where([&](DetectedSKillShot i) {return GetDodgeStage(i, Dangerouslevel); });
	DetectedSKillShot skillshot;
	if (GetDangerousLevel(ToVec2(Extend(target->GetPosition(), Position, 50)), detected, skillshot) != 0)
		return true;
	if (GetDangerousLevel(ToVec2(Extend(target->GetPosition(), Position, 100)), detected, skillshot) != 0)
		return true;
	return false;
}
