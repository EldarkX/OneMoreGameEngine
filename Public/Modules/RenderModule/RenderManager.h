#pragma once

#include "Modules/CoreModule/GameEngine.h"

class RenderManager
{

public:

	RenderManager(SDL_Renderer* Renderer);

	void							DrawBackBuffer();

	void							DrawFrontBuffer();

	void							SwitchBuffers();

	void							AddDrawableComponent(class SpriteComponent *);

	void							RemoveDrawableComponent(class SpriteComponent *);

private:

	SDL_Renderer					*mRenderer;

	vector<class SpriteComponent *>	mDrawableComponents;

};