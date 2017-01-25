#pragma once
#include <string>
#include <iostream>
#include <map>

enum class CardType { Building, Character };
enum class CardColor { White, Yellow, Green, Blue, Red, Lila };
enum class CharacterType {NONE,Murderer, Thief, Mage, King, Preacher, Merchant, ConstructionMaster, Condottiere };

inline std::ostream &operator<<(std::ostream &output, const CharacterType &type) {
	switch (type)
	{
	case CharacterType::NONE:
		output << "NONE";
		break;
	case CharacterType::Murderer:
		output << "Murderer";
		break;
	case CharacterType::Thief:
		output << "Thief";
		break;
	case CharacterType::Mage:
		output << "Mage";
		break;
	case CharacterType::King:
		output << "King";
		break;
	case CharacterType::Preacher:
		output << "Preacher";
		break;
	case CharacterType::Merchant:
		output << "Merchant";
		break;
	case CharacterType::ConstructionMaster:
		output << "ConstructionMaster";
		break;
	case CharacterType::Condottiere:
		output << "Condottiere";
		break;
	}
	return output;
}

inline std::ostream &operator<<(std::ostream &output, const CardColor &color) {
	switch (color)
	{
		case CardColor::White:
			output << "White";
			break;
		case CardColor::Yellow:
			output << "Yellow";
			break;
		case CardColor::Green:
			output << "Green";
			break;
		case CardColor::Blue:
			output << "Blue";
			break;
		case CardColor::Red:
			output << "Red";
			break;
		case CardColor::Lila:
			output << "Lila";
			break;
	}
	return output;
}

inline std::istream &operator>>(std::istream &input, CardColor &color)
{
	try
	{
		std::map<std::string, CardColor> _colorIdentifiers = std::map<std::string, CardColor>();
		_colorIdentifiers.insert(std::make_pair("blauw", CardColor::Blue));
		_colorIdentifiers.insert(std::make_pair("groen", CardColor::Green));
		_colorIdentifiers.insert(std::make_pair("lila", CardColor::Lila));
		_colorIdentifiers.insert(std::make_pair("rood", CardColor::Red));
		_colorIdentifiers.insert(std::make_pair("wit", CardColor::White));
		_colorIdentifiers.insert(std::make_pair("geel", CardColor::Yellow));
		std::string currentInput;
		input >> currentInput;
		color = _colorIdentifiers.find(currentInput)->second;
		return input;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

}

inline std::istream &operator >> (std::istream  &input, CharacterType &card) {
	std::map<std::string, CharacterType> _characterIdentifiers = std::map<std::string, CharacterType>();
	_characterIdentifiers.insert(std::make_pair("Moordenaar", CharacterType::Murderer));
	_characterIdentifiers.insert(std::make_pair("Dief", CharacterType::Thief));
	_characterIdentifiers.insert(std::make_pair("Magier", CharacterType::Mage));
	_characterIdentifiers.insert(std::make_pair("Koning", CharacterType::King));
	_characterIdentifiers.insert(std::make_pair("Prediker", CharacterType::Preacher));
	_characterIdentifiers.insert(std::make_pair("Koopman", CharacterType::Merchant));
	_characterIdentifiers.insert(std::make_pair("Bouwmeester", CharacterType::ConstructionMaster));
	_characterIdentifiers.insert(std::make_pair("Condottiere", CharacterType::Condottiere));
	std::string currentInput;
	input >> currentInput;
	card = _characterIdentifiers.find(currentInput)->second;
	return input;
}
/*
std::ostream &operator<<(std::ostream &output, const CharacterType &type) {
	std::string c = "blue";
	output << c;
	return output;
}

std::istream &operator >> (std::istream  &input, CardColor &card) {
	input >> card;
	return input;
}

std::istream &operator >> (std::istream  &input, CharacterType &card) {
	input >> card;
	return input;
}*/

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