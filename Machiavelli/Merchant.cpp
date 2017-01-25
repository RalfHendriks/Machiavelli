#include "Merchant.h"
#include "GameController.h"

Merchant::Merchant(const int ID, const CharacterType type) : CharacterCard(ID, type)
{

}

Merchant::Merchant()
{
}

Merchant::~Merchant()
{
}

void Merchant::Execute(GameController & game_controller)
{
	auto current_player = game_controller.GetCurrentPlayerTurn();
	current_player->SendMessageToCLient("You have executed the Merchant card. \r\n");

	int gold_earned{ 1 };
	// Loop through al played building cards.. and check if they are green
	for (int i = 0; i < current_player->GetPlayedBuildingCards().size(); i++) {
		if (current_player->GetPlayedBuildingCards().at(i)->GetCardColor() == CardColor::Green)
			gold_earned++;
	}

	game_controller.GetCurrentPlayerTurn()->AddGold(gold_earned);
	current_player->SendMessageToCLient("You have earned " + std::to_string(gold_earned) + " gold with the Merchant card (each for a green played building + 1 for Merchant card). \r\n");

	_executed = true;
}
