
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

	/*CREATE PLAYER*/

	SDL_Texture* mPlayerTexture = IMG_LoadTexture(mRenderer, "D:\\Andrey\\Projects\\VS2019\\OneMoreEngine\\OneMoreEngine\\assets\\images\\Player.png");

	if (!mPlayerTexture)
		cout << IMG_GetError() << endl;

	int mPlayerWidth = 80, mPlayerHeight = 10;

	mPlayer = new Player(this, mPlayerTexture,
		Vector2D(mWindow_width / 2, mWindow_height - mPlayerHeight / 2),
		Vector2D(mPlayerWidth, mPlayerHeight), "mPlayer");

	AddActor(mPlayer);

	/*CREATE BALL*/

	SDL_Texture* mBallTexture = IMG_LoadTexture(mRenderer, "D:\\Andrey\\Projects\\VS2019\\OneMoreEngine\\OneMoreEngine\\assets\\images\\Ball.png");

	if (!mBallTexture)
		cout << IMG_GetError() << endl;

	int mBallWidth = 16, mBallHeight = 16;

	mBall = new Ball(this, mBallTexture,
		Vector2D(mWindow_width / 2., mWindow_height - mPlayerHeight - mBallHeight / 2. - 1),
		Vector2D(mBallWidth, mBallHeight), "Ball");

	mBall->SetVelocity(Vector2D(0, -1));

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
						Actor->GetActorPosition().X() - Actor->GetActorSize().X() / 2,
						Actor->GetActorPosition().Y() - Actor->GetActorSize().Y() / 2,
						Actor->GetActorPosition().X() + Actor->GetActorSize().X() / 2,
						Actor->GetActorPosition().Y() + Actor->GetActorSize().Y() / 2);
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

	mCollisionManager->RemoveAgent(ActorToRemove);

	delete ActorToRemove;
}

void GameEngine::AddActor(class Actor* ActorToAdd)
{
	mCollisionManager->AddAgent(ActorToAdd);

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
			AddActor(newBlock);
		}
	}

	Actor* leftWall = new Actor(this, NULL, Vector2D(4., mWindow_height / 2.), Vector2D(8., mWindow_height), "Left wall");
	leftWall->SetCollisionType(ECollisionType::CTE_Wall);
	AddActor(leftWall);

	Actor* rightWall = new Actor(this, NULL, Vector2D(mWindow_width - 4., mWindow_height / 2.), Vector2D(8., mWindow_height), "Right wall");
	leftWall->SetCollisionType(ECollisionType::CTE_Wall);
	AddActor(rightWall);

	Actor* topWall = new Actor(this, NULL, Vector2D(mWindow_width / 2., 4.), Vector2D(mWindow_width, 8.), "Top wall");
	topWall->SetCollisionType(ECollisionType::CTE_Wall);
	AddActor(topWall);
}