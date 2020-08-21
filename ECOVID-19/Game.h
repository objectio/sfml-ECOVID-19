#pragma once
#include "VirtualScreen.h"
#include "Screen.h"
#include "Global.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include<SFML/Audio/Music.hpp>
#include <iostream>
#include <time.h>

class Game : public virtualScreen
{
public:
	virtual int Run(sf::RenderWindow& window);
};