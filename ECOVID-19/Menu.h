#pragma once
#include "VirtualScreen.h"
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 4

class Menu : public virtualScreen {
public:
	Menu();
	~Menu();

	virtual int Run(sf::RenderWindow& window);
	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	bool playing;
	int alpha_max;
	int alpha_div;
	float width; 
	float height;

	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
};