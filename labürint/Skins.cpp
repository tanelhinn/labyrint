#include "Skins.h"


Skins::Skins(float width, float height)
{
	isSkinChosen = false;
	areNumbersUp = true;
	sf::Texture playerTexture;



	if(!font.loadFromFile("Data/mainfont.ttf"))
		std::cout << "error main font file not found" << std::endl;

	choosingText1.setFont(font);
	choosingText1.setCharacterSize(35);
	choosingText1.setColor(sf::Color(116,178,0));
	choosingText1.setString("Vali oma kostüüm!");
	choosingText1.setPosition(sf::Vector2f(width / 6, height * 0.2));

	choosingText2.setFont(font);
	choosingText2.setCharacterSize(25);
	choosingText2.setColor(sf::Color(255,105,208));
	choosingText2.setString("Vajuta numbrit 1'st kuni 6'ni, et valida kostüümi!");
	choosingText2.setPosition(sf::Vector2f(width / 6, height * 0.4));

	choosingTextPly1.setFont(font);
	choosingTextPly1.setCharacterSize(30);
	choosingTextPly1.setColor(sf::Color(255,132,0));
	choosingTextPly1.setString("Mängija 1 kord valida kostüüm!");
	choosingTextPly1.setPosition(sf::Vector2f(width / 6, height * 0.6));

	choosingTextPly2.setFont(font);
	choosingTextPly2.setCharacterSize(30);
	choosingTextPly2.setColor(sf::Color(255,132,0));
	choosingTextPly2.setString("Mängija 2 kord valida kostüüm!");
	choosingTextPly2.setPosition(sf::Vector2f(width / 6, height * 0.6));

}


Skins::~Skins(void)
{
}

void Skins::update(sf::RenderWindow &window)
{
	if(!plyTexture1.loadFromFile("Data/player1.png"))
		std::cout << "error loading player1.png" << std::endl;
	if(!plyTexture2.loadFromFile("Data/player2.png"))
		std::cout << "error loading player2.png" << std::endl;
	if(!plyTexture3.loadFromFile("Data/player3.png"))
		std::cout << "error loading player3.png" << std::endl;
	if(!plyTexture4.loadFromFile("Data/player4.png"))
		std::cout << "error loading player4.png" << std::endl;
	if(!plyTexture5.loadFromFile("Data/player5.png"))
		std::cout << "error loading player5.png" << std::endl;
	if(!plyTexture6.loadFromFile("Data/player6.png"))
		std::cout << "error loading player6.png" << std::endl;
	plySprite1.setTexture(plyTexture1);
	plySprite2.setTexture(plyTexture2);
	plySprite3.setTexture(plyTexture3);
	plySprite4.setTexture(plyTexture4);
	plySprite5.setTexture(plyTexture5);
	plySprite6.setTexture(plyTexture6);
	plySprite1.setPosition(window.getSize().x / 10 * 1, window.getSize().y - window.getSize().y / 6);
	plySprite2.setPosition(window.getSize().x / 10 * 2, window.getSize().y - window.getSize().y / 6);
	plySprite3.setPosition(window.getSize().x / 10 * 3, window.getSize().y - window.getSize().y / 6);
	plySprite4.setPosition(window.getSize().x / 10 * 4, window.getSize().y - window.getSize().y / 6);
	plySprite5.setPosition(window.getSize().x / 10 * 5, window.getSize().y - window.getSize().y / 6);
	plySprite6.setPosition(window.getSize().x / 10 * 6, window.getSize().y - window.getSize().y / 6);


	if(isSkinChosen == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		skinNumber = 1;
		isSkinChosen = true;
		areNumbersUp = false;
	}
	else if(isSkinChosen == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		skinNumber = 2;
		isSkinChosen = true;
		areNumbersUp = false;
	}
	else if(isSkinChosen == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		skinNumber = 3;
		isSkinChosen = true;
		areNumbersUp = false;
	}
	else if(isSkinChosen == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		skinNumber = 4;
		isSkinChosen = true;
		areNumbersUp = false;
	}
	else if(isSkinChosen == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		skinNumber = 5;
		isSkinChosen = true;
		areNumbersUp = false;
	}
	else if(isSkinChosen == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
	{
		skinNumber = 6;
		isSkinChosen = true;
		areNumbersUp = false;
	}
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) && isSkinChosen == true)
	{
		areNumbersUp = true;
		//std::cout << "Numbers are up. areNumbersUp == true;" << std::endl;
	}
	if(isSkinChosen == true && areNumbersUp == true)
	{
		if(skinNumber == 1)
		{
			if(!playerTexture.loadFromFile("Data/player1.png"))
				std::cout << "error loading player1.png" << std::endl;
		}
		else if(skinNumber == 2)
		{
			if(!playerTexture.loadFromFile("Data/player2.png"))
				std::cout << "error loading player2.png" << std::endl;
		}
		else if(skinNumber == 3)
		{
			if(!playerTexture.loadFromFile("Data/player3.png"))
				std::cout << "error loading player3.png" << std::endl;
		}
		else if(skinNumber == 4)
		{
			if(!playerTexture.loadFromFile("Data/player4.png"))
				std::cout << "error loading player4.png" << std::endl;
		}
		else if(skinNumber == 5)
		{
			if(!playerTexture.loadFromFile("Data/player5.png"))
				std::cout << "error loading player5.png" << std::endl;
		}
		else if(skinNumber == 6)
		{
			if(!playerTexture.loadFromFile("Data/player6.png"))
				std::cout << "error loading player6.png" << std::endl;
		}
	}
}

void Skins::draw(sf::RenderWindow &window, int whichPlayerChoosingSkin)
{
	window.draw(choosingText1);
	window.draw(choosingText2);
	window.draw(plySprite1);
	window.draw(plySprite2);
	window.draw(plySprite3);
	window.draw(plySprite4);
	window.draw(plySprite5);
	window.draw(plySprite6);

	if(whichPlayerChoosingSkin == 1)
		window.draw(choosingTextPly1);
	if(whichPlayerChoosingSkin == 2)
		window.draw(choosingTextPly2);
}