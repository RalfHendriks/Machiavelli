#include "Condottiere.h"
#include "GameController.h"

Condottiere::Condottiere(const int ID, const CharacterType type) : CharacterCard(ID, type)
{
}

Condottiere::Condottiere()
{
}

Condottiere::~Condottiere()
{
}

void Condottiere::Execute(GameController & game_controller)
{
	auto current_player = game_controller.GetCurrentPlayerTurn();
	auto opponent_player = game_controller.GetOpponent();
	current_player->SendMessageToCLient("You have executed the Condottiere card. \r\n");

	// Check if opponent is preacher. If so, you cant steal cards
	bool is_preacher{ false };
	for (int i = 0; i < opponent_player->GetCharacterCards().size(); i++) {
		if (opponent_player->GetCharacterCards().at(i)->GetType() == CharacterType::Preacher)
			is_preacher = true;
	}

	if (is_preacher) {
		current_player->SendMessageToCLient("Your opponent has a Preacher character card. You can't remove a building card from him. \r\n");
	}
	else if (opponent_player->GetPlayedBuildingCards().size() >= 8 || opponent_player->GetPlayedBuildingCards().size() == 0) {
		current_player->SendMessageToCLient("Your opponent has 0 OR 8 or more building cards. You can't remove a building card from him. \r\n");
	}
	else {
		current_player->SendMessageToCLient("Please select a building card you want to remove from your opponent: \r\n");

		std::string compare_input{ current_player->GetPlayerInput() };
		bool selected{ false };

		while (!selected && !game_controller.game_ended) {
			if (current_player->GetPlayerInput() != compare_input) {
				compare_input = current_player->GetPlayerInput();

				if (std::stoi(compare_input) <= 0 || std::stoi(compare_input) > opponent_player->GetPlayedBuildingCards().size()) {
					current_player->SendMessageToCLient("You have selected a card out of range. Please select another one. \r\n");
				}
				else {

					if (current_player->GetGold() < opponent_player->GetPlayedBuildingCards()[std::stoi(compare_input) - 1]->GetPrice() - 1) {
						current_player->SendMessageToCLient("You have not enough gold to remove this card from your opponent. \r\n");
					} else {
						current_player->AddGold(-(opponent_player->GetPlayedBuildingCards()[std::stoi(compare_input) - 1]->GetPrice() - 1));
						opponent_player->RemovePlayedBuildingCard(std::stoi(compare_input));
						selected = true;
					}
				}
			}
		}
	}

	int gold_earned{ 0 };
	// Loop through al played building cards.. and check if they are red
	for (int i = 0; i < current_player->GetPlayedBuildingCards().size(); i++) {
		if (current_player->GetPlayedBuildingCards().at(i)->GetCardColor() == CardColor::Red)
			gold_earned++;
	}

	game_controller.GetCurrentPlayerTurn()->AddGold(gold_earned);
	current_player->SendMessageToCLient("You have earned " + std::to_string(gold_earned) + " gold with the Condottiere card (each for a red played building). \r\n");

	_executed = true;
}

void Condottiere::PrintCharacterCards(GameController & game_controller) const
{
	auto current_player = game_controller.GetCurrentPlayerTurn();

	std::string out = "";
	int identifier = 1;
	for (const auto &card : current_player->GetPlayedBuildingCards()) {
		out += "[" + std::to_string(identifier) + "] " + card->GetName() + "\r\n";
		identifier++;
	}

	current_player->SendMessageToCLient(out);
}