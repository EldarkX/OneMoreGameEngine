#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"
#include "Modules/RenderModule/RenderManager.h"

#include "Modules/RenderModule/Shader.h"
#include "Modules/RenderModule/Texture.h"

void SpriteComponent::Destroy()
{
	GetOwner()->GetGameEngine()->GetRenderManager()->RemoveDrawableComponent(this);

	BaseComponent::Destroy();
}

void SpriteComponent::BeginPlay()
{
	GetOwner()->GetGameEngine()->GetRenderManager()->AddDrawableComponent(this);
}

void SpriteComponent::SetTexture(Texture* newTexture)
{
	mTexture = newTexture;
}

void SpriteComponent::Draw(Shader* shader)
{
	Matrix4D scale = Matrix4D::OneMatrix();
	scale[0][0] = static_cast<float>(60);
	scale[1][1] = static_cast<float>(60);

	if (mTexture)
		mTexture->SetActive();

	Matrix4D world = scale * mOwner->GetActorTransform()->GetComputedTransform();

	shader->SetMatrixUniform("uWorldTransform", world);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
