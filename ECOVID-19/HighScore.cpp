#include "HighScore.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;
using namespace sf;

HighScore::HighScore(void)
{
	alpha_max = 3 * 255;
	alpha_div = 3;
}

struct High_Score
{
	string name;
	int score = 0;
};

bool sortByScore(const High_Score& lhs, const High_Score& rhs) { return lhs.score > rhs.score; }

int HighScore::Run(sf::RenderWindow& window)
{
	Event event;
	bool Running = true;
	int alpha = 0;

	Font font;
	Text Title;
	Text Exit;
	Text Score;
	Text Name;
	vector<Text> HighScoreSorted;
	vector<Text> NamesSorted;

	High_Score playerName;
	vector<High_Score> High_Scores;

	if (!font.loadFromFile("neodgm.ttf"))
	{
		//handle error
		cerr << "Error loading neodgm.tff!" << endl;
		return -1;
	}

	Texture ScoreBackTexture;
	ScoreBackTexture.loadFromFile("images/Score.png");
	Sprite ScoreBackground;
	ScoreBackground.setTexture(ScoreBackTexture);
	ScoreBackground.setPosition(0, 0);
	
	string line;
	ifstream HighScoreFile("HighScores.txt");
	while (!HighScoreFile.eof())
	{
		HighScoreFile >> playerName.score >> playerName.name;
		High_Scores.push_back(playerName);
	}
	HighScoreFile.close();
	
	sort(High_Scores.begin(), High_Scores.end(), sortByScore);
	for (High_Score& n : High_Scores)
	{
		Score.setString(to_string(n.score));
		Name.setString(n.name);

		HighScoreSorted.push_back(Score);
		NamesSorted.push_back(Name);
	}
	
	Title.setFont(font);
	Title.setCharacterSize(40);
	Title.setString("High Scores");
	Title.setPosition(360.f, 50.f);

	Exit.setFont(font);
	Exit.setCharacterSize(30);
	Exit.setString("Start");
	Exit.setPosition(430.f, window.getSize().y / 1.2);

	float y = (window.getSize().y / 3.95);
	float x = (window.getSize().x / 6);
	
	High_Scores.resize(10);

	for (size_t i = 0; i < High_Scores.size(); i++)
	{
		Name.setString(High_Scores[i].name);
		Score.setString(to_string(High_Scores[i].score));

		NamesSorted.push_back(Name);
		HighScoreSorted.push_back(Score);
	}
	for (size_t i = 0; i < HighScoreSorted.size(); i++)
	{
		HighScoreSorted[i].setFont(font);
		HighScoreSorted[i].setCharacterSize(24);
		HighScoreSorted[i].setPosition(window.getSize().x / 1.67, x);
		HighScoreSorted[i].setFillColor(Color(13, 53, 106, 255));
		x += 34;
	}
	for (size_t i = 0; i < NamesSorted.size(); i++)
	{
		NamesSorted[i].setFont(font);
		NamesSorted[i].setCharacterSize(24);
		NamesSorted[i].setPosition(window.getSize().x / 2.6, y);
		NamesSorted[i].setFillColor(Color(13, 53, 106, 255));
		y += 34;
	}
	
	while (Running)
	{
		while (window.pollEvent(event))
		{
			// Window closed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			//Key pressed
			if (event.type == sf::Event::KeyPressed)
			{
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					return 0;
				}
				if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					return 0;
				}
			}
		}
		if (alpha < alpha_max)
		{
			alpha = alpha + 5;
		}
		ScoreBackground.setColor(Color(255, 255, 255, alpha / alpha_div));
		window.clear();
		window.draw(ScoreBackground);
		window.draw(Title);
		if (alpha == alpha_max) {
			window.draw(Exit);
			for (int i = 0; i < 10; i++)
			{
				window.draw(HighScoreSorted[i]);
				window.draw(NamesSorted[i]);
			}
		}
		
		window.display();
		
	}
	return (-1);
}