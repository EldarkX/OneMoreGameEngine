#pragma once

#include "Modules/ObjectModule/Object/Components/BaseComponent.h"

class SpriteComponent : public BaseComponent
{

public:

	void			Tick(float deltaTime) override;

	SDL_Texture		*GetTexture() const { return mTexture; }
	void			SetTexture(SDL_Texture* newTexture) { mTexture = newTexture; }

private:

	virtual void	Draw();

	SDL_Texture		*mTexture = nullptr;

};