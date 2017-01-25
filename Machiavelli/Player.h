
#ifndef Player_hpp
#define Player_hpp
 
#include <string>
#include <vector>
#include "Socket.h"
#include "Character.h"
#include "Building.h"
#include <memory>
#include <algorithm>

class Player {
public:
	Player(const std::string name, Socket& socket);

	const std::string GetName() const;
	const int GetGold() const;
	const bool IsKing() const;

	const std::vector<std::shared_ptr<CharacterCard>> GetCharacterCards() const;
	const std::vector<std::shared_ptr<BuildingCard>> GetBuildingCards() const;
	const std::vector<std::shared_ptr<BuildingCard>> GetPlayedBuildingCards() const;
	const bool GetFirstToEight() const;
	const int GetBuildingPoints() const;
	void AddGold(const int amount);
	void AddCharacterCard(std::shared_ptr<CharacterCard> card);
	void AddBuildingCard(std::shared_ptr<BuildingCard> card);
	void BuildBuildimg(int index);
	void RemoveBuildingCard(int index);
	void DisplayBuildingCards();
	void DisplayBuildedBuildings();
	std::shared_ptr<CharacterCard> GetCharacterCard(CharacterType type);
	void RemoveGold(const int amount);
	void SetIsKing(const bool isKing);
	void SetReady(const bool status);
	void SetFirstToEight() { _first_to_eight = true; }
	void SendMessageToCLient(const std::string message);
	void SetLastPLayerInput(const std::string input) { _lastInput = input; }
	std::string GetPlayerInput() { return _lastInput; }
	void DisplayBuildableBuildings();
	bool IsReady() { return _ready; }
	bool HasCharacter(CharacterType c);
	bool CanBuildBuildings();
private:
    const std::string _name;
	std::string _lastInput;
	int _current_gold;
	bool _is_king;
	bool _ready;
	bool _first_to_eight;
	Socket& _socket;
	std::vector<std::shared_ptr<CharacterCard>> _character_cards;
	std::vector<std::shared_ptr<BuildingCard>> _building_cards;
	std::vector<std::shared_ptr<BuildingCard>> _played_building_cards;
};

#endif // Player_hpp