#pragma once
#include "MainVariables.h"
enum FioraPassiveType
{
	FioraNone, FioraPrePassive, FioraNormalPassive, FioraUltiPassive
};
enum FioraPassiveDirection
{
	FioraNE, FioraSE, FioraNW, FioraSW
};
class FioraPassiveStatus
{
public :
	bool HasPassive;
	FioraPassiveType PassiveType;
	Vec3 TargetPredictedPosition;
	SArray <FioraPassiveDirection> PassiveDirections;
	SArray<Vec3> PassivePredictedPositions;
	FioraPassiveStatus(bool hasPassive, FioraPassiveType passiveType, Vec3 targetPredictedPosition
		, SArray <FioraPassiveDirection> passiveDirections, SArray<Vec3> passivePredictedPositions)
	{
		HasPassive = hasPassive;
		PassiveType = passiveType;
		TargetPredictedPosition = targetPredictedPosition;
		PassiveDirections = passiveDirections;
		PassivePredictedPositions = passivePredictedPositions;
	}
	FioraPassiveStatus() { HasPassive = false; PassiveType = FioraNone; };
};
class FioraPassiveObject
{
public :
	string PassiveName;
	IUnit* Object;
	FioraPassiveType PassiveType;
	FioraPassiveDirection PassiveDirection;
	FioraPassiveObject(string passiveName, IUnit* obj, FioraPassiveType passiveType, FioraPassiveDirection passiveDirection)
	{
		PassiveName = passiveName;
		Object = obj;
		PassiveType = passiveType;
		PassiveDirection = passiveDirection;
	}
	FioraPassiveObject() {};
};
SArray<IUnit*> FioraUltiPassiveObjects;
SArray<IUnit*> FioraPassiveObjects;
SArray<IUnit*>FioraPrePassiveObjects;
vector<string> FioraPassiveName(
{ "Fiora_Base_Passive_NE.troy",
		"Fiora_Base_Passive_SE.troy",
		"Fiora_Base_Passive_NW.troy",
		"Fiora_Base_Passive_SW.troy",
		"Fiora_Base_Passive_NE_Timeout.troy",
		"Fiora_Base_Passive_SE_Timeout.troy",
		"Fiora_Base_Passive_NW_Timeout.troy",
		"Fiora_Base_Passive_SW_Timeout.troy" }
);

