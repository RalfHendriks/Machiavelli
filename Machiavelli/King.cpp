#include "King.h"
#include "GameController.h"

King::King(const int ID, const std::string name, const CharacterType type) : CharacterCard(ID, name, type)
{
}

King::~King()
{
}

void King::Execute(GameController & game_controller)
{
}
