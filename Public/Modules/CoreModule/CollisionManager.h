#pragma once

#include "GameEngine.h"

class CollisionManager
{
    public:

        void AddAgent(class CollisionComponent *Agent);
		void RemoveAgent(class CollisionComponent *Agent);

        void CheckAllCollisions();

    private:

		bool AreCollided(class CollisionComponent *Agent1, class CollisionComponent *Agent2);

        vector<class CollisionComponent*> Agents;
};

