
#define SERIAL_DEBUG
#ifdef SERIAL_DEBUG
#define SER_PRINT(X) Serial.print((X))
#define SER_PRINT2(X,Y) Serial.print((X),(Y))
#define SER_PRINTLN(X) Serial.println((X))
#define SER_PRINTLN2(X,Y) Serial.println((X),(Y))
#else
#define SER_PRINT(X)
#define SER_PRINT2(X,Y)
#define SER_PRINTLN(X)
#define SER_PRINTLN2(X,Y)
#endif

//define this if plotter has a battery voltage feedback connected
//#define HAS_BATTERY_MEASUREMENT 
 
//which remote control to use
#define SONY_DVD_REMOTE

//servo pin
#define SERVO_PIN A5

//servo values for pen up/down
#define PEN_UP 80
#define PEN_DOWN 30


//IR-receiver pin
#define RECV_PIN  A0
 
//stepper motor pins
#define LEFT_STEP_PIN_1 7
#define LEFT_STEP_PIN_2 8
#define LEFT_STEP_PIN_3 9
#define LEFT_STEP_PIN_4 10
#define RIGHT_STEP_PIN_1 2
#define RIGHT_STEP_PIN_2 3
#define RIGHT_STEP_PIN_3 5
#define RIGHT_STEP_PIN_4 6
