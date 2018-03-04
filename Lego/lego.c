#include <kipr/botball.h>
#include <math.h>
unsigned int motorPorts[] = {0,1};
unsigned int servoPort = 0;
double pos[] = {0,0,0};
double PI = 3.141592;

void move(double distance, double speed)
{
  for(unsigned int i = 0;i<motorPorts.length;i++) motor(motorPorts[i], speed);
  msleep(distance*1000/speed);
  ao();
  pos[0] += cos(pos[2]*PI)*distance;
  pos[1] += sin(pos[2]*PI)*distance;
}

double kt = 1;

void turn(double radians, double speed)//the radians variable is the radians divided by PI
{
  if(radians<0) {
    radians *= -1;
    speed *= -1;
  };
  motor(motorPorts[0], radians * speed * kt);
  motor(motorPorts[1], radians * speed * kt);
  msleep(radians*1000/speed);
  ao();
  pos[2] += radians;
}

void turnTo(double radians, double speed)//the radians variable is the radians divided by PI
{
  turn(radians-pos[2],speed);
  pos[2] = radians;
}

void moveTo(double x, double y, double speed)
{
  turnTo(atan2(y-pos[1],x-pos[0])/PI,100);
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

void code()
{
  
}

int main()
{
  code();
  return 0;
}
