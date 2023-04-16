#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <PS2X_lib.h>  //for v1.6

PS2X ps2x; // create PS2 Controller Class
RF24 radio(9,10); // (CE,CS)
const uint64_t pipe = 0xE8E8F0F0E1LL;

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte type = 0;
byte payload[6];
byte buttons = 0;
byte dPads = 0;
//int LEDpin = 8;
//int LEDstate = 0;

void setup(){
 Serial.begin(57600);
 radio.begin();
 radio.openWritingPipe(pipe);
 //pinMode(LEDpin, OUTPUT);
 error = ps2x.config_gamepad(6,4,3,5, false, false);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 /*
 if(error == 0){
  //Serial.println("Found Controller, configured successful");
   //Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
  //Serial.println("holding L1 or R1 will print out the analog stick values.");
  //Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1){}
   //Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2){}
   //Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3){}
   //Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   //Serial.print(ps2x.Analog(1), HEX);
   */ 
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        //Serial.println("Unknown Controller type");
       break;
       case 1:
        //Serial.println("DualShock Controller Found");
       break;
       case 2:
         //Serial.println("GuitarHero Controller Found");
       break;
     }
 }

void loop(){
   /* You must Read Gamepad to get new values
   Read GamePad and set vibration values
   ps2x.read_gamepad(small motor on/off, larger motor strength from 0-255)
   if you don't enable the rumble, use ps2x.read_gamepad(); with no values
   
   you should call this at least once a second
   */
  buttons = 0;
  dPads = 0;
      
 if(error == 1){ //skip loop if no controller found
  //return; 
 }
  
 if(type == 2){ //Guitar Hero Controller

 }

 else { //DualShock Controller
  
    ps2x.read_gamepad();          //read controller 
    bitWrite(buttons, 0, ps2x.Button(PSB_SELECT)); //byte 1, bit 0
    bitWrite(buttons, 1, ps2x.Button(PSB_START)); //byte , bit 1
    bitWrite(buttons, 2, ps2x.Button(PSB_L1)); //byte 1, bit 2
    bitWrite(buttons, 3, ps2x.Button(PSB_R1)); //byte 1, bit 3
    bitWrite(buttons, 4, ps2x.Button(PSB_L2)); //byte 1, bit 4
    bitWrite(buttons, 5, ps2x.Button(PSB_R2)); //byte 1, bit 5
    bitWrite(buttons, 6, ps2x.Button(PSB_L3)); //byte 1, bit 6
    bitWrite(buttons, 7, ps2x.Button(PSB_R3)); //byte 1, bit 7
    bitWrite(dPads, 0, ps2x.Button(PSB_PAD_UP)); //byte 2, bit 0
    bitWrite(dPads, 1, ps2x.Button(PSB_PAD_DOWN)); //byte 2, bit 1
    bitWrite(dPads, 2, ps2x.Button(PSB_PAD_LEFT)); //byte 2, bit 2
    bitWrite(dPads, 3, ps2x.Button(PSB_PAD_RIGHT)); //byte 2, bit 3
    bitWrite(dPads, 4, ps2x.Button(PSB_TRIANGLE)); //byte 2, bit 4
    bitWrite(dPads, 5, ps2x.Button(PSB_CROSS)); //byte 2, bit 5
    bitWrite(dPads, 6, ps2x.Button(PSB_SQUARE)); //byte 2, bit 6
    bitWrite(dPads, 7, ps2x.Button(PSB_CIRCLE)); //byte 2, bit 7

   
 }
  payload[0] = buttons;
  payload[1] = dPads;
  payload[2] = ps2x.Analog(PSS_LY);
  payload[3] = ps2x.Analog(PSS_LX);
  payload[4] = ps2x.Analog(PSS_RY);
  payload[5] = ps2x.Analog(PSS_RX);
  //if(bitRead(dPads,7)){LEDstate = !LEDstate;}
  radio.write(&payload, sizeof(payload));
  //digitalWrite(LEDpin,LEDstate);
  //Serial.println(ps2x.ButtonDataByte(), BIN);
  //delay(20);
     
}
