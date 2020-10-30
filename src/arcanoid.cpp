#include "../inc/arcanoid.h"
#include "../inc/moveableObject.h"
#include "../inc/collisions.h"
#include "../inc/Ball.h"

#include <algorithm>

Game::Game(int window_width, int window_height)
      : _window_width(window_width),
        _window_height(window_height)
{
	if (Game::_game)
		delete this;
  
	Game::_game = this;
};

void Game::PreInit()
{
    Game::gameStatus = EGameStatus::GSE_Game;

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		  cout << "Can't init SDL" << endl;

    Game::_window = SDL_CreateWindow("Arcanoid", 200, 200, _window_width,
      _window_height, 0);

    Game::_renderer = SDL_CreateRenderer(_window, 1, SDL_RENDERER_ACCELERATED);

	IMG_Init(IMG_INIT_PNG);
}

void Game::Init()
{
	collisionManager = new CollisionManager();

	//Create player

	SDL_Texture* playerTexture = IMG_LoadTexture(Game::_renderer, "D:\\Andrey\\Projects\\VS2019\\OneMoreEngine\\OneMoreEngine\\assets\\images\\player.png");

	if (!playerTexture)
		cout << IMG_GetError() << endl;

	int playerWidth = 80, playerHeight = 10;

	player = new MoveableObject(playerTexture,
	Vector2D(_window_width / 2 - playerWidth / 2, _window_height - playerHeight), "Player",
	Vector2D(playerWidth, playerHeight));

	player->SetCollisionType(ECollisionType::CTE_Player);

	//Create ball

	collisionManager->AddActiveAgent(player);
	collisionManager->AddAgent(player);

	SDL_Texture* ballTexture = IMG_LoadTexture(Game::_renderer, "D:\\Andrey\\Projects\\VS2019\\OneMoreEngine\\OneMoreEngine\\assets\\images\\ball.png");

	if (!ballTexture)
		cout << IMG_GetError() << endl;

	int ballWidth = 16, ballHeight = 16;

	ball = new Ball(ballTexture,
		Vector2D(_window_width / 2 - ballWidth / 2, _window_height - playerHeight - ballHeight - 1), "Ball",
		Vector2D(ballWidth, ballHeight));

	ball->SetVelocity(Vector2D(0, -1));

	collisionManager->AddActiveAgent(ball);
	collisionManager->AddAgent(ball);

	LoadLevel("tmp");
}

void Game::Tick()
{
    auto			mTicksCount = SDL_GetTicks();
	auto			second = 0.;

    unsigned int	nbFrames = 0; 

    while (gameStatus == EGameStatus::GSE_Game)
    {
		// DELTA TIME CALCULATION
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 7));
		DeltaTime = (SDL_GetTicks() - mTicksCount) / 1000.f;
		DeltaTime = DeltaTime > 0.05 ? 0.05 : DeltaTime;
		mTicksCount = SDL_GetTicks();

		if (SHOW_FPS)
		{
			nbFrames++;

			second += DeltaTime;

			if (second >= 1)
			{
				second = 0.;
				cout << "FPS: " << nbFrames << endl;
				nbFrames = 0;
			}
		}

	    // INPUT HANDLE
		if (SDL_PollEvent(&event))
		{
			handleInput(&event);
		}

		//BACK BUFFER RESET
		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(_renderer);

		//COLLISION HANDLE
		collisionManager->CheckAllCollisions();

		//OBJECTS UPDATE
		player->Tick();

		ball->Tick();
      
		for (auto &block : blocks)
			block->Tick();

		if (DEBUG_COLLISIONS)
		{
			SDL_SetRenderDrawColor(_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

			SDL_RenderDrawLine(_renderer, ball->GetLeftUpCorner().X(), ball->GetLeftUpCorner().Y(), ball->GetRightBottomCorner().X(), ball->GetRightBottomCorner().Y());

			SDL_RenderDrawLine(_renderer, player->GetLeftUpCorner().X(), player->GetLeftUpCorner().Y(), player->GetRightBottomCorner().X(), player->GetRightBottomCorner().Y());

			for (auto& block : blocks)
				SDL_RenderDrawLine(_renderer, block->GetLeftUpCorner().X(), block->GetLeftUpCorner().Y(), block->GetRightBottomCorner().X(), block->GetRightBottomCorner().Y());
		}

		//FRONT BUFFER RENDER
		SDL_RenderPresent(_renderer);	
    }
}

void Game::End()
{

}

MoveableObject *Game::GetPlayer() const
{
  return player;
}

SDL_Window *Game::GetWindow()
{
  return _window;
}

SDL_Renderer *Game::GetRenderer()
{
  return _renderer;
}

Game *Game::GetInstance()
{
  return _game;
}

void Game::RemoveBlock(class Object* Block)
{
	blocks.erase(find(blocks.cbegin(), blocks.cend(), Block));
}

void Game::LoadLevel(string path)
{
	SDL_Texture* blockTexture = IMG_LoadTexture(Game::_renderer, "D:\\Andrey\\Projects\\VS2019\\OneMoreEngine\\OneMoreEngine\\assets\\images\\block.png");

	if (!blockTexture)
    cout << "Error: can't load block texture!" << endl;

	vector<string> level;

	int blocksInRow = 14;
	int rows = 5;

	double offsetW = _window_width / 8;
	double offsetH = _window_height / 10;

	double gapW = 10;
	double gapH = 10;

	double blockWidth = (_window_width - offsetW * 2 - gapW * blocksInRow)
                    / blocksInRow;

	double blockHeight = (_window_height - offsetH - _window_height * 0.6
                    - gapH * rows) / rows;

	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < blocksInRow; ++col)
		{
			Object* newBlock = new Object(
				blockTexture,
				Vector2D(offsetW + blockWidth * col + gapW * col, offsetH + blockHeight * row + gapH * row), "Block " + to_string(row * blocksInRow + col),
				Vector2D(blockWidth, blockHeight)
			);
			newBlock->SetCollisionType(ECollisionType::CTE_Block);
			blocks.push_back(newBlock);
			collisionManager->AddAgent(newBlock);

		}
	}

	Object* leftWall = new Object(NULL, Vector2D(0, 0), "Left wall", Vector2D(1, _window_height));
	leftWall->SetCollisionType(ECollisionType::CTE_Wall);
	collisionManager->AddAgent(leftWall);

	Object* rightWall = new Object(NULL, Vector2D(_window_width - 1., 0), "Right wall", Vector2D(1, _window_height));
	leftWall->SetCollisionType(ECollisionType::CTE_Wall);
	collisionManager->AddAgent(rightWall);

	Object* topWall = new Object(NULL, Vector2D(0, 0), "Top wall", Vector2D(_window_width, 1));
	topWall->SetCollisionType(ECollisionType::CTE_Wall);
	collisionManager->AddAgent(topWall);
}