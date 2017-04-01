#pragma once
#include "YasuoConfig.h"

int YasuoLastETick;
UnitDash* YasuoDashData;

inline void YasuoVariableOnSpellCast(CastedSpell const& Args)
{
	if (Args.Caster_ != Player())
		return;
	if (GSpellData->GetSlot(Args.Data_) == kSlotE)
	{
		YasuoLastETick = GGame->TickCount();
	}
}
inline void YasuoVariableOnDash(UnitDash* Args)
{
	if (Args->Source != Player())
		return;
	YasuoDashData = Args;
}
inline void YasuoVariableOnPlayAnimation(IUnit* Source, std::string const Args)
{
	if (Source != Player())
		return;
	//GGame->PrintChat(Args.c_str());
	if (Args == string("1df607e5"))
	{
		GOrbwalking->SetAttacksAllowed(false);
		pDelay->Add(500, [&]() {GOrbwalking->SetAttacksAllowed(true); });
	}
}