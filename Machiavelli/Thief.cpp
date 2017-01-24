#include "Thief.h"
#include "GameController.h"

Thief::Thief(const int ID, const std::string name, const CharacterType type) : CharacterCard(ID, name, type)
{

}

Thief::~Thief()
{
}

void Thief::Execute(std::shared_ptr<GameController> game_controller)
{
}
