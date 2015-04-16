#include "Walls.h"


Walls::Walls(sf::Vector2f position, sf::Vector2f size)
{

	rect.setPosition(position);
	rect.setSize(size);

}


Walls::~Walls(void)
{
}

void Walls::draw(sf::RenderWindow &window, sf::Color color)
{
	rect.setFillColor(color);

	window.draw(rect);
}