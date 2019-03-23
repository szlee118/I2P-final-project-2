#include "main.h"
#include "GameWindow.h"

int main(int argc, char *argv[])
{
    GameWindow *Aqua_Dine= new GameWindow();
    try{
        Aqua_Dine->game_play();
    }
    catch(int e){
       1;
    }

    delete Aqua_Dine;
    return 0;
}
