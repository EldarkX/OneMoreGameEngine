#include "Modules/CoreModule/CollisionManager.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"
#include "Modules/MathModule/Vector2D.h"

void CollisionManager::AddAgent(class Actor* Agent)
{
	Agents.push_back(Agent);
}


void CollisionManager::RemoveAgent(class Actor* Agent)
{
	Agents.erase(find(Agents.cbegin(), Agents.cend(), Agent));
}

void CollisionManager::CheckAllCollisions()
{
	for (auto& ActiveAgent : Agents)
	{
		if (ActiveAgent->GetIsPendingToKill())
			continue;

		for (auto& Agent : Agents)
		{
			if (ActiveAgent == Agent || Agent->GetIsPendingToKill())
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
	Vector2D LeftUp1 = Actor1->GetActorPosition() - Actor1->GetActorSize() / 2;
	Vector2D RightBottom1 = Actor1->GetActorPosition() + Actor1->GetActorSize() / 2;
	Vector2D LeftUp2 = Actor2->GetActorPosition() - Actor2->GetActorSize() / 2;
	Vector2D RightBottom2 = Actor2->GetActorPosition() + Actor2->GetActorSize() / 2;

	if (LeftUp1.X() <= RightBottom2.X() && RightBottom1.X() >= LeftUp2.X() &&
		LeftUp1.Y() <= RightBottom2.Y() && RightBottom1.Y() >= LeftUp2.Y())
	{
		//*point = (Actor1->GetActorPosition() + Actor2->GetActorPosition()) / 2; //wrong calc
		return true;
	}
	return false;
}

