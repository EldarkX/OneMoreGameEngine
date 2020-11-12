
#include "Modules/CoreModule/GameEngine.h"
#include "Modules/ObjectModule/Object/Actor/Actor.h"

#include "Modules/CoreModule/CollisionManager.h"
#include "Modules/CoreModule/RenderManager.h"
#include "Modules/CoreModule/InputManager.h"

#include <algorithm>

GameEngine::GameEngine(int window_width, int window_height)
      : mWindow_width(window_width),
        mWindow_height(window_height)
{
	mGameStatus = EGameStatus::GSE_Game;
};

int GameEngine::PreInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		cout << "Can't init SDL" << endl;
		return -1;
	}

    mWindow = SDL_CreateWindow("Arcanoid", 200, 200, mWindow_width, mWindow_height, 0);

	if (!mWindow)
	{
		cout << "Can't create SDL_Window" << endl;
		return -1;
	}

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!mRenderer)
	{
		cout << "Can't create SDL_Renderer" << endl;
		return -1;
	}

	mRenderManager = new RenderManager(mRenderer);

	if (!mRenderManager)
	{
		cout << "Can't create Render Manager" << endl;
		return -1;
	}

	if (IMG_Init(IMG_INIT_PNG) == -1)
	{
		cout << "Can't init IMG" << endl;
		return -1;
	}

	mCollisionManager = new CollisionManager();

	if (!mCollisionManager)
	{
		cout << "Can't create Collision Manager" << endl;
		return -1;
	}

	mInputManager = new InputManager();

	if (!mInputManager)
	{
		cout << "Can't create Input Manager" << endl;
		return -1;
	}

	return 1;
}

void GameEngine::Tick()
{
	for (auto Actor : mActors)
	{
		Actor->BeginPlay();
	}

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
			mInputManager->HandleInput(&event);
		}

		if (mGameStatus != EGameStatus::GSE_Pause)
		{
			mRenderManager->DrawBackBuffer();

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
			
			//DRAWING

			mRenderManager->DrawFrontBuffer();
			mRenderManager->SwitchBuffers();
		}
    }
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
	while (!ActorsToKill.empty())
	{
		Actor *a = ActorsToKill.back();
		ActorsToKill.pop_back();
		RemoveActor(a);
	}
}

GameEngine::~GameEngine()
{
	while (!mActors.empty())
	{
		RemoveActor(mActors.back());
	}

	while (!mNewActors.empty())
	{
		RemoveActor(mNewActors.back());
	}

	if (mCollisionManager)
		delete mCollisionManager;

	if (mRenderer)
		SDL_DestroyRenderer(mRenderer);

	if (mWindow)
		SDL_DestroyWindow(mWindow);

	SDL_Quit();
}

