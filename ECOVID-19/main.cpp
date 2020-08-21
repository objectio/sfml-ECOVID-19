#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Screen.h"
#include <iostream>
#define WIDTH 900
#define HEIGHT 600

using namespace std;
using namespace sf;

int main(int argc, char** argv)
{
	vector<virtualScreen*> Screens;
	int screen = 0;

	RenderWindow window(VideoMode(WIDTH, HEIGHT), "ECOVID-19");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(70);

	Menu s0;
	Screens.push_back(&s0);
	Game s1;
	Screens.push_back(&s1);
	Explain s2;
	Screens.push_back(&s2);
	GameOver s3;
	Screens.push_back(&s3);

	while (screen >= 0)
	{
		screen = Screens[screen]->Run(window);
	}
	system("pause");
	return EXIT_SUCCESS;
}