#include "Menu.h"
#include <iostream>
using namespace std;

Menu::Menu(void)
{
	playing = false;
	width = 900;
	height = 600;
	alpha_max = 255 * 3;
	alpha_div = 3;
	selectedItemIndex = 0;
}

Menu::~Menu() {}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color(29, 47, 87, 255));
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color(29, 47, 87, 255));
	}
}

int Menu::Run(sf::RenderWindow& window)
{
	sf::Event event;
	bool Running = true;
	sf::Font font;
	int alpha = 0;
	sf::Text ECOVID;
	ECOVID.setFont(font);
	ECOVID.setCharacterSize(40);
	ECOVID.setStyle(sf::Text::Bold);
	ECOVID.setString("E  C  O  V  I  D  -  1  9");
	ECOVID.setPosition(190.f, 30.f);
	ECOVID.setFillColor(sf::Color(237, 237, 182, 255));

	sf::Texture menuTex;
	menuTex.loadFromFile("images/Menu.png");
	sf::Sprite menuBackground;
	menuBackground.setTexture(menuTex);

	if (!font.loadFromFile("neodgm.ttf"))
	{
		//handle error
		cerr << "Error loading neodgm.tff!" << endl;
		return -1;
	}

	menu[0].setFont(font);
	menu[0].setStyle(sf::Text::Bold);
	menu[0].setFillColor(sf::Color(29, 47, 87, 255));
	menu[0].setString("Play");
	menu[0].setCharacterSize(35);
	menu[0].setPosition(sf::Vector2f(430.f, height / (MAX_NUMBER_OF_ITEMS + 1) * 1.6));

	menu[1].setFont(font);
	menu[1].setStyle(sf::Text::Bold);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Explain");
	menu[1].setCharacterSize(35);
	menu[1].setPosition(sf::Vector2f(410.f, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.1));

	menu[2].setFont(font);
	menu[2].setStyle(sf::Text::Bold);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Score");
	menu[2].setCharacterSize(35);
	menu[2].setPosition(sf::Vector2f(425.f, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.6));

	menu[3].setFont(font);
	menu[3].setStyle(sf::Text::Bold);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Exit");
	menu[3].setCharacterSize(35);
	menu[3].setPosition(sf::Vector2f(430.f, height / (MAX_NUMBER_OF_ITEMS + 1) * 3.1));
	//menu[2].setPosition(sf::Vector2f(430.f, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.35));

	selectedItemIndex = 0;

	while (Running)
	{

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			
			if (event.type == sf::Event::KeyReleased)
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					MoveUp();
					break;

				case sf::Keyboard::Down:
					MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (GetPressedItem())
					{
					case 0:
						cout << "start button has been pressed" << endl;
						playing = true;
						return (1);
						break;

					case 1:
						cout << "explain button has been pressed" << endl;
						return (2);
						break;

					case 2:
						return (3);
						break;

					case 3:
						window.close();
						break;
					}

					break;
				}
			break;
		
		}
		if (alpha < alpha_max)
		{
			alpha = alpha + 5;
		}
		menuBackground.setColor(sf::Color(255, 255, 255, alpha / alpha_div));

		window.clear();
		window.draw(menuBackground);
		window.draw(ECOVID);
		if (alpha == alpha_max) {
			draw(window);
		}
		window.display();
	}

	return (-1);
}