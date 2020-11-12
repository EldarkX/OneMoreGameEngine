#include "Modules/CoreModule/InputManager.h"

#include "Modules/ObjectModule/Object/Components/InputComponent.h"

void    InputManager::HandleInput(const SDL_Event *event)
{
	for (auto Input : mInputComponents)
	{
		Input->ProccessInput(event);
	}
}

void InputManager::AddInputComponent(class InputComponent *Input)
{
	mInputComponents.push_back(Input);
}

void InputManager::RemoveInputComponent(class InputComponent* Input)
{
	mInputComponents.erase(find(mInputComponents.cbegin(), mInputComponents.cend(), Input));
}
