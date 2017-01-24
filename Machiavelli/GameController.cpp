#include "GameController.h"
#include "CardFactory.h"

GameController::GameController()
{
	_factory = std::make_shared<CardFactory>(CardFactory());
	_game_started = false;
}

void GameController::StartGame()
{
	_game_started;
}

void GameController::AddPlayer(std::shared_ptr<Player> player)
{
	_currentPlayers.push_back(player);
	std::cout << "New player connected: " << player->GetName() << "\r\n";
	std::cout << "Current players in lobby: "<< _currentPlayers.size();
	if (_currentPlayers.size() == 2) {
		StartGame();
	}
}

void GameController::RemovePlayer(std::shared_ptr<Player> player)
{
	_currentPlayers.erase(std::remove(_currentPlayers.begin(), _currentPlayers.end(), player), _currentPlayers.end());
}

void GameController::HandlePlayerInput(std::shared_ptr<Player> player, std::string playerInput)
{
}

const bool GameController::HasGameStarted() const
{
	return _game_started;
}

const std::shared_ptr<CharacterCard> GameController::GetMurderedCharacter() const
{
	return _murdered_character;
}

const std::shared_ptr<CharacterCard> GameController::GetRobbedCharacter() const
{
	return _robbed_character;
}
