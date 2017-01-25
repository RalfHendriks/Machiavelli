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
	auto current_player = game_controller.GetCurrentPlayerTurn();

	current_player->SendMessageToCLient("You have executed the King card. \r\n");

	_executed = true;
}
