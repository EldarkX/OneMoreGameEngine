
#include "Modules/CoreModule/GameEngine.h"
#include "Modules/ObjectModule/Object/Actor/Actor.h"

#include "Modules/CoreModule/CollisionManager.h"

#include "Modules/ObjectModule/Object/Components/InputComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"

#include "Ball.h"
#include "Player.h"
#include "Block.h"

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

	/*CREATE PLAYER*/

	SDL_Texture* mPlayerTexture = IMG_LoadTexture(mRenderer, "D:\\Andrey\\Projects\\VS2019\\OneMoreEngine\\OneMoreEngine\\assets\\images\\Player.png");

	if (!mPlayerTexture)
		cout << IMG_GetError() << endl;

	mPlayer = new Player(this, "mPlayer");
	mPlayer->Sprite->SetTexture(mPlayerTexture);

	AddActor(mPlayer);

	/*CREATE BALL*/

	SDL_Texture* mBallTexture = IMG_LoadTexture(mRenderer, "D:\\Andrey\\Projects\\VS2019\\OneMoreEngine\\OneMoreEngine\\assets\\images\\Ball.png");

	if (!mBallTexture)
		cout << IMG_GetError() << endl;

	mBall = new Ball(this, "Ball");

	mBall->Sprite->SetTexture(mBallTexture);

	AddActor(mBall);

	LoadLevel("tmp");
}

void GameEngine::Tick()
{
    auto			mTicksCount = SDL_GetTicks();
	auto			second = 0.;

    unsigned int	nbFrames = 0; 

    while (mGameStatus != EGameStatus::GSE_Exit)
    {
		// DELTA TIME CALCULATION
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 1));
		DeltaTime = (SDL_GetTicks() - mTicksCount) / 1000.f;
		DeltaTime = DeltaTime > 0.05f ? 0.05f : DeltaTime;
		mTicksCount = SDL_GetTicks();

		if (DEBUG_SHOW_FPS)
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

		if (mGameStatus != EGameStatus::GSE_Pause)
		{
			//BACK BUFFER RESET
			SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(mRenderer);

			//COLLISION HANDLE
			mCollisionManager->CheckAllCollisions();

			//OBJECTS UPDATE

			mIsActorsUpdating = true;
			for (auto& Actor : mActors)
			{
				Actor->Tick(DeltaTime);
			}
			mIsActorsUpdating = false;

			for (auto& newActor : mNewActors)
			{
				mActors.push_back(newActor);
			}

			mNewActors.clear();

			if (DEBUG_COLLISIONS)
			{
				SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

				for (auto& Actor : mActors)
				{
					SDL_RenderDrawLine(mRenderer,
						static_cast<int>(Actor->GetActorPosition().X() - Actor->GetActorSize().X() / 2.f),
						static_cast<int>(Actor->GetActorPosition().Y() - Actor->GetActorSize().Y() / 2.f),
						static_cast<int>(Actor->GetActorPosition().X() + Actor->GetActorSize().X() / 2.f),
						static_cast<int>(Actor->GetActorPosition().Y() + Actor->GetActorSize().Y() / 2.f));
				}
			}

			KillActors();

			//FRONT BUFFER RENDER
			SDL_RenderPresent(mRenderer);
		}
    }
}

void GameEngine::End()
{
	while (!mActors.empty())
	{
		RemoveActor(mActors.back());
	}

	while (!mNewActors.empty())
	{
		RemoveActor(mNewActors.back());
	}

	delete mCollisionManager;

	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}


void GameEngine::RemoveActor(Actor *ActorToRemove)
{
	mActors.erase(find(mActors.cbegin(), mActors.cend(), ActorToRemove));

	ActorToRemove->Destroy();
}

void GameEngine::AddActor(class Actor* ActorToAdd)
{
	if (mIsActorsUpdating)
	{
		mNewActors.push_back(ActorToAdd);
	}
	else
	{
		mActors.push_back(ActorToAdd);
	}
}

void GameEngine::KillActors()
{
	vector<Actor*> ActorsToKill;
	for (auto Actor : mActors)
	{
		if (Actor->GetIsPendingToKill())
		{
			ActorsToKill.push_back(Actor);
		}
	}
	while (!ActorsToKill.empty())
	{
		Actor *a = ActorsToKill.back();
		ActorsToKill.pop_back();
		RemoveActor(a);
	}
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

	float offsetW = mWindow_width / 8.f;
	float offsetH = mWindow_height / 10.f;

	float gapW = 10;
	float gapH = 10;

	float blockWidth = (mWindow_width - offsetW * 2 - gapW * mBlocksInRow)
		/ mBlocksInRow;

	float blockHeight = (mWindow_height - offsetH - mWindow_height * 0.6f
		- gapH * rows) / rows;

	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < mBlocksInRow; ++col)
		{
			Block* newBlock = new Block(this, "Block " + to_string(row * mBlocksInRow + col));

			newBlock->SetActorPosition(Vector2D(offsetW + blockWidth * col + gapW * col,
				offsetH + blockHeight * row + gapH * row));
			newBlock->SetActorSize(Vector2D(blockWidth, blockHeight));

			newBlock->Collision->SetCollisionType(ECollisionType::CTE_Block);

			newBlock->Sprite->SetTexture(blockTexture);

			AddActor(newBlock);
		}
	}

	Block* leftWall = new Block(this, "Left wall");
	leftWall->SetActorPosition(Vector2D(4.f, mWindow_height / 2.f));
	leftWall->SetActorSize(Vector2D(8.f, static_cast<float>(mWindow_height)));
	leftWall->Collision->SetCollisionType(ECollisionType::CTE_Wall);
	AddActor(leftWall);

	Block* rightWall = new Block(this, "Right wall");
	rightWall->SetActorPosition(Vector2D(mWindow_width - 4.f, mWindow_height / 2.f));
	rightWall->SetActorSize(Vector2D(8.f, static_cast<float>(mWindow_height)));
	rightWall->Collision->SetCollisionType(ECollisionType::CTE_Wall);
	AddActor(rightWall);

	Block* topWall = new Block(this, "Top wall");
	topWall->SetActorPosition(Vector2D(mWindow_width / 2.f, 4.f));
	topWall->SetActorSize(Vector2D(static_cast<float>(mWindow_width), 8.f));
	topWall->Collision->SetCollisionType(ECollisionType::CTE_Wall);
	AddActor(topWall);
}