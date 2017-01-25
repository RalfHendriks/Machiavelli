#include "Building.h"

BuildingCard::BuildingCard(std::string name, int cost) : _name{ name }, _cost{ cost }
{}

BuildingCard::BuildingCard(std::string name, int cost, CardColor color) : _name{ name }, _cost{ cost }, _color{color}
{}

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
	input >> card._name >> card._cost >> card._color;
	return input;
}

std::ostream & operator<<(std::ostream & output, BuildingCard & card)
{
	output << "[Name] " << card._name << "\r\n";
	output << "[Cost] " << card._cost << "\r\n";
	output << "[Color] " << card._color << "\r\n";
	output << "\r\n";
	return output;
}
