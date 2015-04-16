#include "Background.h"


Background::Background(sf::Texture &bgTexture)
{


	bgSprite.setTexture(bgTexture);

}


Background::~Background(void)
{
}

void Background::draw(sf::RenderWindow &window, int hasGameStarted)
{

	window.draw(bgSprite);
}
