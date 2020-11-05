
#include "Modules/CoreModule/GameEngine.h"
#include "Modules/ObjectModule/Object/Actor/Actor.h"

#include "Modules/CoreModule/CollisionManager.h"

#include "Modules/ObjectModule/Object/Components/InputComponent.h"

#include "Ball.h"
#include "Player.h"

#include <algorithm>

GameEngine::GameEngine(int window_width, int window_height)
      : mWindow_width(window_width),
        mWindow_height(window_height)
{

};

void GameEngine::PreInit()
{
    mGameStatus = EGameStatus::GSE_Game;

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		  cout << "Can't init SDL" << endl;

    mWindow = SDL_CreateWindow("Arcanoid", 200, 200, mWindow_width,
      mWindow_height, 0);

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	IMG_Init(IMG_INIT_PNG);
}

void GameEngine::Init()
{
	mCollisionManager = new CollisionManager();

	//Create mPlayer

	SDL_Texture* mPlayerTexture = IMG_LoadTexture(mRenderer, "D:\\Andrey\\Projects\\VS2019\\OneMoreEngine\\OneMoreEngine\\assets\\images\\Player.png");

	if (!mPlayerTexture)
		cout << IMG_GetError() << endl;

	int mPlayerWidth = 80, mPlayerHeight = 10;

	mPlayer = new Player(this, mPlayerTexture,
	Vector2D(mWindow_width / 2, mWindow_height - mPlayerHeight / 2),
	Vector2D(mPlayerWidth, mPlayerHeight), "mPlayer");

	mCollisionManager->AddActiveAgent(mPlayer);
	mCollisionManager->AddAgent(mPlayer);

	//Create mBall

	SDL_Texture* mBallTexture = IMG_LoadTexture(mRenderer, "D:\\Andrey\\Projects\\VS2019\\OneMoreEngine\\OneMoreEngine\\assets\\images\\Ball.png");

	if (!mBallTexture)
		cout << IMG_GetError() << endl;

	int mBallWidth = 16, mBallHeight = 16;

	mBall = new Ball(this, mBallTexture,
		Vector2D(mWindow_width / 2 - mBallWidth / 2, mWindow_height - mPlayerHeight - mBallHeight - 1),
		Vector2D(mBallWidth, mBallHeight), "Ball");

	mBall->SetVelocity(Vector2D(0, -1));

	mCollisionManager->AddActiveAgent(mBall);
	mCollisionManager->AddAgent(mBall);

	LoadLevel("tmp");
}

void GameEngine::Tick()
{
    auto			mTicksCount = SDL_GetTicks();
	auto			second = 0.;

    unsigned int	nbFrames = 0; 

    while (mGameStatus == EGameStatus::GSE_Game)
    {
		// DELTA TIME CALCULATION
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 1));
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
			handleInput(this, &event);
		}

		//BACK BUFFER RESET
		SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(mRenderer);

		//COLLISION HANDLE
		mCollisionManager->CheckAllCollisions();

		//OBJECTS UPDATE
		mPlayer->Tick(DeltaTime);

		mBall->Tick(DeltaTime);
      
		for (auto &block : mBlocks)
			block->Tick(DeltaTime);

		//if (DEBUG_COLLISIONS)
		//{
		//	SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

		//	SDL_RenderDrawLine(mRenderer, mBall->GetLeftUpCorner().X(), mBall->GetLeftUpCorner().Y(), mBall->GetRightBottomCorner().X(), mBall->GetRightBottomCorner().Y());

		//	SDL_RenderDrawLine(mRenderer, mPlayer->GetLeftUpCorner().X(), mPlayer->GetLeftUpCorner().Y(), mPlayer->GetRightBottomCorner().X(), mPlayer->GetRightBottomCorner().Y());

		//	for (auto& block : mBlocks)
		//		SDL_RenderDrawLine(mRenderer, block->GetLeftUpCorner().X(), block->GetLeftUpCorner().Y(), block->GetRightBottomCorner().X(), block->GetRightBottomCorner().Y());
		//}

		//FRONT BUFFER RENDER
		SDL_RenderPresent(mRenderer);	
    }
}

void GameEngine::End()
{
	for (auto obj : mBlocks)
		delete obj;

	delete mPlayer;
	delete mBall;

	delete mCollisionManager;

	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}


void GameEngine::RemoveBlock(class Object* Block)
{
	mBlocks.erase(find(mBlocks.cbegin(), mBlocks.cend(), Block));
}

class Actor* GameEngine::CreateActor(SDL_Texture* ActorTexture, Vector2D ActorPosition, Vector2D ActorSize, string ObjectName)
{ 
	return nullptr;
}

void GameEngine::LoadLevel(string path)
{
	SDL_Texture* blockTexture = IMG_LoadTexture(mRenderer, "D:\\Andrey\\Projects\\VS2019\\OneMoreEngine\\OneMoreEngine\\assets\\images\\block.png");

	if (!blockTexture)
    cout << "Error: can't load block texture!" << endl;

	vector<string> level;

	int mBlocksInRow = 14;
	int rows = 5;

	double offsetW = mWindow_width / 8;
	double offsetH = mWindow_height / 10;

	double gapW = 10;
	double gapH = 10;

	double blockWidth = (mWindow_width - offsetW * 2 - gapW * mBlocksInRow)
                    / mBlocksInRow;

	double blockHeight = (mWindow_height - offsetH - mWindow_height * 0.6
                    - gapH * rows) / rows;

	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < mBlocksInRow; ++col)
		{
			Actor* newBlock = new Actor(this,
				blockTexture,
				Vector2D(offsetW + blockWidth * col + gapW * col, offsetH + blockHeight * row + gapH * row),
				Vector2D(blockWidth, blockHeight), "Block " + to_string(row * mBlocksInRow + col)
			);
			newBlock->SetCollisionType(ECollisionType::CTE_Block);
			mBlocks.push_back(newBlock);
			mCollisionManager->AddAgent(newBlock);

		}
	}

	Actor* leftWall = new Actor(this, NULL, Vector2D(0, 0), Vector2D(1, mWindow_height), "Left wall");
	leftWall->SetCollisionType(ECollisionType::CTE_Wall);
	mCollisionManager->AddAgent(leftWall);

	Actor* rightWall = new Actor(this, NULL, Vector2D(mWindow_width - 1., 0), Vector2D(1, mWindow_height), "Right wall");
	leftWall->SetCollisionType(ECollisionType::CTE_Wall);
	mCollisionManager->AddAgent(rightWall);

	Actor* topWall = new Actor(this, NULL, Vector2D(0, 0), Vector2D(mWindow_width, 1), "Top wall");
	topWall->SetCollisionType(ECollisionType::CTE_Wall);
	mCollisionManager->AddAgent(topWall);
}