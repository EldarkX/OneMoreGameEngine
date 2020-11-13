
#include "Modules/ObjectModule/Object/Components/InputComponent.h"

#include "Modules/CoreModule/InputManager.h"
#include "Modules/ObjectModule/Object/Actor/Actor.h"

void InputComponent::BeginPlay()
{
	mOwner->GetGameEngine()->GetInputManager()->AddInputComponent(this);
}

void InputComponent::ProccessInput(const SDL_Event* event)
{
	if (event->type == SDL_QUIT || event->key.keysym.sym == SDL_KeyCode::SDLK_ESCAPE)
	{
		mOwner->GetGameEngine()->SetGameStatus(EGameStatus::GSE_Exit);
	}
}

void InputComponent::Destroy()
{
	mOwner->GetGameEngine()->GetInputManager()->RemoveInputComponent(this);

	BaseComponent::Destroy();
}


