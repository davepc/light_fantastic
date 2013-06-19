#include "light_fantastic.h"

static int hue = 0;
static int saturation = 100; 

void setcolour(){
  hue = opA;

  for(int i=1; i<256; i+=1){
    leds.setPixel(i, makeColor(hue, lightness, saturation));
  }
}
