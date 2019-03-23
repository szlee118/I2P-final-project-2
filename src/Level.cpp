#include "Level.h"
#include<iostream>
using namespace std;

LEVEL::LEVEL(const int level) {
    char buffer[50];
    this->level=level;
}

LEVEL::~LEVEL()
{
    for(int i=0;i < NumOfGrid;i++)
    {
        levelMap[i].roadPoint = false;
    }
}

void
LEVEL::setLevel(const int level)
{
    this->level = level;
}
