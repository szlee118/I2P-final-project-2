#include "fish.h"
#include "main.h"
#include "GameWindow.h"
#include<iostream>
using namespace std;

const int axis_x[] = {-1, 1, 0, 0};
const int axis_y[] = {0, 0, -1, 1};
const char direction_name[][10] = {"LEFT", "RIGHT", "UP", "DOWN"};
int curX=0,curY=0;//of sharks or tuna;

Fish::Fish(int level)
{

    if (direction==LEFT)pos_x=600;
    // default direction is right
    direction = RIGHT;
    direction_count[LEFT] = 1;
    direction_count[RIGHT] = 1;
    direction_count[UP] = 1;
    direction_count[DOWN] = 1;

    Load_Move(level);
}

Fish::~Fish()
{

    for(unsigned int i=0; i<moveImg.size(); i++)
    {
        ALLEGRO_BITMAP *img = moveImg[i];

        moveImg.erase(moveImg.begin() + i);

        i--;
        al_destroy_bitmap(img);
    }
    moveImg.clear();
}

void
Fish::Load_Move(int level)
{
    char buffer[50];

    ALLEGRO_BITMAP *img;
    sprintf(buffer, "./fish1.png");
    int ran=rand()%10;
    if(ran==0||ran==3||ran==6||ran==7){
            img = al_load_bitmap("oo.png");
            pos_x=0;
            worth=1;
    }
    else if(ran==1&&level!=1){
            img = al_load_bitmap("yy.png");
            pos_x=0;
            speed=4;
            worth=2;
    }
    else if(ran==1&&(level==1)){
            img = al_load_bitmap("oo.png");
            pos_x=0;
            worth=1;
    }
    else if(ran==2){
            img = al_load_bitmap("shark.png");
            pos_x=0;
            speed=15;
            worth=0;
            score=1;
    }
    else if(ran==4&&level!=1){
            direction=LEFT;
            pos_x=600;
            img = al_load_bitmap("yy_left.png");
            speed=4;
            worth=2;
    }
    else if(ran==4&&level==1){
            img = al_load_bitmap("oo.png");
            pos_x=0;
            worth=1;
    }
    else if(ran==5){
            direction=LEFT;
            img = al_load_bitmap("shark.png");
            pos_x=600;
            speed=15;
            worth=0;
            score=1;
        }
    else if(ran==9&&level>=3){
           img=al_load_bitmap("golden.png");
           pos_x=0;
           speed=10;
           worth=3;
    }
    else{
         if(level<=2&&level!=0){img = al_load_bitmap("oo.png");worth=1;}
         if(level>2||level==0){img=al_load_bitmap("shark.png");worth=0;score=1;speed=15;}
         pos_x=0;
    }
    if(img)moveImg.push_back(img);
}

void
Fish::Draw()
{
    //int w, h;
    int offset = 0;
    float frameWidth=84.25*2;
    float frameHeight=45.728*2;
    // calculate the number of pictures before current direction

    if(!moveImg[0])
        return;

    // draw bitmap align grid edge
    if(worth!=0)al_draw_bitmap(moveImg[0], pos_x, pos_y, 0);
    else  {
            al_draw_bitmap_region(moveImg[0],0,(direction==LEFT)?frameHeight+20:20,frameWidth,frameHeight,pos_x,pos_y,0);
            //curY=(curX==4)?((curY<11)?curY+1:0):curY;
            //curX=(curX<4)?curX+1:0;
    }
}

bool
Fish::Move()
{

    pos_x += (rand()%10) * axis_x[direction];
    pos_y += (rand()%10) * axis_y[direction];

    return false;

}
