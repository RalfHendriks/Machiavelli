#include "ConstructionMaster.h"
#include "GameController.h"

ConstructionMaster::ConstructionMaster(const int ID, const std::string name, const CharacterType type) : CharacterCard(ID, name, type)
{
}

ConstructionMaster::~ConstructionMaster()
{
}

void ConstructionMaster::Execute(GameController & game_controller)
{
}
