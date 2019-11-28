
/*
 Stepper Motor Control - one revolution

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.


 Created 11 Mar. 2007
 Modified 30 Nov. 2009
 by Tom Igoe

 */
#include <IRremote.h>
#include <Stepper.h>
#include <Servo.h>

const int stepsPerRevolution = 500;  // change this to fit the number of steps per revolution for your motor
const int RECV_PIN = 7;
const int redPin = 2;
const int greenPin = 3;
const int servoPin = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
Servo servo;

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  // lights
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  // servo setup
  servo.attach(servoPin);
  servo.write(0);
}


void loop(){
  if (irrecv.decode(&results)){
 
        if (results.value == 0XFFFFFFFF)
          results.value = key_value;

        switch(results.value){
          case 0xdeb92:
          Serial.println("clockwise");
          digitalWrite(redPin, HIGH);
          servo.write(180);
          myStepper.step(-stepsPerRevolution);
          myStepper.step(-stepsPerRevolution);
          myStepper.step(-stepsPerRevolution);
          myStepper.step(-stepsPerRevolution);
          delay(5);
          digitalWrite(redPin, LOW);
          break;
          case 0x3eb92:
          Serial.println("counterclockwise");
          digitalWrite(greenPin, HIGH);
          servo.write(0);
          myStepper.step(stepsPerRevolution);
          myStepper.step(stepsPerRevolution);
          myStepper.step(stepsPerRevolution);
          myStepper.step(stepsPerRevolution);
          delay(5);
          digitalWrite(greenPin, LOW);
          break;
          case 0xFFE21D:
          Serial.println("CH+");
          break;
          case 0xFF22DD:
          Serial.println("|<<");
          break;
          case 0xFF02FD:
          Serial.println(">>|");
          break ;  
          case 0xFFC23D:
          Serial.println(">|");
          break ;               
          case 0xFFE01F:
          Serial.println("-");
          break ;  
          case 0xFFA857:
          Serial.println("+");
          break ;  
          case 0xFF906F:
          Serial.println("EQ");
          break ;  
          case 0xFF6897:
          Serial.println("0");
          break ;  
          case 0xFF9867:
          Serial.println("100+");
          break ;
          case 0xFFB04F:
          Serial.println("200+");
          break ;
          case 0xFF30CF:
          Serial.println("1");
          break ;
          case 0xFF18E7:
          Serial.println("2");
          break ;
          case 0xFF7A85:
          Serial.println("3");
          break ;
          case 0xFF10EF:
          Serial.println("4");
          break ;
          case 0xFF38C7:
          Serial.println("5");
          break ;
          case 0xFF5AA5:
          Serial.println("6");
          break ;
          case 0xFF42BD:
          Serial.println("7");
          break ;
          case 0xFF4AB5:
          Serial.println("8");
          break ;
          case 0xFF52AD:
          Serial.println("9");
          break ;      
        }
        key_value = results.value;
        irrecv.resume(); 
  }
}
