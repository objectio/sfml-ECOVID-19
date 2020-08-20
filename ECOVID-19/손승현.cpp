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

	// �÷��̾� 
	Texture t1;
	Texture t2;
	t1.loadFromFile("images/human.png");
	t2.loadFromFile("images/human2.png");
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
	float frame = 10.0f;
	float frameSpeed = 10.0f;
	const int changeCount = 10; //�� �����ӿ� ü���� ����
	const int gravity = 10; //�߷�, ������ �� ���
	bool isJumping = false; //���� ������
	bool isJumpingtwice = false; //���� ���� ������
	bool isBottom = true; //�ٴڿ� ���� ��Ҵ���

	//����ũ
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


	//���� ������
	int hp = 120;
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

		//����ũ �̵�
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

		//�浹
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

		Time startTime = clock.getElapsedTime();            // startTime�� ���� �������� �󸶰� �������� �����. ���� ������ �Ǹ� startTime���� Game Score ���. 
		Time now = clock.getElapsedTime();                  // now�� ������ ���� �� ��.
		cout << startTime.asSeconds() << endl;
		if (now.asSeconds() >= 3) {
			now = clock.restart();                          // now�� 3�� �� ������ �ʱ�ȭ ��Ŵ. �׷��Ƿ� 3�ʸ��� �������� �ູ���� ���� 100���� 1�� �ٰ� ��.
			satiety = satiety - 3;
			happy = happy - 3;
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
		/*if (Keyboard::isKeyPressed(Keyboard::Up)) //��Ű ����
		{
			if (isBottom && !isJumpingtwice) //�ٴ��̰�, ���� �������� ���� �� ���� ���� ����
			{
				isJumpingtwice = true;
				isBottom = false;
				
				humanPos.y = HUMAN_Y_BOTTOM - 300; //�����ؼ� ���ַ� ���� �ʵ��� ����
				//{
					//isJumping = false;
					//isJumpingtwice = true;
					//isBottom = true;
				//}
			}
		}*/
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
			isJumpingtwice = false;
			//isBottom = true;
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
		//if (cakePos.x <= 0)
		//{
			//cakePos.x = WIDTH;
		//}
		//else
		//{
			//cakePos.x -= cakeSpeed;
		//}

		//����ũ ��ġ
		//cake.setPosition(cakePos.x, cakePos.y);
		//��� ��ġ
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