#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"

void SpriteComponent::Tick(double deltaTime)
{
	if (mTexture)
		Draw();
}

void SpriteComponent::Draw()
{
	SDL_Renderer* Renderer = mOwner->GetGameEngine()->GetRenderer();

	SDL_Rect info;

	info.x = mOwner->GetActorPosition().X() - mOwner->GetActorSize().X() / 2;
	info.y = mOwner->GetActorPosition().Y() - mOwner->GetActorSize().Y() / 2;
	info.w = mOwner->GetActorSize().X();
	info.h = mOwner->GetActorSize().Y();

	SDL_RenderCopy(Renderer, mTexture, NULL, &info);
}