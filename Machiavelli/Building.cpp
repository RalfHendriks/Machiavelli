#include "Building.h"

BuildingCard::BuildingCard(std::string name, int cost, CardColor color) : _name{ name }, _cost{ cost }, _color{color}
{}

BuildingCard::BuildingCard(std::string name, int cost, CardColor color, std::string description) : _name{ name }, _cost{ cost }, _color{ color }, _description{description}
{}

BuildingCard::~BuildingCard()
{
}
