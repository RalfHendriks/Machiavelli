#include "Player.h"
#include <map>

Player::Player(const std::string name, Socket& socket) : _name{ name }, _socket{ socket }
{
	_ready = false;
	_is_king = false;
	_first_to_eight = false;
	_current_gold = 10;
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

const bool Player::GetFirstToEight() const
{
	return _first_to_eight;
}

const int Player::GetBuildingPoints() const
{
	int score = 0;
	std::map<std::string, CardColor> colors = std::map<std::string, CardColor>();
	for (const auto &building : _played_building_cards)
	{
		score += building->GetPrice();
		std::string _currentColor = ColorToString(building->GetCardColor());
		if (colors.find(_currentColor) == colors.end()) {
			colors.insert(std::pair<std::string, CardColor>(_currentColor,building->GetCardColor()));
		}
	}
	score += colors.size() == 5 ? 3 : 0;
	score += _first_to_eight ? (_played_building_cards.size() == 8 ? 2 : 0) : 4;
	return score;
}

void Player::AddGold(const int amount)
{
	_current_gold = _current_gold + amount;
}

void Player::AddCharacterCard(std::shared_ptr<CharacterCard> card)
{
	_character_cards.push_back(card);
}

void Player::AddBuildingCard(std::shared_ptr<BuildingCard> card)
{
	_building_cards.push_back(card);
}

void Player::BuildBuildimg(int index)
{
	int i = 0;
	std::shared_ptr<BuildingCard> card = nullptr;
	for (const auto &building : _building_cards)
	{
		if (i == index-1) {
			card = building;
			break;
		}
		i++;
	}

	RemoveGold(card->GetPrice());
	_played_building_cards.push_back(card);
	RemoveBuildingCard(index);
}

void Player::RemoveBuildingCard(int index)
{
	_building_cards.erase(std::remove(_building_cards.begin(), _building_cards.end(), _building_cards[index-1]), _building_cards.end());
}

void Player::RemovePlayedBuildingCard(int index)
{
	_played_building_cards.erase(std::remove(_played_building_cards.begin(), _played_building_cards.end(), _played_building_cards[index - 1]), _played_building_cards.end());
}

void Player::DisplayBuildingCards()
{
	int i = 1;
	for (const auto &building : _building_cards)
	{
		SendMessageToCLient("["+std::to_string(i)+"]"+building->GetName() + " <" + ColorToString(building->GetCardColor()) + ", " + std::to_string(building->GetPrice()) + ">:\r\n");
		i++;
	}
}

void Player::DisplayBuildedBuildings()
{
}

std::shared_ptr<CharacterCard> Player::GetCharacterCard(CharacterType type)
{
	for (const auto &character : _character_cards)
	{
		if (character->GetType() == type) {
			return character;
		}
	}
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

void Player::DisplayBuildableBuildings()
{
	std::string out = "";
	int i = 1;
	for (const auto &building : _building_cards)
	{
		if (_current_gold >= building->GetPrice()) {
			out += "["+std::to_string(i)+"] " + building->GetName() + " price: "+ std::to_string(building->GetPrice()) + "\r\n";
		}
		i++;
	}
	SendMessageToCLient(out);
}

void Player::ResetForRound()
{
	_character_cards.clear();
}

bool Player::HasCharacter(CharacterType c)
{
	for (const auto &character : _character_cards)
	{
		if (character->GetType() == c) {
			return true;
		}
	}
	return false;
}

bool Player::CanBuildBuildings()
{
	for (const auto &building : _building_cards)
	{
		if (_current_gold >= building->GetPrice()) {
			return true;
		}
	}
	return false;
}
