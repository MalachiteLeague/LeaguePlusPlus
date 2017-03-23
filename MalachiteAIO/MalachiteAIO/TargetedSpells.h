#pragma once
#include "MainVariables.h"

class TargetedSpellData
{
public:
	string ChampionName = "";
	bool IsMissile = false;
	eSpellSlot Slot = kSlotUnknown;
	vector<string> SpellNames;
	bool UseSpellSlotNonMissile = true;
	TargetedSpellData(){};
	TargetedSpellData(string championname, bool ismissile, eSpellSlot slot, vector<string> missilename = vector<string>{}, bool usespellslot = true)
	{
		ChampionName = championname;
		IsMissile = ismissile;
		Slot = slot;
		SpellNames = missilename;
		UseSpellSlotNonMissile = usespellslot;
	};
	bool IsEqualSpellName(string name)
	{
		for (string i : this->SpellNames)
		{
			if (Contains(name, i))
				return true;
		}
		return false;
	}
};

SArray<TargetedSpellData> SpellBlockerTargetedSpells;

inline void SpellBlockerTargetedSpellOnLoad()
{
	//missile
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Akali", true, kSlotQ, vector<string>{"akalimota"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Anivia", true, kSlotE, vector<string>{"frostbite"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Annie", true, kSlotQ, vector<string>{"disintegrate"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Brand", true, kSlotR, vector<string>{"brandwildfire", "brandwildfiremissile"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Caitlyn", true, kSlotR, vector<string>{"caitlynaceintheholemissile"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Cassiopeia", true, kSlotE, vector<string>{"cassiopeiatwinfang"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Elise", true, kSlotQ, vector<string>{"elisehumanq"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("FiddleSticks", true, kSlotE, vector<string>{"fiddlesticksdarkwind", "fiddlesticksdarkwindmissile" }));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Gangplank", true, kSlotQ, vector<string>{"parley"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Janna", true, kSlotW, vector<string>{"sowthewind"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Kassadin", true, kSlotQ, vector<string>{"nulllance"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Katarina", true, kSlotQ, vector<string>{"katarinaq", "katarinaqmis"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Kayle", true, kSlotQ, vector<string>{"judicatorreckoning"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Leblanc", true, kSlotQ, vector<string>{"leblancq", "leblancrqmissle","leblancqchain"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Lulu", true, kSlotW, vector<string>{"luluw"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Malphite", true, kSlotQ, vector<string>{"seismicshard"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("MissFortune", true, kSlotQ, vector<string>{"missfortunericochetshot", "missFortunershotextra"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Nami", true, kSlotW, vector<string>{"namiwenemy", "namiwmissileenemy"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Nunu", true, kSlotE, vector<string>{"iceblast"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Pantheon", true, kSlotQ, vector<string>{"pantheonq"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Ryze", true, kSlotE, vector<string>{"ryzee", "ryzeemissile"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Shaco", true, kSlotE, vector<string>{"twoshivpoison"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Sona", true, kSlotQ, vector<string>{"sonaqmissile"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Swain", true, kSlotE, vector<string>{"swaintorment"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Syndra", true, kSlotR, vector<string>{"syndrar"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Teemo", true, kSlotQ, vector<string>{"blindingdart"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Tristana", true, kSlotE, vector<string>{"detonatingshot"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("TwistedFate", true, kSlotW, vector<string>{"bluecardattack"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("TwistedFate", true, kSlotW, vector<string>{"goldcardattack"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("TwistedFate", true, kSlotW, vector<string>{"redcardattack"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Vayne", true, kSlotE, vector<string>{"vaynecondemnmissile"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Veigar", true, kSlotR, vector<string>{"veigarr"}));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Viktor", true, kSlotQ, vector<string>{"viktorpowertransfer"}));
	// none missile
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Akali", false, kSlotR, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Alistar", false, kSlotW, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Blitzcrank", false, kSlotE, vector<string>{"PowerFistAttack"}, false));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Brand", false, kSlotE, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Chogath", false, kSlotR, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Darius", false, kSlotW, vector<string>{"DariusNoxianTacticsONHAttack"}, false));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Darius", false, kSlotR, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Ekko", false, kSlotE, vector<string>{"EkkoEAttack"}, false));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Elise", false, kSlotQ, vector<string>{"EliseSpiderQCast"}, false));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Evelynn", false, kSlotE, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Fiddlesticks", false, kSlotQ, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Fizz", false, kSlotQ, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Garen", false, kSlotQ, vector<string>{"GarenQAttack"}, false));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Garen", false, kSlotR, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Hecarim", false, kSlotE, vector<string>{"HecarimRampAttack"}, false));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Irelia", false, kSlotQ, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Irelia", false, kSlotE, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Jarvan", false, kSlotR, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Jax", false, kSlotQ, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Jax", false, kSlotR, vector<string>{"JaxRelentlessAttack"}, false));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Jayce", false, kSlotQ, vector<string>{"JayceToTheSkies"}, false));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Jayce", false, kSlotE, vector<string>{"JayceThunderingBlow"}, false));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Leesin", false, kSlotR, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Leona", false, kSlotQ, vector<string>{"LeonaShieldOfDaybreakAttack"}, false));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Lissandra", false, kSlotR, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Lucian", false, kSlotQ, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Malzahar", false, kSlotE, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Malzahar", false, kSlotE, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Maokai", false, kSlotW, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Mordekaiser", false, kSlotQ, vector<string>{"MordekaiserQAttack", "MordekaiserQAttack1", "MordekaiserQAttack2"}, false));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Mordekaiser", false, kSlotR, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Nasus", false, kSlotQ, vector<string>{"NasusQAttack"}, false));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("MonkeyKing", false, kSlotQ, vector<string>{"MonkeyKingQAttack"}, false));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Nidalee", false, kSlotQ, vector<string>{"NidaleeTakedownAttack", "Nidalee_CougarTakedownAttack"}, false));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Olaf", false, kSlotE, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Pantheon", false, kSlotW, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Poppy", false, kSlotE, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Quinn", false, kSlotE, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Rammus", false, kSlotE, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("RekSai", false, kSlotE, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Renekton", false, kSlotW, vector<string>{"RenektonExecute", "RenektonSuperExecute"}, false));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Ryze", false, kSlotW, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Singed", false, kSlotE, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Skarner", false, kSlotR, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("TahmKench", false, kSlotW, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Talon", false, kSlotQ, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Trundle", false, kSlotR, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Udyr", false, kSlotE, vector<string>{"UdyrBearAttack", "UdyrBearAttackUlt"}, false));
	//SpellBlockerTargetedSpells.Add(TargetedSpellData("Vi", false, kSlotR, vector<string>{}, true));//special
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Viktor", false, kSlotQ, vector<string>{"ViktorQBuff"}, false));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Vladimir", false, kSlotQ, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Volibear", false, kSlotW, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Volibear", false, kSlotQ, vector<string>{"VolibearQAttack"}, false));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Warwick", false, kSlotQ, vector<string>{}, true));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("XinZhao", false, kSlotQ, vector<string>{"XenZhaoThrust3"}, false));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Yorick", false, kSlotQ, vector<string>{"yorickqattack"}, false));
	SpellBlockerTargetedSpells.Add(TargetedSpellData("Zilean", false, kSlotE, vector<string>{}, true));
}