

#include <SFML/Graphics.hpp>
#include <iostream>
#include "TetrisGame.h"
#include "TestSuite.h"


int main()
{	
	// run some sanity tests on our classes to ensure they're working as expected.
	TestSuite::runTestSuite();

	std::srand(static_cast<unsigned int>(std::time(nullptr)));


	// load images
	sf::Sprite blockSprite;			// the tetromino block sprite
	sf::Texture blockTexture;		// the tetromino block texture
	sf::Sprite backgroundSprite;	// the background sprite
	sf::Texture backgroundTexture;	// the background texture
	
	backgroundTexture.loadFromFile("images/background.png");// load the background sprite
	backgroundSprite.setTexture(backgroundTexture);

	blockTexture.loadFromFile("images/tiles.png");	// load the tetris block sprite
	blockSprite.setTexture(blockTexture);

	// load sounds
	sf::SoundBuffer blockDropBuffer;
	sf::SoundBuffer blockRotateBuffer;
	sf::SoundBuffer gameOverBuffer;
	sf::SoundBuffer levelUpBuffer;

	blockDropBuffer.loadFromFile("sfx/blockDrop.ogg");
	blockRotateBuffer.loadFromFile("sfx/blockRotate.ogg");
	gameOverBuffer.loadFromFile("sfx/gameOver.ogg");
	levelUpBuffer.loadFromFile("sfx/levelUp.ogg");

	sf::Sound blockDrop;
	blockDrop.setBuffer(blockDropBuffer);

	sf::Sound blockRotate;
	blockRotate.setBuffer(blockDropBuffer);

	sf::Sound gameOver;
	gameOver.setBuffer(blockDropBuffer);

	sf::Sound levelUp;
	levelUp.setBuffer(blockDropBuffer);

	sf::Music music;
	music.openFromFile("sfx/tetrisMusic.ogg");
	music.play();
	music.setLoop(true);

	// create the game window
	sf::RenderWindow window(sf::VideoMode(640, 800), "Tetris Game Window");	
	
	window.setFramerateLimit(30);				// set a max framerate of 30 FPS

	const Point gameboardOffset{ 54, 125 };		// the pixel offset of the top left of the gameboard 
	const Point nextShapeOffset{ 490, 210 };	// the pixel offset of the next shape Tetromino

	// set up a tetris game
	TetrisGame game(window, blockSprite, gameboardOffset, nextShapeOffset, blockDrop, blockRotate, gameOver, levelUp);

	// set up a clock so we can determine seconds per game loop
	sf::Clock clock;		

	// create an event for handling userInput from the GUI (graphical user interface)
	sf::Event guiEvent;	

	// the main game loop
	while (window.isOpen())
	{
		// how long since the last loop (fraction of a second)		
		float deltaTime = clock.getElapsedTime().asSeconds();
		clock.restart();		

		// handle any window or keyboard events that have occured since the last game loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)	// handle close button clicked
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				game.onKeyPressed(event);	// handle key press
			}
		}

		game.processGameLoop(deltaTime);	// handle tetris game logic in here.

		// Draw the game to the screen
		window.clear(sf::Color::White);	// clear the entire window
		window.draw(backgroundSprite);	// draw the background (onto the window) 				
		game.draw();					// draw the game (onto the window)
		window.display();				// re-display the entire window
	}
	
	return 0;
}
