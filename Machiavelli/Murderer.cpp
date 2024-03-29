#include "Murderer.h"
#include "GameController.h"
#include "CardFactory.h"

Murderer::Murderer(const int ID, const CharacterType type) : CharacterCard(ID, type)
{
}

Murderer::Murderer()
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

	PrintCharacterCards(game_controller);

	while (!selected && !game_controller.game_ended) {
		if (current_player->GetPlayerInput() != compare_input) {
			compare_input = current_player->GetPlayerInput();

			if (std::stoi(compare_input) <= 0 || std::stoi(compare_input) >= game_controller.GetCardFactory()->GetCharacterCards().size()) {
				current_player->SendMessageToCLient("You have selected a card out of range. Please choose again. \r\n");
			} else {
				CharacterType character_type = GetCharacterType(game_controller, std::stoi(compare_input));
				game_controller.SetMurderedCard(character_type);

				selected = true;
			}
		}
	}
	_executed = true;
}

void Murderer::PrintCharacterCards(GameController & game_controller) const
{
	auto current_player = game_controller.GetCurrentPlayerTurn();
	auto factory = game_controller.GetCardFactory();

	std::string out = "";
	int identifier = 1;
	for (const auto &card : factory->GetCharacterCards()) {
		if (card->GetID() != 1) {
			out += "[" + std::to_string(identifier) + "] " + card->GetName() + "\r\n";
			identifier++;
		}
	}

	current_player->SendMessageToCLient(out);
}

const CharacterType Murderer::GetCharacterType(GameController & game_controller, const int index)
{
	auto factory = game_controller.GetCardFactory();
	return factory->GetCharacterCards().at(index)->GetType();
}

