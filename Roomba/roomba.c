#include <kipr/botball.h>
#include <math.h>
typedef int bool;
#define true 1
#define false 0
double pos[] = {0,0,0};
double PI = 3.141592;
void move(double distance, double speed)
{
  create_drive_direct(speed,speed);
  msleep(distance/speed);
  create_stop();
  pos[0] += cos(pos[2]*PI)*distance;
  pos[1] += sin(pos[2]*PI)*distance;
}
void turn(double radians)//the radians variable is the radians divided by PI
{
  set_create_total_angle(radians*180);
  pos[2] += radians;
}
bool getButtonState(int buttonId)
{
  printf("%i",digital(buttonId));
  return false;
}
void turnTo(double radians)//the radians variable is the radians divided by PI
{
  turn(radians-pos[2]);
  pos[2] = radians;
}
void moveTo(double x, double y, double speed)
{
  turnTo(atan2(y-pos[1],x-pos[0]));
  double distX = x-pos[0];
  double distY = y-pos[1];
  move(sqrt(distX*distX+distY*distY),speed);
  pos[0] = x;
  pos[1] = y;
}
void resetPos()
{
  pos[0] = 0;
  pos[1] = 0;
  pos[2] = 0;
}
void setPos(double m[])
{
  pos[0] = m[0];
  pos[1] = m[1];
  pos[2] = m[2];
}
/*double[] getPos()
{
  return pos;
}*/
int main()
{
  create_connect();
  move(10,1);
  create_disconnect();
  return 0;
}