
#include "Modules/LevelModule/BGComponent.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"

void BGComponent::SetTextures(const vector<SDL_Texture*>& Textures)
{
	int count = 0;
	for (SDL_Texture* text : Textures)
	{
		BGTexture newBGTexture;
		newBGTexture.mTexture = text;
		newBGTexture.mOffsetX = count * mOwner->GetGameEngine()->GetWindowWidth();
		mBGTextures.push_back(newBGTexture);
		++count;
	}
}

void BGComponent::Tick(float deltaTime)
{
	for (auto bgText : mBGTextures)
	{
		bgText.mOffsetX += mScrollSpeed * deltaTime;

		if (bgText.mOffsetX < -mOwner->GetGameEngine()->GetWindowWidth())
		{
			bgText.mOffsetX = (mBGTextures.size() - 1) * mOwner->GetGameEngine()->GetWindowWidth() - 1;
		}
	}
	
}
