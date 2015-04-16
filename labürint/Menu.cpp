#include "Menu.h"
#include <iostream>


Menu::Menu(float width, float height, int hasGameStarted)
{

	if(!font.loadFromFile("Data/mainfont.ttf"))
	{
		std::cout << "Error loading mainfont.ttf" << std::endl;
	}
	if(hasGameStarted == 0)
	{
		menuText[0].setFont(font);
		menuText[0].setColor(sf::Color(221,0,29));
		menuText[0].setString("Labürint");
		menuText[0].setCharacterSize(50);
		menuText[0].setPosition(sf::Vector2f(width / 11, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

		menuText[1].setFont(font);
		menuText[1].setColor(sf::Color(255,178,0));
		menuText[1].setString("JUHEND: Mängija 1 liigub nuppudega WASD, mängija 2 nooltega");
		menuText[1].setCharacterSize(30);
		menuText[1].setPosition(sf::Vector2f(width / 11, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

		menuText[2].setFont(font);
		menuText[2].setColor(sf::Color(255,178,0));
		menuText[2].setString("Jookse oma sõbraga punase alani, et läbida tase.");
		menuText[2].setCharacterSize(25);
		menuText[2].setPosition(sf::Vector2f(width / 11, height / (MAX_NUMBER_OF_ITEMS + 1) * 3 - 50));

		menuText[3].setFont(font);
		menuText[3].setColor(sf::Color(255,178,0));
		menuText[3].setString("Punase alani jõudes saad ühe punkti juurde! Võidab see, kellel neid on rohkem.");
		menuText[3].setCharacterSize(25);
		menuText[3].setPosition(sf::Vector2f(width / 11, height / (MAX_NUMBER_OF_ITEMS + 1) * 4 - 100));

		menuText[4].setFont(font);
		menuText[4].setColor(sf::Color(255,178,0));
		menuText[4].setString("Seintele vastu minnes alustad taseme algusest!");
		menuText[4].setCharacterSize(25);
		menuText[4].setPosition(sf::Vector2f(width / 11, height / (MAX_NUMBER_OF_ITEMS + 1) * 5 - 150));

		menuText[5].setFont(font);
		menuText[5].setColor(sf::Color(62,219,0));
		menuText[5].setString("Vajuta tühikut, et alustada mängu!");
		menuText[5].setCharacterSize(35);
		menuText[5].setPosition(sf::Vector2f(width / 11, height / (MAX_NUMBER_OF_ITEMS + 1) * 6));
	}

}


Menu::~Menu(void)
{
}


void Menu::draw(sf::RenderWindow &window, int hasGameStarted)
{
	for(int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		if(hasGameStarted == 0)
			window.draw(menuText[i]);
	}
}

