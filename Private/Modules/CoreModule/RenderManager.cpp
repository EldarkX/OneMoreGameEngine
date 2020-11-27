
#include "Modules/CoreModule/RenderManager.h"

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"

RenderManager::RenderManager(SDL_Renderer* Renderer)
	: mRenderer(Renderer)
{

}

void RenderManager::DrawBackBuffer()
{
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);
}

void RenderManager::DrawFrontBuffer()
{
	for (auto Drawable : mDrawableComponents)
	{
		Drawable->Draw(mRenderer);
	}
}

void RenderManager::SwitchBuffers()
{
	SDL_RenderPresent(mRenderer);
}

void RenderManager::AddDrawableComponent(class SpriteComponent *NewSprite)
{
	if (mDrawableComponents.empty())
	{
		mDrawableComponents.push_back(NewSprite);
	}
	else
	{
		for (auto iter = mDrawableComponents.cbegin(); iter < mDrawableComponents.cend(); ++iter)
		{
			if (NewSprite->GetDrawOrder() < (*iter)->GetDrawOrder())
			{
				mDrawableComponents.insert(iter, NewSprite);
				return;
			}
		}
		mDrawableComponents.push_back(NewSprite);
	}
}

void RenderManager::RemoveDrawableComponent(class SpriteComponent *Sprite)
{
	mDrawableComponents.erase(find(mDrawableComponents.cbegin(), mDrawableComponents.cend(), Sprite));
}

