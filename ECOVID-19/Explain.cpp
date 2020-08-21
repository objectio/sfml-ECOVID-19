#include "Explain.h"
#include <iostream>
using namespace std;

Explain::Explain(void)
{
	alpha_max = 3 * 255;
	alpha_div = 3;
}

int Explain::Run(sf::RenderWindow& window)
{
	int alpha = 0;
	sf::Event Event;
	bool Running = true;

	sf::Font font;
	sf::Text ExplainText;
	sf::Text ReadyText;

	sf::Texture explainBackTex;
	explainBackTex.loadFromFile("images/Explain.png");
	sf::Sprite explainBackground;
	explainBackground.setTexture(explainBackTex);

	if (!font.loadFromFile("neodgm.ttf"))
	{
		//handle error
		cerr << "Error loading neodgm.tff!" << endl;
		return -1;
	}

	ExplainText.setFont(font);
	ExplainText.setCharacterSize(20);
	ExplainText.setString(L"<���۹�> \n\n * �����̽��� : ���� \n * �Ʒ�Ű : ���׸��� \n\n\n <�÷���> \n\n * 1�� ���������� +1�� \n * 3�� ���������� �ڵ����� ü�� -5 �Ҹ� \n * �����۰� �浹 �� : ����hp -1, ������hp & �ູ��hp ���� + 1 \n * ��, ���Ĳٷ��̿� �浹�� ����hp -3 \n * ����hp�� 10�� ���ϼ��� ȭ�鿡 ���� �����Ⱑ ���δ�. \n * ����hp�� 0�� �ǰų� ü���� 0�� �Ǹ� ���ӿ��� \n\n * ���Ĳٷ��� :");
	ExplainText.setPosition(100.f, 100.f);

	ReadyText.setFont(font);
	ReadyText.setCharacterSize(20);
	ReadyText.setString("Press Enter When You Ready");
	ReadyText.setPosition({ 320.f, 500.f });

	sf::Texture bombTex;
	bombTex.loadFromFile("images/bomb.png");
	sf::Sprite bomb;
	bomb.setTexture(bombTex);
	bomb.setPosition({ 260.f, 400.f });

	sf::Texture bomb2Tex;
	bomb2Tex.loadFromFile("images/bomb_2.png");
	sf::Sprite bomb2;
	bomb2.setTexture(bomb2Tex);
	bomb2.setPosition({ 350.f, 400.f });

	while (Running)
	{
		while (window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
			{
				return (-1);
			}
			if (Event.type == sf::Event::KeyPressed)
			{
				switch (Event.key.code)
				{

				case sf::Keyboard::Return:
					return (1);
					break;
				case sf::Keyboard::Escape:
					//Let's get work...
					return (-1);
					break;
				default:
					break;
				}
			}
		}

		if (alpha < alpha_max)
		{
			alpha=alpha+5;
		}
		explainBackground.setColor(sf::Color(255, 255, 255, alpha / alpha_div));

		window.clear();
		window.draw(explainBackground);
		if (alpha == alpha_max) {
			window.draw(ExplainText);
			window.draw(ReadyText);
			window.draw(bomb);
			window.draw(bomb2);
		}
		window.display();
	}
}