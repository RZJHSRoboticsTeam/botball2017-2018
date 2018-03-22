#include <kipr/botball.h>
#include <math.h>

typedef enum { false, true } bool;
int clawOpen = 130;
int clawBGClosed = 850;
int clawCrateClosed = 550;
int gateOpen = 100;
int gateClosed = 1200;
unsigned int gatePort = 1;
unsigned int clawPort = 3;
int lineSensorId= 1;

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


double dabs(double val) {
    if(val < 0) return -val;
    return val;
};

double mValue = 0.0;

void goToLine() {
    double whiteValue = analog(lineSensorId);
    motor(1, -100);
    motor(0, -100);
    printf("1");
    while(dabs(whiteValue-analog(lineSensorId))<25) {
        msleep(100);
    };
    ao();
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
        double color = analog(1);
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
    ao();
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
    printf("4");
    motor(0, 50);
    motor(1, -50);
    msleep(350);
    goToLine();
    motor(0, -100);
    motor(1, -100);
    printf("6");
    msleep(2500);
    motor(0, -50);
    motor(1, 50);
    msleep(500);
    goToLine();
    msleep(1000);
    motor(0, 50);
    motor(1, -50);
    msleep(2000);
    motor(0, -100);
    motor(1, -100);
    msleep(500);
  
    
    
    /*
    ao();// allign y position with crates 
    motor(0,100);
    motor(1,100);
    msleep(6150);
    ao();// turn to crates
    motor(1,-40);
    motor(0,40);
    msleep(1600);
    ao();// allign x position to crates
    openClaw();
    motor(1,-100);
    motor(0,-100);
    msleep(2300);
    ao();//grab crate
    msleep(400);
    //closeClaw(false);
    set_servo_position(3, 890);
    msleep(1000); 
    motor(1,100);
    motor(0,100);
    msleep(2900);
    ao();//align to yellow zone
    motor(1,40);
    motor(0,-40);
    msleep(2800);
    ao();//move to yellow zone
    motor(1,-100);
    motor(0,-100);
    msleep(2000);
    ao();// back up to line
    openClaw();
    
    motor(1, 100);
    motor(0, 100);
    msleep(4000);
    ao();// turn to blue pom
    motor (1, -40);
    motor (0, 40);
    msleep(600);
    set_servo_position(1, 100);
    motor (1, 100); 
    motor (0, 100);
    msleep(3800);
    //openGate()
    set_servo_position(1, 1200);
    motor (1, -100);
    motor (0, -100);
    msleep(
    */

}

int main()
{
    //wait_for_light(0);
    //msleep(60000); //wait for roomba to finish
    code();

    return 0;
}
