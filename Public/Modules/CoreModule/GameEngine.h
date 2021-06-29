#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "glew.h"


#include <Windows.h>

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <assert.h>

#include "Modules/MathModule/Vector2D.h"
#include "Modules/MathModule/Matrix4.h"

#include "DataTypes.h"

#include "Utils/Delegate/MulticastDelegate.h"
#include "Utils/AssetManager/AssetsManagerUtils.h"

using namespace DelegateLib;

using std::cout;
using std::endl;
using std::vector;
using std::string;

using std::to_string;

#define  DEBUG_COLLISIONS 0
#define  DEBUG_SHOW_FPS 1

class GameEngine
{

public:

	GameEngine(int window_width, int window_height);
	GameEngine(GameEngine& gameEngine) = delete;
	GameEngine(GameEngine&& gameEngine) = delete;
	
	void operator=(const GameEngine& gameEngine) = delete;
	void operator=(const GameEngine&& gameEngine) = delete;

	int								PreInit();

	virtual int						Init() = 0;

	virtual void					Tick();

	SDL_Window*						GetWindow() const { return mWindow; }

	class CollisionManager			*GetCollisionManager() const { return mCollisionManager; }
	class RenderManager				*GetRenderManager() const { return mRenderManager; }
	class InputManager				*GetInputManager() const { return mInputManager; }
	class AssetsManagerUtils		*GetAssetsManagerUtils() const { return mAssetsManagerUtils; }

	inline int						GetWindowWidth() const { return mWindow_width; }
	inline int						GetWindowHeight() const { return mWindow_height; }
	inline int						GetWindowHalfWidth() const { return mWindow_halfWidth; }
	inline int						GetWindowHalfHeight() const { return mWindow_halfHeight; }

	const EGameStatus				GetGameStatus() const { return mGameStatus; }
	void							SetGameStatus(EGameStatus newGameStatus) { mGameStatus = newGameStatus; }

	void							AddActor(class AActor* ActorToAdd);
	void							RemoveActor(class AActor* ActorToRemove);

	void							AddObjectToKill(class AActor* actorToKill) { ActorsToKill.push_back(actorToKill); }

	void							KillActors();

	static GameEngine				*GetGameEngine();

	template<class T>
	T* CreateActor(Vector2D ActorPosition, Vector2D ActorSize, string ObjectName)
	{
		AActor* NewActor = new T();
		NewActor->SetObjectName(ObjectName);

		NewActor->SetActorPosition(ActorPosition);
		NewActor->SetActorScale(ActorSize);

		NewActor->OnStartBeingPendingToKill += MakeDelegate(this, &GameEngine::AddObjectToKill);

		NewActor->BeginPlay();

		AddActor(NewActor);

		return static_cast<T *>(NewActor);
	}

	virtual							~GameEngine();

protected:

	EGameStatus						mGameStatus;

	float							DeltaTime;

	bool							mIsActorsUpdating = false;

    SDL_Window						*mWindow;
	SDL_GLContext					mContext;

    SDL_Event						event;

    int								mWindow_width;
    int								mWindow_height;

	int								mWindow_halfWidth;
	int								mWindow_halfHeight;

    vector<class AActor *>			mActors;
	vector<class AActor*>			mNewActors;
	vector<class AActor*>			ActorsToKill;

	class CollisionManager			*mCollisionManager = nullptr;
	class RenderManager				*mRenderManager = nullptr;
	class InputManager				*mInputManager = nullptr;
	class AssetsManagerUtils		*mAssetsManagerUtils = nullptr;

	static GameEngine				*thisGameEngine;
};
