#pragma once
#include "MainVariables.h"

enum SpellType
{
	ST_Line,
	ST_MissileLine,
	ST_Box,
	ST_Cone,
	ST_MissileCone,
	ST_Circle,
	ST_Ring,
	ST_Arc,
	ST_None,
	ST_Ellipse
};

#define VarSetB(Name) SpellData* _##Name(bool _Var) { Name = _Var; return this; }
#define VarSetI(Name) SpellData* _##Name(int _Var) { Name = _Var; return this; }
#define VarSetF(Name) SpellData* _##Name(float _Var) { Name = _Var; return this; }
#define VarSetS(Name) SpellData* _##Name(std::string const _Var) { Name = _Var; return this; }
#define VarAddS(Name) SpellData* _##Name(std::string const _Var) { Name.push_back(_Var); return this; }

#define AddVarB(Name) bool Name; VarSetB(Name);
#define AddVarI(Name) int Name; VarSetI(Name);
#define AddVarF(Name) float Name; VarSetF(Name);
#define AddVarS(Name) std::string Name; VarSetS(Name);
#define AddVarSV(Name) std::vector<std::string> Name; VarAddS(Name);

struct SpellData
{
	SpellData* Clone()
	{
		SpellData* pOut = new SpellData;
		memcpy(pOut, this, sizeof(SpellData));

		return pOut;
	}

	SpellData* InitializeDefaults()
	{
		memset(this, 0, sizeof(*this));

		AddHitbox = true;
		CanBeRemoved = true;
		CollisionObjects = kCollidesWithNothing;
		ChampName = "";
		DangerValue = 1;
		Delay = 250;
		MenuName = "";
		MissileName = "";
		MissileSpeed = 10000000000000000;
		MultipleNumber = -1;
		Slot = kSlotQ;
		SpellName = "";
		ToggleName = "";
		Type = ST_MissileLine;
		TrapName = "";

		ExtraMissileNames.clear();
		ExtraSpellNames.clear();

		return this;
	}

	int GetRadius();
	int GetRange();

	SpellData* _Radius(int _Var)
	{
		RawRadius = _Var;

		return this;
	}

	SpellData* _Range(int _Var)
	{
		RawRange = _Var;

		return this;
	}

	AddVarB(AddHitbox);
	AddVarI(BehindStart);
	AddVarB(CanBeRemoved);
	AddVarI(CollisionObjects);
	AddVarS(ChampName);
	AddVarI(DangerValue);
	AddVarI(Delay);
	AddVarB(DisabledByDefault);
	AddVarB(DontAddExtraDuration);
	AddVarB(DontCross);
	AddVarB(DontCheckForDuplicates);
	AddVarI(ExtraDelay);
	AddVarI(ExtraDuration);
	AddVarSV(ExtraMissileNames);
	AddVarI(ExtraRange);
	AddVarSV(ExtraSpellNames);
	AddVarB(FixedRange);
	AddVarB(HasEndExplosion);
	AddVarB(HasStartExplosion);
	AddVarI(InfrontStart);
	AddVarB(Invert);
	AddVarB(IsDangerous);
	AddVarB(IsDash);
	AddVarB(IsSummoner);
	AddVarS(MenuName);
	AddVarI(MissileAccel);
	AddVarB(MissileDelayed);
	AddVarB(MissileFromUnit);
	AddVarI(MissileMaxSpeed);
	AddVarI(MissileMinSpeed);
	AddVarS(MissileName);
	AddVarB(MissileOnly);
	AddVarI(MissileSpeed);
	AddVarB(MissileToUnit);
	AddVarF(MultipleAngle);
	AddVarI(MultipleNumber);
	AddVarB(Perpendicular);
	AddVarI(RadiusEx);
	AddVarI(Slot);
	AddVarS(SpellName);
	AddVarB(TakeClosestPath);
	AddVarS(ToggleName);
	AddVarI(Type);
	AddVarS(TrapName);

	//special
	AddVarB(IsSpecial);
	//Galio
	AddVarB(IsGalio);
	//Oriana
	AddVarB(IsOriana);

	// 	AddVarI(Radius);
	// 	AddVarI(Range);
	int Radius;
	int Range;

	int RawRadius;
	int RawRange;
	// 	AddVarI(RawRadius);
	// 	AddVarI(RawRange);
};

class DetectedSKillShot
{
public:
	// step one
	SpellData* Data= nullptr;
	bool IsProcess = false;
	bool IsMissile = false;
	// step 2
	IUnit* MissileObject = nullptr;
	IUnit* Caster = nullptr;
	//CastedSpell ProcessInfo;
	//step 3
	Vec2 Start;
	Vec2 End;
	//step 4 
	int DetectionTime = 0;
	int MissileNWID = 0;
	DetectedSKillShot(SpellData* data, Vec2 start, Vec2 end, int detectiontime, bool isprocess, bool ismissile, IUnit* missileObject, int missileNWID = 0, IUnit* caster= nullptr)
	{
		Data = data, Start = start, End = end, DetectionTime = detectiontime, IsProcess = isprocess, IsMissile = ismissile, MissileObject = missileObject
			, MissileNWID = missileNWID, Caster = caster;
	};
	DetectedSKillShot() { IsNull = true; }
	bool IsNull = false;
	Geometry::IPolygon Polygon;
	void SetPolygon(Geometry::IPolygon poly)
	{
		Polygon = poly;
	}
};

SArray<DetectedSKillShot> DetectedSkillShots;
SArray<DetectedSKillShot> DetectedSkillShotsAlly;
