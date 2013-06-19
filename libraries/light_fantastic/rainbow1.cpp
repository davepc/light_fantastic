#include "light_fantastic.h"

int rainbowColors[180];

void rainbow1_setup(){
  for (int i=0; i<180; i++) {
    int hue = i * 2;
    int saturation = 100;
    int lightness = 20;
    // pre-compute the 180 rainbow colors
    rainbowColors[i] = makeColor(hue, saturation, lightness);
  }
}


void rainbow(int phaseShift, int cycleTime)
{
  int color, x, y, offset, wait;

  wait = cycleTime * 1000 / LEDn;
  for (color=0; color < 180; color++) {
    digitalWrite(1, HIGH);
    for (x=0; x < LEDn; x++) {
      for (y=0; y < 8; y++) {
        int index = (color + x + y*phaseShift/2) % 180;
        leds.setPixel(x + y*LEDn, rainbowColors[index]);
      }
    }
    leds.show();
    digitalWrite(1, LOW);
    delayMicroseconds(wait);
  }
}

void rainbow1(){
  rainbow(10, 2500);
}
