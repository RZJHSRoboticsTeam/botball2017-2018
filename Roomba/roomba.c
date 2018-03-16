#include <kipr/botball.h>
#include <math.h>
typedef enum { false, true } bool;

double pos[] = {0,0,0};
double PI = 3.141592;

unsigned int gatePort = 0;

int gateOpen = 680;
int gateClosed = 1560;

void openGate()
{
  set_servo_position(gatePort,gateOpen);
}

void closeGate()
{
  set_servo_position(gatePort,gateClosed);
}

unsigned int lineSensorId = 0;

double dabs(double val) {
    if(val < 0) return -val;
    return val;
};

double mValue = 0.0;

void goToLine(double Speed) {
    double whiteValue = analog(lineSensorId);
    create_drive_direct(Speed,Speed);
    while(dabs(whiteValue-analog(lineSensorId))<10) {
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
        msleep(10);
        t+=0.01;
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
    create_spin_block(radians,speed);
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
    turnTo(atan2(y-pos[1],x-pos[0])*180/PI,100);
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

double dropOffDistance = 0;
double backUpDistance = 0;

void dropOffPoms()
{
    goToLine(100);
    openGate();
    move(dropOffDistance,100);
    move(dropOffDistance+backUpDistance,-100);
    closeGate();
}
void code()
{
    //goToLine(100);
    //followLine(2, 75, -25, false);
    //followLine(10, 100, 0, true);
    closeGate();
    move(120,100);
    goToLine(100);
    move(120,100);
    goToLine(100);
    //turn(45,100);
    /*goToLine(100);
    followLine(5,100,0,false);
    turn(0.5,100);
    dropOffPoms();*/
    /*
    turn(0.5,100);
    dropOffPoms();
    turn(1,100);
    goToLine(100);
    turn(0.5,100);
    followLine(time2,maxSpeed,minSpeed,false);
    turn(0.5,100);
    move(distance2,100);
    turn(0.5,100);
    goToLine(100);
    move(distance3,-100);
    turn(-0.5,100);
    dropOffPoms();
    */
}
int main()
{
    create_connect();
    //waitForLight(1);
    code();
    create_disconnect();
    return 0;
}