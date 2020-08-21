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
	Music music;
	if (!music.openFromFile("Hot-Coffee.ogg"))
		return -1;
	music.play();

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

	Texture bomb1;
	bomb1.loadFromFile("images/bomb.png");

	//케이크
	Texture cake;
	cake.loadFromFile("images/cake.png");

	//커피
	Texture coffee;
	coffee.loadFromFile("images/coffee.png");

	//치킨
	Texture chicken;
	chicken.loadFromFile("images/chicken.png");

	//피자
	Texture pizza;
	pizza.loadFromFile("images/pizza.png");

	//택배상자
	Texture box;
	box.loadFromFile("images/box.png");
	
	int itemGroup = 0;
	int itemCheck = 2;

	Sprite item;
	item.setScale(Vector2f(0.9f, 0.9f));
	vector<Sprite> items;
	items.push_back(Sprite(item));
	int boxSpawnTimer = 15;


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

		Time SwitchingTime = switch_clock.getElapsedTime();
		if (SwitchingTime.asSeconds() >= 12) {
			SwitchingTime = switch_clock.restart();
			activeBackground++; // 12초마다 activeBackground가 1씩 증가.
		}

		//맵 바뀔 때마다 아이템 바뀌도록 설정.
		if (activeBackground % 2 == 1)
		{
			//itemCheck++;
			background.setTexture(house);
			earthHpText.setFillColor(Color::Black); //글씨 색깔 바꿔줌.
			
			if (itemCheck == 1) {
				item.setTexture(chicken);
				itemCheck = 2;
			}

			else if (itemCheck == 2) {
				item.setTexture(pizza);
				itemCheck = 3;
			}

			else if (itemCheck == 3) {
				item.setTexture(box);
				itemCheck = 1;
			}

		}
		else if (activeBackground % 2 == 0)
		{
		
			background.setTexture(cafe);
			earthHpText.setFillColor(Color::White); //글씨 색깔 바꿔줌.
			if (itemCheck == 1) {
				item.setTexture(cake);
				itemCheck = 2;
			}

			else if (itemCheck == 2) {
				item.setTexture(coffee);
				itemCheck = 3;
			}

			else if (itemCheck == 3) {
				item.setTexture(bomb1);
				itemCheck = 1;
			}
		}
		Event event;
		window.pollEvent(event);

		if (event.type == Event::Closed)
			window.close();

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			return 0;
		}

		if (earthHp <= 0) {
			music.stop();
			return 3;
		}
		if (satiety <= 0 && happy <= 0) {
			music.stop();
			return 3;
		}

		//상자 이동
		for (size_t i = 0; i < items.size(); i++)
		{
			items[i].move(-7.0f, 0.f);

			if (items[i].getPosition().x < 0 - item.getGlobalBounds().width)
				items.erase(items.begin() + i);
		}

		if (boxSpawnTimer < 50)
			boxSpawnTimer++;

		if (boxSpawnTimer >= 50)
		{
			item.setPosition(window.getSize().x, rand() % 250 + 100);
			items.push_back(Sprite(item));
			boxSpawnTimer = 0;
		}

		//충돌
		for (size_t i = 0; i < items.size(); i++)
		{
			if (humanArr[index].getGlobalBounds().intersects(items[i].getGlobalBounds()))
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
			window.draw(items[i]);
		}
		window.draw(hpBar);
		window.draw(earthHpText);
		window.draw(satietyText);
		window.draw(happyText);
		window.draw(earthIcon);
		window.draw(satietyIcon);
		window.draw(happyIcon);
		window.draw(scoreText);

		if (CollisionTime >= 15) window.draw(Garbages[0]);
		if (CollisionTime >= 30) window.draw(Garbages[1]);
		if (CollisionTime >= 45) window.draw(Garbages[2]);
		if (CollisionTime >= 60) window.draw(Garbages[3]);
		if (CollisionTime >= 75) window.draw(Garbages[4]);
		if (CollisionTime >= 90) window.draw(Garbages[5]);
		if (CollisionTime >= 105) window.draw(Garbages[6]);
		if (CollisionTime >= 120) window.draw(Garbages[7]);
		if (CollisionTime >= 135) window.draw(Garbages[8]);
		window.display();

	}

	return -1;
}