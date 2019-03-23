#ifndef _MAIN_H_
#define _MAIN_H_


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <vector>


#define grid_width 40
#define grid_height 40

#define window_width 900
#define window_height 800
#define field_width 700
#define field_height 800

#define Num_FishType 5
#define NumOfGrid (field_width / grid_width) * (field_height / grid_height)

#endif // _MAIN_H_
