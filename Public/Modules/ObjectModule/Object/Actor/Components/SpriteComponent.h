#pragma once

#include "Modules/ObjectModule/Object/Components/BaseComponent.h"

class SpriteComponent : public BaseComponent
{
	friend class	RenderManager;

public:

	SpriteComponent(class Actor* Owner) : BaseComponent(Owner) {};

	virtual void	BeginPlay() override;

	void			Tick(float deltaTime) override;

	SDL_Texture		*GetTexture() const { return mTexture; }
	void			SetTexture(SDL_Texture* newTexture) { mTexture = newTexture; }
	
	int				GetDrawOrder() const { return mDrawOrder; }
	void			SetDrawOrder(int newDrawOrder) { mDrawOrder = newDrawOrder; }


	virtual void	Destroy() override;

private:

	virtual void	Draw(SDL_Renderer* Renderer);

	SDL_Texture		*mTexture = nullptr;

	int				mDrawOrder = 100;

};