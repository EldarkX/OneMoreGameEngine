#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"
#include "Modules/CoreModule/RenderManager.h"

void SpriteComponent::Tick(float deltaTime)
{

}

void SpriteComponent::Destroy()
{
	GetOwner()->GetGameEngine()->GetRenderManager()->RemoveDrawableComponent(this);

	BaseComponent::Destroy();
}

void SpriteComponent::BeginPlay()
{
	GetOwner()->GetGameEngine()->GetRenderManager()->AddDrawableComponent(this);
}

void SpriteComponent::Draw(SDL_Renderer* Renderer)
{
	SDL_Rect info;

	info.x = static_cast<int>(mOwner->GetActorPosition().X() - mOwner->GetActorSize().X() / 2.f);
	info.y = static_cast<int>(mOwner->GetActorPosition().Y() - mOwner->GetActorSize().Y() / 2.f);
	info.w = static_cast<int>(mOwner->GetActorSize().X());
	info.h = static_cast<int>(mOwner->GetActorSize().Y());

	SDL_RenderCopy(Renderer, mTexture, NULL, &info);
}