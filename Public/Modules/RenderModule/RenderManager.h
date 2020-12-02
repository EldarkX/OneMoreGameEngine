#pragma once

#include "Modules/CoreModule/GameEngine.h"

class RenderManager
{

public:

	RenderManager(GameEngine *gameEngine);

	void							DrawBackBuffer();

	void							DrawFrontBuffer();

	void							SwitchBuffers();

	void							AddDrawableComponent(class SpriteComponent *);

	void							RemoveDrawableComponent(class SpriteComponent *);

	Matrix4D						CreateSimpleViewProj(float width, float height);

private:

	vector<class SpriteComponent *>	mDrawableComponents;

	class VertexArray				*mSpriteVerts;
	class Shader					*mSpriteShader;

	GameEngine						*mGameEngine;
};