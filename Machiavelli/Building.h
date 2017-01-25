#pragma once
#include <string>
#include <iostream>
#include <istream>
#include "CardTypes.h"

class BuildingCard
{
public:
	BuildingCard(std::string name, int cost, CardColor color);
	BuildingCard(std::string name, int cost, CardColor color, std::string description);
	BuildingCard(std::string name, int cost, std::string color);
	BuildingCard();
	const std::string GetName() const;
	const std::string GetDescription() const;
	const int GetPrice() const;
	const CardColor GetCardColor() const;

	friend std::istream &operator >> (std::istream  &input, BuildingCard &card);
	~BuildingCard();
private:
	 int _cost;
	 std::string _name;
	 std::string _description;
	 CardColor _color;
};