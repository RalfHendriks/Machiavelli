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
	auto current_player = game_controller.GetCurrentPlayerTurn();

	current_player->SendMessageToCLient("You have executed the Merchant card. \r\n");

	_executed = true;
}
