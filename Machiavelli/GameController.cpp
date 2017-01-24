#include "GameController.h"
#include "CardFactory.h"
#include <random>
#include <time.h>
#include <thread>

GameController::GameController()
{
	_factory = std::make_shared<CardFactory>(CardFactory());
	_game_started = false;
	_skip_character_select = false;
	_current_state = GameState::WaitingForPlayers;
	srand(time(NULL));
}

void GameController::StartGame()
{
	_game_started = true;
	while (_game_started)
	{
		_current_player_turn = _players[0];
		_current_player_turn->SetIsKing(true);
		ResetCards();
		StartCharacterSelect();
		PlayGame();
	}

}

void GameController::ResetCards()
{
	_character_cards = _factory->GetCharacterCards();
	_building_cards = _factory->GetBuildingCards();
}

void GameController::PlayGame()
{
	int currentCharacter = 0;
	while (currentCharacter < 8)
	{

	}

}

void GameController::OutRemainingCharacterCards()
{
	std::string out = "";
	int identifier = 1;
	for (const auto &card : _character_cards) {
		out += "[" + std::to_string(identifier) + "] " + card->GetName() + "\r\n";
		identifier++;
	}
	_current_player_turn->SendMessageToCLient(out);
}

bool GameController::CheckForAllPlayersReady()
{
	bool allReady = true;
	for (const auto &p : _players) {
		if (!p->IsReady()) {
			allReady = false;
			break;
		}
	}
	return allReady;
}

void GameController::RemoveCharacterCard(const int index)
{
	_character_cards.erase(std::remove(_character_cards.begin(), _character_cards.end(), _character_cards[index]), _character_cards.end());
}

void GameController::AddPlayer(std::shared_ptr<Player> player)
{
	_players.push_back(player);
}

void GameController::RemovePlayer(std::shared_ptr<Player> player)
{
	_players.erase(std::remove(_players.begin(), _players.end(), player), _players.end());
}

void GameController::HandlePlayerInput(std::shared_ptr<Player> player, std::string playerInput)
{
	
	std::cout << player->GetName() << ": " << playerInput << "\r\n";
	if (!_game_started) {
		if (playerInput == "join") {
			if (_players.size() == 2) {
				_players[0]->SendMessageToCLient("Player: " + player->GetName() + " has joined. \r\n");
				for (const auto &p : _players) {
					p->SendMessageToCLient("Needed amount of players reached. Type ready to begin. \r\n> ");
				}
			}
		}
		else if (playerInput == "skipcharacterselect") _skip_character_select = true;
		else if (playerInput == "quit") _players[0]->SendMessageToCLient("Player " + player->GetName() + " has quit.\r\n>");
		else if (playerInput == "ready") {
			player->SetReady(true);
			std::string message = "Player: " + player->GetName() + " is ready. \r\n>";
			_players[0] == player ? _players[1]->SendMessageToCLient(message) : _players[0]->SendMessageToCLient(message);

			if (_players.size() == 2 && CheckForAllPlayersReady()) {
				for (const auto &p : _players) {
					p->SendMessageToCLient("All players are ready. Let the best one win!\r\n");
				}

				std::thread g{ &GameController::StartGame, this };
				g.detach();
			}
		}
		else player->SendMessageToCLient("Unkown command please try a valid command! \r\n>");
	}
	else {
		if (player == _current_player_turn) {
			player->SetLastPLayerInput(playerInput);
		}
		else
		{
			player->SendMessageToCLient("It's not your turn please wait for your turn! \r\n>");
		}
	}
}

void GameController::EndTurn()
{
	_current_player_turn->SendMessageToCLient("Your turn has ended, switching turns! \r\n");
	_current_player_turn = _current_player_turn == _players[0] ? _players[1] : _players[0];
	_current_player_turn->SendMessageToCLient("Opponents turn has ended it's your turn! \r\n");
}

void GameController::StartCharacterSelect()
{
	rand();
	if (!_skip_character_select) {
		int r = 3;
		while (r == 3)
		{
			r = rand() % _character_cards.size();
		}
		RemoveCharacterCard(r);
		while (_character_cards.size() > 0)
		{
			OutRemainingCharacterCards();
			_current_player_turn->SendMessageToCLient("Select a character card!\r\n> ");
			int cardIndex = CharacterCardSelect();
			_current_player_turn->AddCharacterCard(_character_cards[cardIndex]);
			RemoveCharacterCard(cardIndex);

			if (_character_cards.size() != 6) {
				OutRemainingCharacterCards();
				_current_player_turn->SendMessageToCLient("Select a character card that will be removed!\r\n> ");
				cardIndex = CharacterCardSelect();
				RemoveCharacterCard(cardIndex);
			}
			EndTurn();
		}
	}
	else
	{
		for (size_t i = 0; i < 4; i++)
		{
			int r = rand() % _character_cards.size();
			_players[(i/2)]->AddCharacterCard(_character_cards[r]);
			RemoveCharacterCard(r);
		}
	}
}

int GameController::CharacterCardSelect()
{
	bool validInput = false;
	int index = 0;
	std::string input = _current_player_turn->GetPlayerInput();
	while (!validInput) {
		if (input != _current_player_turn->GetPlayerInput())
		{
			input = _current_player_turn->GetPlayerInput();
			try
			{
				index = std::stoi(input) + 1;
				if (index <= _character_cards.size())
				{
					auto c = _character_cards[index];
					validInput = true;
				}
				else
					_current_player_turn->SendMessageToCLient("Invalid selection try again!\r\n> ");
			}
			catch (const std::exception& e)
			{
				std::cout << e.what();
				_current_player_turn->SendMessageToCLient("Invalid input!\r\n> ");
			}
		}
	}
	return index;
}
