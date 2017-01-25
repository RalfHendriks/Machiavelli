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
	current_player->SendMessageToCLient("Please select one action of the list below: \r\n");

	std::string compare_input{ current_player->GetPlayerInput() };
	bool selected{ false };
	int choice{ 0 };
	int amount{ 0 };

	PrintOptions(game_controller);

	while (!selected) {
		if (current_player->GetPlayerInput() != compare_input) {
			compare_input = current_player->GetPlayerInput();

			// Check if choice is set, if not check if option is not out of range
			if (choice == 0 && std::stoi(compare_input) <= 0 || std::stoi(compare_input) >= 3) {
				current_player->SendMessageToCLient("You have selected an option out of range. Please choose again. \r\n");
			}
			else {
				// Set choice if not set already
				if(choice == 0)
					choice = std::stoi(compare_input);

				// Check which whoice we need to execute
				if (choice == 1) {
					OptionOne(game_controller);
					selected = true;
				}
				else if (choice == 2) {
					current_player->SendMessageToCLient("Please select an amount of building cards you want in return for your hand cards (min. 1 - max. "+ std::to_string(current_player->GetBuildingCards().size()) + "). \r\n");
				
					// No hand cards, so GO for option 1
					if (current_player->GetBuildingCards().size() == 0) {
						current_player->SendMessageToCLient("You have no cards in your hand. Option 1 automaticly selected for you. \r\n");
						OptionOne(game_controller);
						selected = true;
					}
					else {
						// Check if amount is within the min. and max. value
						if (std::stoi(compare_input) <= 0 || std::stoi(compare_input) > current_player->GetBuildingCards().size()) {
							current_player->SendMessageToCLient("You have selected an option out of range. Please choose again. \r\n");
						} else {
							// First remove all current hand building cards
							for (int i = 0; i < current_player->GetBuildingCards().size(); i++) {
								current_player->RemoveBuildingCard(i);
							}

							selected = true;
						}
					}
				}
			}
		}
	}
	_executed = true;
}

const void Mage::PrintOptions(GameController & game_controller) const
{
	auto current_player = game_controller.GetCurrentPlayerTurn();

	std::string out = "";
	out += "[1] I want to trade my hand cards with the hand cards of my opponent.\r\n";
	out += "[2] I want to remove an amount of my hand cards and get this of amount in building cards in return.\r\n";

	current_player->SendMessageToCLient(out);
}

void Mage::OptionOne(GameController & game_controller)
{
	auto current_player = game_controller.GetCurrentPlayerTurn();
	auto opponent_player = game_controller.GetOpponent();

	auto current_player_hand = current_player->GetBuildingCards();
	auto opponent_player_hand = opponent_player->GetBuildingCards();

	current_player->SetBuildingCards(opponent_player_hand);
	opponent_player->SetBuildingCards(current_player_hand);
}
