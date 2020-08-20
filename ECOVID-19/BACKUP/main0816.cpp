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

	// 플레이어 
	Texture t1;
	Texture t2;
	t1.loadFromFile("images/run1.png");  
	t2.loadFromFile("images/run2.png");  
	Sprite humanArr[2];
	humanArr[0] = Sprite(t1);
	humanArr[1] = Sprite(t2);

	Font font;
	font.loadFromFile("neodgm.ttf");

	// 플레이어 동작
	static const int HUMAN_Y_BOTTOM = HEIGHT - (t1.getSize().y + 50);      // 플레이어 y 위치좌표
	Position humanPos;
	humanPos.x = 50;
	humanPos.y = HUMAN_Y_BOTTOM;
	//프레임에 따라 왼발 오른발 바꿔주기 위한 4개의 변수
	int index = 0; //왼발 오른발 인덱스
	float frame = 5.0f; //
	float frameSpeed = 0.3f; // -> 값을 줄였어!
	const int changeCount = 10; //몇 프레임에 체인지 할지
	const int gravity = 15; //중력, 점프할 때 사용 -> 값을 줄였어!
	const int space = 3; //왼쪽, 오른쪽으로 이동할 때 사용
	bool isJumping = false; //점프 중인지
	bool isBottom = true; //바닥에 발이 닿았는지
	bool isLeft = false; //왼쪽으로 이동하는지
	bool isRight = false; //오른쪽으로 이동하는지

	int score = 0;

	//점수 텍스트로 표시
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(10.f, 10.f);

	//지구hp 텍스트로 표시
	Text earthHpText;
	earthHpText.setFont(font);
	earthHpText.setCharacterSize(12);
	earthHpText.setFillColor(Color::White);

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
	satietyText.setCharacterSize(12);
	satietyText.setFillColor(Color::White);
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
	happyText.setCharacterSize(12);
	happyText.setFillColor(Color::White);
	happyText.setPosition(530.f, 530.f);

	//행복감 게이지 옆 아이콘
	Texture happyTex;
	happyTex.loadFromFile("images/happy.png");
	Sprite happyIcon;
	happyIcon.setTexture(happyTex);
	happyIcon.setScale(Vector2f(1.1f, 1.1f));
	happyIcon.setPosition(535.f, 555.f);

	//케이크
	Texture cakeTex;
	cakeTex.loadFromFile("images/cake.png");
	Sprite cake;
	cake.setTexture(cakeTex);
	cake.setScale(Vector2f(0.5f, 0.5f));
	Position cakePos;
	cakePos.x = WIDTH - 20;
	cakePos.y = HEIGHT - cakeTex.getSize().y;
	//케이크 속도
	float cakeSpeed = 0.3f;

	//커피
	Texture coffeeTex;
	coffeeTex.loadFromFile("images/coffee.png");
	Sprite coffee;
	coffee.setTexture(coffeeTex);
	coffee.setScale(Vector2f(0.5f, 0.5f));
	Position coffeePos;
	coffeePos.x = WIDTH - 10;
	coffeePos.y = HEIGHT - coffeeTex.getSize().y;
	//커피 속도
	float coffeeSpeed = 0.3f;

	//치킨
	Texture chickenTex;
	chickenTex.loadFromFile("images/chicken.png");
	Sprite chicken;
	chicken.setTexture(chickenTex);
	chicken.setScale(Vector2f(0.5f, 0.5f));
	Position chickenPos;
	chickenPos.x = WIDTH - 20;
	chickenPos.y = HEIGHT - chickenTex.getSize().y;
	//치킨 속도
	float chickenSpeed = 0.3f;

	//피자
	Texture pizzaTex;
	pizzaTex.loadFromFile("images/pizza.png");
	Sprite pizza;
	pizza.setTexture(pizzaTex);
	pizza.setScale(Vector2f(0.5f, 0.5f));
	Position pizzaPos;
	pizzaPos.x = WIDTH - 25;
	pizzaPos.y = HEIGHT - pizzaTex.getSize().y;
	//피자 속도
	float pizzaSpeed = 0.3f;

	//택배상자
	Texture boxTex;
	boxTex.loadFromFile("images/cake.png");
	Sprite box;
	box.setTexture(boxTex);
	box.setScale(Vector2f(0.5f, 0.5f));
	Position boxPos;
	boxPos.x = WIDTH - 40;
	boxPos.y = HEIGHT - boxTex.getSize().y;
	//택배상자 속도
	float boxSpeed = 1.0f;

	//아이템 배열
	Sprite item[10];
	item[0] = cake;
	item[1] = coffee;
	item[2] = chicken;
	item[3] = pizza;
	item[4] = box;

	std::vector<Sprite> items;

	//케이크 생성 타이머(초기)
	int cakeSpawnTimer = 0;
	//커피 생성 타이머(초기)
	int coffeeSpawnTimer = 20; //커피 생성과 케이크 생성에서 시간차를 두기 위해 20으로 늘림.

	// 쓰레기
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

	//지구 게이지
	int earthHp = 100;
	int hpMax = 100; //최대값 설정
	RectangleShape hpBar;
	hpBar.setFillColor(Color(125,215,66,255));
	hpBar.setSize(sf::Vector2f((float)earthHp * 5.f, 20.f));             //게이지 
	hpBar.setPosition(200.f, 10.f);                                 //게이지 위치좌표는 200px, 10px

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
	RectangleShape satietyGauge;
	satietyGauge.setFillColor(Color(255,175,31,255));
	satietyGauge.setSize(Vector2f((float)satiety * 3.f, 20.f));       // 게이지 가로길이는 300px, 세로길이는 20px
	satietyGauge.setPosition(80.f, 560.f);                            // 위치좌표는 80px, 560px

	// 행복감 게이지 - 게임 시작하고 3초마다 1씩 줄어듦. 아이템을 먹을 시 회복되며 0이 되면 게임오버.
	int happy = 80;
	static const int happyMax = 100; //최대값 설정
	RectangleShape happyGauge;
	happyGauge.setFillColor(Color(223,95,68,255));
	happyGauge.setSize(Vector2f((float)happy * 3.f, 20.f));          // 게이지 가로길이는 300px, 세로길이는 20px
	happyGauge.setPosition(550.f, 560.f);                            // 위치좌표는 550px, 560px

	Clock score_clock;
	Clock gauge_clock;
	Clock switch_clock;

	RectangleShape fade;
	fade.setSize(Vector2f(window.getSize().x, window.getSize().y));
	Uint8 a = 0;

	Menu menu();

	while (window.isOpen() && earthHp > 0)
	{
		Time startTime = score_clock.getElapsedTime();            // startTime은 게임 시작한지 얼마가 지났는지 기록함. 게임 오버가 되면 startTime으로 Game Score 계산. 
		Time gauge = gauge_clock.getElapsedTime();                  // 게이지 줄일 때 씀.
		cout << startTime.asSeconds() << endl;
		
		if (startTime.asSeconds() >= 1)
		{
			startTime = score_clock.restart();
			score++;
		}

		if (gauge.asSeconds() >= 3) {                         
			gauge = gauge_clock.restart();                          // gauge가 3초 될 때마다 초기화 시킴. 그러므로 3초마다 포만감과 행복감이 각각 100에서 1씩 줄게 됨.
			satiety = satiety - 5;
			happy = happy - 5;
		}

		Time SwitchingTime = switch_clock.getElapsedTime();
		if (SwitchingTime.asSeconds() >= 12) {
			SwitchingTime = switch_clock.restart();
			activeBackground++; // 12초마다 activeBackground가 1씩 증가.
			
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

		//아이템(커피, 케이크) 이동
		for (size_t i = 0; i < items.size(); i++)
		{
			item[i].move(-9.5f, 0.f);

			if (item[i].getPosition().x < 0 - item[i].getGlobalBounds().width)
				items.erase(items.begin() + i);
		}

		//케이크 생성 타이머
		if (cakeSpawnTimer < 120)
			cakeSpawnTimer++;

		if (cakeSpawnTimer >= 120)
		{
			item[0].setPosition(window.getSize().x, rand() % int(window.getSize().y - item[0].getGlobalBounds().height));
			items.push_back(Sprite(item[0]));
			cakeSpawnTimer = 0; //초기화
		}

		//커피 생성 타이머
		if (coffeeSpawnTimer < 140.5)
			coffeeSpawnTimer++;

		if (coffeeSpawnTimer >= 140.5)
		{
			item[1].setPosition(window.getSize().x, rand() % int(window.getSize().y - item[1].getGlobalBounds().height));
			items.push_back(Sprite(item[1]));
			coffeeSpawnTimer = 20; //초기화
		}

		//충돌
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
					satiety = satietyMax; //만족감이 100을 넘어가도 100을 초과하지 않도록 한도 설정.
				if (happy >= 100)
					happy = happyMax; //행복감이 100을 넘어가도 100을 초과하지 않도록 한도 설정
				Sprite GarbageInputSprite;
				//Garbages.push_back(GarbageInputSprite);
				//Garbages[i].setPosition(GarbagesPosition.x, GarbagesPosition.y);
				//Garbages[i].setTexture(GarbagesTexture[SelectedGarbage]);
			
	
			}
			
		}

		//사람 점프 구현
		if (Keyboard::isKeyPressed(Keyboard::Space))//스페이스 입력 감지
		{
			if (isBottom && !isJumping) //바닥이고, 점프하고 있지 않을 때 점프 가능
			{
				isJumping = true;
				isBottom = false;
			}
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
			humanPos.y = HUMAN_Y_BOTTOM;
			isBottom = true;
		}
		if (humanPos.y <= HUMAN_Y_BOTTOM - 400) //점프해서 우주로 가지 않도록 설정
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

		//아이템들 위치
		cake.setPosition(cakePos.x, cakePos.y);
		coffee.setPosition(coffeePos.x, coffeePos.y);
		chicken.setPosition(chickenPos.x, chickenPos.y);
		pizza.setPosition(pizzaPos.x, pizzaPos.y);
		box.setPosition(boxPos.x, boxPos.y);

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