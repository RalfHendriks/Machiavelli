#include "ConstructionMaster.h"
#include "GameController.h"

ConstructionMaster::ConstructionMaster(const int ID, const std::string name, const CharacterType type) : CharacterCard(ID, name, type)
{
}

ConstructionMaster::~ConstructionMaster()
{
}

void ConstructionMaster::Execute(GameController & game_controller)
{
	auto current_player = game_controller.GetCurrentPlayerTurn();
	current_player->SendMessageToCLient("You have executed the Construction Master card. \r\n");

	current_player->AddBuildingCard(game_controller.GetBuildingCards().Pop());
	current_player->AddBuildingCard(game_controller.GetBuildingCards().Pop());

	_executed = true;
}
