#include "light_fantastic.h"

static unsigned long t;
//delay:
static unsigned int d = 10; //Delay local opA
static unsigned int b = 0;  
static unsigned int hue = 0; // lightness local opC


void colour_strobe_setup(){
  t = millis() + 1000;  // initial setup
  ReWrite(d, b);
}

int on;

void colour_strobe(){
  d = opA;

  if ((long)( millis() - t ) >= 0) {
    t += d*10;  
    if (on) {
      set_all(BLACK);
      on = 0;
    } else {
      set_all(makeColorS(hue));
      on = 1;
    }
    hue++;
    if (hue > 359)
      hue = 0;
    else if (hue < 0)
      hue = 359;
  }
}
