#include "HighScore.h"
#include <iostream>
#include <fstream>
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
	Title.setPosition(window.getSize().x / 4, window.getSize().y / 9);
	Title.setFillColor(Color());

	Exit.setFont(font);
	Exit.setCharacterSize(30);
	Exit.setString("Exit");
	Exit.setPosition(window.getSize().x / 2.3, window.getSize().y / 1.2);
	Title.setFillColor(Color());

	float y = (window.getSize().y / 3);
	float x = (window.getSize().y / 3);

	High_Scores.resize(15);

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
		HighScoreSorted[i].setPosition(window.getSize().x / 1.33, x);
		HighScoreSorted[i].setFillColor(Color(255, 0, 0, 255));
		x += 34;
	}
	for (size_t i = 0; i < NamesSorted.size(); i++)
	{
		NamesSorted[i].setFont(font);
		NamesSorted[i].setCharacterSize(24);
		NamesSorted[i].setPosition(window.getSize().x / 7, y);
		NamesSorted[i].setFillColor(Color(255, 0, 0, 255));
		y += 34;
	}

	while (Running)
	{
		while (window.pollEvent(event))
		{
			// Window closed
			if (event.type == sf::Event::Closed)
			{
				return (-1);
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
			alpha++;
		}

		window.draw(Title);
		window.draw(Exit);
		/*for (int i = 0; i < 15; i++)
		{
			window.draw(HighScoreSorted[i]);
			window.draw(NamesSorted[i]);
		}
		window.display();
	}*/
	return (-1);
}