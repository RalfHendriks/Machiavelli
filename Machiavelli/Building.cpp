#include "Building.h"

BuildingCard::BuildingCard(std::string name, int cost, CardColor color) : _name{ name }, _cost{ cost }, _color{color}
{}

BuildingCard::BuildingCard(std::string name, int cost, CardColor color, std::string description) : _name{ name }, _cost{ cost }, _color{ color }, _description{description}
{}

const std::string BuildingCard::GetName() const
{
	return _name;
}

const std::string BuildingCard::GetDescription() const
{
	return _description;
}

const int BuildingCard::GetPrice() const
{
	return _cost;
}

const CardColor BuildingCard::GetCardColor() const
{
	return _color;
}

BuildingCard::~BuildingCard()
{
}