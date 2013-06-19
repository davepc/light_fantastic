#include "light_fantastic.h"
#include "../Encoder/Encoder.h"

#define DEBUG_S 0

#define REA1pin 3
#define REA2pin 9
#define REB1pin 10
#define REB2pin 11
#define PLpin A4
#define PRpin A5
#define BApin 0
#define BBpin 1

int mode = 0;
int opA = 0;
int opB = 0;
int lightness = 3;
static int current = 0;
static int indicator_time = 0;

Encoder ReAo(REA1pin, REA2pin);
Encoder ReBo(REB1pin, REB2pin);
long ReA = -999;
long ReB = -999;

void ReRead();
int ARread(int inputPin);

//Button setup (encoder)
#include "../Bounce/Bounce.h"
Bounce BAo = Bounce(BApin, 5); //Pin BA, 5milisec debounce
Bounce BBo = Bounce(BBpin, 5); //Pin BB, 5milisec debounce

//Pressure sensor:
const int Avgnum = 100;
int Avgr[Avgnum];
void ARsetup(int num_readings, int* ARrc);


void sensor_setup(){
  //Pullups
  pinMode(0, INPUT_PULLUP); // Press button A
  pinMode(1, INPUT_PULLUP); // Press button B
  //pressure sensor:
  ARsetup(Avgnum, Avgr);
}

void sensor_read(){
  //Update from encoder
  ReRead(); 
  BAo.update();
  int BA = BAo.read();
  int PL = ARread(PLpin);
  int PR = ARread(PRpin);
  Serial.print("BA\t");
  Serial.print(BA);
  Serial.print("\tPL\t");
  Serial.print(PL);
  Serial.print("\tPR\t");
  Serial.println(PR);

  if (BBo.update()){
    if (BBo.read() == LOW){
      current++;
      current = current % 3;
      indicator_time = millis() + 3000;
      switch(current){
        case 0:
          ReBo.write(opA);
          break;
        case 1:
          ReBo.write(opB);
          break;
        case 2:
          ReBo.write(lightness);
          break;
      }
    }
  }

  if(DEBUG_S){
    Serial.print("Mode: ");
    Serial.print(mode);
    Serial.print("\tA: ");
    Serial.print(opA);
    Serial.print("\tB: ");
    Serial.print(opB);
    Serial.print("\tC: ");
    Serial.print(lightness);
    Serial.print("\tCurrent:");
    Serial.print(current);
    Serial.println(" ");
  }
}

void ReWrite(int a, int b){
  opA = a;
  opB = b;
  switch(current){
    case 0:
      ReBo.write(opA);
      break;
    case 1:
      ReBo.write(opB);
      break;
  }
}

void ReWriteA(int a){
  opA = a;
  if(current = 0){
    ReBo.write(opA);
  }
}

void ReWriteB(int b){
  opB = b;
  if(current = 0){
    ReBo.write(opB);
  }
}

void ReRead(){
  long ReAn = ReAo.read();
  long ReBn = ReBo.read();


  //no negative:
  if (ReBn < 0) {
    ReBn = 0;
    ReBo.write(0);
  }
  //1000 max - reset to zero (incase turner gets lost and very big.):
  if (ReBn > 1000) {
    ReBn = 0;
    ReBo.write(0);
  }

//Mode:
  if (ReAn != ReA) {
    indicator_time = millis() + 3000;
    ReA = ReAn;
    mode = ReA / 3;
    if (mode >= N_MODES) {
      mode = 0;
      ReAo.write(0);
    }
    if (mode < 0){
      mode = N_MODES - 1;
      ReAo.write(N_MODES -1);
    }

    // Print info
    Serial.print("A:");
    Serial.print(ReAn);
    Serial.print("\tB:");
    Serial.println(ReBn);
  } 

  if (ReBn != ReB) {
    indicator_time = millis() + 3000;
    ReB = ReBn;
    switch(current){
      case 0:
        opA = ReB;
        break;
      case 1:
        opB = ReB;
        break;
      case 2:
        lightness = ReB;
        if (lightness > MAX_L) {
          lightness = MAX_L;
          ReBo.write(MAX_L);
        }
        if (lightness < 1) {
          lightness = 1;
          ReBo.write(1);
        }
        break;
    }
  }
}

//Pressure read and smooth
int ARnum;
int* ARr;
int ARi = 0; 
int ARtot = 0;

void ARsetup(int num_readings, int* ARrc){
  ARr = ARrc;
  ARnum = num_readings;
  for (int i = 0; i < ARnum; i++)
    ARr[i] = 0;          
}

int ARread(int inputPin){    
  ARtot -= ARr[ARi];         
  ARr[ARi] = analogRead(inputPin); 
  ARtot += ARr[ARi]; 
  ARi++; 
  if (ARi >= ARnum)              
    ARi = 0;                       
  return ARtot / ARnum;
}

void sensor_indicator(){
  if ((long)(indicator_time - millis()) >= 0) {
    leds.setPixel(mode_led, makeColorS(mode*360/N_MODES));

    switch(current){
      case 0:
        leds.setPixel(setting_led, RED);
        break;
      case 1:
        leds.setPixel(setting_led, GREEN);
        break;
      case 2:
        leds.setPixel(setting_led, BLUE);
        break;
    }
  }
}
