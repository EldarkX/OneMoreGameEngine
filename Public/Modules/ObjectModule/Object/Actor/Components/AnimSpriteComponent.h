#pragma once

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"

#include <map>

using std::map;
using std::pair;

class AnimSpriteComponent : public SpriteComponent
{

public:

	struct Animation
	{
		Animation(unsigned int animFPS, unsigned int priority, bool isLooping)
			: mAnimFps(animFPS), mPriority(priority), mIsLooping(isLooping) {};

		unsigned int					mAnimFps = 24;
		unsigned int					mPriority = 0;	
		vector<SDL_Texture*>			mTextures;
		size_t							mTexturesAmount = 0;
		bool							mIsLooping = true;
	};

	//vector<SDL_Texture*>			GetCurrentAnimation() const { return mTextures; }
	//void							SetAnimation(const vector<SDL_Texture*>& Textures);
	//
	//int								GetAnimFPS() const { return mAnimFps; }
	//void							SetAnimFPS(int AnimFPS) { mAnimFps = AnimFPS; }

	virtual void					Tick(float deltaTime) override;

	void							AddAnimation(string name, string path, unsigned int framesAmount, unsigned int animFPS = 24,
										unsigned int priority = 0, bool isLooping = false);

	void							SetBaseAnimation(string name);

	void							PlayAnimation(string name, float playRate = 1.f);

	MulticastDelegate1<string>		OnAnimationStartPlay;
	MulticastDelegate1<string>		OnAnimationEndPlay;

	virtual void					BeginPlay() override;

protected:

	map<string, const Animation *>	mAnimations;
	
	pair<string, const Animation *> mCurrentAnimation;
	string							mBaseAnimation;

	float							mCurrentAnimFps;
	float							mCurrentFrame = 0;
};