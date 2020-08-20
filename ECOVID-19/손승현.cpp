#include <SFML/Graphics.hpp>
#include <time.h>
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

	srand(time(NULL));

	RenderWindow window(VideoMode(WIDTH, HEIGHT), "ECOVID-19");

	// 플레이어 
	Texture t1;
	Texture t2;
	t1.loadFromFile("images/human.png");
	t2.loadFromFile("images/human2.png");
	Sprite humanArr[2];
	humanArr[0] = Sprite(t1);
	humanArr[1] = Sprite(t2);

	// 플레이어 동작
	static const int HUMAN_Y_BOTTOM = HEIGHT - (t1.getSize().y + 50);      // 플레이어 y 위치좌표
	Position humanPos;
	humanPos.x = 50;
	humanPos.y = HUMAN_Y_BOTTOM;
	//프레임에 따라 왼발 오른발 바꿔주기 위한 4개의 변수
	int index = 0; //왼발 오른발 인덱스
	float frame = 10.0f;
	float frameSpeed = 10.0f;
	const int changeCount = 10; //몇 프레임에 체인지 할지
	const int gravity = 10; //중력, 점프할 때 사용
	bool isJumping = false; //점프 중인지
	bool isJumpingtwice = false; //이중 점프 중인지
	bool isBottom = true; //바닥에 발이 닿았는지

	//케이크
	Texture cakeTex;
	cakeTex.loadFromFile("images/cake.png");
	Sprite cake;
	cake.setTexture(cakeTex);
	cake.setScale(Vector2f(0.5f, 0.5f));
	int cakeSpawnTimer = 200;

	const int ITEM_SIZE = 10;
	Sprite item[ITEM_SIZE];
	for (int i = 0; i < ITEM_SIZE; i++) {
		item[i] = vector<Sprite> cakes;
	} 

	for (int i = 0; i < ITEM_SIZE; i++)
		cakes.push_back(Sprite(item[i]));


	//지구 게이지
	int hp = 120;
	RectangleShape hpBar;
	hpBar.setFillColor(Color::Green);
	hpBar.setSize(sf::Vector2f((float)hp * 5.f, 20.f));             //게이지 
	hpBar.setPosition(200.f, 10.f);                                 //게이지 위치좌표는 200px, 10px

	// 카페 배경 입히기
	Texture background;
	background.loadFromFile("images/coffeehouse.png");
	Sprite sBackground;
	sBackground.setPosition(0, 0);
	sBackground.setTexture(background);

	// 만족감 게이지 - 게임 시작하고 3초마다 1씩 줄어듦. 아이템을 먹을 시 회복되며 0이 되면 게임오버.
	int satiety = 100;
	RectangleShape satietyGauge;
	satietyGauge.setFillColor(Color::Red);
	satietyGauge.setSize(Vector2f((float)satiety * 3.f, 20.f));       // 게이지 가로길이는 300px, 세로길이는 20px
	satietyGauge.setPosition(80.f, 560.f);                            // 위치좌표는 80px, 560px

	// 행복감 게이지 - 게임 시작하고 3초마다 1씩 줄어듦. 아이템을 먹을 시 회복되며 0이 되면 게임오버.
	int happy = 100;
	RectangleShape happyGauge;
	happyGauge.setFillColor(Color::Yellow);
	happyGauge.setSize(Vector2f((float)happy * 3.f, 20.f));          // 게이지 가로길이는 300px, 세로길이는 20px
	happyGauge.setPosition(550.f, 560.f);                            // 위치좌표는 550px, 560px

	Clock clock;

	while (window.isOpen() && hp > 0)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}

		humanArr[index].setPosition(humanArr[index].getPosition().x, humanArr[index].getPosition().y);

		if (humanArr[index].getPosition().y > window.getSize().y - humanArr[index].getGlobalBounds().height)
			humanArr[index].setPosition(humanArr[index].getPosition().x, window.getSize().y - humanArr[index].getGlobalBounds().height);

		if (humanArr[index].getPosition().y < 0)
			humanArr[index].setPosition(humanArr[index].getPosition().x, 0);

		//케이크 이동
		for (size_t i = 0; i < cakes.size(); i++)
		{
			cakes[i].move(-50.0f, 0.f);

			if (cakes[i].getPosition().x < 0 - cake.getGlobalBounds().width)
				cakes.erase(cakes.begin() + i);
		}

		if (cakeSpawnTimer < 300)
			cakeSpawnTimer++;

		if (cakeSpawnTimer >= 300)
		{
			cake.setPosition(window.getSize().x, rand()%int(window.getSize().y - cake.getGlobalBounds().height));
			cakes.push_back(Sprite(cake));
			cakeSpawnTimer = 0;
		}

		//충돌
		for (size_t i = 0; i < cakes.size(); i++)
		{
			if (humanArr[index].getGlobalBounds().intersects(cakes[i].getGlobalBounds()))
			{
				hp--;
				satiety++;
				happy++;
				cakes.erase(cakes.begin() + i);
				if (satiety == 100)
					static const int satiety = 100;
				if (happy == 100)
					static const int happy = 100;
			}
		}

		Time startTime = clock.getElapsedTime();            // startTime은 게임 시작한지 얼마가 지났는지 기록함. 게임 오버가 되면 startTime으로 Game Score 계산. 
		Time now = clock.getElapsedTime();                  // now는 게이지 줄일 때 씀.
		cout << startTime.asSeconds() << endl;
		if (now.asSeconds() >= 3) {
			now = clock.restart();                          // now가 3초 될 때마다 초기화 시킴. 그러므로 3초마다 포만감과 행복감이 각각 100에서 1씩 줄게 됨.
			satiety = satiety - 3;
			happy = happy - 3;
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
		/*if (Keyboard::isKeyPressed(Keyboard::Up)) //윗키 감지
		{
			if (isBottom && !isJumpingtwice) //바닥이고, 이중 점프하지 않을 때 이중 점프 가능
			{
				isJumpingtwice = true;
				isBottom = false;
				
				humanPos.y = HUMAN_Y_BOTTOM - 300; //점프해서 우주로 가지 않도록 설정
				//{
					//isJumping = false;
					//isJumpingtwice = true;
					//isBottom = true;
				//}
			}
		}*/
		//사람 이중 점프
		if (isJumpingtwice)
		{
			humanPos.y -= (gravity * 2); //중력 2배
		}


		if (Keyboard::isKeyPressed(Keyboard::Down)) //아랫키를 누르면 아래로 내려오게끔 하기
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
			isJumpingtwice = false;
			//isBottom = true;
		}
		//사람 스텝
		frame += frameSpeed;
		if (frame > changeCount)
		{
			frame -= changeCount;
			++index;
			if (index >= 2) { index = 0; }
		}
		//케이크 움직임
		//if (cakePos.x <= 0)
		//{
			//cakePos.x = WIDTH;
		//}
		//else
		//{
			//cakePos.x -= cakeSpeed;
		//}

		//케이크 위치
		//cake.setPosition(cakePos.x, cakePos.y);
		//사람 위치
		humanArr[index].setPosition(humanPos.x, humanPos.y);

		hpBar.setSize(sf::Vector2f((float)hp * 5.f, 20.f));
		satietyGauge.setSize(Vector2f((float)satiety * 3.f, 20.f));
		happyGauge.setSize(Vector2f((float)happy * 3.f, 20.f));
		
		window.clear();
		window.draw(sBackground);
		window.draw(satietyGauge);
		window.draw(happyGauge);
		window.draw(humanArr[index]);
		for (size_t i = 0; i < cakes.size(); i++)
		{
			window.draw(cakes[i]);
		}
		window.draw(hpBar);
		window.display();

	}
	
	return 0;
}