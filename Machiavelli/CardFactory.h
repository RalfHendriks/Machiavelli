#pragma once

#include <string>
#include <map>
#include <memory>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Building.h"
#include "Character.h"

class CardFactory
{
public:
	typedef std::map<CardType, std::string> Cards;
	static Cards _mapResources;
	std::shared_ptr<CharacterCard>  CreateCharacter(std::string type, int id);
	std::shared_ptr<BuildingCard>  CreateBuilding(std::string name,int goldCost, CardColor color, std::string description);
	CardFactory();
	~CardFactory();
private:
	void Init();
	std::vector<std::shared_ptr<BuildingCard>> _buildingCards;
	std::vector<std::shared_ptr<CharacterCard>> _characterCards;
	std::map<std::string, CharacterType> _characterIdentifiers;
	static Cards init_resource_map() {
		Cards resources;
		resources[CardType::Building] = "../Resources/buildings.csv";
		resources[CardType::Character] = "../Resources/characters.csv";
		return resources;
	}

};
