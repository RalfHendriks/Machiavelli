#pragma once
#include <string>
#include "CardTypes.h"

class BuildingCard
{
public:
	BuildingCard(std::string name, int cost, CardColor color);
	BuildingCard(std::string name, int cost, CardColor color, std::string description);

	const std::string GetName() const;
	const std::string GetDescription() const;
	const int GetPrice() const;
	const CardColor GetCardColor() const;

	~BuildingCard();
private:
	const int _cost;
	const std::string _name;
	const std::string _description;
	const CardColor _color;
};