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
    while(dabs(whiteValue-analog(lineSensorId))<25) {
        msleep(100);
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
    msleep(dabs(distance*1000/speed));
    create_stop();
    pos[0] += cos(pos[2]*PI)*distance;
    pos[1] += sin(pos[2]*PI)*distance;
}

void turn(double radians, double speed)//the radians variable is the radians divided by PI
{
    if(speed<0) {
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

void code()
{
    closeGate();
    move(120,300);
    goToLine(300);
    create_drive_direct(200,200);
    msleep(1000);
    create_stop();
    create_drive_direct(80,200);
    msleep(2500);
    create_stop();
    create_drive_direct(20,200);
    msleep(1125);
    create_stop();
    move(400,300);
    create_drive_direct(100,200);
    msleep(2000);
    create_stop();
    goToLine(300);
    create_drive_direct(-200,-20);
    msleep(500);
    create_stop();
    move(50,300);
    move(100,-300);
    openGate();
    move(100,200);
    move(200,-300);
    move(200,300);
    move(400,-300);
    closeGate();
    move(350,300);
    move(475,-300);
    goToLine(500);
    move(100,300);
    turn(-60,200);
    move(100,300);
    openGate();
    //followLine(1,30,0,false);
    followLine(5.5,200,0,false);
    //create_drive_direct(120,130);
    //msleep(300);
    //create_drive_direct(125,125);
    //msleep(700);
    //create_stop();
    //move(530,300);
    closeGate();
    msleep(1000);
    create_drive_direct(200,100);
    msleep(1000);
    create_stop();
    create_drive_direct(200,0);
    msleep(3500);
    create_stop();
    move(1200,500);
    create_drive_direct(150,100);
    msleep(2000);
    create_stop();
    create_drive_direct(200,100);
    msleep(3000);
    create_stop();
    create_drive_direct(0,-200);
    msleep(500);
    create_stop();
    move(200,-300);
    openGate();
    goToLine(300);
    move(40,300);
    move(400,-300);
    move(450,300);
    move(450,-300);
    closeGate();
    move(370,300);
    move(500,-300);
    openGate();
    create_drive_direct(100,200);
    msleep(2800);
    create_stop();
    create_drive_direct(200,100);
    msleep(2500);
    create_stop();
}
int main()
{
    create_connect();
    enable_servos();
    //wait_for_light(1);
    code();
    create_disconnect();
    disable_servos();
    return 0;
}