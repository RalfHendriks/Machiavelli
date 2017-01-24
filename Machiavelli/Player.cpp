#include "Player.h"

Player::Player(const std::string name, Socket& socket) : _name{ name }, _socket{ socket }
{
	_ready = false;
	AddGold(2);
}

const std::string Player::GetName() const
{
	return _name;
}

const int Player::GetGold() const
{
	return _current_gold;
}

const bool Player::IsKing() const
{
	return _is_king;
}

const std::vector<std::shared_ptr<CharacterCard>> Player::GetCharacterCards() const
{
	return _character_cards;
}

const std::vector<std::shared_ptr<BuildingCard>> Player::GetBuildingCards() const
{
	return _building_cards;
}

const std::vector<std::shared_ptr<BuildingCard>> Player::GetPlayedBuildingCards() const
{
	return _played_building_cards;
}

void Player::AddGold(const int amount)
{
	_current_gold = _current_gold + amount;
}

void Player::AddCharacterCard(std::shared_ptr<CharacterCard> card)
{
	_character_cards.push_back(card);
}

void Player::RemoveGold(const int amount)
{
	_current_gold = _current_gold - amount;
}

void Player::SetIsKing(const bool isKing)
{
	_is_king = isKing;
}

void Player::SetReady(const bool status)
{
	_ready = status;
}

void Player::SendMessageToCLient(std::string message)
{
	_socket << message;
}
