#include "Murderer.h"
#include "GameController.h"

Murderer::Murderer(const int ID, const std::string name, const CharacterType type) : CharacterCard(ID, name, type)
{
}

Murderer::~Murderer()
{
}

void Murderer::Execute(GameController & game_controller)
{
	//bool test = game_controller.HasGameStarted();
}
