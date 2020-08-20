#pragma once
#include "VirtualScreen.h"
#include "SFML/Graphics.hpp"

class Explain : public virtualScreen
{
public:
	Explain(void);
	virtual int Run(sf::RenderWindow& window);

private:
	int alpha_max;
	int alpha_div;
	//bool playing;
};