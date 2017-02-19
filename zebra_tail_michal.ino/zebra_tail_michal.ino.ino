#include <FastLED.h>

#define LED_PIN_1     6
//#define LED_PIN_2     5
//#define LED_PIN_3     6
//#define LED_PIN_4     7
//#define LED_PIN_5     8
//#define LED_PIN_6     9

#define START_SKIP_LEDS    0
#define END_SKIP_LEDS    0
#define NUM_LEDS    229 - END_SKIP_LEDS
#define BRIGHTNESS  30
#define LED_TYPE    WS2812B
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];
#define BUTTON_PIN 3
int buttonState = 0;
uint8_t animationIndex = 1;

int UPDATES_PER_SECOND = 102;

// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.
//
// USING palettes is MUCH simpler in practice than in theory, so first just
// run this sketch, and watch the pretty lights as you then read through
// the code.  Although this sketch has eight (or more) different color schemes,
// the entire sketch compiles down to about 6.5K on AVR.
//
// FastLED provides a few pre-configured color palettes, and makes it
// extremely easy to make up your own color schemes with palettes.
//
// Some notes on the more abstract 'theory and practice' of
// FastLED compact palettes are at the bottom of this file.



CRGBPalette16 currentPalette;
TBlendType    currentBlending;
extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

// Gradient palette "bhw1_04_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_04.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw1_04_gp ) {
    0, 229,227,  1,
   15, 227,101,  3,
  142,  40,  1, 80,
  198,  17,  1, 79,
  255,   0,  0, 45};



  // Gradient palette "bhw1_28_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_28.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw1_28_gp ) {
    0,  75,  1,221,
   30, 252, 73,255,
   48, 169,  0,242,
  119,   0,149,242,
  170,  43,  0,242,
  206, 252, 73,255,
  232,  78, 12,214,
  255,   0,149,242};

// Gradient palette "bhw2_turq_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_turq.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw2_turq_gp ) {
    0,   1, 33, 95,
   38,   1,107, 37,
   76,  42,255, 45,
  127, 255,255, 45,
  178,  42,255, 45,
  216,   1,107, 37,
  255,   1, 33, 95};



// Gradient palette "bhw1_03_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_03.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

//DEFINE_GRADIENT_PALETTE( bhw1_03_gp ) {
  //  0,   0,  0,  0,
  //137,  11,112,153,
  //191,  40,219,105,
  //255, 255,255,255};

// Gradient palette "bhw2_38_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_38.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw2_38_gp ) {
    0, 104,205,212,
   28,  32,184,203,
   61,  39, 39,168,
   96,  46,  1,144,
  130,   8,  1, 22,
  163,  17,  3, 28,
  196,  24,  4, 31,
  255, 213,  9, 89};

// Gradient palette "bhw3_61_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw3/tn/bhw3_61.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw3_61_gp ) {
    0,  14,  1, 27,
   48,  17,  1, 88,
  104,   1, 88,156,
  160,   1, 54, 42,
  219,   9,235, 52,
  255, 139,235,233};



// Gradient palette "bhw1_15_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_15.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw1_15_gp ) {
    0,   1,  8, 87,
   71,  23,195,130,
  122, 186,248,233,
  168,  23,195,130,
  255,   1,  8, 87};


// Gradient palette "fruit_03_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ma/fruit/tn/fruit_03.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

DEFINE_GRADIENT_PALETTE( fruit_03_gp ) {
    
0,   2, 25,  3,
0,   2, 25,  3,
  10, 184, 22, 29,
  10, 184, 22, 29,
  20,   2, 25,  3,
20,   2, 25,  3,
30, 184, 22, 29,
  30, 184, 22, 29,
40,   2, 25,  3,
40,   2, 25,  3,
  50, 184, 22, 29,
  50, 184, 22, 29,
  150,   2, 25,  3,
150,   2, 25,  3,
180, 184, 22, 29,
  180, 184, 22, 29,
  220,   2, 25,  3,
220,   2, 25,  3,
255, 184, 22, 29,
  255, 184, 22, 29,
};


// Gradient palette "spring_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/h5/tn/spring.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 64 bytes of program space.

DEFINE_GRADIENT_PALETTE( spring_gp ) {
    0, 255,  0,255,
   17, 255,  1,212,
   33, 255,  2,178,
   51, 255,  7,145,
   68, 255, 13,115,
   84, 255, 22, 92,
  102, 255, 33, 71,
  119, 255, 47, 52,
  135, 255, 62, 37,
  153, 255, 82, 25,
  170, 255,104, 15,
  186, 255,127,  9,
  204, 255,156,  4,
  221, 255,186,  1,
  237, 255,217,  1,
  255, 255,255,  0};



