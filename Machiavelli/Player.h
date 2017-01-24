
#ifndef Player_hpp
#define Player_hpp
 
#include <string>
#include <vector>
#include "Socket.h"
#include "Character.h"
#include "Building.h"
#include <memory>

class Player {
public:
	Player(const std::string name, Socket& socket);

	const std::string GetName() const;
	const int GetGold() const;
	const bool IsKing() const;

	const std::vector<std::shared_ptr<CharacterCard>> GetCharacterCards() const;
	const std::vector<std::shared_ptr<BuildingCard>> GetBuildingCards() const;
	const std::vector<std::shared_ptr<BuildingCard>> GetPlayedBuildingCards() const;

	void AddGold(const int amount);
	void AddCharacterCard(std::shared_ptr<CharacterCard> card);
	void RemoveGold(const int amount);
	void SetIsKing(const bool isKing);
	void SetReady(const bool status);
	void SendMessageToCLient(const std::string message);
	void SetLastPLayerInput(const std::string input) { _last_input = input; }
	std::string GetPlayerInput() { return _last_input; }
	bool IsReady() { return _ready; }
private:
    const std::string _name;
	std::string _last_input;
	int _current_gold;
	bool _is_king;
	bool _ready;
	Socket& _socket;
	std::vector<std::shared_ptr<CharacterCard>> _character_cards;
	std::vector<std::shared_ptr<BuildingCard>> _building_cards;
	std::vector<std::shared_ptr<BuildingCard>> _played_building_cards;
};

#endif // Player_hpp