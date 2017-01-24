#include "Murderer.h"
#include "GameController.h"

Murderer::Murderer(const int ID, const std::string name, const CharacterType type) : CharacterCard(ID, name, type)
{
}

Murderer::~Murderer()
{
}

void Murderer::Execute(GameController & game_controller)
{
	auto current_player = game_controller.GetCurrentPlayerTurn();

	current_player->SendMessageToCLient("You have executed the Murderer card. \r\n");
	current_player->SendMessageToCLient("Please choose which character you want to murder: \r\n");

	std::string compare_input{ current_player->GetPlayerInput() };
	bool selected{ false };

	while (!selected) {
		if (current_player->GetPlayerInput() != compare_input) {
			compare_input = current_player->GetPlayerInput();

			current_player->SendMessageToCLient("You have murdered " + compare_input);
		}
	}

}
