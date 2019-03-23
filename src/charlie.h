#include "fish.h"
#include "main.h"
class Charlie
{
  public:
      int pos_x=0;
      int pos_y=0;

      Charlie();
      ~Charlie();

      bool bonus1=0;
      bool hide=false;
      void control_bigger_fish();
      void double_smaller_fish();

      bool bonus2=0;
      void speed_less();

      bool punish=0;
      void stop_charlie();




  protected:

  private:
      int choice;
      int size=2;
      bool life;
};
