#include <iostream>
#include <cassert>
#include "TetrisGame.h"

const int TetrisGame::BLOCK_WIDTH{32};
const int TetrisGame::BLOCK_HEIGHT{32};
const double TetrisGame::MAX_SECONDS_PER_TICK{0.75};
const double TetrisGame::MIN_SECONDS_PER_TICK{0};
const float TetrisGame::FASTEST_SPEED_SCORE{2000};

TetrisGame::TetrisGame(sf::RenderWindow& window, sf::Sprite& blockSprite, const Point& gameboardOffset, const Point& nextShapeOffset, const sf::Sound& blockDrop, const sf::Sound& blockRotate, const sf::Sound& gameOver, const sf::Sound& levelUp)
	: window(window), blockSprite(blockSprite), gameboardOffset(gameboardOffset), nextShapeOffset(nextShapeOffset), blockDrop(blockDrop), blockRotate(blockRotate), gameOver(gameOver), levelUp(levelUp)
{
	// setup our font for drawing the score
	if (!scoreFont.loadFromFile("fonts/RedOctober.ttf"))
	{
		assert(false && "Missing font: RedOctober.ttf");
	};
	scoreText.setFont(scoreFont);
	scoreText.setCharacterSize(18);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(425, 325);
	updateScoreDisplay();

	reset();
}

void TetrisGame::draw()
{
	drawGameboard();
	window.draw(scoreText);
	drawTetromino(currentShape, gameboardOffset);
	drawTetromino(nextShape, nextShapeOffset);
	drawGhostTetromino();
}

void TetrisGame::onKeyPressed(sf::Event event)
{
	// either move with arrow keys or WASD
	switch (event.key.code) {
		case sf::Keyboard::Up: attemptRotate(currentShape); break;
		case sf::Keyboard::W: attemptRotate(currentShape); break;
		case sf::Keyboard::R: attemptRotate(currentShape); break;
		case sf:: Keyboard::Left: attemptMove(currentShape, -1, 0); break;
		case sf::Keyboard::A: attemptMove(currentShape, -1, 0); break;
		case sf::Keyboard::Down: attemptMove(currentShape, 0, 1); break;
		case sf::Keyboard::S: attemptMove(currentShape, 0, 1); break;
		case sf::Keyboard::Right: attemptMove(currentShape, 1, 0); break;
		case sf::Keyboard::D: attemptMove(currentShape, 1, 0); break;

		case sf::Keyboard::Space:
			drop(currentShape); 
			lock(currentShape); 

			blockDrop.play();

			break;
		default: break;
	}
}

void TetrisGame::processGameLoop(float deltaTime)
{
	secondsSinceLastTick += deltaTime;
	if (secondsSinceLastTick > secondsPerTick) {
		tick();
		secondsSinceLastTick -= secondsPerTick;
	}
	if (shapePlacedSinceLastGameLoop) {
		shapePlacedSinceLastGameLoop = false;

		if (!spawnNextShape()) {
			reset();
			return;
		}

		pickNextShape();

		int completedRowCount = board.removeCompletedRows();

		// tetris score calculation
		float lineScore = 40;
		switch (completedRowCount) {
			case 0: lineScore = 0;
			case 2: lineScore *= 2.5; break;
			case 3: lineScore *= 7.5; break;
			case 4: lineScore *= 25; break;
			default: break;
		}

		score += lineScore;
		updateScoreDisplay();

		determineSecondsPerTick();
	}
}

void TetrisGame::tick()
{
	if (!attemptMove(currentShape, 0, 1)) lock(currentShape);
}

void TetrisGame::reset()
{
	score = 0;
	determineSecondsPerTick();
	board.empty();
	pickNextShape();
	spawnNextShape();
	pickNextShape();
}

void TetrisGame::pickNextShape()
{
	nextShape.setShape(Tetromino::getRandomShape());
}

bool TetrisGame::spawnNextShape()
{
	GridTetromino temp = GridTetromino();
	Point spawnLoc = board.getSpawnLoc();
	temp.setGridLoc(spawnLoc);

	if (!isPositionLegal(temp)) return false;
	
	currentShape = nextShape;
	currentShape.setGridLoc(spawnLoc);

	return true;
}

