#include "../inc/controller.h"
#include "../inc/arcanoid.h"
#include "../inc/moveableObject.h"

void    handleInput(const SDL_Event *event)
{
    if (event->type == SDL_QUIT || event->key.keysym.sym == SDL_KeyCode::SDLK_ESCAPE)
    {
        Game::gameStatus = EGameStatus::GSE_Exit;
    }
    else if (event->key.keysym.sym == SDL_KeyCode::SDLK_RIGHT
        || event->key.keysym.sym == SDL_KeyCode::SDLK_d)
    {
        if (event->type == SDL_KEYDOWN)
            Game::GetInstance()->GetPlayer()->SetVelocity(Vec2D(1, 0));
        else
            Game::GetInstance()->GetPlayer()->SetVelocity(Vec2D(0, 0));
    }
    else if (event->key.keysym.sym == SDL_KeyCode::SDLK_LEFT
        || event->key.keysym.sym == SDL_KeyCode::SDLK_a)
    {
        if (event->type == SDL_KEYDOWN)
            Game::GetInstance()->GetPlayer()->SetVelocity(Vec2D(-1, 0));
        else
            Game::GetInstance()->GetPlayer()->SetVelocity(Vec2D(0, 0));
    }
}
