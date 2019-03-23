#include "GameWindow.h"
#include "main.h"
#include <iostream>
#include <cmath>

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)

#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))

#define time_limit 3600
#define score_limit_1 10
#define score_limit_2 20
#define score_limit_3 35
#define score_limit_4 50

using namespace std;
int pause;
int click=0;
int posx,posy;
int mode;
int eaten=0;
int bonus=0;

void
GameWindow::game_init()
{
    bool done=false;

    int x=0;
    int y=500;

    const int maxFrame=15;
    int curFrame=-1;
    int curY=0;
    int frameCount=0;
    int frameDelay=5;
    float frameWidth=256;
    float frameHeight=249.333;

    char buffer[50];
    icon = al_load_bitmap("images/fish.png");
    al_set_display_icon(display, icon);
    c= al_load_bitmap("images/charlie_burned.png");


    image=al_load_bitmap("images/test.jpg");
    image0=al_load_bitmap("images/dark.jpg");
    image10=al_load_bitmap("images/fish6.jpg");
    al_convert_mask_to_alpha(image,al_map_rgb(106,776,48));
    al_convert_mask_to_alpha(image0,al_map_rgb(106,776,48));

    while(!done){
            al_wait_for_event(event_queue,&event);
            if(event.type==ALLEGRO_EVENT_TIMER){
                if(event.timer.source=timer){
                    if(++frameCount>=frameDelay)
                    {
                        frameCount=0;
                        if(curFrame>=4){
                                curFrame=0;
                                curY++;
                        }
                        else curFrame++;
                        if(curY>=3)curY=0;
                    }
                    if(x<600){x+=5;}
                    if(x>=600){x=0;y=500;}
                }
            }
            else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)throw 1;

            else if(event.type== ALLEGRO_EVENT_MOUSE_BUTTON_DOWN&&event.mouse.x>=0){
                cout<<"moving to main page"<<endl;
                if(event.mouse.x>=0&&event.mouse.x<=256&&event.mouse.y>=0&&event.mouse.y<=249.333){mode=1;break;}
                else if(event.mouse.x>=900-256&&event.mouse.x<=900&&event.mouse.y>=0&&event.mouse.y<=249.333){mode=2;level->level=1;break;}
            }

            al_draw_bitmap_region(image,curFrame*frameWidth,curY*frameHeight,frameWidth,frameHeight,0,0,0);
            al_draw_bitmap_region(image,curFrame*frameWidth,curY*frameHeight,frameWidth,frameHeight,900-frameWidth,0,0);
            al_draw_bitmap(image0,150,400,2);
            al_draw_text(font, al_map_rgb(0, 0, 0), 100, 300,0, "Timing mode");
            al_draw_text(font, al_map_rgb(0, 0, 0), 700, 300, 0, "Level mode");
            al_draw_text(font0, al_map_rgb(12,37,204),350,300,0,"AQUA DINE");


            al_flip_display();
            al_clear_to_color(al_map_rgb(255,255,255));
        }

    background=al_load_bitmap("images/tex_Water.jpg");
    al_draw_bitmap(background, 0, 0, 0);
    al_flip_display();

    al_reserve_samples(3);
    al_set_display_icon(display, icon);

    sample = al_load_sample("start.wav");
    startSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(startSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(startSound, al_get_default_mixer());

    if(mode==2)sample = al_load_sample("sounds/waterwater.ogg");
    else if(mode==1)sample =al_load_sample("sounds/mode1.ogg");
    backgroundSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());

    level = new LEVEL((mode==1)?0:1);
}

bool
GameWindow::mouse_hover(int startx, int starty, int width, int height)
{
    if(mouse_x >= startx && mouse_x <= startx + width)
        if(mouse_y >= starty && mouse_y <= starty + height)
            return true;

    return false;
}

void
GameWindow::game_play()
{
    int msg;

    srand(time(NULL));

    msg = -1;
    game_reset();
    game_begin();

     while(msg != GAME_EXIT)
     {
           msg = game_run();
     }

    show_err_msg(msg);
}

void
GameWindow::show_err_msg(int msg)
{
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);

    game_destroy();
    exit(9);
}

GameWindow::GameWindow()
{
    if (!al_init())
        show_err_msg(-1);

    printf("Game Initializing...\n");

    display = al_create_display(900, 800);
    timer = al_create_timer(1.0 / FPS);
    fish_pro = al_create_timer(1.0 / FPS);

    event_queue = al_create_event_queue();

    if(timer == NULL || fish_pro == NULL)
        show_err_msg(-1);

    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    font = al_load_ttf_font("fonts/Caviar_Dreams_Bold.ttf",12,0); // load small font
    Medium_font = al_load_ttf_font("fonts/Caviar_Dreams_Bold.ttf",24,0); //load medium font
    Large_font = al_load_ttf_font("fonts/Caviar_Dreams_Bold.ttf",36,0); //load large font
    font0=al_load_ttf_font("fonts/Fish.ttf",64,0);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(fish_pro));
    al_stop_timer(timer);
    al_start_timer(timer);
    cout<<"before init"<<endl;
    game_init();
    cout<<"after init"<<endl;
}

