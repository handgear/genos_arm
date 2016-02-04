#include <Servo.h> 
#define LED_PIN 6
#define SERVO_PIN_1 2
#define SERVO_PIN_2 3
#define SERVO_PIN_3 4
#define SERVO_PIN_4 5
#define LED_SW 11
#define SERVO_SW 12


Servo servo1, servo2, servo3, servo4;
int fadeValue = 5;
int brightness = 0;    
bool ledSwitch = false;
bool servoSwitch = false;  
int servo1Pos = 30;
int servo2Pos = 60;
int servo3Pos = 90;
int servo4Pos = 120;
int servoToggle = 0;

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

  if(digitalRead(LED_SW) == LOW){//ledSwitch == true
    dimmingLed();
  }
  else
    analogWrite(LED_PIN, 0);

  if(digitalRead(SERVO_SW) == LOW){
    servo1.write(90);//value 10 for test
    servo2.write(90);
    servo3.write(90);
    servo4.write(90);

    delay(200);
  }
  if(digitalRead(SERVO_SW) == HIGH){
    servo1.write(170);//value 10 for test
    servo2.write(170);
    servo3.write(170);
    servo4.write(170);
    delay(200);
  }


  // if(servoSwitch == true && servoToggle == 0){
  //   servoOn();  
  //   servoToggle = 1;
  // }else if(servoSwitch == false && servoToggle == 0){
  //   servoOff();
  //   servoToggle = 1;
  // }

}

void dimmingLed(){
  for(int i=0; i<255; i++){
    analogWrite(LED_PIN, i);
    delay(5);
  }
  
  // brightness = brightness + fadeValue;

  // if (brightness == 0 || brightness == 255) {
  //   fadeValue = -fadeValue ;
  // }
  // delay(25);
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
    delay(200);
    if(digitalRead(SERVO_SW) == LOW && servoSwitch == false){
     servoSwitch = true; 
     servoToggle = 0;
    }
  }else if(digitalRead(SERVO_SW) == LOW && servoSwitch == true){
    delay(200);
    if(digitalRead(SERVO_SW) == LOW && servoSwitch == true){
      servoSwitch = false;
      servoToggle = 0;
    }
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
