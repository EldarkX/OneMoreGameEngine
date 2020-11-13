#pragma once

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"

class AnimSpriteComponent : public SpriteComponent
{

public:

	vector<SDL_Texture*>			GetTextures() const { return mTextures; }
	void							SetTextures(const vector<SDL_Texture*>& Textures)
	{
		mTextures.clear();
		for (SDL_Texture* texture : Textures)
		{
			mTextures.push_back(texture);
		}
		mTexturesAmount = mTextures.size();
	}
	
	int								GetAnimFPS() const { return mAnimFps; }
	void							SetAnimFPS(int AnimFPS) { mAnimFps = AnimFPS; }

	virtual void					Tick(float deltaTime) override;

protected:

	vector<SDL_Texture*>			mTextures;
	float							mCurrentFrame = 0;
	unsigned int					mAnimFps = 24;

	size_t							mTexturesAmount = 0;

};