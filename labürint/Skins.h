#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Skins
{
public:
	Skins(float width, float height);
	~Skins(void);

	void update(sf::RenderWindow &window);
	void draw(sf::RenderWindow &window, int whichPlayerChoosingSkin);
	bool isSkinChosen;
	bool areNumbersUp;
	sf::Texture playerTexture;
	sf::Text choosingText1;
	sf::Text choosingText2;
	sf::Text choosingTextPly1;
	sf::Text choosingTextPly2;

private:
	int skinNumber;
	sf::Texture plyTexture1;
	sf::Texture plyTexture2;
	sf::Texture plyTexture3;
	sf::Texture plyTexture4;
	sf::Texture plyTexture5;
	sf::Texture plyTexture6;
	sf::Sprite plySprite1;
	sf::Sprite plySprite2;
	sf::Sprite plySprite3;
	sf::Sprite plySprite4;
	sf::Sprite plySprite5;
	sf::Sprite plySprite6;
	sf::Font font;

	
	
	
};

