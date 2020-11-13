#pragma once

#include "Modules/ObjectModule/Object/Components/BaseComponent.h"

class SpriteComponent : public BaseComponent
{
	friend class	RenderManager;

public:

	virtual void	BeginPlay() override;

	SDL_Texture		*GetTexture() const { return mTexture; }
	void			SetTexture(SDL_Texture* newTexture) { mTexture = newTexture; }
	
	int				GetDrawOrder() const { return mDrawOrder; }
	void			SetDrawOrder(int newDrawOrder) { mDrawOrder = newDrawOrder; }


	virtual void	Destroy() override;

protected:

	virtual void	Draw(SDL_Renderer* Renderer);

	int				mDrawOrder = 100;

	SDL_Texture		*mTexture = nullptr;

};