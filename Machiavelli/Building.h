#pragma once
#include <string>
#include <iostream>
#include <istream>
#include "CardTypes.h"

class BuildingCard
{
public:
	BuildingCard(std::string name, int cost);
	BuildingCard(std::string name, int cost, CardColor color);
	BuildingCard();
	const std::string GetName() const;
	const std::string GetDescription() const;
	const int GetPrice() const;
	const CardColor GetCardColor() const;

	friend std::istream &operator >> (std::istream  &input, BuildingCard &card);
	friend std::ostream &operator << (std::ostream  &output, BuildingCard &card);
	~BuildingCard();
private:
	 int _cost;
	 std::string _name;
	 std::string _description;
	 CardColor _color;
};