#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <vector>
#include <string>

#include "Modules/MathModule/Vector2D.h"
#include "DataTypes.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;

using std::to_string;

#define  DEBUG_COLLISIONS 1
#define  SHOW_FPS 0

class GameEngine
{

public:

	GameEngine(int window_width, int window_height);

    void							PreInit();

    void							Init();

    void							Tick();

    void							End();

    void							LoadLevel(string path);

	class Actor						*GetPlayer() const { return mPlayer; };

	SDL_Window						*GetWindow() const { return mWindow; }
	SDL_Renderer					*GetRenderer() const { return mRenderer; }

	inline int						GetWindowWidth() const { return mWindow_width; }
	inline int						GetWindowHeight() const { return mWindow_height; }

	const EGameStatus				GetGameStatus() const { return mGameStatus; }
	void							SetGameStatus(EGameStatus newGameStatus) { mGameStatus = newGameStatus; }

	void							AddActor(class Actor* ActorToAdd);
	void							RemoveActor(class Actor* ActorToRemove);

	void							KillActors();


	class Actor*					CreateActor(SDL_Texture* ActorTexture, Vector2D ActorPosition, Vector2D ActorSize, string ObjectName);

private:

	EGameStatus						mGameStatus;

	double							DeltaTime;

	bool							mIsActorsUpdating;

    SDL_Window						*mWindow;
    SDL_Renderer					*mRenderer;

    SDL_Event						event;

    int								mWindow_width;
    int								mWindow_height;

    vector<class Actor *>			mActors;
	vector<class Actor*>			mNewActors;
    class Actor						*mPlayer = nullptr;
    class Actor						*mBall = nullptr;

	class CollisionManager			*mCollisionManager = nullptr;

};
