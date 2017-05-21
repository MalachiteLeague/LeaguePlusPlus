#pragma once
#include "PluginSDK.h"
#include <map>
enum EvaderType
{
	Movement, Invulnerability, SpeedBuffer, Wall, Shield
};
class Evader
{
public:
	string ChampionName;
	string MenuName;
	EvaderType Type;
	int Delay;
	eSpellSlot Slot;
	int Range;
	Evader(string championname, string menuname, eSpellSlot slot, int range, EvaderType type, int delay)
	: ChampionName(championname), MenuName(menuname), Slot(slot), Range(range), Type(type), Delay(delay)
	{};
};
struct EvaderDB
{
public:
	std::vector<Evader*> EvadeSpells;
	EvaderDB();
};
EvaderDB* EvadersDB = nullptr;
inline EvaderDB::EvaderDB()
{
	EvadeSpells.push_back(new Evader("Aatrox", "Aatrox Q", kSlotQ, 600, Movement, 500));
	EvadeSpells.push_back(new Evader("Ahri", "Ahri R", kSlotR, 450, Movement, 500));
	EvadeSpells.push_back(new Evader("Braum", "Braum E", kSlotE, 450, Wall, 300));
	EvadeSpells.push_back(new Evader("Caitlyn", "Caitlyn E", kSlotE, -400, Movement, 500));
	EvadeSpells.push_back(new Evader("Corki", "Corki W", kSlotW, 600, Movement, 500));
	EvadeSpells.push_back(new Evader("Draven", "Draven W", kSlotW, 600, SpeedBuffer, 500));
	EvadeSpells.push_back(new Evader("Diana", "Diana W", kSlotW, 600, Shield, 500));
	EvadeSpells.push_back(new Evader("Ekko", "Ekko E", kSlotE, 325, Movement, 500));
	EvadeSpells.push_back(new Evader("Ekko", "Ekko R", kSlotR, 325, Invulnerability, 300));
	EvadeSpells.push_back(new Evader("Evelynn", "Evelynn W", kSlotW, 325, SpeedBuffer, 500));
	EvadeSpells.push_back(new Evader("Ezreal", "Ezreal E", kSlotE, 475, Movement, 500));
	EvadeSpells.push_back(new Evader("Fiora", "Fiora Q", kSlotQ, 400, Movement, 500));
	EvadeSpells.push_back(new Evader("Fiora", "Fiora W", kSlotW, 750, Invulnerability, 300));
	EvadeSpells.push_back(new Evader("Fizz", "Fizz E", kSlotE, 400, Invulnerability, 300));
	EvadeSpells.push_back(new Evader("Garen", "Garen Q", kSlotQ, 400, SpeedBuffer, 500));
	EvadeSpells.push_back(new Evader("Garen", "Garen W", kSlotW, 400, Shield, 500));
	EvadeSpells.push_back(new Evader("Gnar", "Gnar E", kSlotE, 475, Movement, 500));
	EvadeSpells.push_back(new Evader("Gragas", "Gragas E", kSlotE, 600, Movement, 500));
	EvadeSpells.push_back(new Evader("Graves", "Graves E", kSlotE, 425, Movement, 500));
	EvadeSpells.push_back(new Evader("Hecarim", "Hecarim E", kSlotE, 425, SpeedBuffer, 500));
	EvadeSpells.push_back(new Evader("Hecarim", "Hecarim R", kSlotR, 1000, Movement, 500));
	EvadeSpells.push_back(new Evader("Ivern", "Ivern E", kSlotE, 1000, Shield, 500));
	EvadeSpells.push_back(new Evader("Janna", "Janna E", kSlotE, 1000, Shield, 500));
	EvadeSpells.push_back(new Evader("Karma", "Karma E", kSlotE, 1000, Shield, 500));
	EvadeSpells.push_back(new Evader("Kassadin", "Kassadin R", kSlotR, 500, Movement, 500));
	EvadeSpells.push_back(new Evader("Kayle", "Kayle W", kSlotW, 500, SpeedBuffer, 500));
	EvadeSpells.push_back(new Evader("Kayle", "Kayle R", kSlotR, 500, Invulnerability, 500));
	EvadeSpells.push_back(new Evader("Khazix", "Khazix E", kSlotE, 700, Movement, 500));
	EvadeSpells.push_back(new Evader("Kindred", "Kindred Q", kSlotQ, 340, Movement, 500));
	EvadeSpells.push_back(new Evader("Kled", "Kled E", kSlotE, 550, Movement, 500));
	EvadeSpells.push_back(new Evader("Leblanc", "Leblanc W", kSlotW, 700, Movement, 500));
	EvadeSpells.push_back(new Evader("Lissandra", "Lissandra R", kSlotR, 700, Invulnerability, 500));
	EvadeSpells.push_back(new Evader("Lucian", "Lucian E", kSlotE, 425, Movement, 500));
	EvadeSpells.push_back(new Evader("Lulu", "Lulu W", kSlotW, 425, SpeedBuffer, 500));
	EvadeSpells.push_back(new Evader("Lulu", "Lulu E", kSlotE, 425, Shield, 500));
	EvadeSpells.push_back(new Evader("Malphite", "Malphite R", kSlotR, 1000, Movement, 500));
	EvadeSpells.push_back(new Evader("MasterYi", "MasterYi R", kSlotR, 1000, SpeedBuffer, 500));
	EvadeSpells.push_back(new Evader("Morgana", "Morgana E", kSlotE, 1000, Shield, 500));
	EvadeSpells.push_back(new Evader("Nautilus", "Nautilus W", kSlotW, 1000, Shield, 500));
	EvadeSpells.push_back(new Evader("Nocturne", "Nocturne W", kSlotW, 1000, Invulnerability, 500));
	EvadeSpells.push_back(new Evader("Nunu", "Nunu W", kSlotW, 1000, SpeedBuffer, 500));
	EvadeSpells.push_back(new Evader("Orianna", "Orianna E", kSlotW, 1000, Shield, 500));
	EvadeSpells.push_back(new Evader("Poppy", "Poppy W", kSlotW, 1000, SpeedBuffer, 500));
	EvadeSpells.push_back(new Evader("Rakan", "Rakan W", kSlotW, 600, Movement, 500));
	EvadeSpells.push_back(new Evader("Rakan", "Rakan R", kSlotR, 600, SpeedBuffer, 500));
	EvadeSpells.push_back(new Evader("Renekton", "Renekton E", kSlotE, 450, Movement, 500));
	EvadeSpells.push_back(new Evader("Riven", "Riven E", kSlotE, 325, Movement, 500));
	EvadeSpells.push_back(new Evader("Rumble", "Rumble W", kSlotW, 325, Shield, 500));
	EvadeSpells.push_back(new Evader("Sejuani", "Sejuani Q", kSlotQ, 650, Movement, 500));
	EvadeSpells.push_back(new Evader("Shaco", "Shaco Q", kSlotQ, 400, Movement, 500));
	EvadeSpells.push_back(new Evader("Shaco", "Shaco R", kSlotR, 400, Invulnerability, 500));
	EvadeSpells.push_back(new Evader("Shen", "Shen E", kSlotE, 600, Movement, 500));
	EvadeSpells.push_back(new Evader("Shyvana", "Shyvana W", kSlotW, 300, SpeedBuffer, 500));
	EvadeSpells.push_back(new Evader("Shyvana", "Shyvana R", kSlotR, 850, Movement, 500));
	EvadeSpells.push_back(new Evader("Sion", "Sion W", kSlotW, 850, Shield, 500));
	EvadeSpells.push_back(new Evader("Sivir", "Sivir E", kSlotE, 850, Invulnerability, 500));
	EvadeSpells.push_back(new Evader("Skarner", "Skarner W", kSlotW, 850, Shield, 500));
	EvadeSpells.push_back(new Evader("Sona", "Sona E", kSlotE, 850, SpeedBuffer, 500));
	EvadeSpells.push_back(new Evader("Tristana", "Tristana W", kSlotW, 900, Movement, 500));
	EvadeSpells.push_back(new Evader("Tryndamere", "Tryndamere E", kSlotE, 660, Movement, 500));
	EvadeSpells.push_back(new Evader("Urgot", "Urgot W", kSlotW, 660, Shield, 500));
	EvadeSpells.push_back(new Evader("Vayne", "Vayne Q", kSlotQ, 300, Movement, 500));
	EvadeSpells.push_back(new Evader("Vladimir", "Vladimir W", kSlotW, 300, Invulnerability, 500));
	EvadeSpells.push_back(new Evader("Volibear", "Volibear Q", kSlotQ, 300, SpeedBuffer, 500));
	EvadeSpells.push_back(new Evader("Xayah", "Xayah R", kSlotR, 1100, Invulnerability, 500));
	EvadeSpells.push_back(new Evader("Yasuo", "Yasuo W", kSlotW, 1100, Wall, 500));
	EvadeSpells.push_back(new Evader("Zilean", "Zilean E", kSlotE, 1100, SpeedBuffer, 500));

	EvadeSpells.erase(std::remove_if(EvadeSpells.begin(), EvadeSpells.end(),[&](Evader* i)
	{
		return i->ChampionName != string(Player()->ChampionName());
	}),EvadeSpells.end());
}
