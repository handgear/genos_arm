#include <Servo.h> 
#define LED_PIN 9
#define SERVO_PIN_1 2
#define SERVO_PIN_2 3
#define SERVO_PIN_3 4
#define SERVO_PIN_4 5
#define LED_SW 11
#define SERVO_SW 12
#define FADE_VAL 5

Servo servo1, servo2, servo3, servo4;

int brightness = 0;    
bool ledSwitch = false;
bool servoSwitch = false;  
int servo1Pos = 30;
int servo2Pos = 60;
int servo3Pos = 90;
int servo4Pos = 120;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(SERVO_PIN_1, OUTPUT);
  pinMode(SERVO_PIN_2, OUTPUT);
  pinMode(SERVO_PIN_3, OUTPUT);
  pinMode(SERVO_PIN_4, OUTPUT);
  pinMode(LED_SW, INPUT_PULLUP);
  pinMode(SERVO_SW, INPUT_PULLUP);

  servo1.attach(SERVO_PIN_1);
  servo2.attach(SERVO_PIN_2);
  servo3.attach(SERVO_PIN_3);
  servo4.attach(SERVO_PIN_4);
}

void loop() {
  checkSwitch();

  if(ledSwitch == true){
    dimmingLed();
  } 
  if(servoSwitch == true){
    servoOn();  
  }else if(servoSwitch == false){
    servoOff();
  }

}
void dimmingLed(){
  analogWrite(LED_PIN, brightness);

  brightness = brightness + FADE_VAL;

  if (brightness == 0 || brightness == 255) {
    FADE_VAL = -FADE_VAL ;
  }
  delay(25);
}
void checkSwitch(){
  // ledSwitch = false;
  // servoSwitch = false;
  if(digitalRead(LED_SW) == LOW && ledSwitch == false){
    ledSwitch = true;
  }else if(digitalRead(LED_SW) == LOW && ledSwitch == true){
    ledSwitch = false;
  }
  if(digitalRead(SERVO_SW) == LOW && servoSwitch == false){
    servoSwitch = true; 
  }else if(digitalRead(SERVO_SW) == LOW && servoSwitch == true){
    servoSwitch = false;
  }
  delay(200);//prevennt debouncing
}
void servoOn(){
  servo1.write(servo1Pos);
  servo2.write(servo2Pos);
  servo3.write(servo3Pos);
  servo4.write(servo4Pos);
  delay(500);//wait servo to move
}
void servoOff(){
  servo1.write(10);//value 10 for test
  servo2.write(10);
  servo3.write(10);
  servo4.write(10);
  delay(500);//wait servo to move
}