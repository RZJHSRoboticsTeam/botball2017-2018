#include <kipr/botball.h>

int main()
{
  set_servo_position(1,1250);
  set_servo_position(0,400);
  enable_servos();
  motor(0,50);
  motor(1,50);
  msleep(700);
  ao();
  set_servo_position(1,750);
  set_servo_position(0,1310);
  msleep(1000);
  motor(1,50);
  motor(0,-50);
  msleep(1000);
  motor(0,30);
  motor(1,30);
  msleep(1000);
  motor(1,-50);
  motor(0,50);
  msleep(1000);
  motor(0,50);
  motor(1,50);
  msleep(2500);
  printf("Point1\n");

  set_servo_position(1,1000);
printf("point2\n");

set_servo_position(1,750);
set_servo_position(0,1314);
motor(0,-50);
motor(1,-50);
msleep(2500);
printf("Point3");
motor(0,-50);
motor(1,50);
msleep(500);
motor(0,50);
motor(1,50);
msleep(2500);
motor(0,50);
motor(1,-50);
msleep(500);
motor(0,50);
motor(1,50);
msleep(4850);
set_servo_position(1,1500);
msleep(500);
set_servo_position(0,500);
ao();

  return 0;
}
