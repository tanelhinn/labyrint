

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Background
{
public:
	Background(sf::Texture &bgTexture);
	~Background(void);

	void draw(sf::RenderWindow &window, int hasGameStarted);

private:
	
	sf::Sprite bgSprite;
	

};

