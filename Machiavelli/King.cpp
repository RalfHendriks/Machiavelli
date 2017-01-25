#include "King.h"
#include "GameController.h"

King::King(const int ID, const CharacterType type) : CharacterCard(ID, type){
}

King::King()
{
}

King::~King()
{
}

void King::Execute(GameController & game_controller)
{
	auto current_player = game_controller.GetCurrentPlayerTurn();
	current_player->SendMessageToCLient("You have executed the King card. \r\n");

	int gold_earned{ 0 };
	// Loop through al played building cards.. and check if they are yellow
	for (int i = 0; i < current_player->GetPlayedBuildingCards().size(); i++) {
		if (current_player->GetPlayedBuildingCards().at(i)->GetCardColor() == CardColor::Yellow)
			gold_earned++;
	}

	game_controller.GetCurrentPlayerTurn()->AddGold(gold_earned);
	current_player->SendMessageToCLient("You have earned " + std::to_string(gold_earned) + " gold with the King card (each for a yellow played building). \r\n");

	_executed = true;
}
