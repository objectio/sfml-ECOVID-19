#pragma once
#include "VirtualScreen.h"
#include "Screen.h"
#include <SFML/Graphics.hpp>

class HighScore : public virtualScreen
{
public:
	HighScore(void);
	virtual int Run(sf::RenderWindow& window);

private:
	int alpha_max;
	int alpha_div;
};