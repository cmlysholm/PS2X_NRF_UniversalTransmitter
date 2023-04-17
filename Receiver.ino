#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <Servo.h>

RF24 radio(9,10); //VCC:3v3, CE:PIN9, SCN:PIN10, SCK:PIN13, MOSI:PIN11, MISO:PIN12
const uint64_t pipe = 0xE8E8F0F0E1LL;
byte payload[6]; 
byte buttons;
byte buttonsLast = 0;
byte dPads;
byte dPadsLast = 0;
byte buttonPress;
byte dPadPress;
byte LY, LX, RY, RX;
Servo myservo;

int LEDstate = 0;
int LEDpin = 8;
int servoPin = 5;
int servoAngle = 90;
//int LY, LX, RX, RY;

void setup(void){
   Serial.begin(57600);
   radio.begin(); 
   radio.openReadingPipe(1,pipe);
   radio.startListening();
   pinMode(LEDpin,OUTPUT);
   myservo.attach(servoPin);
   //radio.printDetails();
}

void loop(void){

 if( radio.available() ){
  bool done = false;
  while (!done){
   done = radio.read(payload, sizeof(payload)); 
  }
  buttons = payload[0];
  dPads = payload[1];
  LY = payload[2];
  LX = payload[3];
  RY = payload[4];
  RX = payload[5];
  }
 else{
  //Serial.println("No Radio Available");//NO RADIO AVAILABLE
  } 
 //Check if buttons have JUST BEEN PRESSED
 buttonPress = ~buttonsLast & buttons;
 dPadPress = ~dPadsLast & dPads; 
 buttonsLast = buttons;
 dPadsLast = dPads; 
 
 //DO STUFF WITH THE NEW BUTTON INPUTS -- PUT CODE HERE
if(bitRead(dPadPress,0)){Serial.println("D Pad UP was pressed.");}
if(bitRead(dPadPress,1)){Serial.println("D Pad DOWN was pressed.");}
if(bitRead(dPadPress,2)){Serial.println("D Pad LEFT was pressed.");}
if(bitRead(dPadPress,3)){Serial.println("D Pad RIGHT was pressed.");}
if(bitRead(dPadPress,4)){Serial.println("TRIANGLE was pressed.");}
if(bitRead(dPadPress,5)){Serial.println("X was pressed.");}
if(bitRead(dPadPress,6)){Serial.println("SQUARE was pressed.");}
if(bitRead(dPadPress,7)){Serial.println("CIRCLE was pressed.");}

if(bitRead(buttonPress,0)){Serial.println("SELECT was pressed.");}
if(bitRead(buttonPress,1)){Serial.println("START was pressed.");}
if(bitRead(buttonPress,2)){Serial.println("L1 was pressed.");}
if(bitRead(buttonPress,3)){Serial.println("R1 was pressed.");}
if(bitRead(buttonPress,4)){Serial.println("L2 was pressed.");}
if(bitRead(buttonPress,5)){Serial.println("R2 was pressed.");}
if(bitRead(buttonPress,6)){Serial.println("Left stick was clicked.");}
if(bitRead(buttonPress,7)){Serial.println("Right stick was clicked.");}

if(bitRead(buttons,2)){Serial.println(LX);} //Display the analog value if L1 is held.
if(bitRead(buttons,4)){Serial.println(LY);}
if(bitRead(buttons,3)){Serial.println(RX);}
if(bitRead(buttons,5)){Serial.println(RY);}

if(bitRead(buttons,3)){servoAngle = map(RX,0,255,0,180); myservo.write(servoAngle); delay(15);}


/*
if(bitRead(dPadPress,7)){LEDstate = !LEDstate;} //CIRCLE BUTTON
digitalWrite(LEDpin,LEDstate);
Serial.println(LX);
*/
//Serial.println(payload[1],BIN);
delay(50);
}


