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
	ExplainText.setString(L"포스트 코로나 시대에 불가피하게 늘어나는 일회용품.\n과연 우리는 점점 쌓여가는 쓰레기들로부터 지구를 지킬 수 있을 것인가?!\n인간의 생존이냐 지구의 존속이냐...그것이 문제로다! \n\n\n ◆ 조작법 ◆ \n\n ▷ 스페이스바 : 점프 \n\n ▷ 방향키 : 좌우이동 \n\n\n ◆ 플레이 ◆ \n\n ▷ 1초 지날때마다 +1점 \n\n ▷ 3초 지날때마다 자동으로 포만감hp & 행복감hp(=체력) -4 소모 \n\n ▷ 아이템과 충돌 시 : 지구hp -1, 포만감hp & 행복감hp(=체력) 각각 + 1 \n\n ▷ 힐템(잎사귀)와 충돌 시 : 지구hp +1, 포만감hp & 행복감hp(=체력) 각각 + 1, \n    화면 위 쓰레기 쌓이는 속도 감소 \n\n ▷ 지구hp가 10씩 깎일수록 화면에 점점 일회용품 쓰레기가 쌓임. \n\n ▷ 지구hp가 0이 되거나, 체력이 0이 되면 GAME OVER !\n\n▷ GameOver 후, Entry를 선택해 내 score 등록 가능. 단, 이름은 6글자수로 제한!");
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