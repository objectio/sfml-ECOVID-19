#include <SFML/Graphics.hpp>
#include <time.h>
#include "Menu.h"
#include <iostream>
using namespace std;
using namespace sf;
#define WIDTH 900
#define HEIGHT 600

struct Position
{
	int x;
	int y;
};


int main() {
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "ECOVID-19");

	// �÷��̾� 
	Texture t1;
	Texture t2;
	t1.loadFromFile("images/run1.png");
	t2.loadFromFile("images/run2.png");
	Sprite humanArr[2];
	humanArr[0] = Sprite(t1);
	humanArr[1] = Sprite(t2);

	// �÷��̾� ����
	static const int HUMAN_Y_BOTTOM = HEIGHT - (t1.getSize().y + 50);      // �÷��̾� y ��ġ��ǥ
	Position humanPos;
	humanPos.x = 50;
	humanPos.y = HUMAN_Y_BOTTOM;
	//�����ӿ� ���� �޹� ������ �ٲ��ֱ� ���� 4���� ����
	int index = 0; //�޹� ������ �ε���
	float frame = 0.f;
	float frameSpeed = 0.4f;
	const int changeCount = 5; //�� �����ӿ� ü���� ����
	const int gravity = 10; //�߷�, ������ �� ���
	bool isJumping = false; //���� ������
	bool isJumpingtwice = false; //���� ���� ������
	bool isBottom = true; //�ٴڿ� ���� ��Ҵ���

	//����ũ
	Texture t3;
	t3.loadFromFile("images/Cake.png");
	Sprite cake(t3);
	static const int CAKE_Y_BOTTOM = HEIGHT - (t3.getSize().y + 50);         //����ũ y ��ǥ
	Position cakePos;
	cakePos.x = WIDTH - 20;
	cakePos.y = CAKE_Y_BOTTOM;
	const int cakeSpeed = 2;                                        //����ũ �ӵ�

	//���� ������
	int hp = 100;
	RectangleShape hpBar;
	hpBar.setFillColor(Color::Green);
	hpBar.setSize(sf::Vector2f((float)hp * 5.f, 20.f));             //������ 
	hpBar.setPosition(200.f, 10.f);                                 //������ ��ġ��ǥ�� 200px, 10px

	// ī�� ��� ������
	Texture background;
	background.loadFromFile("images/coffeehouse.png");
	Sprite sBackground;
	sBackground.setPosition(0, 0);
	sBackground.setTexture(background);

	// ������ ������ - ���� �����ϰ� 3�ʸ��� 1�� �پ��. �������� ���� �� ȸ���Ǹ� 0�� �Ǹ� ���ӿ���.
	int satiety = 100;
	RectangleShape satietyGauge;
	satietyGauge.setFillColor(Color::Red);
	satietyGauge.setSize(Vector2f((float)satiety * 3.f, 20.f));       // ������ ���α��̴� 300px, ���α��̴� 20px
	satietyGauge.setPosition(80.f, 560.f);                            // ��ġ��ǥ�� 80px, 560px

	// �ູ�� ������ - ���� �����ϰ� 3�ʸ��� 1�� �پ��. �������� ���� �� ȸ���Ǹ� 0�� �Ǹ� ���ӿ���.
	int happy = 100;
	RectangleShape happyGauge;
	happyGauge.setFillColor(Color::Yellow);
	happyGauge.setSize(Vector2f((float)happy * 3.f, 20.f));          // ������ ���α��̴� 300px, ���α��̴� 20px
	happyGauge.setPosition(550.f, 560.f);                            // ��ġ��ǥ�� 550px, 560px

	Clock clock;

	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased)
				switch (event.key.code)
				{
				case Keyboard::Up:
					menu.MoveUp();
					break;

				case Keyboard::Down:
					menu.MoveDown();
					break;

				case Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						cout << "start button has been pressed" << endl;
						break;

					case 1:
						cout << "explain button has been pressed" << endl;
						break;

					case 2:
						window.close();
						break;
					}

					break;
				}
			break;

			if (event.type == Event::Closed)
				window.close();
		}
		/*
		Time startTime = clock.getElapsedTime();            // startTime�� ���� �������� �󸶰� �������� �����. ���� ������ �Ǹ� startTime���� Game Score ���.
		Time now = clock.getElapsedTime();                  // now�� ������ ���� �� ��.
		cout << startTime.asSeconds() << endl;
		if (now.asSeconds() >= 3) {
			now = clock.restart();                          // now�� 3�� �� ������ �ʱ�ȭ ��Ŵ. �׷��Ƿ� 3�ʸ��� �������� �ູ���� ���� 100���� 1�� �ٰ� ��.
			satiety--;
			happy--;
		}

		//��� ���� ����
		if (Keyboard::isKeyPressed(Keyboard::Space)) //�����̽� �Է� ����
		{
			if (isBottom && !isJumping) //�ٴ��̰�, �����ϰ� ���� ���� �� ���� ����
			{
				isJumping = true;
				isBottom = false;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) //��Ű ����
		{
			if (isBottom && !isJumpingtwice) //�ٴ��̰�, ���� �������� ���� �� ���� ���� ����
			{
				isJumpingtwice = true;
				isBottom = false;
			}
		}
		//��� ���� ����
		if (isJumpingtwice)
		{
			humanPos.y -= (gravity * 2); //�߷� 2��
		}


		if (Keyboard::isKeyPressed(Keyboard::Down)) //�Ʒ�Ű�� ������ �Ʒ��� �������Բ� �ϱ�
		{
			if (isJumpingtwice)
			{
				isBottom = true;
				isJumpingtwice = false;
				humanPos.y += (gravity * 2);
			}
		}


		if (isJumping)
		{
			humanPos.y -= gravity; //���� ���ϋ��� �߷� ���ֱ�
		}
		else
		{
			humanPos.y += gravity; //�������� ���� ���� �߷� ���ؼ� �Ʒ��� ���Բ� ���ֱ�
		}
		if (humanPos.y >= HUMAN_Y_BOTTOM) //�ٴڿ��� ���Ϸ� ���� �ʵ��� ����
		{
			humanPos.y = HUMAN_Y_BOTTOM;
			isBottom = true;
		}
		if (humanPos.y <= HUMAN_Y_BOTTOM - 100) //�����ؼ� ���ַ� ���� �ʵ��� ����
		{
			isJumping = false;
			isJumpingtwice = false;
			isBottom = true;
		}
		//��� ����
		frame += frameSpeed;
		if (frame > changeCount)
		{
			frame -= changeCount;
			++index;
			if (index >= 2) { index = 0; }
		}
		//����ũ ������
		if (cakePos.x <= 0)
		{
			cakePos.x = WIDTH;
		}
		else
		{
			cakePos.x -= cakeSpeed;
		}
		//����ũ ��ġ
		cake.setPosition(cakePos.x, cakePos.y);
		//��� ��ġ
		humanArr[index].setPosition(humanPos.x, humanPos.y);
		*/
		//satietyGauge.setSize(Vector2f((float)satiety * 3.f, 20.f));
		//happyGauge.setSize(Vector2f((float)happy * 3.f, 20.f));
		window.clear();
		menu.draw(window);
		//window.draw(sBackground);
		//window.draw(satietyGauge);
		//window.draw(happyGauge);
		//window.draw(humanArr[index]);
		//window.draw(cake);
		//window.draw(hpBar);
		window.display();

	}

	return 0;
}