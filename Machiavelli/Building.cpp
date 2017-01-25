#include "Building.h"

BuildingCard::BuildingCard(std::string name, int cost, CardColor color) : _name{ name }, _cost{ cost }, _color{color}
{}

BuildingCard::BuildingCard(std::string name, int cost, CardColor color, std::string description) : _name{ name }, _cost{ cost }, _color{ color }, _description{description}
{}

BuildingCard::BuildingCard(std::string name, int cost) : _name{ name }, _cost{ cost }, _color{CardColor::Yellow}
{
}

BuildingCard::BuildingCard()
{

}

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

std::istream & operator >> (std::istream & input, BuildingCard & card)
{
	input >> card._name;
	input >> card._cost;
	return input;
}
