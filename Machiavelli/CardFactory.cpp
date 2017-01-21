#include "CardFactory.h"

CardFactory::Cards CardFactory::_mapResources = init_resource_map();

CardFactory::CardFactory()
{
	Init();
}

CardFactory::~CardFactory()
{
}

void CardFactory::Init()
{
	
	for (auto const& item: _mapResources)
	{
		std::ifstream in(item.second);
		while (in)
		{
			std::string s;
			if (!std::getline(in, s)) break;

			std::istringstream ss(s);

			while (ss)
			{
				std::string s;
				if (!std::getline(ss, s, ',')) break;


				std::vector<std::string> record;
				std::stringstream ss(s);
				std::string selected;
				while (std::getline(ss, selected, ';')) {
					record.push_back(selected);
				}

				if (item.first == CardType::building) {

				}
				if (item.first == CardType::character) {

				}
			}
		}
	}
}
