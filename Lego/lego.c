#include <kipr/botball.h>
#include <math.h>

typedef enum { false, true } bool;
int clawOpen = 100;
int clawBGClosed = 850;
int clawCrateClosed = 550;
int gateOpen = 100;
int gateClosed = 1200;
unsigned int gatePort = 1;
unsigned int clawPort = 2;

void openGate()
{
  set_servo_position(gatePort,gateOpen);
}

void closeGate()
{
  set_servo_position(gatePort,gateClosed);
}

void openClaw()
{
  set_servo_position(clawPort,clawOpen);
}

void closeClaw(bool botGuy)
{
  int distance = clawCrateClosed;
  if(botGuy) distance = clawBGClosed
  set_servo_position(clawPort,distance);
}

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
ao();//align to crate
openClaw();
closeClaw(false);
openGate();
closeGate();

}

int main()
{
  waitForLight(0);
  code();
  return 0;
}