vector<string> FioraPrePassiveName(
{
	"Fiora_Base_Passive_NE_Warning.troy",
		"Fiora_Base_Passive_SE_Warning.troy",
		"Fiora_Base_Passive_NW_Warning.troy",
		"Fiora_Base_Passive_SW_Warning.troy"
});
inline FioraPassiveDirection GetPassiveDirection(IUnit* x)
{
	if (Contains(x->GetObjectName(),"NE", false))
	{
		return FioraNE;
	}
	else if (Contains(x->GetObjectName(), "SE", false))
	{
		return FioraSE;
	}
	else if (Contains(x->GetObjectName(), "NW", false))
	{
		return FioraNW;
	}
	else
	{
		return FioraSW;
	}
}
inline SArray<FioraPassiveObject> FioraGetPassiveObjects()
{
	SArray<FioraPassiveObject> PassiveObjects;
	for (IUnit* x : FioraPrePassiveObjects.Where([&](IUnit* i) {return i != nullptr /*&& i->IsVisible()*/; }).ToVector())
	{
		PassiveObjects.Add(FioraPassiveObject(x->GetObjectName(), x, FioraPrePassive, GetPassiveDirection(x)));
	}
	for (IUnit* x : FioraPassiveObjects.Where([&](IUnit* i) {return i != nullptr/* && i->IsVisible()*/; }).ToVector())
	{
		PassiveObjects.Add(FioraPassiveObject(x->GetObjectName(), x, FioraNormalPassive, GetPassiveDirection(x)));
	}
	for (IUnit* x : FioraUltiPassiveObjects.Where([&](IUnit* i) {return i != nullptr/* && i->IsVisible()*/; }).ToVector())
	{
		PassiveObjects.Add(FioraPassiveObject(x->GetObjectName(), x, FioraUltiPassive, GetPassiveDirection(x)));
	}
	return PassiveObjects;
}
inline FioraPassiveStatus FioraGetPassiveStatus(IUnit* target, float delay = 0.25f)
{
	SArray<FioraPassiveObject> allobjects = FioraGetPassiveObjects()
		.Where([&](FioraPassiveObject x) {return  x.Object != nullptr/* && x.Object->IsVisible()*/
			&& Distance(x.Object->GetPosition(), target->GetPosition()) <= 500; });
	Vec3 targetpredictedpos;
	GPrediction->GetFutureUnitPosition(target, delay, true, targetpredictedpos);
	if (!allobjects.Any())
	{
		return FioraPassiveStatus(false, FioraNone, Vec3(0, 0, 0), vector<FioraPassiveDirection>{}, vector<Vec3>{});
	}
	else
	{
		auto x = allobjects.FirstOrDefault();
		SArray<FioraPassiveDirection> listdirections;
		for (FioraPassiveObject a : allobjects.ToVector())
		{
			listdirections.Add(a.PassiveDirection);
		}
		SArray<Vec3>listpositions;
		for (FioraPassiveDirection a : listdirections.ToVector())
		{
			if (a == FioraNE)
			{
				Vec2 pos = ToVec2(targetpredictedpos);
				pos.y = pos.y + 200;
				listpositions.Add(ToVec3(pos));
			}
			else if (a == FioraNW)
			{
				Vec2 pos = ToVec2(targetpredictedpos);
				pos.x = pos.x + 200;
				listpositions.Add(ToVec3(pos));
			}
			else if (a == FioraSE)
			{
				Vec2 pos = ToVec2(targetpredictedpos);
				pos.x = pos.x - 200;
				listpositions.Add(ToVec3(pos));
			}
			else if (a == FioraSW)
			{
				Vec2 pos = ToVec2(targetpredictedpos);
				pos.y = pos.y - 200;
				listpositions.Add(ToVec3(pos));
			}
		}
		if (x.PassiveType == FioraPrePassive)
		{
			return  FioraPassiveStatus(true, FioraPrePassive, targetpredictedpos, listdirections, listpositions);
		}
		if (x.PassiveType == FioraNormalPassive)
		{
			return  FioraPassiveStatus(true, FioraNormalPassive, targetpredictedpos, listdirections, listpositions);
		}
		if (x.PassiveType == FioraUltiPassive)
		{
			return  FioraPassiveStatus(true, FioraUltiPassive, targetpredictedpos, listdirections, listpositions);
		}
		return  FioraPassiveStatus(true, FioraNone, targetpredictedpos, listdirections, listpositions);
	}
}
inline SArray<Vec3> FioraGetRadiusPoints(Vec3 targetpredictedpos, Vec3 passivepredictedposition)
{
	SArray<Vec3> RadiusPoints;
	for (int i = 50; i <= 300; i = i + 25)
	{
		auto x = Extend(targetpredictedpos, passivepredictedposition, i);
		for (int j = -45; j <= 45; j = j + 5)
		{
			RadiusPoints.Add(RotateAround(x, targetpredictedpos, j * PI / 180.f));
		}
	}
	return RadiusPoints;
}

inline float FioraGetPassiveDamage(IUnit* target)
{
	return
		(0.03f + ((0.045f * 0.01f)) * Player()->PhysicalDamageMod() / 100) * target->GetMaxHealth();
}
inline float FioraGetUltiPassiveDamage(IUnit* target)
{
	return FioraGetPassiveDamage(target) * 4;
}
inline float FioraGetUltiDamage(IUnit* target)
{
	return FioraGetUltiPassiveDamage(target) + GDamage->GetAutoAttackDamage(Player(),target, true) * 4;
}
inline float FioraGetFastDamage(IUnit* target)
{
	float damage = 0;
	damage += GetSpellDamage(target, kSlotQ);
	if (Q->IsReady())
		damage += GetSpellDamage(target, kSlotQ);
	if (R->IsReady())
	{
		damage += FioraGetUltiDamage(target);
		return damage;
	}
	else
	{
		auto status = FioraGetPassiveStatus(target, 0);
		if (status.HasPassive)
		{
			damage += status.PassivePredictedPositions.Count() * FioraGetPassiveDamage(target) + GDamage->GetAutoAttackDamage(Player(),target,true);
			if (status.PassivePredictedPositions.Count() < 3)
				damage += (3 - status.PassivePredictedPositions.Count()) * GDamage->GetAutoAttackDamage(Player(), target, true);
			return damage;
		}
		else
		{
			damage += GDamage->GetAutoAttackDamage(Player(), target, true) * 2;
			return damage;
		}
	}
}

