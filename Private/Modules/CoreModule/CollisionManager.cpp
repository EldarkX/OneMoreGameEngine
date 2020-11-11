#include "Modules/CoreModule/CollisionManager.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"

#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"

#include "Modules/MathModule/Vector2D.h"

void CollisionManager::AddAgent(class CollisionComponent* Agent)
{
	Agents.push_back(Agent);
}


void CollisionManager::RemoveAgent(class CollisionComponent* Agent)
{
	Agents.erase(find(Agents.cbegin(), Agents.cend(), Agent));
}

void CollisionManager::CheckAllCollisions()
{
	for (size_t AgentIndex = 0, AgentsAmount = Agents.size(); AgentIndex < AgentsAmount - 1; ++AgentIndex)
	{
		if (!Agents[AgentIndex]->GetOwner()->GetIsPendingToKill())
		{
			for (size_t AgentToCheckIndex = AgentIndex + 1; AgentToCheckIndex < AgentsAmount; ++AgentToCheckIndex)
			{
				if (!Agents[AgentToCheckIndex]->GetOwner()->GetIsPendingToKill())
				{
					if (AreCollided(Agents[AgentIndex], Agents[AgentToCheckIndex]))
					{
						Agents[AgentIndex]->TriggerCollision(Agents[AgentToCheckIndex]->GetOwner(), Agents[AgentToCheckIndex]);
						Agents[AgentToCheckIndex]->TriggerCollision(Agents[AgentIndex]->GetOwner(), Agents[AgentIndex]);
					}
				}
			}
		}	
	}
}

bool CollisionManager::AreCollided(CollisionComponent* Agent1, CollisionComponent* Agent2)
{
	Vector2D LeftUp1 = Agent1->GetOwner()->GetActorPosition() - Agent1->GetOwner()->GetActorSize() / 2.;
	Vector2D RightBottom1 = Agent1->GetOwner()->GetActorPosition() + Agent1->GetOwner()->GetActorSize() / 2.;
	Vector2D LeftUp2 = Agent2->GetOwner()->GetActorPosition() - Agent2->GetOwner()->GetActorSize() / 2.;
	Vector2D RightBottom2 = Agent2->GetOwner()->GetActorPosition() + Agent2->GetOwner()->GetActorSize() / 2.;
	
	if (LeftUp1.X() <= RightBottom2.X() && RightBottom1.X() >= LeftUp2.X() &&
		LeftUp1.Y() <= RightBottom2.Y() && RightBottom1.Y() >= LeftUp2.Y())
	{
		return true;
	}
	return false;
}

