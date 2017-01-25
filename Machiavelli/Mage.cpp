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
	auto current_player = game_controller.GetCurrentPlayerTurn();

	current_player->SendMessageToCLient("You have executed the Mage card. \r\n");

	_executed = true;
}