void
GameWindow::game_begin()
{
    printf(">>> Start Level[%d]\n", level->getLevel());
    draw_running_map();

    al_play_sample_instance(startSound);
    al_get_sample_instance_playing(startSound);
    al_play_sample_instance(backgroundSound);

    al_start_timer(timer);
    al_start_timer(fish_pro);
}

int
GameWindow::game_run()
{
    char buffer[50];

    int error = GAME_CONTINUE;

    if (!al_is_event_queue_empty(event_queue)) {

        error = process_event();
        if(mode==1&&Coin_Inc_Count>=time_limit||eaten==1){
                eaten=0;
                al_stop_timer(timer);
                al_clear_to_color(al_map_rgb(255,255,255));
                cout<<"score: "<<score<<endl;
                if(score>=score_limit_4&&level->level==4)sprintf(buffer,"YOU WIN !!!");
                else sprintf(buffer, "Your Score Is: %d", score);

                al_draw_text(Medium_font, al_map_rgb(0, 0, 0), 70, 300, 0, buffer);
                sprintf(buffer, "Your Level Is: %d",level->level);
                if(mode==2)al_draw_text(Medium_font, al_map_rgb(0, 0, 0), 70, 360, 0, buffer);
                al_draw_text(Medium_font, al_map_rgb(0, 0, 0), 70, 600, 0, "PRESS ENTER TO MAIN MENU");
                al_draw_bitmap(image10,300,100,0);
                al_flip_display();
                score=0;
                al_destroy_sample_instance(backgroundSound);
                while(1){
                    al_wait_for_event(event_queue,&event);
                    if(event.type==ALLEGRO_EVENT_KEY_DOWN){
                        if(event.keyboard.keycode==ALLEGRO_KEY_ENTER){

                            game_init();
                            game_reset();
                            game_begin();
                            break;
                        }
                    }
                }
        }
    }
    return error;
}

void
GameWindow::game_reset()
{
    // reset game and begin
    charlie->hide=false;
    lastClicked = -1;
    Coin_Inc_Count = 0;
    Fish_Pro_Count = 0;
    mute = false;
    redraw = false;
    time_begin=0;
    bonus=0;
    FishSet.clear();
    //BubbleSet.clear();

    // stop sample instance
    al_stop_sample_instance(backgroundSound);
    al_stop_sample_instance(startSound);

    // stop timer
    al_stop_timer(timer);
    al_stop_timer(fish_pro);
}

void
GameWindow::game_destroy()
{
    game_reset();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);

    al_destroy_timer(timer);
    al_destroy_timer(fish_pro);

    al_destroy_bitmap(icon);
    al_destroy_bitmap(background);

    al_destroy_sample(sample);
    al_destroy_sample_instance(startSound);
    al_destroy_sample_instance(backgroundSound);
}

