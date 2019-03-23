#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include "main.h"

typedef struct Node {
    int h, g, f;
    bool roadPoint;
}Node;

class LEVEL {
public:
    LEVEL(const int);
    ~LEVEL();
    int level=1;
    int bonus=0;
    void setLevel(const int);
    bool isRoad(int index) { return levelMap[index].roadPoint; }
    int getMonsterSpeed() {
         if(level==1)return FishSpeed;
         else if(level==2)return FishSpeed/2;
         else if(level==3) return FishSpeed/4;
         else if(level==4) return FishSpeed/5;
         else if(level==0) return FishSpeed/4;
    }
    int getLevel() { return level; }
    //void search_destination();
    std::vector<int> ReturnPath() { return road_grid; }

    int FishNum[Num_FishType];

private:
    Node levelMap[NumOfGrid];
    std::vector<int> road_grid;
    // current level number
    //int level = 1;
    // maximum number of monster of a level
    int Fish_MAX = 10;
    // frequency of producing  monster
    int FishSpeed = 80;
};


#endif // LEVEL_H_INCLUDED
