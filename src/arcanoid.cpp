#include "../inc/arcanoid.h"
#include "../inc/moveableObject.h"

#include <ctime>

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
}

void Game::Init()
{
	IMG_Init(IMG_INIT_PNG);

	SDL_Texture* playerTexture = IMG_LoadTexture(Game::_renderer, "D:\\Andrey\\Projects\\VS2019\\OneMoreEngine\\OneMoreEngine\\assets\\images\\player.png");

	if (!playerTexture)
		cout << IMG_GetError() << endl;

	int playerWidth = 80, playerHeight = 10;

	player = new MoveableObject(playerTexture,
	Vec2D(_window_width / 2 - playerWidth / 2,
		  _window_height - playerHeight),
	Vec2D(playerWidth, playerHeight));

	LoadLevel("tmp");
}

void Game::Tick()
{
    time_t        seconds = time(NULL);
    unsigned int  nbFrames = 0; 

    while (Game::gameStatus == EGameStatus::GSE_Game)
    {
		nbFrames++;

		if (SDL_PollEvent(&event))
		{
			handleInput(&event);
		}
		SDL_RenderClear(Game::_renderer);

		player->Tick();
      
		for (auto &block : blocks)
			block->Tick();

		SDL_RenderPresent(Game::_renderer);

		if (time(NULL) - seconds >= 1)
		{
			Game::DeltaTime = (float)(time(NULL) - seconds) / nbFrames;
			seconds = time(NULL);

			//cout << "FPS = " << nbFrames << endl;
			cout << "DeltaTime = " << Game::DeltaTime << endl;

			nbFrames = 0;
		}
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

void Game::LoadLevel(string path)
{

	SDL_Texture* blockTexture = IMG_LoadTexture(Game::_renderer, "D:\\Andrey\\Projects\\VS2019\\OneMoreEngine\\OneMoreEngine\\assets\\images\\block.png");

	if (!blockTexture)
    cout << "Error: can't load block texture!" << endl;

	vector<string> level;

	int blocksInRow = 12;
	int rows = 8;

	int offsetW = _window_width / 8;
	int offsetH = _window_height / 10;

	int gapW = 10;
	int gapH = 10;

	int blockWidth = (_window_width - offsetW * 2 - gapW * blocksInRow)
                    / blocksInRow;

	int blockHeight = (_window_height - offsetH - _window_height * 0.6
                    - gapH * rows) / rows;  

	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < blocksInRow; ++col)
		{
			blocks.push_back(new Object(blockTexture,
				Vec2D(offsetW + blockWidth * col + gapW * col,
				offsetH + blockHeight * row + gapH * row),
				Vec2D(blockWidth, blockHeight)));
		}
	}
}