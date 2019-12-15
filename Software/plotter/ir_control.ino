#include <IRremote.h>
#include "MachineDefs.h"
 
IRrecv irrecv(RECV_PIN);
decode_results results;  

#ifdef SONY_DVD_REMOTE
#define POWER 0xa8b92 // power
#define CODE_BIG_PRINT 0x490 // vol +
#define CODE_SMALL_PRINT 0xc90 // vol -
#define CODE_LEFT_REEL_IN 0xdeb92 // left arrow
#define CODE_LEFT_REEL_OUT 0x3eb92 // right arrow
#define CODE_RIGHT_REEL_IN 0x9eb92 // up arrow
#define CODE_RIGHT_REEL_OUT 0x5eb92 // down arrow
#define CODE_LEFT_CALIBRATION 0xcb92 // prev
#define CODE_RIGHT_CALIBRATION 0x8cb92 // next
#define CODE_STOP 0x1cb92 // stop
#define CODE_RESUME 0x4cb92 // play
// have not remapped rest below
#define CODE_ENABLE_CONT_DRIVE 0xffb04f //c
#define CODE_DISABLE_CONT_DRIVE 0xBADC0DE //not button for this shit 
#define CODE_1 0x5ab92
#define CODE_2 0x12b92
#define CODE_3 0xcab92
#define CODE_4 0x14b92
#define CODE_5 0x54b92
#define CODE_6 0xacb92
#define CODE_7 0x34b92
#define CODE_8 0xf8b92
#define CODE_9 0xf0b92

#else
#error What remote?
#endif 


void setupIR() 
{
  irrecv.enableIRIn(); // Start the receiver  
}

void readIR()
{
  float lDist;
  bool fail = false;
  
  if (irrecv.decode(&results)) {         
    switch(results.value) {
#ifndef NO_REMOTE      
       case POWER:  //power
         storePositionInEEPROM();
               
         break;         
       case CODE_BIG_PRINT:  //up
         printSize = 2;
         break;
       case CODE_SMALL_PRINT:  //down
         printSize = 0.5;
         break;
       case CODE_LEFT_REEL_IN: //left -
         Serial.println("LEFT BISH");
         manualLeft = -1;
         break;
       case CODE_LEFT_REEL_OUT: //left +
         manualLeft = 1;
         break;
       case CODE_RIGHT_REEL_IN: //right -
         Serial.println("RIGHT SUH");
         manualRight = -1;
         break;
       case CODE_RIGHT_REEL_OUT: //right +
         manualRight = 1;
         break;
       case CODE_LEFT_CALIBRATION:  //prev - calibrate 200 mm from left
         currentLeftSteps = 200*stepsPerMM;
         testPen();         
         break;
       case CODE_RIGHT_CALIBRATION:  //next - calibrate 200 mm from right
         currentRightSteps = 200*stepsPerMM;              

         lDist = currentLeftSteps/stepsPerMM;
         disparity = (long)sqrt(lDist*lDist-200L*200L);

         SER_PRINT("Cal: lDist)");
         SER_PRINTLN(lDist);

         SER_PRINT("Cal: Disp=");
         SER_PRINTLN(disparity);

         break;   
       case CODE_DISABLE_CONT_DRIVE: 
         continousManualDrive = false;
         break;
       case CODE_ENABLE_CONT_DRIVE: 
         continousManualDrive = true;
         break;
       case CODE_STOP:  
         stopPressed = true;
#if  CODE_DISABLE_CONT_DRIVE == 0xBADC0DE
        //just disable continous drive when pressing stop. Re-enable with CODE_ENABLE_CONT_DRIVE again
         continousManualDrive = false;
#endif
         break;
       case CODE_RESUME:
          //resume print, or start new
          program = 1; //start print
          resumePlot = true;       
         break;
       case CODE_1: program = 1; currentPlot = 1; break;
       case CODE_2: program = 1; currentPlot = 2; break;
       case CODE_3: program = 1; currentPlot = 3; break;
       case CODE_4: program = 1; currentPlot = 4; break;
       case CODE_5: program = 1; currentPlot = 5; break;
       case CODE_6: program = 1; currentPlot = 6; break;
       case CODE_7: program = 1; currentPlot = 7; break;
       case CODE_8: program = 1; currentPlot = 8; break;
       case CODE_9: program = 1; currentPlot = 9; break;       
       default:
          fail=true;           
#endif //NO_REMOTE         
    }   
    if(fail) {
       SER_PRINT("???: ");
    }
    else {
       makePenNoise(1);
    }
    SER_PRINTLN2(results.value, HEX);      
    
    irrecv.resume(); // Receive the next value
  }  
}
