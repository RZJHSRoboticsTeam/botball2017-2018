#include <kipr/botball.h>
#include <math.h>
double matrix[] = {0,0,0};
int movementPorts[] = {0,0};
int turnPorts[2] = {}; //{left,right}
void move(double distance, double speed = 1)
{
  for(int i = 0;i<movementPorts.Length;i++) {
    mrp(movementPorts[i],speed,distance);
  };
  matrix[0] += cos(matrix[2]*PI)*distance;
  matrix[1] += sin(matrix[2]*PI)*distance;
}
void turn(double radians, double speed = 1)//the radians variable is the radians divided by pi
{
  for(int i = 0;i<turnPorts.Length;i++) {
    mult = 1;
    if(i==0) {
      mult = -1;
    };
    mrp(movementPorts[i],speed*mult,radians/2);
  };
  matrix[2] += radians;
  if(matrix[2] > 2) {
    matrix[2] -= 2;
  }
  if(matrix[2] < 0) {
    matrix[2] += 2;
  }
}
bool getButtonState(int buttonId)
{
  return false;
}
void turnTo(double radians, double speed = 1)//the radians variable is the radians divided by pi
{
  turn(radians-matrix[2],speed);
  matrix[2] = radians;
}
void moveTo(double x, double y, double speed = 1)
{
  turnTo(atan2(y-matrix[1],x-matrix[0])/PI);
  double distX = x-matrix[0];
  double distY = y-matrix[1];
  move(sqrt(distX*distX+distY*distY),speed);
  matrix[0] = x;
  matrix[1] = y;
}
void resetMatrix()
{
  matrix = {0,0,0};
}
void setMatrix(double m[])
{
  matrix = m;
}
double[] getMatrix()
{
  return matrix;
}
int main()
{
  return 0;
}