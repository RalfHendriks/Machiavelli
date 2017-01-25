#include "ConstructionMaster.h"
#include "GameController.h"

ConstructionMaster::ConstructionMaster(const int ID, const CharacterType type) : CharacterCard(ID, type)
{
}

ConstructionMaster::ConstructionMaster()
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
