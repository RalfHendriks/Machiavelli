#include "GameController.h"
#include "CardFactory.h"

GameController::GameController()
{
	_factory = std::make_shared<CardFactory>(CardFactory());
}

void GameController::StartGame()
{
}

void GameController::AddPlayer()
{
}

void GameController::RemovePlayer()
{
}
