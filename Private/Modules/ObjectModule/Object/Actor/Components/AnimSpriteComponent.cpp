
#include "Modules/ObjectModule/Object/Actor/Components/AnimSpriteComponent.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"

void AnimSpriteComponent::PlayAnimation(string name, float playRate)
{
	if (mAnimations.count(name))
	{
		const Animation* AnimToSet = mAnimations[name];
		if (!mCurrentAnimation.second ||
			(AnimToSet != mCurrentAnimation.second && AnimToSet->mPriority > mCurrentAnimation.second->mPriority))
		{
			mCurrentAnimation.first = name;
			mCurrentAnimation.second = AnimToSet;
			mCurrentAnimFps = mCurrentAnimation.second->mAnimFps * playRate;

			mCurrentFrame = 0;

			OnAnimationStartPlay(name);
		}
	}
}

void AnimSpriteComponent::Tick(float deltaTime)
{
	if (mCurrentAnimation.second)
	{
		mCurrentFrame += mCurrentAnimFps * deltaTime;

		if (mCurrentFrame >= mCurrentAnimation.second->mTexturesAmount)
		{
			if (mCurrentAnimation.second->mIsLooping)
			{
				mCurrentFrame -= mCurrentAnimation.second->mTexturesAmount;
			}
			else
			{
				OnAnimationEndPlay(mCurrentAnimation.first);
				mCurrentAnimation.second = nullptr;
				PlayAnimation(mBaseAnimation);			
			}
		}

		SetTexture(mCurrentAnimation.second->mTextures[static_cast<int>(mCurrentFrame)]);
	}
}

void AnimSpriteComponent::AddAnimation(string name, string path, unsigned int framesAmount,
	unsigned int animFPS /*= 24*/, unsigned int priority /*= 0*/, bool isLooping /*= false*/)
{
	string zero;
	string new_path;

	Animation* newAnim = new Animation(animFPS, priority, isLooping);

	for (unsigned int i = 1; i <= framesAmount; ++i)
	{
		zero = i < 10 ? "0" : "";
		new_path = path + zero + std::to_string(i) + ".png";
		newAnim->mTextures.push_back(IMG_LoadTexture(GetOwner()->GetGameEngine()->GetRenderer(), new_path.c_str()));
	}

	newAnim->mTexturesAmount = newAnim->mTextures.size();

	mAnimations[name] = newAnim;
}

void AnimSpriteComponent::SetBaseAnimation(string name)
{
	if (!mAnimations.count(name))
	{
		cout << "Error: can't set base animation" << endl;
		exit(-1);
	}

	mBaseAnimation = name;

	mCurrentAnimation.first = name;
	mCurrentAnimation.second = mAnimations[mBaseAnimation];
}

void AnimSpriteComponent::BeginPlay()
{
	SpriteComponent::BeginPlay();
}
