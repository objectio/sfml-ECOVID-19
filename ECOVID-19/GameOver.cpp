#include "GameOver.h"
#include <iostream>
//#include <fstream>
using namespace std;

GameOver::GameOver(void) {

	alpha_max = 255 * 3;
	alpha_div = 3;
	playing = false;
}
	
int GameOver::Run(sf::RenderWindow& window)
{
	Event event;
	bool Running = true;
	int alpha = 0;
	Text scoreText;
	Text scoreT;
	Text gameoverText;
	Text Exit;
	Text Restart;
	int menu = 0;

	ofstream HighScoreFile;

	Texture GameOverTex;
	GameOverTex.loadFromFile("images/GameOver.png");
	Sprite GameOverBackground;
	GameOverBackground.setTexture(GameOverTex);
	GameOverBackground.setPosition(0, 0);

	Font font;
	if (!font.loadFromFile("neodgm.ttf"))
	{
		cerr << "Error loading neodgm.ttf" << endl;
		return -1;
	}

	scoreText.setFont(font);
	scoreText.setCharacterSize(30);
	scoreText.setString("Your Score is ");
	scoreText.setPosition(300.f, 100.f);

	scoreT.setFont(font);
	scoreT.setCharacterSize(30);
	scoreT.setString(to_string(GameScore));
	scoreT.setPosition(540.f, 100.f);

	gameoverText.setFont(font);
	gameoverText.setCharacterSize(60);
	gameoverText.setFillColor(Color::Red);
	gameoverText.setPosition(300.f, 260.f);
	gameoverText.setString("GAME OVER !");

	Exit.setFont(font);
	Exit.setCharacterSize(30);
	Exit.setString("Exit");
	Exit.setPosition(550.f, 400.f);
	
	Restart.setFont(font);
	Restart.setCharacterSize(30);
	Restart.setString("Restart");
	Restart.setPosition(300.f, 400.f);

	while (Running)
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				return (-1);
			if (Keyboard::isKeyPressed(Keyboard::Escape))
				return 0;
			if (event.type == Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
					menu = 0;
					break;
				case sf::Keyboard::Right:
					menu = 1;
					break;
				case sf::Keyboard::Return:
					if (menu == 0) {
						playing = true;
						return (1);
					}
					else {
						return (-1);
					}
					break;
				default:
					break;
				}
			}
			

		}
		if (menu == 0)
		{
			Exit.setFillColor(sf::Color(255, 255, 255, 255));
			Restart.setFillColor(sf::Color(255, 0, 0, 255));
		}
		else
		{
			Exit.setFillColor(sf::Color(255, 0, 0, 255));
			Restart.setFillColor(sf::Color(255, 255, 255, 255));
		}

		if (alpha < alpha_max)
		{
			alpha = alpha + 5;
		}
		GameOverBackground.setColor(Color(255, 255, 255, alpha / alpha_div));

		window.draw(GameOverBackground);
		window.draw(gameoverText);
		window.draw(scoreText);
		window.draw(scoreT);
		window.draw(Exit);
		window.draw(Restart);
		window.display();

	}

	return -1;
}
