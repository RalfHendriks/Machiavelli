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
	_player_builded_building_goal = false;
	_murdered_card = CharacterType::NONE;
	srand(time(NULL));
}

void GameController::StartGame()
{
	_game_started = true;
	_current_player_turn = _players[0];
	_current_player_turn->SetIsKing(true);
	ResetCards();
	while (!_player_builded_building_goal)
	{
		StartCharacterSelect();
		PlayGame();
	}

}

void GameController::ResetCards()
{
	_character_cards.Clear();
	_building_cards.Clear();

	// Add character cards to deck
	for (const auto &card : _factory->GetCharacterCards()) {
		card->SetExecuted(false);
		_character_cards.AddCard(card);
	}

	// Add building cards to deck
	for (const auto &card : _factory->GetBuildingCards()) {
		_building_cards.AddCard(card);
	}
}

void GameController::PlayGame()
{
	int currentCharacter = 1;
	while (currentCharacter < 9)
	{
		std::string currentKing = GetCurrentKing();
		for (const auto &p : _players) {
			p->SendMessageToCLient("King " + currentKing + " asks for the " + CharacterTypeToString(CharacterType(currentCharacter)) + "\r\n");
		}

		bool validCharacter = false;
		for (const auto &p : _players) {
			if (p->HasCharacter(CharacterType(currentCharacter))) {
				if (_murdered_card == CharacterType(currentCharacter)) {
					p->SendMessageToCLient("You've got this card! Unfortunately this character has been murdered^^\r\n\r\n");
					if (CharacterType(currentCharacter) == CharacterType::King) {
						SwitchKing();
					}
				}
				else {
					p->SendMessageToCLient("You've got this card! It's now your turn! \r\n\r\n");
					_current_player_turn = p;
					validCharacter = true;
					if (CharacterType(currentCharacter) == CharacterType::King) {
						SwitchKing();
						currentKing = _current_player_turn->GetName();
					}
					if (CharacterType(currentCharacter) == _robbed_card)
					{
						p->SendMessageToCLient("You've been robbed all your gold is stolen! \r\n\r\n");
						int gold = p->GetGold();
						auto robber = _players[0] == p ? _players[1] : _players[0];
						robber->AddGold(gold);
						p->RemoveGold(gold);
					}
				}

			}
		}
		if (validCharacter) {
			_current_state = CharacterState::ChoiceState;
			while (_current_state == CharacterState::ChoiceState)
			{
				std::string t = CharacterTypeToString(CharacterType(currentCharacter));
				_current_player_turn->SendMessageToCLient("You are the: " + t + "\r\n");
				_current_player_turn->SendMessageToCLient("Current gold: " + std::to_string(_current_player_turn->GetGold()) + "\r\n\r\n");
				_current_player_turn->SendMessageToCLient("Buildings: \r\n");
				for (const auto &building : _current_player_turn->GetPlayedBuildingCards())
				{
					_current_player_turn->SendMessageToCLient(building->GetName() + " <" + ColorToString(building->GetCardColor()) + ", " + std::to_string(building->GetPrice()) + ">:\r\n");
				}
				GenerateOptions(currentCharacter);
				int choice = GetPlayerChoice();
				switch (choice)
				{
				case 1:
					_current_player_turn->AddGold(2);
					_current_player_turn->SendMessageToCLient("Two gold coins have been added! \r\n");
					SendMessageToOpponent(_current_player_turn->GetName() + " took two gold coins \r\n");
					_current_state = CharacterState::BuildState;
					break;
				case 2:
					for (size_t i = 0; i < 2; i++)
					{
						int rIndex = rand() % _building_cards.Size();
						_current_player_turn->SendMessageToCLient("New building card added: " + _building_cards.Get(rIndex)->GetName() + "\r\n");
						_current_player_turn->AddBuildingCard(_building_cards.Get(rIndex));
						_building_cards.RemoveCard(rIndex);
					}
					_current_player_turn->SendMessageToCLient("\r\n");
					_current_player_turn->DisplayBuildingCards();
					_current_player_turn->SendMessageToCLient("Select a card that will be removed. \r\n>");
					_current_player_turn->RemoveBuildingCard(GetPlayerChoice());
					_current_state = CharacterState::BuildState;
					break;
				case 3:
					_current_player_turn->GetCharacterCard(CharacterType(currentCharacter))->Execute(*this);
					break;
				}
			}
			int canbuild = CharacterType(currentCharacter) == CharacterType::ConstructionMaster ? 3 : 1;
			int build = 0;
			while (_current_state == CharacterState::BuildState && build < canbuild)
			{
				if (_current_player_turn->CanBuildBuildings()){
					_current_player_turn->SendMessageToCLient("Building fase would you like to build any building?\r\n");
					_current_player_turn->SendMessageToCLient("[1] Yes\r\n");
					_current_player_turn->SendMessageToCLient("[2] No\r\n>");
					int input = GetPlayerChoice();
					switch (input)
					{
						case 1:
						{
							_current_player_turn->SendMessageToCLient("Which building would you like to build?\r\n");
							_current_player_turn->DisplayBuildableBuildings();
							int input = GetPlayerChoice();
							_current_player_turn->BuildBuildimg(input);
							SendMessageToOpponent(_current_player_turn->GetName() + " builded one building! \r\n");
							if (!_player_builded_building_goal && _current_player_turn->GetPlayedBuildingCards().size() == 8)
							{
								_player_builded_building_goal = true;
								_current_player_turn->SetFirstToEight();
								SendMessageToOpponent(_current_player_turn->GetName() + " builded eight buildings!\r\n");
							}
							build++;
							break;
						}
						case 2:
						default:
						{
							_current_state == CharacterState::ExecuteState;
							build = 3;
							break;
						}
					}
				}
				else {
					_current_player_turn->SendMessageToCLient("You cant build any buildings, proceeding to next state!\r\n");
					break;
				}
			}
			if (!_current_player_turn->GetCharacterCard(CharacterType(currentCharacter))->IsExecuted())
				_current_player_turn->GetCharacterCard(CharacterType(currentCharacter))->Execute(*this);
		}
		currentCharacter++;
	}
	CheckForGameWinner();
}

