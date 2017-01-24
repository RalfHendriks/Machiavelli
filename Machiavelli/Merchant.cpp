#include "Merchant.h"
#include "GameController.h"

Merchant::Merchant(const int ID, const std::string name, const CharacterType type) : CharacterCard(ID, name, type)
{

}

Merchant::~Merchant()
{
}

void Merchant::Execute(GameController & game_controller)
{
}
