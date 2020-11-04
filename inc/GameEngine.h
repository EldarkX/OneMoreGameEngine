#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <vector>
#include <string>

#include "controller.h"
#include "Vector2D.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;

using std::to_string;

#define  DEBUG_COLLISIONS 0
#define  SHOW_FPS 1

enum class EGameStatus
{
    GSE_Game,
    GSE_Exit
};

class Game
{

public:

    Game(int window_width, int window_height);

    void							PreInit();

    void							Init();

    void							Tick();

    void							End();

    void							LoadLevel(string path);

    class MoveableObject			*GetPlayer() const;

    static SDL_Window				*GetWindow();
    static SDL_Renderer				*GetRenderer();

    static Game						*GetInstance();

	inline int						GetWindowWidth() const { return _window_width; }
	inline int						GetWindowHeight() const { return _window_height; }

	void							RemoveBlock(class Object* Block);

    inline static					EGameStatus gameStatus;
    inline static double			DeltaTime;

private:

    inline static Game             *_game;

    inline static SDL_Window       *_window;
    inline static SDL_Renderer     *_renderer;

    SDL_Event						event;

    int								_window_width;
    int								_window_height;

    vector<class Object *>			blocks;
    class MoveableObject            *player = nullptr;
    class MoveableObject            *ball = nullptr;

	class CollisionManager			*collisionManager = nullptr;

};
