#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"
#include "Modules/RenderModule/RenderManager.h"

#include "Modules/RenderModule/Shader.h"

void SpriteComponent::Destroy()
{
	GetOwner()->GetGameEngine()->GetRenderManager()->RemoveDrawableComponent(this);

	BaseComponent::Destroy();
}

void SpriteComponent::BeginPlay()
{
	GetOwner()->GetGameEngine()->GetRenderManager()->AddDrawableComponent(this);
}

void SpriteComponent::Draw(Shader* shader)
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
