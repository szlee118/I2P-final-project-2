#ifndef _GAMEWINDOW_H_
#define _GAMEWINDOW_H_
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include <list>
#include <time.h>
#include "fish.h"
#include "charlie.h"
#include "Level.h"

#define GAME_INIT -1
#define GAME_SETTING 0
#define GAME_SELECT 1
#define GAME_BEGIN 2
#define GAME_CONTINUE 3
#define GAME_FAIL 4
#define GAME_TERMINATE 5
#define GAME_NEXT_LEVEL 6
#define GAME_EXIT 7

// clock rate
const float FPS = 60;
// total number of level
const int LevelNum = 4;

class GameWindow
{
public:
    // constructor
    GameWindow();
    // each process of scene
    void game_init();
    void game_reset();
    void game_play();
    void game_begin();

    int game_run();
    int game_update();

    void show_err_msg(int msg);
    void game_destroy();

    // each drawing scene function
    void draw_running_map();

    // process of updated event
    int process_event();
    // detect if mouse hovers over a rectangle
    bool mouse_hover(int, int, int, int);

private:

    ALLEGRO_BITMAP *icon;
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_BITMAP *image=NULL;
    ALLEGRO_BITMAP *image0=NULL;
    ALLEGRO_BITMAP *image1=NULL;
    ALLEGRO_BITMAP *image2=NULL;
    ALLEGRO_BITMAP *image3=NULL;
    ALLEGRO_BITMAP *image4=NULL;
    ALLEGRO_BITMAP *image5=NULL;
    ALLEGRO_BITMAP *image6=NULL;
    ALLEGRO_BITMAP *image7=NULL;
    ALLEGRO_BITMAP *image8=NULL;
    ALLEGRO_BITMAP *image9=NULL;
    ALLEGRO_BITMAP *image10=NULL;
    ALLEGRO_BITMAP *c=NULL;

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *Medium_font = NULL;
    ALLEGRO_FONT *Large_font = NULL;
    ALLEGRO_FONT *font0 = NULL;


    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *fish_pro = NULL;

    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *startSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *clearSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *failSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *backgroundSound = NULL;

    int Fish_Pro_Count = 0;
    int Coin_Inc_Count = 0;
    int mouse_x, mouse_y;
    int lastClicked = -1;
    int score=0;
    int time_begin=0;

    //LEVEL *level = NULL;
    LEVEL*level = new LEVEL(1);
    Charlie*charlie=new Charlie();
    std::vector<Fish*>FishSet;
    //std::vector<Bubble*>BubbleSet;

    bool redraw = false;
    bool mute = false;

    Fish* create_fish();
};

#endif // _GAMEWINDOW_H_

