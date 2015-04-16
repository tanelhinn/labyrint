#pragma once
#include <SFML/Graphics.hpp>


#define MAX_NUMBER_OF_ITEMS 6

class Menu
{
public:
	Menu(float width, float height, int hasGameStarted);
	~Menu(void);

	void draw(sf::RenderWindow &window, int hasGameStarted);

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menuText[MAX_NUMBER_OF_ITEMS];


};

