#include "GameOver.h"
#include <iostream>
#include <fstream>
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
	Text Name;
	Text AskEntry;
	Text Entry;
	Text CurHighScore;
	Text completeText;
	string NameEntry;
	int menu = 0;
	int isEntry = 0;
	int EntryComplete = 0;

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
	scoreText.setPosition(310.f, 295.f);
	scoreText.setFillColor(sf::Color(183, 67, 0, 255));

	scoreT.setFont(font);
	scoreT.setCharacterSize(30);
	scoreT.setString(to_string(GameScore));
	scoreT.setPosition(540.f, 297.f);
	scoreT.setFillColor(sf::Color(183, 67, 0, 255));

	gameoverText.setFont(font);
	gameoverText.setCharacterSize(60);
	gameoverText.setFillColor(Color(101, 38, 31, 255));
	gameoverText.setPosition(300.f, 200.f);
	gameoverText.setString("GAME OVER !");

	Exit.setFont(font);
	Exit.setCharacterSize(30);
	Exit.setString("Exit");
	Exit.setPosition(550.f, 400.f);
	
	Restart.setFont(font);
	Restart.setCharacterSize(30);
	Restart.setString("Restart");
	Restart.setPosition(300.f, 400.f);

	Entry.setFont(font);
	Entry.setCharacterSize(30);
	Entry.setString("Entry");
	Entry.setPosition(300.f, 450.f);

	AskEntry.setFont(font);
	AskEntry.setCharacterSize(18);
	AskEntry.setString("Please type your name and press enter:");
	AskEntry.setPosition(440.f, 450.f);
	//AskEntry.setFillColor(Color(150, 103, 88, 255));

	Name.setFont(font);
	Name.setCharacterSize(20);
	Name.setPosition(550.f, 480.f);
	Name.setFillColor(Color(250, 230, 150, 255));

	completeText.setFont(font);
	completeText.setCharacterSize(20);
	completeText.setString("Record Complete !");
	completeText.setPosition(510.f, 515.f);
	completeText.setFillColor(Color(250, 230, 192, 255));

	while (Running)
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
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
				case sf::Keyboard::Down:
					menu = 2;
					break;
				case sf::Keyboard::Return:
					if (menu == 0) {
						playing = true;
						return (1);
					}
					else if (menu == 2) {
						isEntry = 1;
					}
					else {
						window.close();
					}
					break;
				default:
					break;
				}
			}
			if (isEntry == 1)
			{
				if (event.type == Event::KeyPressed)
				{
					if (Keyboard::isKeyPressed(Keyboard::Return))
					{
						if (NameEntry.length() > 0)
						{
							HighScoreFile.open("HighScores.txt", ios::app);
							HighScoreFile << "\n" << GameScore << " " << NameEntry;
							HighScoreFile.close();

							EntryComplete = 1;
						}
					}
				}
				//SFML special event check for entering text to screen
				if (event.type == Event::TextEntered)
				{
					if (event.text.unicode >= 32 && event.text.unicode <= 128)
					{
						if (NameEntry.size() < 6)
						{
							NameEntry += ((char)event.text.unicode);
							Name.setString(NameEntry);
						}
					}
					else if (event.text.unicode == 8 && NameEntry.length() > 0)
					{
						NameEntry.erase(NameEntry.length() - 1, NameEntry.length());
						Name.setString(NameEntry);
					}
				}
			}
		}
		if (menu == 0)
		{
			Exit.setFillColor(sf::Color(255, 255, 255, 255));
			Restart.setFillColor(sf::Color(91, 62, 52, 255));
			Entry.setFillColor(sf::Color(255, 255, 255, 255));
		}
		else if (menu == 1)
		{
			Exit.setFillColor(sf::Color(91, 62, 52, 255));
			Restart.setFillColor(sf::Color(255, 255, 255, 255));
			Entry.setFillColor(sf::Color(255, 255, 255, 255));
		}
		else
		{
			Exit.setFillColor(sf::Color(255, 255, 255, 255));
			Restart.setFillColor(sf::Color(255, 255, 255, 255));
			Entry.setFillColor(sf::Color(91, 62, 52, 255));
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
		window.draw(Entry);
		if (isEntry == 1)
		{
			window.draw(AskEntry);
			window.draw(Name);
		}
		if (EntryComplete == 1)
			window.draw(completeText);
		window.display();

	}

	return -1;
}
