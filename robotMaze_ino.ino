/* Robot AI Control from Raspberry Pi 3
Written by: Pearse Swail - George Mason University - ECE499
Last Modified: 3/9/17
This program receives hardwired inputs from the RP3 in the form of
distances in cm. The robot then follows walls by turning slightly 
when the sensors/inputs get below thresholds.

This code references the following sources:
- ROBOTIS CO,.LTD Wheel mode example, found from 
the Lofaro Labs Wiki - http://wiki.lofarolabs.com/index.php/OpenCM_9.04
*/

// Dynamixel on Serial1,2,3 (USART1,2,3)
#define DXL_BUS_SERIAL1 1
#define DXL_BUS_SERIAL2 2
#define DXL_BUS_SERIAL3 3

// defining IDs for left and right servos/wheels
#define ID_LEFT 1
#define ID_RIGHT 2

#define SERIAL

Dynamixel Dxl(DXL_BUS_SERIAL1);

// set analog pins
int leftSens = 10;
int rightSens = 11;

// set digital pins
int IR = 12;

void setup() {
  // Initialize the dynamixel bus:
  Dxl.begin(3); // 1Mhz Baudrate
  
  Dxl.wheelMode(ID_LEFT);
  Dxl.wheelMode(ID_RIGHT);

  pinMode(leftSens, INPUT);
  pinMode(rightSens, INPUT);
  pinMode(IR, INPUT);
}

void loop() {
  stop();

  while(digitalRead(IR) == 0) // exit when IR senses a black line
  {
    int left = digitalRead(leftSens);
    int right = digitalRead(rightSens);
    
    if(left < 7)
      turnRight();
    else if(right < 7)
      turnLeft();
    else
      goStraight();    
  }
  stop();
}

void stop()
{
  Dxl.goalSpeed(ID_LEFT, 0);
  Dxl.goalSpeed(ID_RIGHT, 1024);
}
void turnRight()
{
  Dxl.goalSpeed(ID_LEFT, 50);
  Dxl.goalSpeed(ID_RIGHT, 1074);
}

void turnLeft()
{
  Dxl.goalSpeed(ID_LEFT, 1074);
  Dxl.goalSpeed(ID_RIGHT, 50);
}

void goStraight()
{
  Dxl.goalSpeed(ID_LEFT, 50);
  Dxl.goalSpeed(ID_RIGHT, 50);
}
