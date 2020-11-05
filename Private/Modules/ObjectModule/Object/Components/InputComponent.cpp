#include "Modules/ObjectModule/Object/Components/InputComponent.h"
#include "Modules/CoreModule/GameEngine.h"
#include "Modules/MathModule/Vector2D.h"

#include "Player.h"

void    handleInput(GameEngine *Game, const SDL_Event *event)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

    if (event->type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE])
    {
        Game->SetGameStatus(EGameStatus::GSE_Exit);
    }
	else if (event->key.keysym.sym == SDL_KeyCode::SDLK_RIGHT
		|| event->key.keysym.sym == SDL_KeyCode::SDLK_d)
    {
        if (event->type == SDL_KEYDOWN)
            Game->GetPlayer()->SetVelocity(Vector2D(1, 0));
        else
            Game->GetPlayer()->SetVelocity(Vector2D(0, 0));
    }
    else if (event->key.keysym.sym == SDL_KeyCode::SDLK_LEFT
        || event->key.keysym.sym == SDL_KeyCode::SDLK_a)
    {
        if (event->type == SDL_KEYDOWN)
            Game->GetPlayer()->SetVelocity(Vector2D(-1, 0));
        else
            Game->GetPlayer()->SetVelocity(Vector2D(0, 0));
    }
}
