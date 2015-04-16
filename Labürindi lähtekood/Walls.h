#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Walls
{
public:
	Walls(sf::Vector2f position, sf::Vector2f size);
	~Walls(void);

	void draw(sf::RenderWindow &window, sf::Color color);
	sf::RectangleShape rect;
private:

	

};

