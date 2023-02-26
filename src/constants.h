//
// Constants
//
// Pin to connect LED data wire to
#define LED_PIN    D6
// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 111
#define ELEMENTS 27

#define TIMEZONE 3600

#define IDLEINTERVAL 1
#define LAPSESPEED 0
//#define LAPSESPEED 59

// Map the leds to the text boxes
// Leds are just numbered.
// To make it easier to configure, there is an array holding the sizes
// of all elements as well as their meaning.
#define ELEMENTMAP   { 4, 4, 4, 4,     /*   0 -  3*/\
                       4, 6, 1, 6, 4,  /*R  8 -  4*/\
                       4, 4, 4, 4, 4,  /*   9 - 13*/\
                       4, 6, 1, 6, 4,  /*R 18 - 14*/\
                       4, 6, 1, 6, 4,  /*  19 - 23*/\
                       4, 4, 4 };      /*R 26 - 24*/

// This maps the numbers of the above array to semantics
// Hours is clear somehow: 1-12
#define HOURMAP {12, 14, 18, 25, 23, 17, 15, 13, 20, 26, 19, 22}
// Minutes are 5-10-15-20-25-30
#define MINUTEMAP {8, 4, 5, 7}
// text between minute and hour
#define TO 9
#define PAST 10
// Additional text at end
#define OCLOCK 24
