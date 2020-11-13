#pragma once

#include "Modules/ObjectModule/Object/Components/BaseComponent.h"

class InputComponent : public BaseComponent
{

public:

	virtual void BeginPlay() override;

	virtual void ProccessInput(const SDL_Event* event);

	virtual void Destroy() override;

private:

};