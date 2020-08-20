#pragma once
#include <SFML/Graphics.hpp>

class virtualScreen
{
public:
	virtual int Run(sf::RenderWindow& window) = 0;
};