#pragma once

#include <string>
#include <map>
#include <memory>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string> 
#include "Building.h"
#include "Character.h"

class CardFactory
{
public:
	typedef std::map<CardType, std::string> Cards;
	static Cards _mapResources;
	const std::vector<std::shared_ptr<BuildingCard>> GetBuildingCards() const { return _buildingCards; }
	const std::vector<std::shared_ptr<CharacterCard>> GetCharacterCards() const { return _characterCards; }

	CardFactory();
	~CardFactory();
private:
	void Init();
	std::vector<std::shared_ptr<BuildingCard>> _buildingCards;
	std::vector<std::shared_ptr<CharacterCard>> _characterCards;
	std::map<std::string, CharacterType> _characterIdentifiers;
	std::map<std::string, CardColor> _colorIdentifiers;

	std::shared_ptr<CharacterCard> CreateCharacter(std::string type, int id);
	std::shared_ptr<BuildingCard> CreateBuilding(std::string name, int goldCost, CardColor color, std::string description);

	static Cards init_resource_map() {
		Cards resources;
		resources[CardType::Building] = "../Resources/buildings.csv";
		resources[CardType::Character] = "../Resources/characters.csv";
		return resources;
	}

};
