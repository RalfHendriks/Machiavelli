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
		_game_started = false;
	}
	StartCharacterSelect();
}

void GameController::ResetCards()
{
	_character_cards = _factory->GetCharacterCards();
	_building_cards = _factory->GetBuildingCards();
}

void GameController::OutRemainingCharacterCards()
{
	std::string out = "";
	int identifier = 0;
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
	/*std::cout << "New player connected: " << player->GetName() << "\r\n";
	std::cout << "Current players in lobby: " << _players.size() << "\r\n";
	if (_players.size() == 2) {
		_players[0]->SendMessageToCLient("Player " + _players[1]->GetName() + " entered the game!\r\n");
		_players[1]->SendMessageToCLient("Player " + _players[0]->GetName() + " entered the game!\r\n");
		StartGame();
	}*/
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
			_players[0]->SendMessageToCLient("Player: " + player->GetName() + " has joined. \r\n>");
			player->SendMessageToCLient(">");

			if (_players.size() == 2) {
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
			player->SendMessageToCLient(">");

			if (_players.size() == 2 && CheckForAllPlayersReady()) {
				for (const auto &p : _players) {
					p->SendMessageToCLient("All players are ready. Let the best one win!\r\n>");
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
	_current_player_turn = _current_player_turn == _players[0] ? _players[1] : _players[0];
}

void GameController::StartCharacterSelect()
{
	RemoveCharacterCard(rand() % _character_cards.size());
	OutRemainingCharacterCards();
	_current_player_turn->SendMessageToCLient("Select a character card!\r\n> ");
	bool validInput = false;
	std::string input = _current_player_turn->GetPlayerInput();
	while (!validInput){
	
		if (input != _current_player_turn->GetPlayerInput())
		{
			input = _current_player_turn->GetPlayerInput();
			try
			{
				int index = std::stoi(input);
				_current_player_turn->AddCharacterCard(_character_cards[index]);
				RemoveCharacterCard(index);
				validInput = true;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what();
				_current_player_turn->SendMessageToCLient("Invalid input!\r\n> ");
			}
		}

	}
}