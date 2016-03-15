#include <Servo.h> 
#define LED_PIN 6 //pwm led control
#define LED_PALM_PIN 11 //pwm led control
#define SERVO_PIN_1 2 //moving 4 servo
#define SERVO_PIN_2 3
#define SERVO_PIN_3 4 
#define SERVO_PIN_4 5
#define LED_SW 12 
#define SERVO_SW A0 //use as digital input

void moveToTarget(int targetPos1, int targetPos2, int targetPos3, int targetPos4, int interval);

Servo servo1, servo2, servo3, servo4;
// int fadeValue = 5;
// int brightness = 0;    
int oldLedSwitch = LOW;
int oldServoSwitch = LOW; 
int readLedSwitch;
int readServoSwitch;
int stateLedSwitch = LOW;
int stateServoSwitch = LOW;

int LED_dimming = 0;

long time_LED = 0;
long time_servo = 0;
long debounce = 200;

//initial angle for servo 
int servo1Pos = 10;
int servo2Pos = 10;
int servo3Pos = 10;
int servo4Pos = 10;
// int servoToggle = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PALM_PIN, OUTPUT);
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
  //LED On/Off
  if(stateLedSwitch == HIGH){//ledSwitch == true
    dimmingLed();
    analogWrite(LED_PIN, 255 );
    analogWrite(LED_PALM_PIN, 255);
  }
  else{
    LED_dimming = 0;
    analogWrite(LED_PIN, 0);
    analogWrite(LED_PALM_PIN, 0);
  }

  //Servo. It toggle two positions
  if(stateServoSwitch == HIGH){//switch connected
    //0~180 angle
    //first position
    moveToTarget(90,10,90,10,5);//(servo1,servo2,servo3,servo4,interval)
    delay(100);
  }
  //second position
  else{
    moveToTarget(10,90,10,90,5);//(servo1,servo2,servo3,servo4,interval)
    delay(100);
  }

  oldLedSwitch = readLedSwitch;
  oldServoSwitch = readServoSwitch;
}

void checkSwitch(){

  //LED
  if(digitalRead(LED_SW) == LOW)
    readLedSwitch = HIGH;//switch connected
  else
    readLedSwitch = LOW;//switch disconnected
    
  if(readLedSwitch == HIGH && oldLedSwitch == LOW && 
    millis() - time_LED > debounce){
    if(stateLedSwitch == HIGH)
      stateLedSwitch = LOW;
    else
      stateLedSwitch = HIGH;
    time_LED = millis();
  }
  //Servo
  if(digitalRead(SERVO_SW) == LOW)
    readServoSwitch = HIGH;//switch connected
  else
    readServoSwitch = LOW;//switch disconnected

  if(readServoSwitch == HIGH && oldServoSwitch == LOW && 
    millis() - time_servo > debounce){
    if(stateServoSwitch == HIGH)
      stateServoSwitch = LOW;
    else
      stateServoSwitch = HIGH;
    time_servo = millis();
  }


}

void moveToTarget(int targetPos1, int targetPos2, int targetPos3, int targetPos4, int interval){
  while(true){

    //1st servo move
    while(servo1Pos != targetPos1){
      if(targetPos1 - servo1Pos > 0){
        servo1Pos++;
        servo1.write(servo1Pos);
        break;
      }else if(targetPos1 - servo1Pos < 0){
        servo1Pos--;
        servo1.write(servo1Pos);
        break;
      }
    }
    //2nd servo move
    while(servo2Pos != targetPos2){
      if(targetPos2 - servo2Pos > 0){
        servo2Pos++;
        servo2.write(servo2Pos);
        break;
      }else if(targetPos2 - servo2Pos < 0){
        servo2Pos--;
        servo2.write(servo2Pos);
        break;
      }
    }
    //3rd servo move
    while(servo3Pos != targetPos3){
      if(targetPos3 - servo3Pos > 0){
        servo3Pos++;
        servo3.write(servo3Pos);
        break;
      }else if(targetPos3 - servo3Pos < 0){
        servo3Pos--;
        servo3.write(servo3Pos);
        break;
      }
    }
    //4th servo move
    while(servo4Pos != targetPos4){
      if(targetPos4 - servo4Pos > 0){
        servo4Pos++;
        servo4.write(servo4Pos);
        break;
      }else if(targetPos4 - servo4Pos < 0){
        servo4Pos--;
        servo4.write(servo4Pos);
        break;
      }
    }
    //delay for interval. adjust this for servo speed
    //high number for low speed, low number for high speed
    delay(interval);

    if(servo1Pos == targetPos1 && servo2Pos == targetPos2 && 
      servo3Pos == targetPos3 && servo4Pos == targetPos4)
      break;
  }//end of while
}

//LED turns on slowly
void dimmingLed(){
  if(LED_dimming == 0){
    for(int i=0; i<255; i++){
    analogWrite(LED_PIN, i);
    analogWrite(LED_PALM_PIN, i);
    delay(7);
    }
    LED_dimming = 1;
  }
}
