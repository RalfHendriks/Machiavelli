#pragma once
#include <string>
#include "CardTypes.h"

class BuildingCard
{
public:
	BuildingCard(std::string name, int cost, CardColor color);
	BuildingCard(std::string name, int cost, CardColor color, std::string description);
	~BuildingCard();
private:
	int _cost;
	std::string _name;
	std::string _description;
	CardColor _color;
};