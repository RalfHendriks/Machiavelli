
#ifndef Player_hpp
#define Player_hpp
 
#include <string>
#include <vector>
#include "Character.h"
#include "Building.h"
#include <memory>

class Player {
public:
	Player(const std::string name);

	const std::string GetName() const;
	const int GetGold() const;
	const bool IsKing() const;

	const std::vector<std::shared_ptr<CharacterCard>> GetCharacterCards() const;
	const std::vector<std::shared_ptr<BuildingCard>> GetBuildingCards() const;
	const std::vector<std::shared_ptr<BuildingCard>> GetPlayedBuildingCards() const;

	void AddGold(const int amount);
	void RemoveGold(const int amount);
	void SetIsKing(const bool isKing);

private:
    const std::string _name;
	int _current_gold;
	bool _is_king;

	std::vector<std::shared_ptr<CharacterCard>> _character_cards;
	std::vector<std::shared_ptr<BuildingCard>> _building_cards;
	std::vector<std::shared_ptr<BuildingCard>> _played_building_cards;
};

#endif // Player_hpp