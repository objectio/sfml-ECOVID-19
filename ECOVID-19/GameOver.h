#pragma once
#include "VirtualScreen.h"
#include "Screen.h"
#include "Global.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
using namespace std;
using namespace sf;

class GameOver : public virtualScreen {

public:
	GameOver(void);
	virtual int Run(sf::RenderWindow& window);

private:
	int alpha_max;
	int alpha_div;
	bool playing;
};
