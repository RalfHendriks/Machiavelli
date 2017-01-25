#pragma once
#include <vector>
#include <algorithm>

template<typename T>
class Deck 
{
public:
	void AddCard(T card) { _cards.push_back(card); }
	//void RemoveCard(const int index) { _cards.erase(std::remove(_cards.begin(), _cards.end(), _cards[index]), _cards.end()); }
	void RemoveCard(const int index) { _cards.erase(std::remove_if(_cards.begin(), _cards.end(), [&](T card) {return card == _cards[index]; }), _cards.end()); }
	void Shuffle() { random_shuffle(deck.begin(), deck.end()); }
	void Clear() { _cards.clear(); }

	T Pop() { 
		T placeholder = _cards.back();
		_cards.pop_back();
		return placeholder;
	}
	T Get(const int index) { return _cards.at(index); }
	int Size() { return _cards.size(); }

	// Operators
	T& operator[](int index) { return Get(index); }
	const T& operator[](int index) const { return Get(index); }

private:
	std::vector<T> _cards;
};