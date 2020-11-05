#include "Modules/CoreModule/CollisionManager.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"
#include "Modules/MathModule/Vector2D.h"

void CollisionManager::AddAgent(class Actor* Agent)
{
	Agents.push_back(Agent);
}

void CollisionManager::AddActiveAgent(class Actor* ActiveAgent)
{
	ActiveAgents.push_back(ActiveAgent);
}

void CollisionManager::CheckAllCollisions()
{
	for (auto& ActiveAgent : ActiveAgents)
	{
		for (auto& Agent : Agents)
		{
			if (ActiveAgent == Agent)
				continue;

			Vector2D point;
			if (AreCollided(ActiveAgent, Agent, &point))
			{
				ActiveAgent->OnCollision(Agent, point);
				if (Agent)
					Agent->OnCollision(ActiveAgent, point);
			}
		}
	}
}

bool CollisionManager::AreCollided(Actor* Actor1, Actor* Actor2, Vector2D *point)
{
	Vector2D LeftUp1 = Actor1->GetActorPosition() - Actor1->GetActorSize();
	Vector2D RightBottom1 = Actor1->GetActorPosition() + Actor1->GetActorSize();
	Vector2D LeftUp2 = Actor2->GetActorPosition() - Actor2->GetActorSize();
	Vector2D RightBottom2 = Actor2->GetActorPosition() + Actor2->GetActorSize();

	return (LeftUp1.X() <= RightBottom2.X() && RightBottom1.X() >= LeftUp2.X() &&
		LeftUp1.Y() <= RightBottom2.Y() && RightBottom1.Y() >= LeftUp2.Y());
}

