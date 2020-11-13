
#include "Modules/ObjectModule/Object/Actor/Components/AnimSpriteComponent.h"

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