#include "Movingblock.h"
#include "Player.h"
#include "Hostiles.h"


Movingblock::Movingblock(sf::Vector2f blockPos, sf::Vector2f size)
{
	block.setPosition(blockPos);
	block.setSize(size);

	

}


Movingblock::~Movingblock(void)
{
}


void Movingblock::draw(sf::RenderWindow &window, sf::Color blockColor)
{
	block.setFillColor(blockColor);

	window.draw(block);
}
