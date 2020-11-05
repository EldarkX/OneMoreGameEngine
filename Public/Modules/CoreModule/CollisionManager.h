#pragma once

#include "GameEngine.h"

class CollisionManager
{
    public:

        void AddAgent(class Actor *Agent);
        void AddActiveAgent(class Actor *ActiveAgent);

        void CheckAllCollisions();

    private:

		bool AreCollided(Actor *Obj1, Actor *Obj2, class Vector2D*point);

        vector<Actor *> Agents;
        vector<Actor *> ActiveAgents;
};

