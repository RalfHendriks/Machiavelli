#include "GameController.h"
#include "CardFactory.h"

GameController::GameController()
{
	_factory = std::make_shared<CardFactory>(CardFactory());
	_gameStarted = false;
	_skipCharacterSelect = false;
	_currentState = GameState::WaitingForPlayers;
}

void GameController::StartGame()
{
	_gameStarted;

}

void GameController::ResetGame()
{
	_characterCards = _factory->GetCharacterCards();
	_buildingCards = _factory->GetBuildingCards();
}

void GameController::AddPlayer(std::shared_ptr<Player> player)
{
	_currentPlayers.push_back(player);
	std::cout << "New player connected: " << player->GetName() << "\r\n";
	std::cout << "Current players in lobby: " << _currentPlayers.size() << "\r\n";
	if (_currentPlayers.size() == 2) {
		_currentPlayers[0]->SendMessageToCLient("PLayer " + _currentPlayers[1]->GetName() + " entered the game!");
		_currentPlayers[1]->SendMessageToCLient("PLayer " + _currentPlayers[0]->GetName() + " entered the game!");
		StartGame();
	}
}

void GameController::RemovePlayer(std::shared_ptr<Player> player)
{
	_currentPlayers.erase(std::remove(_currentPlayers.begin(), _currentPlayers.end(), player), _currentPlayers.end());
}

void GameController::HandlePlayerInput(std::shared_ptr<Player> player, std::string playerInput)
{
	std::cout << player->GetName() << ": " << playerInput << "\r\n";
	if (playerInput == "skipcharacterselect") _skipCharacterSelect = true;

	player->SetLastPLayerInput(playerInput);
}

void GameController::StartCharacterSelect()
{

}