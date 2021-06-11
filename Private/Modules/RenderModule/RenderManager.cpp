
#include "Modules/RenderModule/RenderManager.h"

#include "Modules/RenderModule/VertexArray.h"
#include "Modules/RenderModule/Shader.h"

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"

RenderManager::RenderManager(GameEngine* gameEngine)
	: mGameEngine(gameEngine)
{
	mSpriteShader = new Shader();

	string ProjectDir = gameEngine->GetAssetsManagerUtils()->GetProjectDir();

	if (!mSpriteShader->Load(ProjectDir + R"(\Assets\Shaders\Sprite.vert)", ProjectDir + R"(\Assets\Shaders\Sprite.frag)"))
	{
		cout << "Shader hasn't been loaded!" << endl;
		exit(-1);
	}

	mSpriteShader->SetActive();

	float vertexBuffer[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f,
		0.5f, 0.5f, 0.f, 1.f, 0.f,
		0.5f, -0.5f, 0.f, 1.f, 1.f,
		-0.5f, -0.5f, 0.f, 0.f, 1.f
	};

	unsigned int indexBuffer[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertexBuffer, 4, indexBuffer, 6);
	mSpriteVerts->SetActive();

	Matrix4D viewProj = CreateSimpleViewProj(static_cast<float>(gameEngine->GetWindowWidth()),
		static_cast<float>(gameEngine->GetWindowHeight()));
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
}

void RenderManager::DrawBackBuffer()
{
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void RenderManager::DrawFrontBuffer()
{
	mSpriteShader->SetActive();
 	mSpriteVerts->SetActive();
	for (auto Drawable : mDrawableComponents)
	{
		Drawable->Draw(mSpriteShader);
	}
}

void RenderManager::SwitchBuffers()
{
	SDL_GL_SwapWindow(mGameEngine->GetWindow());
}

void RenderManager::AddDrawableComponent(class SpriteComponent *NewSprite)
{
	if (mDrawableComponents.empty())
	{
		mDrawableComponents.push_back(NewSprite);
	}
	else
	{
		for (auto iter = mDrawableComponents.cbegin(); iter < mDrawableComponents.cend(); ++iter)
		{
			if (NewSprite->GetDrawOrder() < (*iter)->GetDrawOrder())
			{
				mDrawableComponents.insert(iter, NewSprite);
				return;
			}
		}
		mDrawableComponents.push_back(NewSprite);
	}
}

void RenderManager::RemoveDrawableComponent(class SpriteComponent *Sprite)
{
	mDrawableComponents.erase(find(mDrawableComponents.cbegin(), mDrawableComponents.cend(), Sprite));
}

Matrix4D RenderManager::CreateSimpleViewProj(float width, float height)
{
	return Matrix4D({
		{ 2.0f / width, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 2.0f / height, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f }
	});
}

