#include "CardFactory.h"
#include "Thief.h"

CardFactory::Cards CardFactory::_mapResources = init_resource_map();

std::shared_ptr<CharacterCard> CardFactory::CreateCharacter(std::string type, int id)
{
	auto charType = _characterIdentifiers.find(type)->second;
	switch (charType) {
	case CharacterType::Thief:
		return std::make_shared<Thief>(Thief(id, charType));
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
	_characterIdentifiers.insert(std::make_pair("NONE", CharacterType::NONE));
	_characterIdentifiers.insert(std::make_pair("Moordenaar", CharacterType::Murderer));
	_characterIdentifiers.insert(std::make_pair("Dief", CharacterType::Thief));
	_characterIdentifiers.insert(std::make_pair("Magiër", CharacterType::Mage));
	_characterIdentifiers.insert(std::make_pair("Koning", CharacterType::King));
	_characterIdentifiers.insert(std::make_pair("Prediker", CharacterType::Preacher));
	_characterIdentifiers.insert(std::make_pair("Koopman", CharacterType::Merchant));
	_characterIdentifiers.insert(std::make_pair("Bouwmeester", CharacterType::ContrustionMaster));
	_characterIdentifiers.insert(std::make_pair("Condottiere", CharacterType::Condottiere));
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

				}
				if (item.first == CardType::Character) {
					auto character = CreateCharacter(record[1], std::stoi(record[0]));
				}
			}
		}
	}
}