// Gradient palette "bhw2_xc_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_xc.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw2_xc_gp ) {
    0,   4,  2,  9,
   58,  16,  0, 47,
  122,  24,  0, 16,
  158, 144,  9,  1,
  183, 179, 45,  1,
  219, 220,114,  2,
  255, 234,237,  1};


// Gradient palette "rainbow_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/rainbow.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 48 bytes of program space.

DEFINE_GRADIENT_PALETTE( rainbow_gp ) {
    0, 126,  1,142,
   25, 171,  1, 26,
   48, 224,  9,  1,
   71, 237,138,  1,
   94,  52,173,  1,
  117,   1,201,  1,
  140,   1,211, 54,
  163,   1,124,168,
  186,   1,  8,149,
  209,  12,  1,151,
  232,  12,  1,151,
  255, 171,  1,190};

// Gradient palette "GeeK07_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/heine/tn/GeeK07.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 2320 bytes of program space.

DEFINE_GRADIENT_PALETTE( GeeK07_gp ) {
    0, 255,255,255,
    0, 255,255,255,
    10,   0,  0,  0,
    10,   0,  0,  0,
    20, 255,255,255,
    20, 255,255,255,
    30,   0,  0,  0,
    30,   0,  0,  0,
    40, 255,255,255,
    40, 255,255,255,
    50,   0,  0,  0,
    50,   0,  0,  0,
    150, 255,255,255,
    150, 255,255,255,
    180,   0,  0,  0,
    180,   0,  0,  0,
    220, 255,255,255,
    220, 255,255,255,
    255,   0,  0,  0,
    255,   0,  0,  0
   };


// Gradient palette "bhw1_33_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_33.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw1_33_gp ) {
    0,   2,  1,  8,
   34,  79,  2,212,
  70, 110, 11,197,
  125,   2,  1,  8,
  150,   2,  1,  8,
  180,   2,  1,  8,
  200,   2,  1,  8,
  255,  79,  2,212};



void setup() {
    delay( 1000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN_1, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );

    currentPalette = GeeK07_gp;
    currentBlending = LINEARBLEND;

    pinMode(BUTTON_PIN, INPUT_PULLUP);
    ChangePalettePeriodically();
}

int create_new_blink_interval = 8000;
static unsigned long lastRefreshTime = 0;
void loop()
{
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors(startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);

    // Auto animate
    if(millis() - lastRefreshTime >= create_new_blink_interval) {
      lastRefreshTime += create_new_blink_interval;
      ChangePalettePeriodically();
      animationIndex++;
    }
    
    //Read the button
    buttonState = digitalRead(BUTTON_PIN);
    // check if the pushbutton is pressed - change animation
    if (buttonState == LOW) {
      delay(500);
      ChangePalettePeriodically();
      animationIndex++;
    }
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = START_SKIP_LEDS; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

void FillLEDsFromPaletteColorsAndShow( uint8_t colorIndex=0)
{
    uint8_t brightness = 255;
    
    for( int i = START_SKIP_LEDS; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
        FastLED.show();
    }
}


// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

void ChangePalettePeriodically()
{
  switch(animationIndex){
    case 1:
      currentPalette = GeeK07_gp;
      break;
    case 2:
     currentPalette = bhw1_28_gp;
     FastLED.setBrightness(5);
     break;
    case 3:
     currentPalette = bhw2_turq_gp;
     FastLED.setBrightness(20);
     break;
    case 4:
     currentPalette = bhw2_38_gp;
     UPDATES_PER_SECOND = 102;
     FastLED.setBrightness(30);
     break;
    case 5:
     currentPalette = bhw2_38_gp;
     UPDATES_PER_SECOND = 10;
     FastLED.setBrightness(5);
     break;
    case 6:
     currentPalette = spring_gp;
     UPDATES_PER_SECOND = 50;
     FastLED.setBrightness(10);
     break;
    case 7:
     currentPalette = bhw3_61_gp;
     UPDATES_PER_SECOND = 200;
     FastLED.setBrightness(20);
     break;
    case 8:
     currentPalette = bhw1_15_gp;
     UPDATES_PER_SECOND = 102;
     FastLED.setBrightness(30);
     
     //Go back to start
     animationIndex = 0;
     break;
  }
  currentBlending = LINEARBLEND;
  FillLEDsFromPaletteColorsAndShow();
}


//1 blackwhite, 2blue purple, 3 green blue ?, 4 ,5, 6torquiz, 7?geeen pink,8flame, 9? ,10rainbow
// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};



// Additionl notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact 
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved 
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.
