/*  
 *  THE LIGHT FANTASTIC
 *  Version 0.1
 *  By David Clarke led@siananddave.com

    Based on:
    http://www.pjrc.com/teensy/td_libs_OctoWS2811.html
    Copyright (c) 2013 Paul Stoffregen, PJRC.COM, LLC

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

//Encoder setup
#include "light_fantastic.h"
#include "OctoWS2811.h"
#include "Bounce.h"
#include "Encoder.h"

const int LEDn = 32;     //leds per strip
const int LEDstrips = 8; //strps
const int LEDN = 200;    //actual total LEDs
DMAMEM int LEDdisplayMemory[LEDn*6];
int LEDdrawingMemory[LEDn*6];
const int LEDconfig = WS2811_RGB | WS2811_800kHz;
OctoWS2811 leds(LEDn, LEDdisplayMemory, LEDdrawingMemory, LEDconfig);



//Delay times:
static unsigned long seq_256_rgb_t;

void setup() {
  leds.begin();
  sensor_setup();

  //Mode setups
  rainbow1_setup();
  colour_strobe_setup();

  Serial.begin(9600);
}

void loop() {
  sensor_read();
  //  Serial.println(10);
  switch(mode){
    case 0:
      Serial.println("Mode 0");
      colour_strobe();
      //rainbow1();
      break;
    case 1:
  //    Serial.println("Mode 1");
      setcolour();
      break;
  }

  //Finally show:
  sensor_indicator();
  leds.show();
}


void sequential_8_rgb(){
  int wait = 200;
  for(int i=0; i<8; i++){
    for(int j=0; j<LEDn; j++){
      leds.setPixel(i*LEDn+j, RED);
    }
    delay(wait);
    for(int j=0; j<LEDn; j++){
      leds.setPixel(i*LEDn+j, GREEN);
    }
    delay(wait);
    for(int j=0; j<LEDn; j++){
      leds.setPixel(i*LEDn+j, BLUE);
    }
    delay(wait);
    for(int j=0; j<LEDn; j++){
      leds.setPixel(i*LEDn+j, WHITE);
    }
    delay(wait);
  }
}

int seq_246_rgb_i = 0;
int seq_246_rgb_color = 0;

/*
void seq_256_rgb(int delay){
  if ((long)( millis() - seq_256_rgb_t ) >= 0) {
    seq_256_rgb_t += delay;  
    /*Serial.print(seq_256_rgb_t);
      Serial.print("\t");
      Serial.print(seq_246_rgb_i);
      Serial.print("\t");
      Serial.print(seq_246_rgb_color);
      Serial.print("\t");
      Serial.println(colors[seq_246_rgb_color]);
    int colors[] = {RED, GREEN, BLUE, BLACK};
    all_off();
    leds.setPixel(seq_246_rgb_i, colors[seq_246_rgb_color]);
    seq_246_rgb_color++;
    if (seq_246_rgb_color > 3) {
      seq_246_rgb_color = 0;
      seq_246_rgb_i++;
      if (seq_246_rgb_i > 255)
        seq_246_rgb_i = 0;
    }
  }
}

void sequential_256_rgb_delay(){
  int wait = 200;
  for(int i=0; i<256; i++){
    leds.setPixel(i, RED);
    delay(wait);
    leds.setPixel(i, GREEN);
    delay(wait);
    leds.setPixel(i, BLUE);
    delay(wait);
    leds.setPixel(i, BLACK);
  }
}

*/

