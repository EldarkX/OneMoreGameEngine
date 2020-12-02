#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "glew.h"

#include <Windows.h>

#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

#include "Modules/MathModule/Vector2D.h"
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
#define  DEBUG_SHOW_FPS 0

class GameEngine
{

public:

	GameEngine(int window_width, int window_height);

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

	const EGameStatus				GetGameStatus() const { return mGameStatus; }
	void							SetGameStatus(EGameStatus newGameStatus) { mGameStatus = newGameStatus; }

	void							AddActor(class Actor* ActorToAdd);
	void							RemoveActor(class Actor* ActorToRemove);

	void							AddObjectToKill(class Actor* actorToKill) { ActorsToKill.push_back(actorToKill); }

	void							KillActors();

	template<class T>
	T* CreateActor(Vector2D ActorPosition, Vector2D ActorSize, string ObjectName)
	{
		Actor* NewActor = new T(this, ObjectName);

		NewActor->SetActorPosition(ActorPosition);
		NewActor->SetActorSize(ActorSize);

		NewActor->OnStartBeingPendingToKill += MakeDelegate(this, &GameEngine::AddObjectToKill);

		AddActor(NewActor);

		return static_cast<T *>(NewActor);
	}

	~GameEngine();

protected:

	EGameStatus						mGameStatus;

	float							DeltaTime;

	bool							mIsActorsUpdating = false;

    SDL_Window						*mWindow;
	SDL_GLContext					mContext;

    SDL_Event						event;

    int								mWindow_width;
    int								mWindow_height;

    vector<class Actor *>			mActors;
	vector<class Actor*>			mNewActors;
	vector<class Actor*>			ActorsToKill;

	class CollisionManager			*mCollisionManager = nullptr;
	class RenderManager				*mRenderManager = nullptr;
	class InputManager				*mInputManager = nullptr;
	class AssetsManagerUtils		*mAssetsManagerUtils = nullptr;
};
