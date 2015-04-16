#pragma once
#include <SFML/Graphics.hpp>


class Movingblock
{
public:
	Movingblock(sf::Vector2f blockPos, sf::Vector2f size);
	~Movingblock(void);

	sf::RectangleShape block;
	void draw(sf::RenderWindow &window, sf::Color blockColor);
	//void update(float dt, sf::RenderWindow &window);

private:
	

};

