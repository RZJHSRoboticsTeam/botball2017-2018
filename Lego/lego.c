#include <kipr/botball.h>
#include <math.h>


void code()
{
msleep(20000);

motor(0,-50);
motor(1,-50);
msleep(750);
ao();//back up
motor(0,-25);
motor(1,25);
msleep(750);
ao();//turn around
motor(0,100);
motor(1,100);
msleep(3000);
ao();//go to crates
motor(1,10);
msleep(500);
ao();//align to crates
}

int main()
{
  waitForLight(1);
  code();
  return 0;
}
