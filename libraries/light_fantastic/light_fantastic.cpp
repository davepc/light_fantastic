#include "light_fantastic.h"

int makeColorS(unsigned int hue){
  makeColor(hue, 100, lightness);
}

void set_all(int color){
  for(int i=0; i<256; i++){
    leds.setPixel(i, color);
  }
}