bool TetrisGame::attemptRotate(GridTetromino& shape) const
{
	GridTetromino temp = shape;
	temp.rotateClockwise();
	if (isPositionLegal(temp)) {
		shape.rotateClockwise();
		return true;
	}
	return false;
}

bool TetrisGame::attemptMove(GridTetromino& shape, int x, int y) const
{
	GridTetromino temp = shape;
	temp.move(x, y);
	if (isPositionLegal(temp)) {
		shape.move(x, y);
		return true;
	}
	return false;
}

void TetrisGame::drop(GridTetromino& shape) const
{
	while (attemptMove(shape, 0, 1) == true);
}

void TetrisGame::lock(GridTetromino& shape)
{
	board.setContent(shape.getBlockLocsMappedToGrid(), static_cast<int>(shape.getColor()));
	shapePlacedSinceLastGameLoop = true;
}

void TetrisGame::drawBlock(Point topLeft, int xOffset, int yOffset, TetColor color, int transparency) const
{
	// move the sprite position based on the color to show the correct color

	int colorPosition = static_cast<int>(color) * BLOCK_WIDTH;
	blockSprite.setTextureRect(sf::IntRect(colorPosition, 0, BLOCK_WIDTH, BLOCK_HEIGHT));
	blockSprite.setPosition(sf::Vector2f(topLeft.getAddX(xOffset), topLeft.getAddY(yOffset)));

	sf::Color transparentColor = blockSprite.getColor();
	transparentColor.a = transparency;
	blockSprite.setColor(transparentColor);

	window.draw(blockSprite);
}

void TetrisGame::drawGameboard() const
{
	for (int y = 0; y < board.MAX_Y; y++) {
		for (int x = 0; x < board.MAX_X; x++) {
			
			Point curPoint = Point(x, y);
			int boardContent = board.getContent(curPoint);
			if(boardContent == board.EMPTY_BLOCK) continue;
			drawBlock(gameboardOffset, x * BLOCK_WIDTH, y * BLOCK_HEIGHT, static_cast<TetColor>(boardContent));
		}
	}
}

void TetrisGame::drawTetromino(GridTetromino& tetromino, Point topleft, int transparency) const
{
	std::vector<Point> gridPoints = tetromino.getBlockLocsMappedToGrid();
	for (Point point : gridPoints) {
		drawBlock(topleft, point.getX() * BLOCK_WIDTH, point.getY() * BLOCK_HEIGHT, tetromino.getColor(), transparency);
	}
}

void TetrisGame::drawGhostTetromino() 
{
	ghostShape = currentShape;
	drop(ghostShape);
	drawTetromino(ghostShape, gameboardOffset, 128);
}

void TetrisGame::updateScoreDisplay()
{
	std::string scoreString = "Score: " + std::to_string(score);
	scoreText.setString(scoreString);
}



bool TetrisGame::isPositionLegal(GridTetromino& shape) const
{
	if (!isWithinBorders(shape)) return false;
	
	if(!board.areAllLocsEmpty(shape.getBlockLocsMappedToGrid())) {
		return false;
	}

	return true;
}

bool TetrisGame::isWithinBorders(GridTetromino& shape) const
{
	int maxLeft = 0;
	int maxRight = board.MAX_X;
	int maxDown = board.MAX_Y;

	for (Point point : shape.getBlockLocsMappedToGrid()) {
		int x = point.getX();
		int y = point.getY();
		if (y >= maxDown || x >= maxRight || x < maxLeft) return false;
	}

	return true;
}

void TetrisGame::determineSecondsPerTick()
{
	// make the seconds go faster the more score you have
	float clampedScore = std::max(0.0f, std::min(static_cast<float>(score), FASTEST_SPEED_SCORE));
	float progress = 1.0f - (clampedScore / FASTEST_SPEED_SCORE);
	secondsPerTick = MIN_SECONDS_PER_TICK + progress * (MAX_SECONDS_PER_TICK - MIN_SECONDS_PER_TICK);
	secondsPerTick = std::max(MIN_SECONDS_PER_TICK, std::min(MAX_SECONDS_PER_TICK, secondsPerTick));
	//std::cout << secondsPerTick << std::endl;
}

