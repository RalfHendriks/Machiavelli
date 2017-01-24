#include "Murderer.h"
#include "GameController.h"

Murderer::Murderer(const int ID, const std::string name, const CharacterType type) : CharacterCard(ID, name, type)
{
}

Murderer::~Murderer()
{
}

void Murderer::Execute(std::shared_ptr<GameController> game_controller)
{
	auto current_player = game_controller->GetCurrentPlayerTurn();

	current_player->SendMessageToCLient("You executed the Murderer card. \n");
	current_player->SendMessageToCLient("Please select the character you want to murder:");

	std::string compare_input = current_player->GetPlayerInput();
	bool selected = false;
	while (!selected) {

		if (current_player->GetPlayerInput() != compare_input) {
			compare_input = current_player->GetPlayerInput(); // Set new input

			current_player->SendMessageToCLient("You have murdered " + compare_input);
		}
	}
}
