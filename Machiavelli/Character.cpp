#include "Character.h"

CharacterCard::CharacterCard(const int characterID, const std::string name, const CharacterType type) : _character_id{ characterID }, _name{ name }, _type { type }
{
}

CharacterCard::~CharacterCard()
{
}

const std::string CharacterCard::GetName() const
{
	return _name;
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