inline float FioraGetQPassivedelay(IUnit* target)
{
	if (target == nullptr)
		return 0;
	return Distance(Player(), target) / 1100 + GGame->Latency() / 1000;
}
inline bool FioraCastQtoGapClose(IUnit* target)
{
	if (target == nullptr)
		return false;
	if (Distance(target, Player()) > 600)
		return false;
	auto pos = Extend(Player()->GetPosition(), target->GetPosition(), 400);
	if (!GNavMesh->IsPointWall(pos))
	{
		Q->CastOnPosition(pos);
		return true;
	}
	return false;
}
inline bool FioraCastQtoPrePassive(IUnit* target, float delay)
{
	if (target == nullptr)
		return false;
	auto targetStatus = FioraGetPassiveStatus(target, delay);
	if (!targetStatus.HasPassive || targetStatus.PassiveType != FioraPrePassive)
		return false;
	if (targetStatus.PassiveType != FioraPrePassive)
		return false;
	if (!targetStatus.PassivePredictedPositions.Any())
		return false;
	auto passivepos = targetStatus.PassivePredictedPositions.FirstOrDefault();
	////
	//if (Distance(Player(), passivepos) <= 400 && !GNavMesh->IsPointWall(passivepos))
	//{
	//	Q->CastOnPosition(passivepos);
	//	return true;
	//}
	//return false;
	auto poses = FioraGetRadiusPoints(targetStatus.TargetPredictedPosition, passivepos);
	poses = poses.Where([&](Vec3 x) {return  Distance(Player(), x) <= 400 && !GNavMesh->IsPointWall(x); })
		.OrderBy<float>([&](Vec3 x2) {return Distance(x2, passivepos); });
	if (!poses.Any())
		return false;
	auto pos = poses.FirstOrDefault();
	Q->CastOnPosition(pos);
	return true;
}
inline bool  FioraCastQtoPassive(IUnit* target, float delay)
{
	if (target == nullptr)
		return false;
	auto targetStatus = FioraGetPassiveStatus(target, delay);
	if (!targetStatus.HasPassive || targetStatus.PassiveType != FioraNormalPassive)
		return false;
	if (targetStatus.PassiveType != FioraNormalPassive)
		return false;
	if (!targetStatus.PassivePredictedPositions.Any())
		return false;
	auto passivepos = targetStatus.PassivePredictedPositions.FirstOrDefault();
	////
	//if (Distance(Player(), passivepos) <= 400 && !GNavMesh->IsPointWall(passivepos))
	//{
	//	Q->CastOnPosition(passivepos);
	//	return true;
	//}
	//return false;
	auto poses = FioraGetRadiusPoints(targetStatus.TargetPredictedPosition, passivepos);
	poses = poses.Where([&](Vec3 x) {return  Distance(Player(), x) <= 400 && !GNavMesh->IsPointWall(x); })
		.OrderBy<float>([&](Vec3 x2) {return Distance(x2, passivepos); });
	if (!poses.Any())
		return false;
	auto pos = poses.FirstOrDefault();
	Q->CastOnPosition(pos);
	return true;
}
inline bool FioraCastQtoUltPassive(IUnit* target, float delay)
{
	if (target == nullptr)
		return false;
	auto targetStatus = FioraGetPassiveStatus(target,delay);
	if (!targetStatus.HasPassive || targetStatus.PassiveType != FioraUltiPassive)
		return false;
	if (targetStatus.PassiveType != FioraUltiPassive)
		return false;
	if (!targetStatus.PassivePredictedPositions.Any())
		return false;
	auto passiveposes = targetStatus.PassivePredictedPositions;
	passiveposes.OrderBy<float>([&](Vec3 i) {return Distance(Player(), i); });
	auto passivepos = passiveposes.FirstOrDefault();
	////
	//if (Distance(Player(), passivepos) <= 400 && !GNavMesh->IsPointWall(passivepos))
	//{
	//	Q->CastOnPosition(passivepos);
	//	return true;
	//}
	//return false;
	auto poses = FioraGetRadiusPoints(targetStatus.TargetPredictedPosition, passivepos);
	poses = poses.Where([&](Vec3 x) {return  Distance(Player(), x) <= 400 && !GNavMesh->IsPointWall(x); })
		.OrderBy<float>([&](Vec3 x2) {return Distance(x2, passivepos); });
	if (!poses.Any())
		return false;
	auto pos = poses.FirstOrDefault();
	Q->CastOnPosition(pos);
	return true;
}
inline IUnit* FioraGetUltedTarget()
{
	SArray<IUnit*> targets = ValidEnemies().Where([&](IUnit* i) {return 
		FioraUltiPassiveObjects.Any([&](IUnit* i2) {return i2 != nullptr /*&& i2->IsVisible()*/ && Distance(i2, i) < 50; }); });
	if (!targets.Any())
		return nullptr;
	return targets.FirstOrDefault();
}
inline IUnit* FioraGetTarget(float range)
{
	auto ulted = FioraGetUltedTarget();
	if (IsValidTarget(ulted, 700))
		return ulted;
	return SelectTarget(PhysicalDamage, range);
}