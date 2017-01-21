#pragma once

#include <string>
#include <map>
#include <memory>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Building.h"

class CardFactory
{
public:
	typedef std::map<CardType, std::string> Cards;
	static Cards _mapResources;
	CardFactory();
	~CardFactory();
private:
	void Init();
	std::vector<std::shared_ptr<BuildingCard>> _buildingCards;
	static Cards init_resource_map() {
		Cards resources;
		resources[CardType::building] = "../Resources/buildings.csv";
		resources[CardType::character] = "../Resources/characters.csv";
		return resources;
	}

};
