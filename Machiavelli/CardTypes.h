#pragma once
#include <string>

enum class CardType { Building, Character };
enum class CardColor { White, Yellow, Green, Blue, Red, Lila };
enum class CharacterType {NONE,Murderer, Thief, Mage, King, Preacher, Merchant, ConstructionMaster, Condottiere };

inline const char* CharacterTypeToString(CharacterType c)
{
	switch (c)
	{
	case CharacterType::Murderer:		return "Moordenaar";
	case CharacterType::Thief:			return "Dief";
	case CharacterType::Mage:			return "Magier";
	case CharacterType::King:			return "Koning";
	case CharacterType::Preacher:		return "Prediker";
	case CharacterType::Merchant:		return "Koopman";
	case CharacterType::ConstructionMaster:	return "Bouwmeester";
	case CharacterType::Condottiere:	return "Condottiere";
	default: return "NONE";
	}
}

inline const char* ColorToString(CardColor c)
{
	switch (c)
	{
	default:
	case CardColor::White:		return "wit";
	case CardColor::Yellow:		return "geel";
	case CardColor::Green:		return "groen";
	case CardColor::Blue:		return "blauw";
	case CardColor::Red:		return "rood";
	case CardColor::Lila:		return "lila";
	}
}