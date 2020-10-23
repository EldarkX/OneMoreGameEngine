#pragma once

#include "arcanoid.h"

enum class ECollisionType
{
    CTE_Wall,
    CTE_Block,
    CTE_Player,
    CTE_Ball
};

class CollisionManager
{
    public:

        void AddAgent(class Object *Agent);
        void AddActiveAgent(class Object *ActiveAgent);

        void CheckAllCollisions();

    private:

		bool AreCollided(Object *Obj1, Object *Obj2, class Vec2D*point);

        vector<Object *> Agents;
        vector<Object *> ActiveAgents;
};

