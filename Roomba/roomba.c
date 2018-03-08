#include <kipr/botball.h>
#include <math.h>
typedef enum { false, true } bool;

double pos[] = {0,0,0};
double PI = 3.141592;
unsigned int lineSensorId = 0;

double dabs(double val) {
    if(val < 0) return -val;
    return val;
};

double mValue = 0.0;

void goToLine(double Speed) {
    double whiteValue = analog(lineSensorId);
    create_drive_direct(Speed,Speed);
    while(dabs(whiteValue-analog(lineSensorId))<100) {
        msleep(10);
    };
    create_stop();
    mValue = (whiteValue+analog(lineSensorId))/2.0;
}

void followLine(double time, double maxSpeed, double minSpeed, bool rMode) {
    double defL = maxSpeed;
    double defR = minSpeed;
    if(rMode) {
        defL = minSpeed;
        defR = maxSpeed;
    };
    double t = 0;
    while(t<time) {
        double color = analog(lineSensorId);
        double lSpeed = defL;
        double rSpeed = defR;
        if(color<mValue) {
            lSpeed = defR;
            rSpeed = defL;
        };
        create_drive_direct(lSpeed,rSpeed);
        msleep(1);
        t+=0.001;
    };
    create_stop();
}

void move(double distance, double speed)
{
    create_drive_direct(speed,speed);
    msleep(distance*1000/speed);
    create_stop();
    pos[0] += cos(pos[2]*PI)*distance;
    pos[1] += sin(pos[2]*PI)*distance;
}
void turn(double radians, double speed)//the radians variable is the radians divided by PI
{
    if(radians<0) {
        radians *= -1;
        speed *= -1;
    };
    create_spin_block(speed,radians*180);
    create_stop();
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
    goToLine(100);
    followLine(2, 75, -25, false);
    followLine(10, 100, 0, true);
}
int main()
{
    create_connect();
    code();
    create_disconnect();
    return 0;
}