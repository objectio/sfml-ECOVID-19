#include "Game.h"

using namespace std;
using namespace sf;
#define WIDTH 900
#define HEIGHT 600

struct Position
{
	float x;
	float y;
};

int Game::Run(RenderWindow& window)
{
	// �÷��̾� 
	Texture t1;
	Texture t2;
	t1.loadFromFile("images/run1.png");
	t2.loadFromFile("images/run2.png");
	Sprite humanArr[2];
	humanArr[0] = Sprite(t1);
	humanArr[1] = Sprite(t2);
	humanArr[0].setScale(Vector2f(1.0f, 1.0f));
	humanArr[1].setScale(Vector2f(1.0f, 1.0f));

	Font font;
	font.loadFromFile("neodgm.ttf");

	// �÷��̾� ����
	float HUMAN_Y_BOTTOM = (float)HEIGHT - (float)(t1.getSize().y + 50);      // �÷��̾� y ��ġ��ǥ
	Position humanPos;
	humanPos.x = 50.0;
	humanPos.y = HUMAN_Y_BOTTOM;
	//�����ӿ� ���� �޹� ������ �ٲ��ֱ� ���� 4���� ����
	int index = 0; //�޹� ������ �ε���
	float frame = 5.0f; //
	float frameSpeed = 0.3f;
	const int changeCount = 10; //�� �����ӿ� ü���� ����
	const int gravity = 15; //�߷�, ������ �� ��� -> ���� �ٿ���!
	const int space = 3; //����, ���������� �̵��� �� ���
	bool isJumping = false; //���� ������
	bool isBottom = true; //�ٴڿ� ���� ��Ҵ���
	bool isSmall = false; //ũ�� �۾�����(��ũ����)


	//���� �ؽ�Ʈ�� ǥ��
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(10.f, 10.f);


	//����hp �ؽ�Ʈ�� ǥ��
	Text earthHpText;
	earthHpText.setFont(font);
	earthHpText.setCharacterSize(15);

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
	satietyText.setCharacterSize(15);
	satietyText.setFillColor(Color::Black);
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
	happyText.setCharacterSize(15);
	happyText.setFillColor(Color::Black);
	happyText.setPosition(530.f, 530.f);

	//�ູ�� ������ �� ������
	Texture happyTex;
	happyTex.loadFromFile("images/happy.png");
	Sprite happyIcon;
	happyIcon.setTexture(happyTex);
	happyIcon.setScale(Vector2f(1.1f, 1.1f));
	happyIcon.setPosition(535.f, 555.f);

	//��ź1
	Texture bombTex;
	bombTex.loadFromFile("images/bomb.png");
	Sprite bomb;
	bomb.setTexture(bombTex);
	bomb.setScale(Vector2f(1.0f, 0.9f));

	//��ź2
	Texture bomb2Tex;
	bomb2Tex.loadFromFile("images/bomb_2.png");
	Sprite bomb_2;
	bomb_2.setTexture(bomb2Tex);
	bomb_2.setScale(Vector2f(1.0f, 0.9f));

	//Ŀ��
	Texture coffeeTex;
	coffeeTex.loadFromFile("images/coffee.png");
	Sprite coffee;
	coffee.setTexture(coffeeTex);
	coffee.setScale(Vector2f(0.9f, 0.7f));

	//����ũ
	Texture cakeTex;
	cakeTex.loadFromFile("images/cake.png");
	Sprite cake;
	cake.setTexture(cakeTex);
	cake.setScale(Vector2f(0.9f, 0.7f));

	//ġŲ
	Texture chickenTex;
	chickenTex.loadFromFile("images/chicken.png");
	Sprite chicken;
	chicken.setTexture(chickenTex);
	chicken.setScale(Vector2f(0.9f, 0.7f));

	//����
	Texture pizzaTex;
	pizzaTex.loadFromFile("images/pizza.png");
	Sprite pizza;
	pizza.setTexture(pizzaTex);
	pizza.setScale(Vector2f(0.9f, 0.7f));

	//�ù����
	Texture boxTex;
	boxTex.loadFromFile("images/box.png");
	Sprite box;
	box.setTexture(boxTex);
	box.setScale(Vector2f(0.9f, 0.9f));

	//������ �迭
	Sprite item[20];
	item[0] = bomb;
	item[1] = cake;
	item[2] = coffee;
	item[3] = bomb_2;
	item[4] = chicken;
	item[5] = pizza;
	item[6] = box;

	std::vector<Sprite> items;
	items.push_back(Sprite(item[6]));

	//Sprite Healtem[2];
	//Healtem[0] = tree;
	//Healtem[1] = leaf;

	//std::vector<Sprite> Healtems;
	//Healtems.push_back(Sprite(Healtem[2]));

	//
	int bombSpawnTimer = 0;
	//����ũ ���� Ÿ�̸�(�ʱ�)
	int cakeSpawnTimer = 80;
	//Ŀ�� ���� Ÿ�̸�(�ʱ�)
	int coffeeSpawnTimer = 160;

	//
	int bomb2SpawnTimer = 0;
	//ġŲ, ����, ���� ���� Ÿ�̸�(�ʱ�)
	int chickenSpawnTimer = 400;
	int pizzaSpawnTimer = 200;
	int boxSpawnTimer = 300;  //����

	//����, �ٻ�� ���� Ÿ�̸�(�ʱ�)
	//int treeSpawnTimer = 160;
	//int leafSpawnTimer = 300;

		// ������
	Texture garbageTex1;
	garbageTex1.loadFromFile("images/garbage1.png");
	Sprite Garbage1;
	Garbage1.setTexture(garbageTex1);

	Texture garbageTex2;
	garbageTex2.loadFromFile("images/garbage2.png");
	Sprite Garbage2;
	Garbage2.setTexture(garbageTex2);

	Texture garbageTex3;
	garbageTex3.loadFromFile("images/garbage3.png");
	Sprite Garbage3;
	Garbage3.setTexture(garbageTex3);

	Texture garbageTex4;
	garbageTex4.loadFromFile("images/garbage4.png");
	Sprite Garbage4;
	Garbage4.setTexture(garbageTex4);

	Texture garbageTex5;
	garbageTex5.loadFromFile("images/garbage5.png");
	Sprite Garbage5;
	Garbage5.setTexture(garbageTex5);

	Texture garbageTex6;
	garbageTex5.loadFromFile("images/garbage6.png");
	Sprite Garbage6;
	Garbage6.setTexture(garbageTex6);

	Texture garbageTex7;
	garbageTex5.loadFromFile("images/garbage7.png");
	Sprite Garbage7;
	Garbage7.setTexture(garbageTex7);

	Texture garbageTex8;
	garbageTex8.loadFromFile("images/garbage8.png");
	Sprite Garbage8;
	Garbage8.setTexture(garbageTex8);

	Texture garbageTex9;
	garbageTex9.loadFromFile("images/garbage9.png");
	Sprite Garbage9;
	Garbage9.setTexture(garbageTex9);

	vector<Sprite> Garbages;
	Garbages.push_back(Garbage1);
	Garbages.push_back(Garbage2);
	Garbages.push_back(Garbage3);
	Garbages.push_back(Garbage4);
	Garbages.push_back(Garbage5);
	Garbages.push_back(Garbage6);
	Garbages.push_back(Garbage7);
	Garbages.push_back(Garbage8);
	Garbages.push_back(Garbage9);

	int CollisionTime = 0;

	//���� ������
	int earthHp = 100;
	static const int hpMax = 100; //�ִ밪 ����
	static const int hpMin = 0; //�ּҰ� ����
	RectangleShape hpBar;
	hpBar.setFillColor(Color::Green);
	hpBar.setSize(sf::Vector2f((float)earthHp * 5.f, 20.f));             //������ 
	hpBar.setPosition(200.f, 10.f);                                 //������ ��ġ��ǥ�� 200px, 10px

	//��� ������
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
	static const int satietyMin = 0; //���ּҰ� ����
	RectangleShape satietyGauge;
	satietyGauge.setFillColor(Color::Red);
	satietyGauge.setSize(Vector2f((float)satiety * 3.f, 20.f));       // ������ ���α��̴� 300px, ���α��̴� 20px
	satietyGauge.setPosition(80.f, 560.f);                            // ��ġ��ǥ�� 80px, 560px

	// �ູ�� ������ - ���� �����ϰ� 3�ʸ��� 1�� �پ��. �������� ���� �� ȸ���Ǹ� 0�� �Ǹ� ���ӿ���.
	int happy = 80;
	static const int happyMax = 100; //�ִ밪 ����
	static const int happyMin = 0; //���ּҰ� ����
	RectangleShape happyGauge;
	happyGauge.setFillColor(Color::Yellow);
	happyGauge.setSize(Vector2f((float)happy * 3.f, 20.f));          // ������ ���α��̴� 300px, ���α��̴� 20px
	happyGauge.setPosition(550.f, 560.f);                            // ��ġ��ǥ�� 550px, 560px

	//
	Clock score_clock;
	Clock gauge_clock;
	Clock switch_clock;
	Clock end_clock;


	//Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen()) // && earthHp > 0)
	{

		Time startTime = score_clock.getElapsedTime();            //startTime�� ���� �������� �󸶰� �������� �����. ���� ������ �Ǹ� startTime���� Game Score ���. 
		Time endTime = end_clock.getElapsedTime();
		Time gauge = gauge_clock.getElapsedTime();                  //������ ���� �� ��.
		cout << startTime.asSeconds() << endl;

		if (startTime.asSeconds() >= 1) //�� 1�� ������ 1���� �������� ���� ����.
		{
			startTime = score_clock.restart();
			GameScore++;
		}

		if (gauge.asSeconds() >= 3) {                               //
			gauge = gauge_clock.restart();                          //gauge�� 3�� �� ������ �ʱ�ȭ ��Ŵ. �׷��Ƿ� 3�ʸ��� �������� �ູ���� ���� 100���� 4�� �ٰ� ��.
			satiety = satiety - 5;
			happy = happy - 5;
		}

		/*       */
		Time SwitchingTime = switch_clock.getElapsedTime();
		if (SwitchingTime.asSeconds() >= 12) {
			SwitchingTime = switch_clock.restart();
			activeBackground++; // 12�ʸ��� activeBackground�� 1�� ����.
		}

		//�� �ٲ� ������ ������ �ٲ�� ����.
		if (activeBackground % 2 == 1)
		{
			background.setTexture(house);
			earthHpText.setFillColor(Color::Black); //�۾� ���� �ٲ���.
			item[0].setPosition(-100.f, 0.f);
			item[1].setPosition(-100.f, 0.f);
			item[2].setPosition(-100.f, 0.f);

			//������(��ź2, ġŲ, ����, ����) �̵�

			item[3].move(-9.0f, 0.f);  //������
			item[4].move(-6.0f, 0.f);  //������
			item[5].move(-7.5f, 0.f);  //������
			item[6].move(-10.5f, 0.f);

			//��ź2 ���� Ÿ�̸�
			if (bomb2SpawnTimer < 100)
				bomb2SpawnTimer++;

			if (bomb2SpawnTimer >= 100)
			{
				item[3].setPosition((float)window.getSize().x, (float)(rand() % 250 + 100));//��rand �ڿ� ���ڸ� �����ϱ�
				items.push_back(Sprite(item[3]));
				bomb2SpawnTimer = 0; //�ʱ�ȭ
			}


			//ġŲ ���� Ÿ�̸�
			if (chickenSpawnTimer < 808)
				chickenSpawnTimer++;

			if (chickenSpawnTimer >= 808)
			{
				item[4].setPosition((float)window.getSize().x, (float)(rand() % 270 + 200)); //��rand �ڿ� ���ڸ� �����ϱ�
				items.push_back(Sprite(item[4]));
				chickenSpawnTimer = 400; //�ʱ�ȭ
			}

			//���� ���� Ÿ�̸�
			if (pizzaSpawnTimer < 408)
				pizzaSpawnTimer++;

			if (pizzaSpawnTimer >= 408)
			{
				item[5].setPosition((float)window.getSize().x, (float)(rand() % 290 + 150)); //��rand �ڿ� ���ڸ� �����ϱ�
				items.push_back(Sprite(item[5]));
				pizzaSpawnTimer = 200; //�ʱ�ȭ
			}

			//���� ���� Ÿ�̸�
			if (boxSpawnTimer < 608)
				boxSpawnTimer++;

			if (boxSpawnTimer >= 608)
			{
				item[6].setPosition((float)window.getSize().x, (float)(rand() % 240 + 230));//��rand �ڿ� ���ڸ� �����ϱ�
				items.push_back(Sprite(item[6]));
				boxSpawnTimer = 300; //�ʱ�ȭ
			}

		}
		//
		else if (activeBackground % 2 == 0)
		{
			background.setTexture(cafe);
			earthHpText.setFillColor(Color::White); //�۾� ���� �ٲ���.

			item[3].setPosition(-100.f, 0.f);
			item[4].setPosition(-100.f, 0.f);
			item[5].setPosition(-100.f, 0.f);
			item[6].setPosition(-100.f, 0.f);


			item[0].move(-9.0f, 0.f);//�����ڸ� �����ϱ�
			item[1].move(-7.5f, 0.f);//�����ڸ� �����ϱ�
			item[2].move(-8.0f, 0.f);

			//��ź1 ���� Ÿ�̸�
			if (bombSpawnTimer < 100)
				bombSpawnTimer++;

			if (bombSpawnTimer >= 100)
			{
				item[0].setPosition((float)window.getSize().x, (float)(rand() % 280 + 215));//��rand �ڿ� ���ڸ� �����ϱ�
				items.push_back(Sprite(item[0]));
				bombSpawnTimer = 0; //�ʱ�ȭ
			}


			//����ũ ���� Ÿ�̸�
			if (cakeSpawnTimer < 268)
				cakeSpawnTimer++;

			if (cakeSpawnTimer >= 268)
			{
				item[1].setPosition((float)window.getSize().x, (float)(rand() % 270 + 150));//��rand �ڿ� ���ڸ� �����ϱ�
				items.push_back(Sprite(item[1]));
				cakeSpawnTimer = 80; //�ʱ�ȭ
			}

			//Ŀ�� ���� Ÿ�̸�
			if (coffeeSpawnTimer < 368)
				coffeeSpawnTimer++;

			if (coffeeSpawnTimer >= 368)
			{
				item[2].setPosition((float)window.getSize().x, (float)(rand() % 250 + 210));//��rand �ڿ� ���ڸ� �����ϱ�(�̰� cake���� ���� �ֱ�)
				items.push_back(Sprite(item[2]));
				coffeeSpawnTimer = 160; //�ʱ�ȭ
			}
		}  // �������
		Event event;
		window.pollEvent(event);

		if (event.type == Event::Closed)
			window.close();

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			return 0;
		}

		if (earthHp <= 0)
			return 3;
		if (satiety <= 0 && happy <= 0)
			return 3;


		/*Event event;
		while (window.pollEvent(event))
		{
			if(event.type == Event::KeyReleased)
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
		}*/


		//�浹
		for (size_t i = 0; i < items.size(); i++)
		{
			if (humanArr[index].getGlobalBounds().intersects(item[i].getGlobalBounds()))
			{
				earthHp--;
				satiety++;
				happy++;
				CollisionTime++;
				items.erase(items.begin() + i);

				if (satiety >= 100)
					satiety = satietyMax;

				if (happy >= 100)
					happy = happyMax;

			}
		}


		/*for (size_t i = 0; i < Healtems.size(); i++)
		{
			if (humanArr[index].getGlobalBounds().intersects(Healtem[i].getGlobalBounds()))
			{
				earthHp++;
				Healtems.erase(Healtems.begin() + i);

				if (satiety >= 100)
					satiety = satietyMax;

				if (happy >= 100)
					happy = happyMax;

				if (earthHp >= 100)
					earthHp = hpMax;
			}
		}*/

		if (satiety < 0)
			satiety = satietyMin; //�������� 0���� �۾����� 0�� �Ѿ�� �ʵ��� �ѵ� ����.
		if (happy < 0)
			happy = happyMin; //�������� 0���� �۾����� 0�� �Ѿ�� �ʵ��� �ѵ� ����.
		if (earthHp < 0)
			earthHp = hpMin; //����hp�� 0���� �۾����� 0�� �Ѿ�� �ʵ��� �ѵ� ����.


		if (Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();



		//��� ���� ����
		if (Keyboard::isKeyPressed(Keyboard::Space))//�����̽� �Է� ����
		{
			if (isBottom && !isJumping) //�ٴ��̰�, �����ϰ� ���� ���� �� ���� ����
			{
				isJumping = true;
				isBottom = false;
				isSmall = false;
			}
		}

		//���Ʒ�Ű�� ������ ũ�� �۾�����
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			isSmall = true;
			isJumping = false;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			isSmall = false;
		}
		//
		if (isSmall)
		{
			humanArr[index].setScale(Vector2f(0.8f, 0.8f));
			humanArr[index].setScale(Vector2f(0.8f, 0.8f));
			humanArr[index].setPosition(humanPos.x, humanPos.y - 350);
		}

		if (!isSmall)
		{
			humanArr[index].setScale(Vector2f(1.0f, 1.0f));
			humanArr[index].setScale(Vector2f(1.0f, 1.0f));
			humanArr[index].setPosition(humanPos.x, humanPos.y);
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
			humanPos.y = (float)HUMAN_Y_BOTTOM;
			isBottom = true;
		}
		if (humanPos.y <= HUMAN_Y_BOTTOM - 340) //�����ؼ� ���ַ� ���� �ʵ��� ����
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
		scoreText.setString("Score: " + std::to_string(GameScore));

		//

		window.clear();
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
		window.draw(earthIcon);
		window.draw(satietyIcon);
		window.draw(happyIcon);
		window.draw(scoreText);

		if (CollisionTime >= 10) window.draw(Garbages[0]);
		if (CollisionTime >= 20) window.draw(Garbages[1]);
		if (CollisionTime >= 30) window.draw(Garbages[2]);
		if (CollisionTime >= 40) window.draw(Garbages[3]);
		if (CollisionTime >= 50) window.draw(Garbages[4]);
		if (CollisionTime >= 60) window.draw(Garbages[5]);
		if (CollisionTime >= 70) window.draw(Garbages[6]);
		if (CollisionTime >= 80) window.draw(Garbages[7]);
		if (CollisionTime >= 90) window.draw(Garbages[8]);
		window.display();

	}

	return -1;
}