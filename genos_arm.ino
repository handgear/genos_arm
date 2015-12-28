#include <Servo.h> 
#define pin_servo1 9 
#define pin_sw1 7
#define pin_sw2 6
#define pin_sw3 3
#define pin_sw4 2
#define pin_LED1 11 //able PWM
#define MAX_POS 150 //max in angle(0~180)
#define MIN_POS 30 //min in angle(0~180)
#define DELTA 15 //in angle

Servo servo1;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  pinMode(pin_sw1, INPUT_PULLUP);
  pinMode(pin_sw2, INPUT_PULLUP);
  pinMode(pin_sw3, INPUT_PULLUP);
  pinMode(pin_sw4, INPUT_PULLUP);
  pinMode(pin_LED1, OUTPUT);

  servo1.attach(pin_servo1);  // attaches the servo on pin 9 to the servo object
  //servo1.attach(9,544,2400); //modify pulse width

} 
void loop() {
 
  if(digitalRead(pin_sw1)==LOW)//move to max position
  {
    delay(20);//debouncing
    servo1.write(MAX_POS);
    pos=MAX_POS;
    delay(800);//time for servo to move
    while(pin_sw1==0);//prevent double movment
  }
  if(digitalRead(pin_sw2)==LOW)//move to max position
  {
    delay(20);//debouncing
    servo1.write(MIN_POS);
    pos=MIN_POS;
    delay(800);//time for servo to move
    while(pin_sw2==0);//prevent double movment
  }
  if(digitalRead(pin_sw3)==LOW)//move to max position
  {
    delay(20);//debouncing
    if(pos-DELTA>0)
    {
      servo1.write(pos-DELTA);
      pos=pos-DELTA;
    }
    delay(300);//time for servo to move
    while(pin_sw3==0);//prevent double movment
  }
  if(digitalRead(pin_sw4)==LOW)//move to max position
  {
    delay(20);//debouncing
    if(pos+DELTA<180)
    {
      servo1.write(pos+DELTA);
      pos=pos+DELTA;
    }
    delay(300);//time for servo to move
    while(pin_sw4==0);//prevent double movment
  }

}

