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
	ExplainText.setOutlineColor(sf::Color::Green);
	ExplainText.setCharacterSize(18);
	ExplainText.setString(L"����Ʈ �ڷγ� �ô뿡 �Ұ����ϰ� �þ�� ��ȸ��ǰ.\n���� �츮�� ���� �׿����� �������κ��� ������ ��ų �� ���� ���ΰ�?!\n�ΰ��� �����̳� ������ �����̳�...�װ��� �����δ�! \n\n\n �� ���۹� �� \n\n �� �����̽��� : ���� \n\n �� ����Ű : �¿��̵� \n\n\n �� �÷��� �� \n\n �� 1�� ���������� +1�� \n\n �� 3�� ���������� �ڵ����� ������hp & �ູ��hp(=ü��) -4 �Ҹ� \n\n �� �����۰� �浹 �� : ����hp -1, ������hp & �ູ��hp(=ü��) ���� + 1 \n\n �� ����(�ٻ��)�� �浹 �� : ����hp +1, ������hp & �ູ��hp(=ü��) ���� + 1, \n    ȭ�� �� ������ ���̴� �ӵ� ���� \n\n �� ����hp�� 10�� ���ϼ��� ȭ�鿡 ���� ��ȸ��ǰ �����Ⱑ ����. \n\n �� ����hp�� 0�� �ǰų�, ü���� 0�� �Ǹ� GAME OVER !\n\n�� GameOver ��, Entry�� ������ �� score ��� ����. ��, �̸��� 6���ڼ��� ����!");
	ExplainText.setPosition(60.f, 30.f);

	ReadyText.setFont(font);
	ReadyText.setCharacterSize(20);
	ReadyText.setString("Press Enter When You Ready");
	ReadyText.setPosition({ 320.f, 550.f });
	//ReadyText.setFillColor(sf::Color(48, 163, 35, 255));

	sf::Texture virusTex;
	virusTex.loadFromFile("images/virus.png");
	sf::Sprite virus;
	virus.setTexture(virusTex);
	virus.setScale(0.8f, 0.8f);
	virus.setPosition({ 400.f, 130.f });
	
	sf::Texture ecoTex;
	ecoTex.loadFromFile("images/eco.png");
	sf::Sprite eco;
	eco.setTexture(ecoTex);
	eco.setScale(0.9f, 0.9f);
	eco.setPosition({ 550.f, 180.f });
	
	sf::Texture maskTex;
	maskTex.loadFromFile("images/mask.png");
	sf::Sprite mask;
	mask.setTexture(maskTex);
	mask.setScale(0.9f, 0.9f);
	mask.setPosition({ 700.f, 130.f });

	while (Running)
	{
		while (window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (Event.type == sf::Event::KeyPressed)
			{
				switch (Event.key.code)
				{

				case sf::Keyboard::Return:
					return (1);
					break;
				case sf::Keyboard::Escape:
					return 0;
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
			window.draw(eco);
			window.draw(virus);
			window.draw(mask);
		}
		window.display();
	}
}