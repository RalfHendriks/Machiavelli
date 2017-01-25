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

std::shared_ptr<CharacterCard> CardFactory::CreateCharacter(std::string type, std::stringstream s)
{
	return nullptr;
}

std::shared_ptr<BuildingCard> CardFactory::CreateBuilding(std::string name, int goldCost, CardColor color, std::string description)
{
	return std::make_shared<BuildingCard>(BuildingCard(name,goldCost,color));
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
				std::stringstream ss2;
				std::string selected;

				while (std::getline(ss, selected, ';')) {
					ss2 << selected << ' ';
					record.push_back(selected);
				}


				if (item.first == CardType::Building) {
					BuildingCard card;
					ss2 >> card;
					_buildingCards.push_back(std::make_shared<BuildingCard>(card));
					std::cout << *_buildingCards.at(_buildingCards.size() - 1);

					/*std::string color = record[2];
					std::transform(color.begin(), color.end(), color.begin(), ::tolower);
					record.size() == 3 ? _buildingCards.push_back(CreateBuilding(record[0], std::stoi(record[1]), _colorIdentifiers.find(color)->second, "")) : CreateBuilding(record[0], std::stoi(record[1]), _colorIdentifiers.find(color)->second, record[3]);
					*/
				}
				if (item.first == CardType::Character) {

					auto charType = _characterIdentifiers.find(record[1])->second;
					switch (charType) {
						case CharacterType::Thief:
						{
							Thief thief;
							ss2 >> thief;
							_characterCards.push_back(std::make_shared<Thief>(thief));
							break;
						}
						case CharacterType::Condottiere:
						{
							Condottiere condottiere;
							ss2 >> condottiere;
							_characterCards.push_back(std::make_shared<Condottiere>(condottiere));
							break;
						}
						case CharacterType::ConstructionMaster:
						{
							ConstructionMaster constructionMaster;
							ss2 >> constructionMaster;
							_characterCards.push_back(std::make_shared<ConstructionMaster>(constructionMaster));
							break;
						}
						case CharacterType::King:
						{
							King king;
							ss2 >> king;
							_characterCards.push_back(std::make_shared<King>(king));
							break;
						}
						case CharacterType::Mage:
						{
							Mage mage;
							ss2 >> mage;
							_characterCards.push_back(std::make_shared<Mage>(mage));
							break;
						}
						case CharacterType::Merchant:
						{
							Merchant merchant;
							ss2 >> merchant;
							_characterCards.push_back(std::make_shared<Merchant>(merchant));
							break;
						}
						case CharacterType::Murderer:
						{
							Murderer murderer;
							ss2 >> murderer;
							_characterCards.push_back(std::make_shared<Murderer>(murderer));
							break;
						}
						case CharacterType::Preacher:
						{
							Preacher preacher;
							ss2 >> preacher;
							_characterCards.push_back(std::make_shared<Preacher>(preacher));
							break;
						}
					}
					std::cout << *_characterCards.at(_characterCards.size() - 1);
					/*std::shared_ptr<CharacterCard> character = CreateCharacter(record[1], ss2);
					_characterCards.push_back(character);
					//_characterCards.push_back(CreateCharacter(record[1], std::stoi(record[0])));*/
				}
			}
		}
	}
}
