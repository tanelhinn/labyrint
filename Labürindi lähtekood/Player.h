#pragma once
#include <SFML/Graphics.hpp>
#include "Hostiles.h"


class Player
{
public:
	Player(sf::Vector2f pPos);
	~Player(void);

	enum plyState
	{
		Alive,
		Dying,
		Dead
	};

	void centerOrigin(sf::Sprite& sprite);
	void update(float dt, int hasGameStarted, plyState state, sf::RenderWindow &window, sf::Texture &texture, bool havePlayersCollided);
	void draw(sf::RenderWindow &window, sf::View view, int hasGameStarted, sf::Texture &texture);

	sf::Sprite playerSprite;
private:
	sf::Event plyEvent;
	float x, y;
	bool upPressed;
	bool rightPressed;
	bool verticalPressed;
	bool horizontalPressed;
	int health;
	float speedForDelta;
	

};

