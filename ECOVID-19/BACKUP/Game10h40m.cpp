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
	// 플레이어 
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

	// 플레이어 동작
	float HUMAN_Y_BOTTOM = (float)HEIGHT - (float)(t1.getSize().y + 50);      // 플레이어 y 위치좌표
	Position humanPos;
	humanPos.x = 50.0;
	humanPos.y = HUMAN_Y_BOTTOM;
	//프레임에 따라 왼발 오른발 바꿔주기 위한 4개의 변수
	int index = 0; //왼발 오른발 인덱스
	float frame = 5.0f; //
	float frameSpeed = 0.3f;
	const int changeCount = 10; //몇 프레임에 체인지 할지
	const int gravity = 15; //중력, 점프할 때 사용 -> 값을 줄였어!
	const int space = 3; //왼쪽, 오른쪽으로 이동할 때 사용
	bool isJumping = false; //점프 중인지
	bool isBottom = true; //바닥에 발이 닿았는지
	bool isSmall = false; //크기 작아지기(웅크리기)


	//점수 텍스트로 표시
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(10.f, 10.f);


	//지구hp 텍스트로 표시
	Text earthHpText;
	earthHpText.setFont(font);
	earthHpText.setCharacterSize(15);

	//지구hp 옆 아이콘
	Texture earthTex;
	earthTex.loadFromFile("images/earth.png");
	Sprite earthIcon;
	earthIcon.setTexture(earthTex);
	earthIcon.setScale(Vector2f(1.1f, 1.1f));
	earthIcon.setPosition(180.f, 5.f);

	//만족감 텍스트로 표시
	Text satietyText;
	satietyText.setFont(font);
	satietyText.setCharacterSize(15);
	satietyText.setFillColor(Color::Black);
	satietyText.setPosition(70.f, 530.f);

	//만족감 게이지 옆 아이콘
	Texture satietyTex;
	satietyTex.loadFromFile("images/satiety.png");
	Sprite satietyIcon;
	satietyIcon.setTexture(satietyTex);
	satietyIcon.setScale(Vector2f(1.1f, 1.1f));
	satietyIcon.setPosition(65.f, 555.f);

	//행복감 텍스트로 표시
	Text happyText;
	happyText.setFont(font);
	happyText.setCharacterSize(15);
	happyText.setFillColor(Color::Black);
	happyText.setPosition(530.f, 530.f);

	//행복감 게이지 옆 아이콘
	Texture happyTex;
	happyTex.loadFromFile("images/happy.png");
	Sprite happyIcon;
	happyIcon.setTexture(happyTex);
	happyIcon.setScale(Vector2f(1.1f, 1.1f));
	happyIcon.setPosition(535.f, 555.f);

	//폭탄1
	Texture bombTex;
	bombTex.loadFromFile("images/bomb.png");
	Sprite bomb;
	bomb.setTexture(bombTex);
	bomb.setScale(Vector2f(1.0f, 0.9f));

	//폭탄2
	Texture bomb2Tex;
	bomb2Tex.loadFromFile("images/bomb_2.png");
	Sprite bomb_2;
	bomb_2.setTexture(bomb2Tex);
	bomb_2.setScale(Vector2f(1.0f, 0.9f));

	//커피
	Texture coffeeTex;
	coffeeTex.loadFromFile("images/coffee.png");
	Sprite coffee;
	coffee.setTexture(coffeeTex);
	coffee.setScale(Vector2f(0.9f, 0.7f));

	//케이크
	Texture cakeTex;
	cakeTex.loadFromFile("images/cake.png");
	Sprite cake;
	cake.setTexture(cakeTex);
	cake.setScale(Vector2f(0.9f, 0.7f));

	//치킨
	Texture chickenTex;
	chickenTex.loadFromFile("images/chicken.png");
	Sprite chicken;
	chicken.setTexture(chickenTex);
	chicken.setScale(Vector2f(0.9f, 0.7f));

	//피자
	Texture pizzaTex;
	pizzaTex.loadFromFile("images/pizza.png");
	Sprite pizza;
	pizza.setTexture(pizzaTex);
	pizza.setScale(Vector2f(0.9f, 0.7f));

	//택배상자
	Texture boxTex;
	boxTex.loadFromFile("images/box.png");
	Sprite box;
	box.setTexture(boxTex);
	box.setScale(Vector2f(0.9f, 0.9f));

	//아이템 배열
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
	//케이크 생성 타이머(초기)
	int cakeSpawnTimer = 80;
	//커피 생성 타이머(초기)
	int coffeeSpawnTimer = 160;

	//
	int bomb2SpawnTimer = 0;
	//치킨, 피자, 상자 생성 타이머(초기)
	int chickenSpawnTimer = 400;
	int pizzaSpawnTimer = 200;
	int boxSpawnTimer = 300;  //숫자

	//나무, 잎사귀 생성 타이머(초기)
	//int treeSpawnTimer = 160;
	//int leafSpawnTimer = 300;

		// 쓰레기
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

	//지구 게이지
	int earthHp = 100;
	static const int hpMax = 100; //최대값 설정
	static const int hpMin = 0; //최소값 설정
	RectangleShape hpBar;
	hpBar.setFillColor(Color::Green);
	hpBar.setSize(sf::Vector2f((float)earthHp * 5.f, 20.f));             //게이지 
	hpBar.setPosition(200.f, 10.f);                                 //게이지 위치좌표는 200px, 10px

	//배경 입히기
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

	// 만족감 게이지 - 게임 시작하고 3초마다 1씩 줄어듦. 아이템을 먹을 시 회복되며 0이 되면 게임오버.
	int satiety = 80;
	static const int satietyMax = 100; //최대값 설정
	static const int satietyMin = 0; //♥최소값 설정
	RectangleShape satietyGauge;
	satietyGauge.setFillColor(Color::Red);
	satietyGauge.setSize(Vector2f((float)satiety * 3.f, 20.f));       // 게이지 가로길이는 300px, 세로길이는 20px
	satietyGauge.setPosition(80.f, 560.f);                            // 위치좌표는 80px, 560px

	// 행복감 게이지 - 게임 시작하고 3초마다 1씩 줄어듦. 아이템을 먹을 시 회복되며 0이 되면 게임오버.
	int happy = 80;
	static const int happyMax = 100; //최대값 설정
	static const int happyMin = 0; //♥최소값 설정
	RectangleShape happyGauge;
	happyGauge.setFillColor(Color::Yellow);
	happyGauge.setSize(Vector2f((float)happy * 3.f, 20.f));          // 게이지 가로길이는 300px, 세로길이는 20px
	happyGauge.setPosition(550.f, 560.f);                            // 위치좌표는 550px, 560px

	//
	Clock score_clock;
	Clock gauge_clock;
	Clock switch_clock;
	Clock end_clock;


	//Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen()) // && earthHp > 0)
	{

		Time startTime = score_clock.getElapsedTime();            //startTime은 게임 시작한지 얼마가 지났는지 기록함. 게임 오버가 되면 startTime으로 Game Score 계산. 
		Time endTime = end_clock.getElapsedTime();
		Time gauge = gauge_clock.getElapsedTime();                  //게이지 줄일 때 씀.
		cout << startTime.asSeconds() << endl;

		if (startTime.asSeconds() >= 1) //♥ 1초 지나면 1점씩 오르도록 점수 설정.
		{
			startTime = score_clock.restart();
			GameScore++;
		}

		if (gauge.asSeconds() >= 3) {                               //
			gauge = gauge_clock.restart();                          //gauge가 3초 될 때마다 초기화 시킴. 그러므로 3초마다 포만감과 행복감이 각각 100에서 4씩 줄게 됨.
			satiety = satiety - 5;
			happy = happy - 5;
		}

		/*       */
		Time SwitchingTime = switch_clock.getElapsedTime();
		if (SwitchingTime.asSeconds() >= 12) {
			SwitchingTime = switch_clock.restart();
			activeBackground++; // 12초마다 activeBackground가 1씩 증가.
		}

		//맵 바뀔 때마다 아이템 바뀌도록 설정.
		if (activeBackground % 2 == 1)
		{
			background.setTexture(house);
			earthHpText.setFillColor(Color::Black); //글씨 색깔 바꿔줌.
			item[0].setPosition(-100.f, 0.f);
			item[1].setPosition(-100.f, 0.f);
			item[2].setPosition(-100.f, 0.f);

			//아이템(폭탄2, 치킨, 피자, 상자) 이동

			item[3].move(-9.0f, 0.f);  //♥숫자
			item[4].move(-6.0f, 0.f);  //♥숫자
			item[5].move(-7.5f, 0.f);  //♥숫자
			item[6].move(-10.5f, 0.f);

			//폭탄2 생성 타이머
			if (bomb2SpawnTimer < 100)
				bomb2SpawnTimer++;

			if (bomb2SpawnTimer >= 100)
			{
				item[3].setPosition((float)window.getSize().x, (float)(rand() % 250 + 100));//♥rand 뒤에 숫자만 수정하기
				items.push_back(Sprite(item[3]));
				bomb2SpawnTimer = 0; //초기화
			}


			//치킨 생성 타이머
			if (chickenSpawnTimer < 808)
				chickenSpawnTimer++;

			if (chickenSpawnTimer >= 808)
			{
				item[4].setPosition((float)window.getSize().x, (float)(rand() % 270 + 200)); //♥rand 뒤에 숫자만 수정하기
				items.push_back(Sprite(item[4]));
				chickenSpawnTimer = 400; //초기화
			}

			//피자 생성 타이머
			if (pizzaSpawnTimer < 408)
				pizzaSpawnTimer++;

			if (pizzaSpawnTimer >= 408)
			{
				item[5].setPosition((float)window.getSize().x, (float)(rand() % 290 + 150)); //♥rand 뒤에 숫자만 수정하기
				items.push_back(Sprite(item[5]));
				pizzaSpawnTimer = 200; //초기화
			}

			//상자 생성 타이머
			if (boxSpawnTimer < 608)
				boxSpawnTimer++;

			if (boxSpawnTimer >= 608)
			{
				item[6].setPosition((float)window.getSize().x, (float)(rand() % 240 + 230));//♥rand 뒤에 숫자만 수정하기
				items.push_back(Sprite(item[6]));
				boxSpawnTimer = 300; //초기화
			}

		}
		//
		else if (activeBackground % 2 == 0)
		{
			background.setTexture(cafe);
			earthHpText.setFillColor(Color::White); //글씨 색깔 바꿔줌.

			item[3].setPosition(-100.f, 0.f);
			item[4].setPosition(-100.f, 0.f);
			item[5].setPosition(-100.f, 0.f);
			item[6].setPosition(-100.f, 0.f);


			item[0].move(-9.0f, 0.f);//♥숫자만 수정하기
			item[1].move(-7.5f, 0.f);//♥숫자만 수정하기
			item[2].move(-8.0f, 0.f);

			//폭탄1 생성 타이머
			if (bombSpawnTimer < 100)
				bombSpawnTimer++;

			if (bombSpawnTimer >= 100)
			{
				item[0].setPosition((float)window.getSize().x, (float)(rand() % 280 + 215));//♥rand 뒤에 숫자만 수정하기
				items.push_back(Sprite(item[0]));
				bombSpawnTimer = 0; //초기화
			}


			//케이크 생성 타이머
			if (cakeSpawnTimer < 268)
				cakeSpawnTimer++;

			if (cakeSpawnTimer >= 268)
			{
				item[1].setPosition((float)window.getSize().x, (float)(rand() % 270 + 150));//♥rand 뒤에 숫자만 수정하기
				items.push_back(Sprite(item[1]));
				cakeSpawnTimer = 80; //초기화
			}

			//커피 생성 타이머
			if (coffeeSpawnTimer < 368)
				coffeeSpawnTimer++;

			if (coffeeSpawnTimer >= 368)
			{
				item[2].setPosition((float)window.getSize().x, (float)(rand() % 250 + 210));//♥rand 뒤에 숫자만 수정하기(이거 cake껄로 숫자 넣기)
				items.push_back(Sprite(item[2]));
				coffeeSpawnTimer = 160; //초기화
			}
		}  // 여기까지
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


		//충돌
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
			satiety = satietyMin; //만족감이 0보다 작아지면 0을 넘어가지 않도록 한도 설정.
		if (happy < 0)
			happy = happyMin; //만족감이 0보다 작아지면 0을 넘어가지 않도록 한도 설정.
		if (earthHp < 0)
			earthHp = hpMin; //지구hp가 0보다 작아지면 0을 넘어가지 않도록 한도 설정.


		if (Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();



		//사람 점프 구현
		if (Keyboard::isKeyPressed(Keyboard::Space))//스페이스 입력 감지
		{
			if (isBottom && !isJumping) //바닥이고, 점프하고 있지 않을 때 점프 가능
			{
				isJumping = true;
				isBottom = false;
				isSmall = false;
			}
		}

		//♥아랫키를 누르면 크기 작아지기
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
			humanPos.y -= gravity; //점프 중일때는 중력 뺴주기
		}
		else
		{
			humanPos.y += gravity; //점프하지 않을 때는 중력 더해서 아래로 가게끔 해주기
		}
		if (humanPos.y >= HUMAN_Y_BOTTOM) //바닥에서 지하로 가지 않도록 설정
		{
			humanPos.y = (float)HUMAN_Y_BOTTOM;
			isBottom = true;
		}
		if (humanPos.y <= HUMAN_Y_BOTTOM - 340) //점프해서 우주로 가지 않도록 설정
		{
			isJumping = false;
		}

		//사람 스텝
		frame += frameSpeed;
		if (frame > changeCount)
		{
			frame -= changeCount;
			++index;
			if (index >= 2) { index = 0; }
		}

		//사람 위치
		humanArr[index].setPosition(humanPos.x, humanPos.y);
		//earthHpText.setPosition(humanArr[index].getPosition().x, humanArr[index].getPosition().y - hpText.getGlobalBounds().height); <-이건 무시해도 돼!

		//지구hp 텍스트 위치
		earthHpText.setPosition(190.f, 30.f);
		//지구hp 나타내주는 텍스트
		earthHpText.setString("Earth : " + std::to_string(earthHp) + "/" + std::to_string(hpMax));
		//만족감 나타내주는 텍스트
		satietyText.setString("Satiety : " + std::to_string(satiety) + "/" + std::to_string(satietyMax));
		//행복감 나타내주는 텍스트
		happyText.setString("Happy : " + std::to_string(happy) + "/" + std::to_string(happyMax));

		//캐릭터가 윈도우 창에서 벗어나지 않게끔 해주는 if문들
		if (humanArr[index].getPosition().y > window.getSize().y - humanArr[index].getGlobalBounds().height)
			humanArr[index].setPosition(humanArr[index].getPosition().x, window.getSize().y - humanArr[index].getGlobalBounds().height);

		if (humanArr[index].getPosition().y < 0)
			humanArr[index].setPosition(humanArr[index].getPosition().x, 0);

		if (humanArr[index].getPosition().x < 0)
			humanArr[index].setPosition(0, humanArr[index].getPosition().y);

		if (humanArr[index].getPosition().x > window.getSize().x - humanArr[index].getGlobalBounds().width)
			humanArr[index].setPosition(window.getSize().x - humanArr[index].getGlobalBounds().width, humanArr[index].getPosition().y);

		//3가지 게이지들 크기
		hpBar.setSize(sf::Vector2f((float)earthHp * 5.f, 20.f));
		satietyGauge.setSize(Vector2f((float)satiety * 3.f, 20.f));
		happyGauge.setSize(Vector2f((float)happy * 3.f, 20.f));

		//점수 업데이트
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