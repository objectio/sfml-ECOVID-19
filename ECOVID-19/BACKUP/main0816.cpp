#include <SFML/Graphics.hpp>
#include <time.h>
#include "Menu.h"
#include "background.h"
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
	window.setFramerateLimit(70);

	// �÷��̾� 
	Texture t1;
	Texture t2;
	t1.loadFromFile("images/run1.png");  
	t2.loadFromFile("images/run2.png");  
	Sprite humanArr[2];
	humanArr[0] = Sprite(t1);
	humanArr[1] = Sprite(t2);

	Font font;
	font.loadFromFile("neodgm.ttf");

	// �÷��̾� ����
	static const int HUMAN_Y_BOTTOM = HEIGHT - (t1.getSize().y + 50);      // �÷��̾� y ��ġ��ǥ
	Position humanPos;
	humanPos.x = 50;
	humanPos.y = HUMAN_Y_BOTTOM;
	//�����ӿ� ���� �޹� ������ �ٲ��ֱ� ���� 4���� ����
	int index = 0; //�޹� ������ �ε���
	float frame = 5.0f; //
	float frameSpeed = 0.3f; // -> ���� �ٿ���!
	const int changeCount = 10; //�� �����ӿ� ü���� ����
	const int gravity = 15; //�߷�, ������ �� ��� -> ���� �ٿ���!
	const int space = 3; //����, ���������� �̵��� �� ���
	bool isJumping = false; //���� ������
	bool isBottom = true; //�ٴڿ� ���� ��Ҵ���
	bool isLeft = false; //�������� �̵��ϴ���
	bool isRight = false; //���������� �̵��ϴ���

	int score = 0;

	//���� �ؽ�Ʈ�� ǥ��
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(10.f, 10.f);

	//����hp �ؽ�Ʈ�� ǥ��
	Text earthHpText;
	earthHpText.setFont(font);
	earthHpText.setCharacterSize(12);
	earthHpText.setFillColor(Color::White);

	//����hp �� ������
	Texture earthTex;
	earthTex.loadFromFile("images/earth.png");
	Sprite earthIcon;
	earthIcon.setTexture(earthTex);
	earthIcon.setScale(Vector2f(1.1f, 1.1f));
	earthIcon.setPosition(180.f, 5.f);

	//������ �ؽ�Ʈ�� ǥ��
	Text satietyText;
	satietyText.setFont(font);
	satietyText.setCharacterSize(12);
	satietyText.setFillColor(Color::White);
	satietyText.setPosition(70.f, 530.f);

	//������ ������ �� ������
	Texture satietyTex;
	satietyTex.loadFromFile("images/satiety.png");
	Sprite satietyIcon;
	satietyIcon.setTexture(satietyTex);
	satietyIcon.setScale(Vector2f(1.1f, 1.1f));
	satietyIcon.setPosition(65.f, 555.f);

	//�ູ�� �ؽ�Ʈ�� ǥ��
	Text happyText;
	happyText.setFont(font);
	happyText.setCharacterSize(12);
	happyText.setFillColor(Color::White);
	happyText.setPosition(530.f, 530.f);

	//�ູ�� ������ �� ������
	Texture happyTex;
	happyTex.loadFromFile("images/happy.png");
	Sprite happyIcon;
	happyIcon.setTexture(happyTex);
	happyIcon.setScale(Vector2f(1.1f, 1.1f));
	happyIcon.setPosition(535.f, 555.f);

	//����ũ
	Texture cakeTex;
	cakeTex.loadFromFile("images/cake.png");
	Sprite cake;
	cake.setTexture(cakeTex);
	cake.setScale(Vector2f(0.5f, 0.5f));
	Position cakePos;
	cakePos.x = WIDTH - 20;
	cakePos.y = HEIGHT - cakeTex.getSize().y;
	//����ũ �ӵ�
	float cakeSpeed = 0.3f;

	//Ŀ��
	Texture coffeeTex;
	coffeeTex.loadFromFile("images/coffee.png");
	Sprite coffee;
	coffee.setTexture(coffeeTex);
	coffee.setScale(Vector2f(0.5f, 0.5f));
	Position coffeePos;
	coffeePos.x = WIDTH - 10;
	coffeePos.y = HEIGHT - coffeeTex.getSize().y;
	//Ŀ�� �ӵ�
	float coffeeSpeed = 0.3f;

	//ġŲ
	Texture chickenTex;
	chickenTex.loadFromFile("images/chicken.png");
	Sprite chicken;
	chicken.setTexture(chickenTex);
	chicken.setScale(Vector2f(0.5f, 0.5f));
	Position chickenPos;
	chickenPos.x = WIDTH - 20;
	chickenPos.y = HEIGHT - chickenTex.getSize().y;
	//ġŲ �ӵ�
	float chickenSpeed = 0.3f;

	//����
	Texture pizzaTex;
	pizzaTex.loadFromFile("images/pizza.png");
	Sprite pizza;
	pizza.setTexture(pizzaTex);
	pizza.setScale(Vector2f(0.5f, 0.5f));
	Position pizzaPos;
	pizzaPos.x = WIDTH - 25;
	pizzaPos.y = HEIGHT - pizzaTex.getSize().y;
	//���� �ӵ�
	float pizzaSpeed = 0.3f;

	//�ù����
	Texture boxTex;
	boxTex.loadFromFile("images/cake.png");
	Sprite box;
	box.setTexture(boxTex);
	box.setScale(Vector2f(0.5f, 0.5f));
	Position boxPos;
	boxPos.x = WIDTH - 40;
	boxPos.y = HEIGHT - boxTex.getSize().y;
	//�ù���� �ӵ�
	float boxSpeed = 1.0f;

	//������ �迭
	Sprite item[10];
	item[0] = cake;
	item[1] = coffee;
	item[2] = chicken;
	item[3] = pizza;
	item[4] = box;

	std::vector<Sprite> items;

	//����ũ ���� Ÿ�̸�(�ʱ�)
	int cakeSpawnTimer = 0;
	//Ŀ�� ���� Ÿ�̸�(�ʱ�)
	int coffeeSpawnTimer = 20; //Ŀ�� ������ ����ũ �������� �ð����� �α� ���� 20���� �ø�.

	// ������
	Texture garbageTex1;
	garbageTex1.loadFromFile("images/cake_garbage.png");
	Sprite cakeGarbage;
	cakeGarbage.setTexture(garbageTex1);

	Texture garbageTex2;
	garbageTex2.loadFromFile("images/coffee_garbage.png");
	Sprite coffeeGarbage;
	coffeeGarbage.setTexture(garbageTex2);

	Texture garbageTex3;
	garbageTex3.loadFromFile("images/chicken_garbage.png");
	Sprite chickenGarbage;
	chickenGarbage.setTexture(garbageTex3);

	Texture garbageTex4;
	garbageTex4.loadFromFile("images/pizza_garbage.png");
	Sprite pizzaGarbage;
	pizzaGarbage.setTexture(garbageTex4);

	Texture garbageTex5;
	garbageTex5.loadFromFile("images/postbox_garbage.png");
	Sprite boxGarbage;
	boxGarbage.setTexture(garbageTex5);

	Texture GarbagesTexture[5];
	GarbagesTexture[0] = garbageTex1;
	GarbagesTexture[1] = garbageTex2;
	GarbagesTexture[2] = garbageTex3;
	GarbagesTexture[3] = garbageTex4;
	GarbagesTexture[4] = garbageTex5;
	int SelectedGarbage = 0;

	vector<Sprite> Garbages;
	//Sprite* garbage;
	//garbage = new Sprite;

	Position GarbagesPosition;
	GarbagesPosition.x = 890.f;
	GarbagesPosition.y = 590.f;

	//���� ������
	int earthHp = 100;
	int hpMax = 100; //�ִ밪 ����
	RectangleShape hpBar;
	hpBar.setFillColor(Color(125,215,66,255));
	hpBar.setSize(sf::Vector2f((float)earthHp * 5.f, 20.f));             //������ 
	hpBar.setPosition(200.f, 10.f);                                 //������ ��ġ��ǥ�� 200px, 10px

	/* backgroundImage background;
	background.init(); */
	Sprite background;
	Texture cafe;
	cafe.loadFromFile("images/coffeehouse.png");
	Texture house;
	house.loadFromFile("images/house.png");
	background.setTexture(house);
	background.setPosition(0, 0);
	int activeBackground = 0;

	// ������ ������ - ���� �����ϰ� 3�ʸ��� 1�� �پ��. �������� ���� �� ȸ���Ǹ� 0�� �Ǹ� ���ӿ���.
	int satiety = 80;
	static const int satietyMax = 100; //�ִ밪 ����
	RectangleShape satietyGauge;
	satietyGauge.setFillColor(Color(255,175,31,255));
	satietyGauge.setSize(Vector2f((float)satiety * 3.f, 20.f));       // ������ ���α��̴� 300px, ���α��̴� 20px
	satietyGauge.setPosition(80.f, 560.f);                            // ��ġ��ǥ�� 80px, 560px

	// �ູ�� ������ - ���� �����ϰ� 3�ʸ��� 1�� �پ��. �������� ���� �� ȸ���Ǹ� 0�� �Ǹ� ���ӿ���.
	int happy = 80;
	static const int happyMax = 100; //�ִ밪 ����
	RectangleShape happyGauge;
	happyGauge.setFillColor(Color(223,95,68,255));
	happyGauge.setSize(Vector2f((float)happy * 3.f, 20.f));          // ������ ���α��̴� 300px, ���α��̴� 20px
	happyGauge.setPosition(550.f, 560.f);                            // ��ġ��ǥ�� 550px, 560px

	Clock score_clock;
	Clock gauge_clock;
	Clock switch_clock;

	RectangleShape fade;
	fade.setSize(Vector2f(window.getSize().x, window.getSize().y));
	Uint8 a = 0;

	Menu menu();

	while (window.isOpen() && earthHp > 0)
	{
		Time startTime = score_clock.getElapsedTime();            // startTime�� ���� �������� �󸶰� �������� �����. ���� ������ �Ǹ� startTime���� Game Score ���. 
		Time gauge = gauge_clock.getElapsedTime();                  // ������ ���� �� ��.
		cout << startTime.asSeconds() << endl;
		
		if (startTime.asSeconds() >= 1)
		{
			startTime = score_clock.restart();
			score++;
		}

		if (gauge.asSeconds() >= 3) {                         
			gauge = gauge_clock.restart();                          // gauge�� 3�� �� ������ �ʱ�ȭ ��Ŵ. �׷��Ƿ� 3�ʸ��� �������� �ູ���� ���� 100���� 1�� �ٰ� ��.
			satiety = satiety - 5;
			happy = happy - 5;
		}

		Time SwitchingTime = switch_clock.getElapsedTime();
		if (SwitchingTime.asSeconds() >= 12) {
			SwitchingTime = switch_clock.restart();
			activeBackground++; // 12�ʸ��� activeBackground�� 1�� ����.
			
		}

		if (activeBackground % 2 == 1) {
			background.setTexture(cafe);
		}
		else
		{
			background.setTexture(house);
		}                  

		int CollisionTime = 0;

		Event event;
		while (window.pollEvent(event))
		{
			/*
				*/
			if (event.type == Event::Closed)
				window.close();
		}

		//������(Ŀ��, ����ũ) �̵�
		for (size_t i = 0; i < items.size(); i++)
		{
			item[i].move(-9.5f, 0.f);

			if (item[i].getPosition().x < 0 - item[i].getGlobalBounds().width)
				items.erase(items.begin() + i);
		}

		//����ũ ���� Ÿ�̸�
		if (cakeSpawnTimer < 120)
			cakeSpawnTimer++;

		if (cakeSpawnTimer >= 120)
		{
			item[0].setPosition(window.getSize().x, rand() % int(window.getSize().y - item[0].getGlobalBounds().height));
			items.push_back(Sprite(item[0]));
			cakeSpawnTimer = 0; //�ʱ�ȭ
		}

		//Ŀ�� ���� Ÿ�̸�
		if (coffeeSpawnTimer < 140.5)
			coffeeSpawnTimer++;

		if (coffeeSpawnTimer >= 140.5)
		{
			item[1].setPosition(window.getSize().x, rand() % int(window.getSize().y - item[1].getGlobalBounds().height));
			items.push_back(Sprite(item[1]));
			coffeeSpawnTimer = 20; //�ʱ�ȭ
		}

		//�浹
		for (size_t i = 0; i < items.size(); i++)
		{
			
			if (humanArr[index].getGlobalBounds().intersects(item[i].getGlobalBounds()))
			{
				earthHp--;
				satiety++;
				happy++;
				score++;
				CollisionTime++;
				SelectedGarbage++;
				if (SelectedGarbage > 5) SelectedGarbage = 0;
				items.erase(items.begin() + i);
				GarbagesPosition.x = GarbagesPosition.x - 10.f;
				GarbagesPosition.y = GarbagesPosition.y - 5.f;

				if (satiety >= 100)
					satiety = satietyMax; //�������� 100�� �Ѿ�� 100�� �ʰ����� �ʵ��� �ѵ� ����.
				if (happy >= 100)
					happy = happyMax; //�ູ���� 100�� �Ѿ�� 100�� �ʰ����� �ʵ��� �ѵ� ����
				Sprite GarbageInputSprite;
				//Garbages.push_back(GarbageInputSprite);
				//Garbages[i].setPosition(GarbagesPosition.x, GarbagesPosition.y);
				//Garbages[i].setTexture(GarbagesTexture[SelectedGarbage]);
			
	
			}
			
		}

		//��� ���� ����
		if (Keyboard::isKeyPressed(Keyboard::Space))//�����̽� �Է� ����
		{
			if (isBottom && !isJumping) //�ٴ��̰�, �����ϰ� ���� ���� �� ���� ����
			{
				isJumping = true;
				isBottom = false;
			}
		}

		if (isJumping)
		{
			humanPos.y -= gravity; //���� ���϶��� �߷� ���ֱ�
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
		if (humanPos.y <= HUMAN_Y_BOTTOM - 400) //�����ؼ� ���ַ� ���� �ʵ��� ����
		{
			isJumping = false;
		}

		//��� ����
		frame += frameSpeed;
		if (frame > changeCount)
		{
			frame -= changeCount;
			++index;
			if (index >= 2) { index = 0; }
		}

		//�����۵� ��ġ
		cake.setPosition(cakePos.x, cakePos.y);
		coffee.setPosition(coffeePos.x, coffeePos.y);
		chicken.setPosition(chickenPos.x, chickenPos.y);
		pizza.setPosition(pizzaPos.x, pizzaPos.y);
		box.setPosition(boxPos.x, boxPos.y);

		//��� ��ġ
		humanArr[index].setPosition(humanPos.x, humanPos.y);
		//earthHpText.setPosition(humanArr[index].getPosition().x, humanArr[index].getPosition().y - hpText.getGlobalBounds().height); <-�̰� �����ص� ��!

		//����hp �ؽ�Ʈ ��ġ
		earthHpText.setPosition(190.f, 30.f);
		//����hp ��Ÿ���ִ� �ؽ�Ʈ
		earthHpText.setString("Earth : " + std::to_string(earthHp) + "/" + std::to_string(hpMax));
		//������ ��Ÿ���ִ� �ؽ�Ʈ
		satietyText.setString("Satiety : " + std::to_string(satiety) + "/" + std::to_string(satietyMax));
		//�ູ�� ��Ÿ���ִ� �ؽ�Ʈ
		happyText.setString("Happy : " + std::to_string(happy) + "/" + std::to_string(happyMax));

		//ĳ���Ͱ� ������ â���� ����� �ʰԲ� ���ִ� if����
		if (humanArr[index].getPosition().y > window.getSize().y - humanArr[index].getGlobalBounds().height)
			humanArr[index].setPosition(humanArr[index].getPosition().x, window.getSize().y - humanArr[index].getGlobalBounds().height);

		if (humanArr[index].getPosition().y < 0)
			humanArr[index].setPosition(humanArr[index].getPosition().x, 0);

		if (humanArr[index].getPosition().x < 0)
			humanArr[index].setPosition(0, humanArr[index].getPosition().y);

		if (humanArr[index].getPosition().x > window.getSize().x - humanArr[index].getGlobalBounds().width)
			humanArr[index].setPosition(window.getSize().x - humanArr[index].getGlobalBounds().width, humanArr[index].getPosition().y);

		//3���� �������� ũ��
		hpBar.setSize(sf::Vector2f((float)earthHp * 5.f, 20.f));
		satietyGauge.setSize(Vector2f((float)satiety * 3.f, 20.f));
		happyGauge.setSize(Vector2f((float)happy * 3.f, 20.f));
		
		//���� ������Ʈ
		scoreText.setString("Score: " + std::to_string(score));

		window.clear();
		//menu.draw(window);
		window.draw(background);
		window.draw(satietyGauge);
		window.draw(happyGauge);
		window.draw(humanArr[index]);
		for (size_t i = 0; i < items.size(); i++)
		{
			window.draw(item[i]);
		}
		window.draw(hpBar);
		window.draw(earthHpText);
		window.draw(satietyText);
		window.draw(happyText);
		window.draw(scoreText);
		window.draw(earthIcon); 
		window.draw(satietyIcon); 
		window.draw(happyIcon);
		for (int i = 0; i < Garbages.size(); i++)
			window.draw(Garbages[i]);
		window.display();

	}
	
	//delete garbage;
	return 0;
}