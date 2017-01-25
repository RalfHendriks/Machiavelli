#include "Preacher.h"
#include "GameController.h"

Preacher::Preacher(const int ID, const std::string name, const CharacterType type) : CharacterCard(ID, name, type)
{
}

Preacher::~Preacher()
{
}

void Preacher::Execute(GameController & game_controller)
{
	auto current_player = game_controller.GetCurrentPlayerTurn();

	current_player->SendMessageToCLient("You have executed the Preacher card. \r\n");

	_executed = true;
}
