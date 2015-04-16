#include "Hostiles.h"

Hostiles::Hostiles(sf::Vector2f pPos2)
{
	hostileSprite.setPosition(pPos2);
	health = 1000;
}


Hostiles::~Hostiles(void)
{
}

void Hostiles::update(float dt, int hasGameStarted, hostileState hState, sf::RenderWindow &window, sf::Texture &texture, bool havePlayersCollided)
{
	speedForDelta = 0.24f;
	switch(hState)
	{
	case Alive:
		if(hasGameStarted == 1 || hasGameStarted == 3 || hasGameStarted == 4 || hasGameStarted == 5 || hasGameStarted == 6)
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if(hostileSprite.getPosition().y <= 0)
					hostileSprite.setPosition(hostileSprite.getPosition().x, 0);
				else
				{
					if(havePlayersCollided == false)
						hostileSprite.move(0, -speedForDelta * dt);
				
				}
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if(hostileSprite.getPosition().y + texture.getSize().y >= window.getSize().y)
					hostileSprite.setPosition(hostileSprite.getPosition().x, window.getSize().y - texture.getSize().y);
				else
				{
					if(havePlayersCollided == false)
						hostileSprite.move(0, speedForDelta * dt);
					
						
				}
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if(hostileSprite.getPosition().x <= 0)
					hostileSprite.setPosition(0, hostileSprite.getPosition().y);
				else
				{
					if(havePlayersCollided == false)
						hostileSprite.move(-speedForDelta * dt, 0);
					
				}
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if(hostileSprite.getPosition().x + texture.getSize().x >= window.getSize().x)
					hostileSprite.setPosition(window.getSize().x - texture.getSize().x, hostileSprite.getPosition().y);
				else
				{
					if(havePlayersCollided == false)
						hostileSprite.move(speedForDelta * dt, 0);
					
				}
			}


		}
		break;
	case Dying:

		break;
	case Dead:

		break;
	}

}

void Hostiles::draw(sf::RenderWindow &window, sf::Texture &texture, int hasGameStarted)
{
	hostileSprite.setTexture(texture);

	if(hasGameStarted == 1 || 3)
	{

		window.draw(hostileSprite);
	}
}