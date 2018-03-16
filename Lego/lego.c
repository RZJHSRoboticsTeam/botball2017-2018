#include <kipr/botball.h>
#include <math.h>

typedef enum { false, true } bool;
int clawOpen = 200;
int clawBGClosed = 850;
int clawCrateClosed = 550;
int gateOpen = 100;
int gateClosed = 1200;
unsigned int gatePort = 1;
unsigned int clawPort = 3;

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
    if(botGuy){ distance = clawBGClosed;}
    set_servo_position(clawPort,distance);
}

void code()
{
    enable_servos();
    set_servo_position(1, 50);
    set_servo_position(3, 1430);
    msleep(500);
    set_servo_position(1,40); //servo position so it fits
    msleep(500);
    //msleep(20000);
    set_servo_position(1, 1040);
	msleep(500);


    motor(1,40);
    motor(0,-40);
    msleep(1200);
    ao();// allign y position with crates
    motor(0,100);
    motor(1,100);
    msleep(6000);
    ao();// turn to crates
    motor(1,-40);
    motor(0,40);
    msleep(1590);
    ao();// allign x position to crates
    openClaw();
    motor(1,-100);
    motor(0,-100);
    msleep(2675);
    ao();//grab crate
    msleep(1000);
    //closeClaw(false);
    set_servo_position(3, 580);
    msleep(1000);
    motor(1,100);
    motor(0,100);
    msleep(1500);
    ao();//move out
    motor(1,100);
    motor(0,100);
    msleep(600);
    ao();//align to yellow zone
    motor(1,40);
    motor(0,-40);
    msleep(2500);
    ao();//move to yellow zone
    motor(1,-100);
    motor(0,-100);
    msleep(1500);


    openGate();
    closeGate();

}

int main()
{
    //wait_for_light(0);
    code();

    return 0;
}
