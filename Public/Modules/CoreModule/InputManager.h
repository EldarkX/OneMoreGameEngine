#pragma once

#include "Modules/CoreModule/GameEngine.h"

class InputManager
{

public:

	void    HandleInput(const SDL_Event* event);

	void	AddInputComponent(class InputComponent*);
	void	RemoveInputComponent(class InputComponent*);

private:

	vector<class InputComponent*> mInputComponents;

};

