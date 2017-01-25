#include "Condottiere.h"
#include "GameController.h"

Condottiere::Condottiere(const int ID, const std::string name, const CharacterType type) : CharacterCard(ID, name, type)
{
}

Condottiere::~Condottiere()
{
}

void Condottiere::Execute(GameController & game_controller)
{
	auto current_player = game_controller.GetCurrentPlayerTurn();

	current_player->SendMessageToCLient("You have executed the Condottiere card. \r\n");

	_executed = true;
}
