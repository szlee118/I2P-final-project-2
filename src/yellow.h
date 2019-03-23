#ifndef CLAW_H_INCLUDED
#define CLAW_H_INCLUDED

#include "fish.h"

class Yellow : public Fish
{
public:
    Wolf(std::vector<int> path) : Fish(path)
    {
        direction_count[LEFT] = 5;
        direction_count[RIGHT] = 5;
        direction_count[UP] = 4;
        direction_count[DOWN] = 4;

        HealthPoint = 20;
        speed = 1;
        worth = 5;
        score = 50;

        strncpy(class_name, "Wolf", 20);

        Load_Move();
    }

};


#endif // CLAW_H_INCLUDED
