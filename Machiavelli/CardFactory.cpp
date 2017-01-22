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

std::shared_ptr<CharacterCard> CardFactory::CreateCharacter(std::string type, int id)
{
	auto charType = _characterIdentifiers.find(type)->second;
	switch (charType) {
	case CharacterType::Thief:
		return std::make_shared<Thief>(Thief(id, charType));
	case CharacterType::Condottiere:
		return std::make_shared<Condottiere>(Condottiere(id, charType));
	case CharacterType::ConstructionMaster:
		return std::make_shared<ConstructionMaster>(ConstructionMaster(id, charType));
	case CharacterType::King:
		return std::make_shared<King>(King(id, charType));
	case CharacterType::Mage:
		return std::make_shared<Mage>(Mage(id, charType));
	case CharacterType::Merchant:
		return std::make_shared<Merchant>(Merchant(id, charType));
	case CharacterType::Murderer:
		return std::make_shared<Murderer>(Murderer(id, charType));
	case CharacterType::Preacher:
		return std::make_shared<Preacher>(Preacher(id, charType));
	default:
		return nullptr;
	}
}

std::shared_ptr<BuildingCard> CardFactory::CreateBuilding(std::string name, int goldCost, CardColor color, std::string description)
{
	return std::shared_ptr<BuildingCard>();
}

CardFactory::CardFactory()
{
	_characterIdentifiers = std::map<std::string, CharacterType>();
	_characterIdentifiers.insert(std::make_pair(CharacterTypeToString(CharacterType::NONE), CharacterType::NONE));
	_characterIdentifiers.insert(std::make_pair(CharacterTypeToString(CharacterType::Murderer), CharacterType::Murderer));
	_characterIdentifiers.insert(std::make_pair(CharacterTypeToString(CharacterType::Thief), CharacterType::Thief));
	_characterIdentifiers.insert(std::make_pair(CharacterTypeToString(CharacterType::Mage), CharacterType::Mage));
	_characterIdentifiers.insert(std::make_pair(CharacterTypeToString(CharacterType::King),CharacterType::King));
	_characterIdentifiers.insert(std::make_pair(CharacterTypeToString(CharacterType::Preacher), CharacterType::Preacher));
	_characterIdentifiers.insert(std::make_pair(CharacterTypeToString(CharacterType::Merchant), CharacterType::Merchant));
	_characterIdentifiers.insert(std::make_pair(CharacterTypeToString(CharacterType::ConstructionMaster), CharacterType::ConstructionMaster));
	_characterIdentifiers.insert(std::make_pair(CharacterTypeToString(CharacterType::Condottiere), CharacterType::Condottiere));
	Init();
}

CardFactory::~CardFactory()
{
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
				if (!std::getline(ss, s, ',')) break;


				std::vector<std::string> record;
				std::stringstream ss(s);
				std::string selected;
				while (std::getline(ss, selected, ';')) {
					record.push_back(selected);
				}

				if (item.first == CardType::Building) {
					//_buildingCards.push_back(CreateBuilding());
				}
				if (item.first == CardType::Character) {
					_characterCards.push_back(CreateCharacter(record[1], std::stoi(record[0])));
				}
			}
		}
	}
}
