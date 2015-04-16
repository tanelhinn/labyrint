#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Player.h"
#include <vector>
#include <iostream>


class Hostiles
{
public:
	Hostiles(sf::Vector2f pPos2);
	~Hostiles(void);

	

	enum hostileState
	{
		Alive,
		Dying,
		Dead
	};
	
	void draw(sf::RenderWindow &window, sf::Texture &texture, int hasGameStarted);
	void update(float dt, int hasGameStarted, hostileState hState, sf::RenderWindow &window, sf::Texture &texture, bool havePlayersCollided);
	sf::Sprite hostileSprite;

private:
	
	int health;
	float speedForDelta;

};

