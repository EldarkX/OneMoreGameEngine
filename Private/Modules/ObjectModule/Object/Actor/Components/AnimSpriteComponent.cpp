
#include "Modules/ObjectModule/Object/Actor/Components/AnimSpriteComponent.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"

void AnimSpriteComponent::SetTextures(const vector<SDL_Texture*>& Textures)
{
	mTextures = Textures;

	mCurrentFrame = 0;

	mTexturesAmount = mTextures.size();
}

void AnimSpriteComponent::Tick(float deltaTime)
{
	if (mTexturesAmount > 0)
	{
		mCurrentFrame += mAnimFps * deltaTime;

		if (mCurrentFrame >= mTexturesAmount)
		{
			mCurrentFrame -= mTexturesAmount;
		}

		SetTexture(mTextures[static_cast<int>(mCurrentFrame)]);
	}
}

void AnimSpriteComponent::BeginPlay()
{
	SpriteComponent::BeginPlay();
}
