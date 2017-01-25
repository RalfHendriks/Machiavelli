#include "Preacher.h"
#include "GameController.h"

Preacher::Preacher(const int ID, const CharacterType type) : CharacterCard(ID, type)
{
}

Preacher::Preacher()
{
}

Preacher::~Preacher()
{
}

void Preacher::Execute(GameController & game_controller)
{
	auto current_player = game_controller.GetCurrentPlayerTurn();
	current_player->SendMessageToCLient("You have executed the Preacher card. \r\n");

	int gold_earned{ 0 };
	// Loop through al played building cards.. and check if they are yellow
	for (int i = 0; i < current_player->GetPlayedBuildingCards().size(); i++) {
		if (current_player->GetPlayedBuildingCards().at(i)->GetCardColor() == CardColor::Blue)
			gold_earned++;
	}

	game_controller.GetCurrentPlayerTurn()->AddGold(gold_earned);
	current_player->SendMessageToCLient("You have earned " + std::to_string(gold_earned) + " gold with the Preacher card (each for a blue played building). \r\n");

	_executed = true;
}
