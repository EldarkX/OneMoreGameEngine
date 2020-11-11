#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"

void SpriteComponent::Tick(float deltaTime)
{
	if (mTexture)
		Draw();
}

void SpriteComponent::Draw()
{
	SDL_Renderer* Renderer = mOwner->GetGameEngine()->GetRenderer();

	SDL_Rect info;

	info.x = static_cast<int>(mOwner->GetActorPosition().X() - mOwner->GetActorSize().X() / 2.f);
	info.y = static_cast<int>(mOwner->GetActorPosition().Y() - mOwner->GetActorSize().Y() / 2.f);
	info.w = static_cast<int>(mOwner->GetActorSize().X());
	info.h = static_cast<int>(mOwner->GetActorSize().Y());

	SDL_RenderCopy(Renderer, mTexture, NULL, &info);
}