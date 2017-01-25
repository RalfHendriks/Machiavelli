#include "Thief.h"
#include "GameController.h"

Thief::Thief(const int ID, const std::string name, const CharacterType type) : CharacterCard(ID, name, type)
{

}

Thief::~Thief()
{
}

void Thief::Execute(GameController & game_controller)
{
	auto current_player = game_controller.GetCurrentPlayerTurn();

	current_player->SendMessageToCLient("You have executed the Thief card. \r\n");
	current_player->SendMessageToCLient("Please choose which character you want to rob: \r\n");

	std::string compare_input{ current_player->GetPlayerInput() };
	bool selected{ false };

	PrintCharacterCards(game_controller);

	while (!selected) {
		if (current_player->GetPlayerInput() != compare_input) {
			compare_input = current_player->GetPlayerInput();

			if (std::stoi(compare_input) <= 0 || std::stoi(compare_input) >= game_controller.GetCardFactory()->GetCharacterCards().size() - 1) {
				current_player->SendMessageToCLient("You have selected a card out of range. Please select another one. \r\n");
			}
			else {
				CharacterType character_type = GetCharacterType(game_controller, std::stoi(compare_input));

				// Check if character is not murdered
				if (character_type == game_controller.GetMurderedCard()) {
					current_player->SendMessageToCLient("You have selected a character card that is murdered. Please select another one. \r\n");
				} else {
					game_controller.SetRobbedCard(character_type);
					selected = true;
				}
			}
		}
	}
	_executed = true;
}

void Thief::PrintCharacterCards(GameController & game_controller) const
{
	auto current_player = game_controller.GetCurrentPlayerTurn();
	auto factory = game_controller.GetCardFactory();

	std::string out = "";
	int identifier = 1;
	for (const auto &card : factory->GetCharacterCards()) {
		if (card->GetID() != 1 && card->GetID() != 2) {
			out += "[" + std::to_string(identifier) + "] " + card->GetName() + "\r\n";
			identifier++;
		}
	}

	current_player->SendMessageToCLient(out);
}

const CharacterType Thief::GetCharacterType(GameController & game_controller, const int index)
{
	auto factory = game_controller.GetCardFactory();
	return factory->GetCharacterCards().at(index + 1)->GetType();
}