#include "../inc/CollisionManager.h"

#include "../inc/object.h"
#include "../inc/Vector2D.h"

void CollisionManager::AddAgent(class Object* Agent)
{
	Agents.push_back(Agent);
}

void CollisionManager::AddActiveAgent(class Object* ActiveAgent)
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

bool CollisionManager::AreCollided(Object *Obj1, Object *Obj2, Vector2D *point)
{
	return (Obj1->GetLeftUpCorner().X() <= Obj2->GetRightBottomCorner().X() &&
		Obj1->GetRightBottomCorner().X() >= Obj2->GetLeftUpCorner().X() &&
		Obj1->GetLeftUpCorner().Y() <= Obj2->GetRightBottomCorner().Y() &&
		Obj1->GetRightBottomCorner().Y() >= Obj2->GetLeftUpCorner().Y());
}

