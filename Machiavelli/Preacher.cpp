#include "Preacher.h"
#include "GameController.h"

Preacher::Preacher(const int ID, const std::string name, const CharacterType type) : CharacterCard(ID, name, type)
{
}

Preacher::~Preacher()
{
}

void Preacher::Execute(std::shared_ptr<GameController> game_controller)
{
}
