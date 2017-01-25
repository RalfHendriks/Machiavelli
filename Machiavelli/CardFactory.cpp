#include "CardFactory.h"
#include "Thief.h"
#include "King.h"
#include "Condottiere.h"
#include "ConstructionMaster.h"
#include "Mage.h"
#include "Merchant.h"
#include "Murderer.h"
#include "Preacher.h"

CardFactory::Cards CardFactory::_mapResources = init_resource_map();

CardFactory::CardFactory()
{
	_characterIdentifiers = std::map<std::string, CharacterType>();
	_characterIdentifiers.insert(std::make_pair(CharacterTypeToString(CharacterType::Murderer), CharacterType::Murderer));
	_characterIdentifiers.insert(std::make_pair(CharacterTypeToString(CharacterType::Thief), CharacterType::Thief));
	_characterIdentifiers.insert(std::make_pair(CharacterTypeToString(CharacterType::Mage), CharacterType::Mage));
	_characterIdentifiers.insert(std::make_pair(CharacterTypeToString(CharacterType::King),CharacterType::King));
	_characterIdentifiers.insert(std::make_pair(CharacterTypeToString(CharacterType::Preacher), CharacterType::Preacher));
	_characterIdentifiers.insert(std::make_pair(CharacterTypeToString(CharacterType::Merchant), CharacterType::Merchant));
	_characterIdentifiers.insert(std::make_pair(CharacterTypeToString(CharacterType::ConstructionMaster), CharacterType::ConstructionMaster));
	_characterIdentifiers.insert(std::make_pair(CharacterTypeToString(CharacterType::Condottiere), CharacterType::Condottiere));

	_colorIdentifiers = std::map<std::string, CardColor>();
	_colorIdentifiers.insert(std::make_pair(ColorToString(CardColor::Blue), CardColor::Blue));
	_colorIdentifiers.insert(std::make_pair(ColorToString(CardColor::Green), CardColor::Green));
	_colorIdentifiers.insert(std::make_pair(ColorToString(CardColor::Lila), CardColor::Lila));
	_colorIdentifiers.insert(std::make_pair(ColorToString(CardColor::Red), CardColor::Red));
	_colorIdentifiers.insert(std::make_pair(ColorToString(CardColor::White), CardColor::White));
	_colorIdentifiers.insert(std::make_pair(ColorToString(CardColor::Yellow), CardColor::Yellow));
	Init();
}

CardFactory::~CardFactory()
{
}

std::shared_ptr<CharacterCard> CardFactory::CreateCharacter(std::string type, int id)
{
	auto charType = _characterIdentifiers.find(type)->second;
	switch (charType) {
	case CharacterType::Thief:
		return std::make_shared<Thief>(Thief(id, CharacterTypeToString(CharacterType::Thief), charType));
	case CharacterType::Condottiere:
		return std::make_shared<Condottiere>(Condottiere(id, CharacterTypeToString(CharacterType::Condottiere), charType));
	case CharacterType::ConstructionMaster:
		return std::make_shared<ConstructionMaster>(ConstructionMaster(id, CharacterTypeToString(CharacterType::ConstructionMaster), charType));
	case CharacterType::King:
		return std::make_shared<King>(King(id, CharacterTypeToString(CharacterType::King), charType));
	case CharacterType::Mage:
		return std::make_shared<Mage>(Mage(id, CharacterTypeToString(CharacterType::Mage), charType));
	case CharacterType::Merchant:
		return std::make_shared<Merchant>(Merchant(id, CharacterTypeToString(CharacterType::Merchant), charType));
	case CharacterType::Murderer:
		return std::make_shared<Murderer>(Murderer(id, CharacterTypeToString(CharacterType::Murderer), charType));
	case CharacterType::Preacher:
		return std::make_shared<Preacher>(Preacher(id, CharacterTypeToString(CharacterType::Preacher), charType));
	default:
		return nullptr;
	}
}

std::shared_ptr<BuildingCard> CardFactory::CreateBuilding(std::string name, int goldCost, CardColor color, std::string description)
{
	return std::make_shared<BuildingCard>(BuildingCard(name,goldCost,color,description));
}

void CardFactory::Init()
{
	
	for (auto const& item: _mapResources)
	{
		std::ifstream in(item.second);
		while (in)
		{
			std::string s;
			if (!std::getline(in, s)) break;

			std::istringstream ss(s);

			while (ss)
			{
				std::string s;
				if (!std::getline(ss, s)) break;


				std::vector<std::string> record;
				std::stringstream ss(s);
				std::string selected;
				/*BuildingCard card;
				ss >> card;*/
				while (std::getline(ss, selected, ';')) {
					record.push_back(selected);
				}

				if (item.first == CardType::Building) {
					std::string color = record[2];
					std::transform(color.begin(), color.end(), color.begin(), ::tolower);
					record.size() == 3 ? _buildingCards.push_back(CreateBuilding(record[0], std::stoi(record[1]), _colorIdentifiers.find(color)->second, "")) : CreateBuilding(record[0], std::stoi(record[1]), _colorIdentifiers.find(color)->second, record[3]);
				}
				if (item.first == CardType::Character) {
					_characterCards.push_back(CreateCharacter(record[1], std::stoi(record[0])));
				}
			}
		}
	}
}
