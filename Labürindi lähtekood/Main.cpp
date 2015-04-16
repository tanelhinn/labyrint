

//Koostas Tanel Hinn
//Võru Kreutzwaldi Gümnaasium 8b
//2015


//includes
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <list>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Player.h"
#include "Menu.h"
#include "Background.h"
#include "Hostiles.h"
#include "Skins.h"
#include "Walls.h"
#include "Movingblock.h"


int main()
{

	sf::Vector2i screenSize(800, 600);
	sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "Labürint", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(30);



	//stuff
	sf::Vector2f pPos(window.getSize().x / 4 - 32, window.getSize().y / 4);
	sf::Vector2f pPos2(window.getSize().x / 4 * 3, window.getSize().y / 4 * 3);
	sf::View gameView;
	gameView.setSize(window.getSize().x, window.getSize().y);
	sf::Clock mouseClock;
	bool isFullscreen = false;
	bool havePlayersCollided = false;
	int hasGameStarted = 0; // 0 == peamenüü, 2 == skinni valik, 1 == mängu esimene mapp, 3 == teine map, 4 == kolmas map, jne
	int whichPlayerChoosingSkin = 0;
	int tempNumber = 0;
	float speedForBlock = 0.16f;
	float speedForBlock2 = 0.16f;

	Player::plyState state = Player::Alive;
	Hostiles::hostileState hState = Hostiles::Alive;
	sf::Font mainFont;
	int ply1points = 0;
	int ply2points = 0;
	sf::Text ply1score;
	sf::Text ply2score;
	if(!mainFont.loadFromFile("Data/mainfont.ttf"))
	{
		std::cout << "Error loading Data/mainfont.ttf" << std::endl;
	}

	//laeb sounde
	sf::SoundBuffer selectBuffer;
	sf::SoundBuffer nextBuffer;
	sf::SoundBuffer crashBuffer;
	sf::SoundBuffer gameStartBuffer;
	sf::SoundBuffer gameEndBuffer;
	sf::Sound selectSound;
	sf::Sound nextSound;
	sf::Sound crashSound;
	sf::Sound gameStartSound;
	sf::Sound gameEndSound;
	if(!selectBuffer.loadFromFile("Data/select.wav"))
		std::cout << "Error could not load select.wav" << std::endl;
	if(!nextBuffer.loadFromFile("Data/next.wav"))
		std::cout << "Error could not load next.wav" << std::endl;
	if(!crashBuffer.loadFromFile("Data/crash.wav"))
		std::cout << "Error could not load crash.wav" << std::endl;
	if(!gameStartBuffer.loadFromFile("Data/gameStart.wav"))
		std::cout << "Error could not load gameStart.wav" << std::endl;
	if(!gameEndBuffer.loadFromFile("Data/gameEnd.wav"))
		std::cout << "Error could not load gameEnd.wav" << std::endl;
	selectSound.setBuffer(selectBuffer);
	nextSound.setBuffer(nextBuffer);
	crashSound.setBuffer(crashBuffer);
	gameStartSound.setBuffer(gameStartBuffer);
	gameEndSound.setBuffer(gameEndBuffer);




	std::ostringstream ply1scoreText; //string buffer to convert numbers to string
	ply1scoreText << "Mängija 1 skoor: " << ply1points;// put float into string buffer

	std::ostringstream ply2scoreText;
	ply2scoreText << "Mängija 2 skoor: " << ply2points;

	ply1score.setFont(mainFont);
	ply1score.setColor(sf::Color(116,219,0));
	ply1score.setString(ply1scoreText.str());
	ply1score.setCharacterSize(20);
	ply1score.setPosition(100,0);

	ply2score.setFont(mainFont);
	ply2score.setColor(sf::Color(116,219,0));
	ply2score.setString(ply2scoreText.str());
	ply2score.setCharacterSize(20);
	ply2score.setPosition(600,0);



	Menu menu(window.getSize().x, window.getSize().y, hasGameStarted);
	Walls wall1(sf::Vector2f(0,0), sf::Vector2f(100,window.getSize().y));
	Walls wall2(sf::Vector2f(window.getSize().x - 100,0), sf::Vector2f(100, window.getSize().y));
	Walls wall3(sf::Vector2f(100,0), sf::Vector2f(600,100));
	Walls wall4(sf::Vector2f(100,500), sf::Vector2f(600,100));
	Walls wall5(sf::Vector2f(100,190), sf::Vector2f(500,50));
	Walls wall6(sf::Vector2f(200,380), sf::Vector2f(500,50));
	Walls wallLv1Red(sf::Vector2f(320, 240), sf::Vector2f(140,140));
	Walls lv2wall1(sf::Vector2f(0,0), sf::Vector2f(15, window.getSize().y));
	Walls lv2wall2(sf::Vector2f(0,0), sf::Vector2f(window.getSize().x ,15));
	Walls lv2wall3(sf::Vector2f(window.getSize().x - 15, 0), sf::Vector2f(15, window.getSize().y));
	Walls lv2wall4(sf::Vector2f(0, window.getSize().y - 15), sf::Vector2f(window.getSize().x, 15));
	Walls lv2wall5(sf::Vector2f(100,515), sf::Vector2f(685, 15));
	Walls lv2wall6(sf::Vector2f(15, 55), sf::Vector2f(685, 15));
	Walls lv2wall7(sf::Vector2f(100,125), sf::Vector2f(15, 405));
	Walls lv2wall8(sf::Vector2f(100,125), sf::Vector2f(485, 15));
	Walls lv2wall9(sf::Vector2f(685, 55), sf::Vector2f(15, 405));
	Walls lv2wall10(sf::Vector2f(215, 445), sf::Vector2f(485 ,15));
	Walls lv2wall11(sf::Vector2f(215, 140), sf::Vector2f(15, 320));
	Walls lv2wall12(sf::Vector2f(570, 125), sf::Vector2f(15, 320));
	Walls wallLv2Red(sf::Vector2f(115, 140), sf::Vector2f(100, 50));
	Walls wallLv2Red2(sf::Vector2f(585, 395), sf::Vector2f(100, 50));
	Walls lv3wall1(sf::Vector2f(0,0), sf::Vector2f(window.getSize().x, 50));
	Walls lv3wall2(sf::Vector2f(0,0), sf::Vector2f(50, window.getSize().y));
	Walls lv3wall3(sf::Vector2f(window.getSize().x - 50, 0), sf::Vector2f(50, window.getSize().y));
	Walls lv3wall4(sf::Vector2f(0, window.getSize().y - 50), sf::Vector2f(window.getSize().x ,50));
	Walls lv3wall5(sf::Vector2f(350, 50), sf::Vector2f(100, window.getSize().y - 100));
	Walls lv3wall6(sf::Vector2f(50, 115), sf::Vector2f(225, 50));
	Walls lv3wall7(sf::Vector2f(450, 115), sf::Vector2f(225, 50));
	Walls lv3wall8(sf::Vector2f(525, 235), sf::Vector2f(225, 50));
	Walls lv3wall9(sf::Vector2f(125, 235), sf::Vector2f(225, 50));
	Walls lv3wall10(sf::Vector2f(450, 335), sf::Vector2f(225, 50));
	Walls lv3wall11(sf::Vector2f(50, 335), sf::Vector2f(225, 50));
	Walls lv3wall12(sf::Vector2f(525, 435), sf::Vector2f(225, 50));
	Walls lv3wall13(sf::Vector2f(125, 435), sf::Vector2f(225, 50));
	Walls wallLv3Red(sf::Vector2f(285, 485), sf::Vector2f(65,65));
	Walls wallLv3Red2(sf::Vector2f(450, 50), sf::Vector2f(65,65));
	Walls lv4wall1(sf::Vector2f(390, 0), sf::Vector2f(20, window.getSize().y));
	Walls lv4wall2(sf::Vector2f(0,0), sf::Vector2f(window.getSize().x / 2 - 10,270));
	Walls lv4wall3(sf::Vector2f(window.getSize().x / 2 + 10, 330), sf::Vector2f(window.getSize().x / 2 - 10, 270));
	Walls lv4wall4(sf::Vector2f(0,270), sf::Vector2f(10, window.getSize().y - 270));
	Walls lv4wall5(sf::Vector2f(window.getSize().x - 10, 0), sf::Vector2f(10, 330));
	Walls lv4wall6(sf::Vector2f(60, 330), sf::Vector2f(330 , 10));
	Walls lv4wall7(sf::Vector2f(410, 260), sf::Vector2f(320, 10));
	Walls lv4wall8(sf::Vector2f(10, 590), sf::Vector2f(580,10));
	Walls lv4wall9(sf::Vector2f(410, 0), sf::Vector2f(380,10));
	Walls lv4wall10(sf::Vector2f(60,340), sf::Vector2f(10, 200));
	Walls lv4wall11(sf::Vector2f(720, 60), sf::Vector2f(10, 200));
	Walls lv4wall12(sf::Vector2f(130,400), sf::Vector2f(200,130));
	Walls lv4wall13(sf::Vector2f(470, 70), sf::Vector2f(200,130));
	Walls wallLv4Red(sf::Vector2f(310,340), sf::Vector2f(80, 50));
	Walls wallLv4Red2(sf::Vector2f(410,210), sf::Vector2f(80, 50));


	Walls lv5wall1(sf::Vector2f(0,0), sf::Vector2f(window.getSize().x, 30));
	Walls lv5wall2(sf::Vector2f(0,0), sf::Vector2f(30, window.getSize().y));
	Walls lv5wall3(sf::Vector2f(0, window.getSize().y - 30), sf::Vector2f(window.getSize().x, 30));
	Walls lv5wall4(sf::Vector2f(window.getSize().x - 30, 0), sf::Vector2f(30, window.getSize().y));
	Walls lv5wall5(sf::Vector2f(30, window.getSize().y / 2 - 50), sf::Vector2f(window.getSize().x - 60, 100));
	Walls wallLv5Red(sf::Vector2f(30,30), sf::Vector2f(20 ,220));
	Walls wallLv5Red2(sf::Vector2f(window.getSize().x - 50, 350), sf::Vector2f(20, 220));
	Walls lv5wall6(sf::Vector2f(140,460), sf::Vector2f(100,100));
	Walls lv5wall7(sf::Vector2f(300,360), sf::Vector2f(100,100));
	Walls lv5wall8(sf::Vector2f(560,40), sf::Vector2f(100,100));
	Walls lv5wall9(sf::Vector2f(400,140), sf::Vector2f(100,100));
	Walls lv5wall10(sf::Vector2f(100, 70), sf::Vector2f(150, 140));
	Walls lv5wall11(sf::Vector2f(550, 390), sf::Vector2f(150,140));



	sf::Clock playerClock;
	sf::Texture bgTexture;
	sf::Texture bgTexture2;
	sf::Texture bgTexture3;
	sf::Texture bgTexture4;
	sf::Texture bgTexture5;
	sf::Texture bgTexture6;
	sf::Texture bgTexture7;
	sf::Texture winner1txture;
	sf::Texture winner2txture;
	sf::Texture winnerScrQuitT;
	sf::Texture end1;
	sf::Texture end2;
	sf::Sprite winner1spr;
	sf::Sprite winner2spr;
	sf::Sprite winnerScrQuit;
	sf::Sprite end1spr;
	sf::Sprite end2spr;

	if(!winner1txture.loadFromFile("Data/winner1.png"))
		std::cout << "Error loading winner1.png" << std::endl;
	if(!winner2txture.loadFromFile("Data/winner2.png"))
		std::cout << "Error loading winner2.png" << std::endl;
	if(!winnerScrQuitT.loadFromFile("Data/endInfo.png"))
		std::cout << "Error loading endInfo.png" << std::endl;
	if(!end1.loadFromFile("Data/end1.png"))
		std::cout << "Error loading end1.png" << std::endl;
	if(!end2.loadFromFile("Data/end2.png"))
		std::cout << "Error loading end2.png" << std::endl;

	winner1spr.setTexture(winner1txture);
	winner1spr.setPosition(window.getSize().x / 4 - 30, window.getSize().y / 3);
	winner2spr.setTexture(winner2txture);
	winner2spr.setPosition(window.getSize().x / 4 - 30, window.getSize().y / 3);
	winnerScrQuit.setTexture(winnerScrQuitT);
	winnerScrQuit.setPosition(window.getSize().x / 4 - 30, window.getSize().y / 2);
	end1spr.setTexture(end1);
	end2spr.setTexture(end2);
	end1spr.setPosition(window.getSize().x / 4 - 30, window.getSize().y - 250);
	end2spr.setPosition(window.getSize().x - 310, window.getSize().y - 40);



	if(!bgTexture.loadFromFile("Data/background.png"))
	{
		std::cout << "Could not load background image" << std::endl;
	}

	if(!bgTexture2.loadFromFile("Data/background2.png"))
	{
		std::cout << "Could not load background2 image" << std::endl;
	}
	if(!bgTexture3.loadFromFile("Data/background3.png"))
	{
		std::cout << "Could not load background3 image" << std::endl;
	}
	if(!bgTexture4.loadFromFile("Data/background4.png"))
	{
		std::cout << "Could not load background4 image" << std::endl;
	}
	if(!bgTexture5.loadFromFile("Data/background5.png"))
	{
		std::cout << "Could not load background5 image" << std::endl;
	}
	if(!bgTexture6.loadFromFile("Data/background6.png"))
	{
		std::cout << "Could not load background6 image" << std::endl;
	}
	if(!bgTexture7.loadFromFile("Data/background7.png"))
	{
		std::cout << "Could not load background7 image" << std::endl;
	}

	Background background(bgTexture);
	Background background2(bgTexture2);
	Background background3(bgTexture3);
	Background background4(bgTexture4);
	Background background5(bgTexture5);
	Background background6(bgTexture6);
	Background background7(bgTexture7);

	Skins plySkin(window.getSize().x, window.getSize().y);
	Skins plySkin2(window.getSize().x, window.getSize().y);

	Player player(pPos);
	Hostiles hostile(pPos2);



	/*sf::Music bgMusic;

	if(!bgMusic.openFromFile("Data/bgMusic.ogg"))
	{
	std::cout << "Error loading background music file" << std::endl;
	}
	bgMusic.setVolume(45);
	bgMusic.play();*/

	while(window.isOpen())
	{
		sf::Event event;

		sf::Time mouseElapsed = mouseClock.getElapsedTime();

		if(mouseElapsed.asSeconds() >= 4)
		{
			window.setMouseCursorVisible(false);
		}

		while(window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if(event.key.code == sf::Keyboard::Escape)
					window.close();
				if(event.key.code == sf::Keyboard::Return && isFullscreen == false)
				{
					window.create(sf::VideoMode(screenSize.x, screenSize.y), "Labürint", sf::Style::Fullscreen);
					isFullscreen = true;
				}
				else if(event.key.code == sf::Keyboard::Return && isFullscreen == true)
				{
					window.create(sf::VideoMode(screenSize.x, screenSize.y), "Labürint", sf::Style::Titlebar | sf::Style::Close);
					isFullscreen = false;
				}
				break;
			case sf::Event::KeyReleased:
				if(hasGameStarted == 0 && event.key.code == sf::Keyboard::Space)
				{
					nextSound.play();
					hasGameStarted = 2;
				}
				/*if(hasGameStarted == 1 && event.key.code == sf::Keyboard::Space)
				{
					hasGameStarted = 5;
					pPos.x = 350;
					pPos.y = 280;
					player.playerSprite.setPosition(pPos);
					pPos2.x = 418;
					pPos2.y = 280;
					hostile.hostileSprite.setPosition(pPos2);
				}*/
				break;
			case sf::Event::MouseMoved:
				window.setMouseCursorVisible(true);
				mouseClock.restart();
				mouseElapsed = mouseClock.getElapsedTime();

				/*std::cout << "X : " << event.mouseMove.x << std::endl;
				std::cout << "Y : " << event.mouseMove.y << std::endl;*/


				break;
			}


		}//event taking ends here


		sf::Time playerTime = playerClock.getElapsedTime();

		player.update(playerTime.asMilliseconds(), hasGameStarted, state, window, plySkin.playerTexture, havePlayersCollided);
		hostile.update(playerTime.asMilliseconds(), hasGameStarted, hState, window, plySkin2.playerTexture, havePlayersCollided);


		playerClock.restart().asMilliseconds();


		//Draw stuff, clear before display.
		//hasGameStarted == 0 on main menüü, == 2 skinni valik, == 1 mängu esimene level, == 3 mängu teine level, == 4 mängu kolmas level
		if(hasGameStarted == 0)
		{
			window.clear(sf::Color(255,255,119));
			menu.draw(window, hasGameStarted);
			window.display();
		}
		if(hasGameStarted == 2)
		{
			window.clear(sf::Color(212,255,170));
			whichPlayerChoosingSkin = 1;
			plySkin.update(window);
			if(plySkin.isSkinChosen == false)
				plySkin.draw(window, whichPlayerChoosingSkin);
			if(plySkin.isSkinChosen == true && plySkin.areNumbersUp == false)
				tempNumber = 1;
			if(plySkin.isSkinChosen == true && plySkin.areNumbersUp == true)
			{
				whichPlayerChoosingSkin = 2;
				plySkin.draw(window, whichPlayerChoosingSkin);
				plySkin2.update(window);
				if(tempNumber == 1)
				{
					nextSound.play();
					tempNumber = 0;
				}

			}
			if(plySkin2.isSkinChosen == true && plySkin2.areNumbersUp == true)
			{
				gameStartSound.play();
				hasGameStarted = 1;
			}

			window.display();
		}
		if(hasGameStarted == 1)
		{
			window.clear(sf::Color::White);
			background.draw(window, hasGameStarted);
			player.draw(window, gameView, hasGameStarted, plySkin.playerTexture);
			hostile.draw(window, plySkin2.playerTexture, hasGameStarted);
			wall1.draw(window, sf::Color(33,198,224,150));
			wall2.draw(window, sf::Color(33,198,224,150));
			wall3.draw(window, sf::Color(33,198,224,150));
			wall4.draw(window, sf::Color(33,198,224,150));
			wall5.draw(window, sf::Color(33,198,224,150));
			wall6.draw(window, sf::Color(33,198,224,150));
			wallLv1Red.draw(window,sf::Color::Red);



			if(player.playerSprite.getGlobalBounds().intersects(wall1.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(wall2.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(wall3.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(wall4.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(wall5.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(wall6.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(wallLv1Red.rect.getGlobalBounds()))
			{
				selectSound.play();
				ply1points += 1;
				ply1scoreText.str("");
				ply1scoreText << "Mängija 1 skoor: " << ply1points;
				hasGameStarted = 3;
				pPos.x = 20;
				pPos.y = 20;
				player.playerSprite.setPosition(pPos);
				pPos2.x = window.getSize().x - 20 - plySkin2.playerTexture.getSize().x;
				pPos2.y = window.getSize().y - 20 - plySkin2.playerTexture.getSize().y;
				hostile.hostileSprite.setPosition(pPos2);
			}
			if(hostile.hostileSprite.getGlobalBounds().intersects(wall1.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(wall2.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(wall3.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(wall4.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(wall5.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(wall6.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(wallLv1Red.rect.getGlobalBounds()))
			{
				selectSound.play();
				ply2points += 1;
				ply2scoreText.str("");
				ply2scoreText << "Mängija 2 skoor: " << ply2points;
				hasGameStarted = 3;
				pPos.x = 20;
				pPos.y = 20;
				player.playerSprite.setPosition(pPos);
				pPos2.x = window.getSize().x - 20 - plySkin2.playerTexture.getSize().x;
				pPos2.y = window.getSize().y - 20 - plySkin2.playerTexture.getSize().y;
				hostile.hostileSprite.setPosition(pPos2);
			}

			ply1score.setString(ply1scoreText.str());
			ply2score.setString(ply2scoreText.str());
			window.draw(ply1score);
			window.draw(ply2score);

			window.display();
		}
		if(hasGameStarted == 3)
		{
			window.clear(sf::Color::White);
			background2.draw(window, hasGameStarted);
			player.draw(window, gameView, hasGameStarted, plySkin.playerTexture);
			hostile.draw(window, plySkin2.playerTexture, hasGameStarted);
			lv2wall1.draw(window, sf::Color(109,240,105,150));
			lv2wall2.draw(window, sf::Color(109,240,105,150));
			lv2wall3.draw(window, sf::Color(109,240,105,150));
			lv2wall4.draw(window, sf::Color(109,240,105,150));
			lv2wall5.draw(window, sf::Color(109,240,105,150));
			lv2wall6.draw(window, sf::Color(109,240,105,150));
			lv2wall7.draw(window, sf::Color(109,240,105,150));
			lv2wall8.draw(window, sf::Color(109,240,105,150));
			lv2wall9.draw(window, sf::Color(109,240,105,150));
			lv2wall10.draw(window, sf::Color(109,240,105,150));
			lv2wall11.draw(window, sf::Color(109,240,105,150));
			lv2wall12.draw(window, sf::Color(109,240,105,150));
			wallLv2Red.draw(window, sf::Color::Red);
			wallLv2Red2.draw(window, sf::Color::Red);

			if(player.playerSprite.getGlobalBounds().intersects(wallLv2Red.rect.getGlobalBounds()))
			{
				selectSound.play();
				ply1points += 1;
				ply1scoreText.str("");
				ply1scoreText << "Mängija 1 skoor: " << ply1points;
				hasGameStarted = 4;
				pPos.x = 60;
				pPos.y = 60;
				player.playerSprite.setPosition(pPos);
				pPos2.x = window.getSize().x - 60 - plySkin2.playerTexture.getSize().x;
				pPos2.y = window.getSize().y - 60 - plySkin2.playerTexture.getSize().y;
				hostile.hostileSprite.setPosition(pPos2);
			}
			if(hostile.hostileSprite.getGlobalBounds().intersects(wallLv2Red2.rect.getGlobalBounds()))
			{
				selectSound.play();
				ply2points += 1;
				ply2scoreText.str("");
				ply2scoreText << "Mängija 2 skoor: " << ply2points;
				hasGameStarted = 4;
				pPos.x = 60;
				pPos.y = 60;
				player.playerSprite.setPosition(pPos);
				pPos2.x = window.getSize().x - 60 - plySkin2.playerTexture.getSize().x;
				pPos2.y = window.getSize().y - 60 - plySkin2.playerTexture.getSize().y;
				hostile.hostileSprite.setPosition(pPos2);
			}


			if(player.playerSprite.getGlobalBounds().intersects(lv2wall1.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv2wall2.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv2wall3.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv2wall4.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv2wall5.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv2wall6.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv2wall7.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv2wall8.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv2wall9.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv2wall10.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv2wall11.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv2wall12.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }

			if(hostile.hostileSprite.getGlobalBounds().intersects(lv2wall1.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv2wall2.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv2wall3.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv2wall4.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv2wall5.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv2wall6.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv2wall7.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv2wall8.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv2wall9.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv2wall10.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv2wall11.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv2wall12.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }


			/*ply1scoreText.str("");
			ply2scoreText.str("");
			ply1scoreText << "Mängija 1 skoor: " << ply1points;
			ply2scoreText << "Mängija 2 skoor: " << ply2points;*/

			ply1score.setString(ply1scoreText.str());
			ply2score.setString(ply2scoreText.str());
			window.draw(ply1score);
			window.draw(ply2score);

			window.display();

		}
		if(hasGameStarted == 4)
		{
			window.clear(sf::Color::White);
			background3.draw(window, hasGameStarted);
			player.draw(window, gameView, hasGameStarted, plySkin.playerTexture);
			hostile.draw(window, plySkin2.playerTexture, hasGameStarted);
			lv3wall1.draw(window, sf::Color(255,135,229,150));
			lv3wall2.draw(window, sf::Color(255,135,229,150));
			lv3wall3.draw(window, sf::Color(255,135,229,150));
			lv3wall4.draw(window, sf::Color(255,135,229,150));
			lv3wall5.draw(window, sf::Color(255,135,229,150));
			lv3wall6.draw(window, sf::Color(255,135,229,150));
			lv3wall7.draw(window, sf::Color(255,135,229,150));
			lv3wall8.draw(window, sf::Color(255,135,229,150));
			lv3wall9.draw(window, sf::Color(255,135,229,150));
			lv3wall10.draw(window, sf::Color(255,135,229,150));
			lv3wall11.draw(window, sf::Color(255,135,229,150));
			lv3wall12.draw(window, sf::Color(255,135,229,150));
			lv3wall13.draw(window, sf::Color(255,135,229,150));
			wallLv3Red.draw(window, sf::Color::Red);
			wallLv3Red2.draw(window, sf::Color::Red);

			//lv3block1.draw(window, sf::Color(33,198,224,150));


			if(player.playerSprite.getGlobalBounds().intersects(wallLv3Red.rect.getGlobalBounds()))
			{
				selectSound.play();
				ply1points += 1;
				ply1scoreText.str("");
				ply1scoreText << "Mängija 1 skoor: " << ply1points;
				hasGameStarted = 5;
				pPos.x = 350;
				pPos.y = 280;
				player.playerSprite.setPosition(pPos);
				pPos2.x = 418;
				pPos2.y = 280;
				hostile.hostileSprite.setPosition(pPos2);
			}
			if(hostile.hostileSprite.getGlobalBounds().intersects(wallLv3Red2.rect.getGlobalBounds()))
			{
				selectSound.play();
				ply2points += 1;
				ply2scoreText.str("");
				ply2scoreText << "Mängija 2 skoor: " << ply2points;
				hasGameStarted = 5;
				pPos.x = 350;
				pPos.y = 280;
				player.playerSprite.setPosition(pPos);
				pPos2.x = 418;
				pPos2.y = 280;
				hostile.hostileSprite.setPosition(pPos2);
			}

			if(player.playerSprite.getGlobalBounds().intersects(lv3wall1.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv3wall2.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv3wall3.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv3wall4.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv3wall5.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv3wall6.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv3wall7.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv3wall8.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv3wall9.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv3wall10.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv3wall11.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv3wall12.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv3wall13.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }

			if(hostile.hostileSprite.getGlobalBounds().intersects(lv3wall1.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv3wall2.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv3wall3.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv3wall4.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv3wall5.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv3wall6.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv3wall7.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv3wall8.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv3wall9.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv3wall10.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv3wall11.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv3wall12.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv3wall13.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }

			ply1score.setString(ply1scoreText.str());
			ply2score.setString(ply2scoreText.str());
			window.draw(ply1score);
			window.draw(ply2score);
			window.display();
		}
		if(hasGameStarted == 5)
		{
			window.clear(sf::Color::White);
			background4.draw(window, hasGameStarted);
			player.draw(window, gameView, hasGameStarted, plySkin.playerTexture);
			hostile.draw(window, plySkin2.playerTexture, hasGameStarted);
			lv4wall1.draw(window, sf::Color(255,250,132,150));
			lv4wall2.draw(window, sf::Color(255,250,132,150));
			lv4wall3.draw(window, sf::Color(255,250,132,150));
			lv4wall4.draw(window, sf::Color(255,250,132,150));
			lv4wall5.draw(window, sf::Color(255,250,132,150));
			lv4wall6.draw(window, sf::Color(255,250,132,150));
			lv4wall7.draw(window, sf::Color(255,250,132,150));
			lv4wall8.draw(window, sf::Color(255,250,132,150));
			lv4wall9.draw(window, sf::Color(255,250,132,150));
			lv4wall10.draw(window, sf::Color(255,250,132,150));
			lv4wall11.draw(window, sf::Color(255,250,132,150));
			lv4wall12.draw(window, sf::Color(255,250,132,150));
			lv4wall13.draw(window, sf::Color(255,250,132,150));

			wallLv4Red.draw(window, sf::Color::Red);
			wallLv4Red2.draw(window, sf::Color::Red);

			if(player.playerSprite.getGlobalBounds().intersects(wallLv4Red.rect.getGlobalBounds()))
			{
				selectSound.play();
				ply1points += 1;
				ply1scoreText.str("");
				ply1scoreText << "Mängija 1 skoor: " << ply1points;
				hasGameStarted = 6;
				pPos.x = 50;
				pPos.y = window.getSize().y - 100;
				player.playerSprite.setPosition(pPos);
				pPos2.x = window.getSize().x - 50 - 32;
				pPos2.y = 50 + 32;
				hostile.hostileSprite.setPosition(pPos2);
			}

			if(hostile.hostileSprite.getGlobalBounds().intersects(wallLv4Red2.rect.getGlobalBounds()))
			{
				selectSound.play();
				ply2points += 1;
				ply2scoreText.str("");
				ply2scoreText << "Mängija 2 skoor: " << ply2points;
				hasGameStarted = 6;
				pPos.x = 50;
				pPos.y = window.getSize().y - 100;
				player.playerSprite.setPosition(pPos);
				pPos2.x = window.getSize().x - 50 - 32;
				pPos2.y = 50 + 32;
				hostile.hostileSprite.setPosition(pPos2);
			}



			if(player.playerSprite.getGlobalBounds().intersects(lv4wall1.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv4wall2.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv4wall3.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv4wall4.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv4wall5.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv4wall6.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv4wall7.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv4wall8.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv4wall9.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv4wall10.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv4wall11.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv4wall12.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv4wall13.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }

			if(hostile.hostileSprite.getGlobalBounds().intersects(lv4wall1.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv4wall2.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv4wall3.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv4wall4.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv4wall5.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv4wall6.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv4wall7.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv4wall8.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv4wall9.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv4wall10.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv4wall11.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv4wall12.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv4wall13.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }


			//lv4block1.draw(window, sf::Color::Green);
			//lv4block2.draw(window, sf::Color::Green);


			/*if(lv4block1.block.getPosition().y < 370)
				speedForBlock = -speedForBlock;
			else if(lv4block1.block.getPosition().y > 540)
				speedForBlock = -speedForBlock;

			lv4block1.block.move(0, speedForBlock * playerTime.asMilliseconds());

			if(lv4block2.block.getPosition().y < 370)
				speedForBlock2 = -speedForBlock2;
			else if(lv4block2.block.getPosition().y > 540)
				speedForBlock2 = -speedForBlock2;

			lv4block2.block.move(0, speedForBlock2 * playerTime.asMilliseconds());*/


			/*if(lv4block1.block.getGlobalBounds().intersects(player.playerSprite.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(lv4block2.block.getGlobalBounds().intersects(player.playerSprite.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }*/




			ply1score.setString(ply1scoreText.str());
			ply2score.setString(ply2scoreText.str());
			window.draw(ply1score);
			window.draw(ply2score);
			window.display();
		}
		if(hasGameStarted == 6)
		{
			window.clear(sf::Color::White);
			background5.draw(window, hasGameStarted);
			player.draw(window, gameView, hasGameStarted, plySkin.playerTexture);
			hostile.draw(window, plySkin2.playerTexture, hasGameStarted);

			lv5wall1.draw(window, sf::Color(255,84,109,150));
			lv5wall2.draw(window, sf::Color(255,84,109,150));
			lv5wall3.draw(window, sf::Color(255,84,109,150));
			lv5wall4.draw(window, sf::Color(255,84,109,150));
			lv5wall5.draw(window, sf::Color(255,84,109,150));
			lv5wall6.draw(window, sf::Color(255,84,109,150));
			lv5wall7.draw(window, sf::Color(255,84,109,150));
			lv5wall8.draw(window, sf::Color(255,84,109,150));
			lv5wall9.draw(window, sf::Color(255,84,109,150));
			lv5wall10.draw(window, sf::Color(255,84,109,150));
			lv5wall11.draw(window, sf::Color(255,84,109,150));

			wallLv5Red.draw(window, sf::Color::Red);
			wallLv5Red2.draw(window, sf::Color::Red);

			if(player.playerSprite.getGlobalBounds().intersects(wallLv5Red2.rect.getGlobalBounds()))
			{
				gameEndSound.play();
				ply1points += 1;
				ply1scoreText.str("");
				ply1scoreText << "Mängija 1 skoor: " << ply1points;
				hasGameStarted = 9;
			}

			if(hostile.hostileSprite.getGlobalBounds().intersects(wallLv5Red.rect.getGlobalBounds()))
			{
				gameEndSound.play();
				ply2points += 1;
				ply2scoreText.str("");
				ply2scoreText << "Mängija 2 skoor: " << ply2points;
				hasGameStarted = 9;
			}

			if(player.playerSprite.getGlobalBounds().intersects(lv5wall1.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv5wall2.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv5wall3.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv5wall4.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv5wall5.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv5wall6.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv5wall7.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv5wall8.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv5wall9.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv5wall10.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }
			if(player.playerSprite.getGlobalBounds().intersects(lv5wall11.rect.getGlobalBounds()))
			{ player.playerSprite.setPosition(pPos); crashSound.play(); }

			if(hostile.hostileSprite.getGlobalBounds().intersects(lv5wall1.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv5wall2.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv5wall3.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv5wall4.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv5wall5.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv5wall6.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv5wall7.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv5wall8.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv5wall9.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv5wall10.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }
			if(hostile.hostileSprite.getGlobalBounds().intersects(lv5wall11.rect.getGlobalBounds()))
			{ hostile.hostileSprite.setPosition(pPos2); crashSound.play(); }

			ply1score.setString(ply1scoreText.str());
			ply2score.setString(ply2scoreText.str());
			window.draw(ply1score);
			window.draw(ply2score);
			window.display();
		}
		if(hasGameStarted == 7)
		{
			window.clear(sf::Color::White);
			background6.draw(window, hasGameStarted);
			player.draw(window, gameView, hasGameStarted, plySkin.playerTexture);
			hostile.draw(window, plySkin2.playerTexture, hasGameStarted);


			ply1score.setString(ply1scoreText.str());
			ply2score.setString(ply2scoreText.str());
			window.draw(ply1score);
			window.draw(ply2score);
			window.display();
		}
		if(hasGameStarted == 8)
		{
			window.clear(sf::Color::White);
			background7.draw(window, hasGameStarted);
			player.draw(window, gameView, hasGameStarted, plySkin.playerTexture);
			hostile.draw(window, plySkin2.playerTexture, hasGameStarted);


			ply1score.setString(ply1scoreText.str());
			ply2score.setString(ply2scoreText.str());
			window.draw(ply1score);
			window.draw(ply2score);
			window.display();
		}

		if(hasGameStarted == 9)
		{
			window.clear(sf::Color::White);
			if(ply1points > ply2points)
			{
				window.draw(winner1spr);
			}
			else if(ply1points < ply2points)
			{
				window.draw(winner2spr);
			}
			window.draw(winnerScrQuit);
			window.draw(end1spr);
			window.draw(end2spr);
			window.display();
		}

	}

}






/*if(player.playerSprite.getGlobalBounds().intersects(hostile.hostileSprite.getGlobalBounds()))
{
if(hostile.hostileSprite.getGlobalBounds().intersects(player.playerSprite.getGlobalBounds()))
{
//if((player.playerSprite.getPosition().x <= hostile.hostileSprite.getPosition().x + plySkin2.playerTexture.getSize().x) || (player.playerSprite.getPosition().x + plySkin.playerTexture.getSize().x >= hostile.hostileSprite.getPosition().x) || (player.playerSprite.getPosition().y <= hostile.hostileSprite.getPosition().y + plySkin2.playerTexture.getSize().y) || (player.playerSprite.getPosition().y + plySkin.playerTexture.getSize().y >= hostile.hostileSprite.getPosition().y))
havePlayersCollided = true;
if((player.playerSprite.getPosition().x + plySkin.playerTexture.getSize().x >= hostile.hostileSprite.getPosition().x) && (player.playerSprite.getPosition().x + plySkin.playerTexture.getSize().x < hostile.hostileSprite.getPosition().x + plySkin2.playerTexture.getSize().x / 2))
player.playerSprite.setPosition(hostile.hostileSprite.getPosition().x - plySkin.playerTexture.getSize().x - 1, player.playerSprite.getPosition().y);
if((player.playerSprite.getPosition().y + plySkin.playerTexture.getSize().y >= hostile.hostileSprite.getPosition().y) && (player.playerSprite.getPosition().y + plySkin.playerTexture.getSize().y < hostile.hostileSprite.getPosition().y + plySkin2.playerTexture.getSize().y / 2))
player.playerSprite.setPosition(player.playerSprite.getPosition().x, hostile.hostileSprite.getPosition().y - plySkin.playerTexture.getSize().y - 1);
if((player.playerSprite.getPosition().x <= hostile.hostileSprite.getPosition().x + plySkin2.playerTexture.getSize().x) && (player.playerSprite.getPosition().x > hostile.hostileSprite.getPosition().x + plySkin2.playerTexture.getSize().x / 2))
player.playerSprite.setPosition(hostile.hostileSprite.getPosition().x + plySkin2.playerTexture.getSize().x + 1,player.playerSprite.getPosition().y);
if((player.playerSprite.getPosition().y <= hostile.hostileSprite.getPosition().y + plySkin2.playerTexture.getSize().y) && (player.playerSprite.getPosition().y > hostile.hostileSprite.getPosition().y + plySkin2.playerTexture.getSize().y / 2))
player.playerSprite.setPosition(player.playerSprite.getPosition().x, hostile.hostileSprite.getPosition().y + plySkin2.playerTexture.getSize().y + 1);

if((hostile.hostileSprite.getPosition().x + plySkin2.playerTexture.getSize().x >= player.playerSprite.getPosition().x) && (hostile.hostileSprite.getPosition().x + plySkin2.playerTexture.getSize().x < player.playerSprite.getPosition().x + plySkin.playerTexture.getSize().x / 2))
hostile.hostileSprite.setPosition(player.playerSprite.getPosition().x - plySkin2.playerTexture.getSize().x - 1, player.playerSprite.getPosition().y);
if((hostile.hostileSprite.getPosition().y + plySkin2.playerTexture.getSize().y >= player.playerSprite.getPosition().y) && (hostile.hostileSprite.getPosition().y + plySkin2.playerTexture.getSize().y < player.playerSprite.getPosition().y + plySkin.playerTexture.getSize().y / 2))
hostile.hostileSprite.setPosition(hostile.hostileSprite.getPosition().x, player.playerSprite.getPosition().y - plySkin2.playerTexture.getSize().y - 1);
if((hostile.hostileSprite.getPosition().x <= player.playerSprite.getPosition().x + plySkin.playerTexture.getSize().x) && (hostile.hostileSprite.getPosition().x > player.playerSprite.getPosition().x + plySkin.playerTexture.getSize().x / 2))
hostile.hostileSprite.setPosition(player.playerSprite.getPosition().x + plySkin.playerTexture.getSize().x + 1,player.playerSprite.getPosition().y);
if((hostile.hostileSprite.getPosition().y <= player.playerSprite.getPosition().y + plySkin.playerTexture.getSize().y) && (hostile.hostileSprite.getPosition().y > player.playerSprite.getPosition().y + plySkin.playerTexture.getSize().y / 2))
hostile.hostileSprite.setPosition(hostile.hostileSprite.getPosition().x, player.playerSprite.getPosition().y + plySkin.playerTexture.getSize().y + 1);
}

}
else
havePlayersCollided = false;*/
