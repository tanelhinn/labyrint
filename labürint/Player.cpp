#include "Player.h"



Player::Player(sf::Vector2f pPos)
{
	speedForDelta = 0.24f;
	playerSprite.setPosition(pPos);

}


Player::~Player(void)
{
}



void Player::update(float dt, int hasGameStarted, plyState state, sf::RenderWindow &window, sf::Texture &texture, bool havePlayersCollided)
{

	//float x = sinf(playerSprite.getRotation() * 3.14159265 / 180) * dt2;
	//float y = -cosf(playerSprite.getRotation() * 3.14159265 / 180) * dt2;


	switch (state)
	{
	case Alive:
		if(hasGameStarted == 1 || hasGameStarted == 3 || hasGameStarted == 4 || hasGameStarted == 5 || hasGameStarted == 6)
		{
			if(playerSprite.getPosition().y <= 0)
				playerSprite.setPosition(playerSprite.getPosition().x, 0);
			if(playerSprite.getPosition().y + texture.getSize().y >= window.getSize().y)
				playerSprite.setPosition(playerSprite.getPosition().x, window.getSize().y - texture.getSize().y);
			if(playerSprite.getPosition().x <= 0)
				playerSprite.setPosition(0, playerSprite.getPosition().y);
			if(playerSprite.getPosition().x + texture.getSize().x >= window.getSize().x)
				playerSprite.setPosition(window.getSize().x - texture.getSize().x, playerSprite.getPosition().y);

			/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				playerSprite.rotate(-0.08 * dt);
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				playerSprite.rotate(0.08 * dt);
			}*/

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				if(havePlayersCollided == false)
					playerSprite.move(0, -speedForDelta * dt);


			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				if(havePlayersCollided == false)
					playerSprite.move(0, speedForDelta * dt);

			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				if(havePlayersCollided == false)
					playerSprite.move(-speedForDelta * dt, 0);

			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				if(havePlayersCollided == false)
					playerSprite.move(speedForDelta * dt, 0);

			}

			while(window.pollEvent(plyEvent))
			{
				if(plyEvent.type == sf::Event::KeyReleased)
				{
					if(plyEvent.key.code == sf::Keyboard::W)
					{
						verticalPressed = false;
					}
					if(plyEvent.key.code == sf::Keyboard::S)
					{
						verticalPressed = false;
					}
					if(plyEvent.key.code == sf::Keyboard::A)
					{
						horizontalPressed = false;
					}
					if(plyEvent.key.code == sf::Keyboard::D)
					{
						horizontalPressed = false;
					}
				}
			}


		}
		break;
	}
}

void Player::draw(sf::RenderWindow &window, sf::View view, int hasGameStarted, sf::Texture &texture)
{
	playerSprite.setTexture(texture);
	//playerSprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

	if(hasGameStarted == 1 || 3)
	{
		window.draw(playerSprite);
		view.setCenter(window.getSize().x / 2, window.getSize().y / 2);

		window.setView(view);
	}
}