void GameController::NewRound()
{
	std::string king = "";
	for (const auto &p : _players) {
		p->ResetForRound();
		if (p->IsKing()) {
			king = p->GetName();
			_current_player_turn = p;
		}
	}
	ResetCards();
	_building_cards.Shuffle();
	_murdered_card = CharacterType::NONE;
	_robbed_card = CharacterType::NONE;
}

void GameController::CheckForGameWinner()
{
	bool victory = false;
	std::string	winner = "";
	int	winnerPoints = 0;
	for (const auto &p : _players) {
		if (p->GetFirstToEight()) {
			victory = true;
			winner = p->GetName();
			p->SendMessageToCLient("Game finished!" + winner + " played 8 or more building cards!  \r\n");
		}
	}
	if (victory) {
		for (const auto &p : _players) {
			int points = p->GetBuildingPoints();
			if (winnerPoints < points) {
				winnerPoints = points;
				winner = p->GetName();
			}
			p->SendMessageToCLient("You've got:" + std::to_string(points) + " points!  \r\n");
		}
		SendMessageToOpponent(winner + " won the game with " + std::to_string(winnerPoints) + " points!  \r\n");
	}
	else {
		NewRound();
	}
}

void GameController::SwitchKing()
{
	_current_player_turn->SetIsKing(true);
	auto oldKing = _players[0] == _current_player_turn ? _players[1] : _players[0];
	oldKing->SetIsKing(false);
}

void GameController::SendMessageToOpponent(std::string message)
{
	auto player = _current_player_turn == _players[0] ? _players[1] : _players[0];
	player->SendMessageToCLient(message);
}

void GameController::GenerateOptions(int currentChar)
{
	_current_player_turn->SendMessageToCLient("\r\n");
	_current_player_turn->SendMessageToCLient("Handcards: \r\n");
	_current_player_turn->DisplayBuildingCards();
	_current_player_turn->SendMessageToCLient("\r\n");
	_current_player_turn->SendMessageToCLient("Make a choice: \r\n");
	_current_player_turn->SendMessageToCLient("[1] Take two gold pieces \r\n");
	_current_player_turn->SendMessageToCLient("[2] Take two buildingcards and put one buildingcard away \r\n");
	if (!_current_player_turn->GetCharacterCard(CharacterType(currentChar))->IsExecuted())
	{
		_current_player_turn->SendMessageToCLient("[3] Execute card special ability \r\n>");
	}

}

void GameController::OutRemainingCharacterCards()
{
	std::string out = "";
	int identifier = 1;
	for(int i = 0; i < _character_cards.Size(); i++) {
		out += "[" + std::to_string(identifier) + "] " + _character_cards.Get(i)->GetName() + "\r\n";
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
	_character_cards.RemoveCard(index);
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

std::string GameController::GetCurrentKing()
{
	std::string currentKing = "";
	for (const auto &p : _players) {
		if (p->IsKing()) {
			currentKing = p->GetName();
		}
	}
	return currentKing;
}

void GameController::StartCharacterSelect()
{
	for (const auto &p : _players) {
		p->SendMessageToCLient("A new round has started! \r\nAll characters are going back in the deck and they're getting shuffled! \r\n");
		p->SendMessageToCLient("It's up to you king " + GetCurrentKing() + "!\r\n\r\n");
	}

	if (!_skip_character_select) {
		int r = 3;
		while (r == 3)
		{
			r = rand() % _character_cards.Size();
		}
		RemoveCharacterCard(r);
		while (_character_cards.Size() > 0)
		{
			OutRemainingCharacterCards();
			_current_player_turn->SendMessageToCLient("Select a character card!\r\n> ");
			int cardIndex = CharacterCardSelect();
			_current_player_turn->AddCharacterCard(_character_cards.Get(cardIndex));
			RemoveCharacterCard(cardIndex);

			if (_character_cards.Size() != 6) {
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
			int r = rand() % _character_cards.Size();
			_players[(i/2)]->AddCharacterCard(_character_cards.Get(r));
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
				index = std::stoi(input);
				if (index <= _character_cards.Size())
				{
					index = index -1;
					auto c = _character_cards.Get(index);
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
	_current_player_turn->SetLastPLayerInput("");
	return index;
}

int GameController::GetPlayerChoice()
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
				if (!index > 3) {
					index = std::stoi(input);
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
	_current_player_turn->SetLastPLayerInput("");
	return index;
}
