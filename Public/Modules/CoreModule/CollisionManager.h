#pragma once

#include "GameEngine.h"

class CollisionManager
{
    public:

        void AddAgent(class Actor *Agent);
		void RemoveAgent(class Actor* Agent);

        void CheckAllCollisions();

    private:

		bool AreCollided(Actor *Actor1, Actor *Actor2, class Vector2D*point);

        vector<Actor *> Agents;
};

