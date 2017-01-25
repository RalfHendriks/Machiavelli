#include "Character.h"

/*CharacterCard::CharacterCard(const int characterID, const std::string name, const CharacterType type) : _character_id{ characterID }, _name{ name }, _type{ type }, _executed{false}
{
}*/

CharacterCard::CharacterCard(int id, CharacterType type) : _character_id{ id }, _type{type}
{
}

CharacterCard::CharacterCard()
{
}

CharacterCard::~CharacterCard()
{
}

const std::string CharacterCard::GetName() const
{
	return CharacterTypeToString(_type);
}

const int CharacterCard::GetID() const
{
	return _character_id;
}

const std::string CharacterCard::GetDescription() const
{
	return _description;
}

const CharacterType CharacterCard::GetType() const
{
	return _type;
}

const bool CharacterCard::IsExecuted() const
{
	return _executed;
}

void CharacterCard::SetExecuted(const bool status)
{
	_executed = status;
}

void CharacterCard::Execute(GameController & game_controller)
{
}

std::ostream & operator<<(std::ostream & output, CharacterCard & card)
{
	output << "[ID] " << card._character_id << "\r\n";
	output << "[Name] " << card.GetName() << "\r\n";
	output << "\r\n";
	return output;
}

std::istream & operator >> (std::istream & input, CharacterCard & card)
{
	input >> card._character_id >> card._type;
	return input;
}
