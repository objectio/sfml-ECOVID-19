#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class backgroundImage
{
public:
	backgroundImage();
	~backgroundImage();
	void init();
	Sprite& GetBackground();
	void SwitchingBackground();
	int activeBackground;

private:
	Sprite background;
	Texture cafe;
	Texture house;
};