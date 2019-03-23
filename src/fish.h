#ifndef FISH_H_INCLUDED
#define FISH_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>

enum {LEFT=0, RIGHT, UP, DOWN};
class Fish
{
    public:
    Fish(int level);
    ~Fish();

    // Draw image per frame
    // override virtual function "Object::Draw"
    void Draw();
    // Load bitmaps of animation image into container "moveImg"
    void Load_Move(int);

    // Update fish position per frame
    // And detect if it reaches end point but not destroyed
    bool Move();

    // functions that return informations of fishes
    int getDir() { return direction; }
    int getWorth() { return worth; }
    int getScore() { return score; }

    int pos_x=0, pos_y=rand()%700;

    protected:
    int direction_count[4];
    int speed = 2;
    int worth = 0;
    int score = 0;
    char class_name[20];

    private:
    // direction and index for "path"
    unsigned int step;
    int direction;
    // animation counter
    int counter;
    // animation image of current direction
    int sprite_pos;

    // set of animation images
    std::vector<ALLEGRO_BITMAP*> moveImg;
    // path on map
    std::vector<int> path;

};


#endif // FISH_H_INCLUDED
