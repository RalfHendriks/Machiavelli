#include "Player.h"

Player::Player(const std::string name) : _name{name}
{
}

const std::string Player::GetName() const
{
	return _name;
}

void Player::AddGold(const int amount)
{
	_current_gold = _current_gold + amount;
}

void Player::RemoveGold(const int amount)
{
	_current_gold = _current_gold - amount;
}

void Player::SetIsKing(const bool isKing)
{
	_isKing = isKing;
}
