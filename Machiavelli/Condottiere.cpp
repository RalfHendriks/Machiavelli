#include "Condottiere.h"
#include "GameController.h"

Condottiere::Condottiere(const int ID, const std::string name, const CharacterType type) : CharacterCard(ID, name, type)
{
}

Condottiere::~Condottiere()
{
}

void Condottiere::Execute(std::shared_ptr<GameController> game_controller)
{
}