int
GameWindow::process_event()
{
    int instruction = GAME_CONTINUE;
    // offset for pause window
    int offsetX = 600/2 - 200;
    int offsetY = 800/2 - 200;

    al_wait_for_event(event_queue, &event);
    redraw = false;

    if(event.type == ALLEGRO_EVENT_TIMER) {
        if(event.timer.source == timer) {
            redraw = true;
            Coin_Inc_Count = (Coin_Inc_Count + 1);
            int score_limit;
            switch(level->level)
            {
               case 1:score_limit=score_limit_1;break;
               case 2:score_limit=score_limit_2;break;
               case 3:score_limit=score_limit_3;break;
               case 4:score_limit=score_limit_4;break;
            }
            if(mode==2&&score>=score_limit)
            {
                //score=0;
                if(level->level==4){
                  eaten=1;
                  al_stop_timer(timer);
                  //return GAME_EXIT;
                }
                else {
                        charlie->hide=false;
                        level->setLevel(level->level+1);
                        c= al_load_bitmap("images/charlie_burned.png");
                         al_stop_sample_instance(backgroundSound);
                         al_stop_sample_instance(startSound);

                        game_reset();
                        game_begin();
                }
            }
        }
        else{
            if(Fish_Pro_Count == 0) {

                Fish *m = create_fish();

                if(m != NULL)FishSet.push_back(m);

            }
            Fish_Pro_Count = (Fish_Pro_Count + 1) % level->getMonsterSpeed();
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch(event.keyboard.keycode) {

            case ALLEGRO_KEY_P:
                /*TODO: handle pause event here*/
                cout<<"P"<<endl;
                pause=1;
                goto pause;
                break;
            case ALLEGRO_KEY_M:
                cout<<"M"<<endl;
                mute = !mute;
                if(mute)
                    al_stop_sample_instance(backgroundSound);
                else
                    al_play_sample_instance(backgroundSound);
                break;
            case ALLEGRO_KEY_RIGHT:
                cout<<"RIGHT"<<endl;
                al_set_sample_instance_gain(backgroundSound,float(110)/float(100));
                break;
            case ALLEGRO_KEY_LEFT:
                cout<<"LEFT"<<endl;
                al_set_sample_instance_gain(backgroundSound,float(90)/float(100));
                break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
        click=0;
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
        if(event.mouse.x<=600)charlie->pos_x=event.mouse.x-50;
        charlie->pos_y=event.mouse.y-37.5;

    }
    if(redraw) {
        // update each object in game
        pause=0;
        pause:
        while(pause){
            al_stop_sample_instance(backgroundSound);
            al_wait_for_event(event_queue,&event);
            if(event.type==ALLEGRO_EVENT_KEY_DOWN){
                if(event.keyboard.keycode==ALLEGRO_KEY_P){
                        if(!mute)al_play_sample_instance(backgroundSound);
                        break;
                }
            }
        }

         instruction = game_update();
         if(instruction==GAME_EXIT)return instruction;

        // Re-draw map
        draw_running_map();
        redraw = false;
    }
    return instruction;
}

void
GameWindow::draw_running_map()
{
    unsigned int i, j;

    al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_bitmap(background, 0, 0, 0);

    al_draw_filled_rectangle(700, 0, 900, 800, al_map_rgb(50, 50, 50));


    char buffer[50];

    sprintf(buffer, "Time: %d", Coin_Inc_Count/60);
    al_draw_text(Medium_font, al_map_rgb(255, 255, 255), 750, 20 + 30, 0, buffer);

    sprintf(buffer, "Score: %d", score);
    al_draw_text(Medium_font, al_map_rgb(255, 255, 255), 750, 20 + 2*30, 0, buffer);

    sprintf(buffer,"Level: %d",level->level);
    if(mode==1){
        al_draw_text(font0, WHITE,740,500,0,"Timing");
        al_draw_text(font0, WHITE,755,600,0,"Mode");
    }
    else if(mode==2){
        al_draw_text(font0, WHITE,710,500,0,buffer);
        al_draw_text(font0, WHITE,755,600,0,"Mode");
    }

    //stuffs with hiding 5 seconds
    if(charlie->hide==true&&time_begin==0){
            time_begin=Coin_Inc_Count/60;
            c= al_load_bitmap("images/charlie_hide.png");
            cout<<"hideen"<<endl;
    }
    if(charlie->hide==true&&(Coin_Inc_Count/60)-time_begin>3){
            cout<<"turing back"<<endl;
            charlie->hide=false;
            c= al_load_bitmap("images/charlie_burned.png");
            time_begin=0;
    }

    //stuffs with bubble||contorlling||
    if(bonus==1){
        1;
    }



    al_draw_bitmap(c,charlie->pos_x,charlie->pos_y,0);

    for(i=0; i<FishSet.size(); i++)
    {

        FishSet[i]->Draw();
    }

    al_flip_display();
}
int
GameWindow::game_update()
{
    unsigned int i, j;
    // update every fish
    // check if it is destroyed
    for(i=0; i < FishSet.size(); i++)
    {
         bool isDestroyed = false;

         if(abs(charlie->pos_x-FishSet[i]->pos_x)<40&&abs(charlie->pos_y-FishSet[i]->pos_y)<40){
                //collide with shark
                bonus=0;
                if(FishSet[i]->getScore()&&charlie->hide==false){
                        eaten=1;
                        isDestroyed=false;
                }
                //collide with shark,hidden
                else if(FishSet[i]->getScore()&&charlie->hide==true){
                       eaten=0;
                       isDestroyed=false;
                }
                //collide with yellow
                else if(FishSet[i]->getWorth()==2){
                    isDestroyed=true;
                    charlie->hide=true;
                }
                //collide with golden
                else if(FishSet[i]->getWorth()==3){
                    bonus=1;
                    isDestroyed=true;
                }
                else isDestroyed=true;
                score+=FishSet[i]->getWorth();
         }
         if(FishSet[i]->pos_x>=660||FishSet[i]->pos_x<0)isDestroyed=true;


        FishSet[i]->Move();

        if(isDestroyed)
        {

            Fish *m = FishSet[i];
            FishSet.erase(FishSet.begin() + i);
            i--;
            delete m;

        }
    }

    return GAME_CONTINUE;
}

Fish*
GameWindow::create_fish()
{
    Fish *m = NULL;

    m= new Fish(level->level);

    return m;
}
