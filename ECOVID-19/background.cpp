#include "background.h"

backgroundImage::backgroundImage() {}
backgroundImage::~backgroundImage() {}

void backgroundImage::init()
{
	cafe.loadFromFile("images/coffeehouse.png");
	house.loadFromFile("images/house.png");

	background.setTexture(house);
	background.setPosition(0, 0);
	
	activeBackground = 0;
}

Sprite& backgroundImage::GetBackground()
{
	return background;
}

void backgroundImage::SwitchingBackground()
{
	if (activeBackground % 2 == 1) {
		background.setTexture(cafe);
	}
	else
	{
		background.setTexture(house);
	}
	
}