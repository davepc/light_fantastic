#ifndef light_fantastic_h
#define light_fantastic_h

#include "Arduino.h"
//LED setup
#include "../OctoWS2811/OctoWS2811.h"


extern const int LEDn;     //leds per strip
extern const int LEDstrips; //strps
//extern const int LEDN = 200;    //actual total LEDs
extern OctoWS2811 leds;


extern int mode;
extern int lightness;
extern int opA;
extern int opB;
extern int opC;

extern int grid[][32];
extern int mode_led;
extern int setting_led;

//max lightness
#define MAX_L 20

//Total modes
#define N_MODES 7

//Named colours
#define RED    0x0F0000
#define GREEN  0x000F00
#define BLUE   0x00000F
#define BLACK  0x000000
#define WHITE  0x020202


// Helper functions:
void set_all(int color);
void sensor_setup();
void sensor_read();
void sensor_indicator();
int makeColor(unsigned int hue, unsigned int saturation, unsigned int lightness);
int makeColorS(unsigned int hue);
//called by each mode setup function to set mode specific options. 
void ReWrite(int a, int b);
void ReWriteA(int a);
void ReWriteB(int b);



//Mode functions:
// 0
void rainbow1_setup();
void rainbow1();
// 1
void colour_strobe_setup();
void colour_strobe();
// 2
void setcolour();


#endif //light_fantastic_h
