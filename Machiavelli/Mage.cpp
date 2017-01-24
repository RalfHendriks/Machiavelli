#include "Mage.h"
#include "GameController.h"

Mage::Mage(const int ID, const std::string name, const CharacterType type) : CharacterCard(ID, name, type)
{
}

Mage::~Mage()
{
}

void Mage::Execute(GameController & game_controller)
{
}
