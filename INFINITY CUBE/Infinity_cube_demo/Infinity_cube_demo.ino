#include <FastLED.h>
#include "IRremote.h"

// How many leds in your strip?
#define NUM_LEDS 216
#define SKLOP 9

#define BRIGHTNESS  255




int  mode = 0;







// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3

//stranice

//LEGENDA//
/*
 *STRANICE
F... FRONT(SPREDNJA)
L... LEFT(LEVA)
R... RIGHT(DESNA)
B... BACK(ZADNJA)
C... CIELING(STROP)
G... GROUND(TLA)

  *DEL OBROČA (POGLED OD SPREDAJ)
L... LEVA
R... DESNA
U... UP
D... DOWN

FORMAT = STRANICA|DEL OBROČA


            :ddsssssssssssssssssssssssssssssssshmm
          /doyy                              .yyoM
        /ho` sy                            -yy- :M
      +d+`   sy                          -hy.   :M
   `+d+      sy                        :hs.     :M
 `od/        sy                      :ho`       :M
/Nmooooooooo+dmooooooooooooooooooooodo`         :M
ss```````````yh````````````````````sm           :M
so           sy                    sm           :M
so           sy                    sm           -M
so           sy                    om           :M
so           sy                    om           :M
so           sy                    om           :M
so           sy                    om           :M
so           sy                    om           :M
so           sy                    om           :M
so           sy                    +m           :M
so           sh                    sm           :M
so         `odooooooooooooooooooooohNoooooooooodNs
so       `oh/                      om        :hs. 
so     .sh:                        om      :hs`   
so   .sh-                          om    /do`     
so .yy-                            om  /do`       
syyy.                              om+do`         
oNhsssssssssssssssssssssssssssssssshm+`        



*/




//Sprednja stranica
#define FL 0
#define FU FL+SKLOP
#define FR FU+SKLOP
#define FD FR+SKLOP

//Leva stranica
#define LD FD+SKLOP
#define LR GD+SKLOP
#define LU LR+SKLOP
#define LL LU+SKLOP


//zadnja stranica
#define BD LD+SKLOP
#define BU RU+SKLOP
#define BL BU+SKLOP
#define BR CU+SKLOP



//Desna stranica
#define RD BD+SKLOP
#define RL RD+SKLOP
#define RU RL+SKLOP
#define RR GU+SKLOP

//Spodnja stranica
#define GU BL+SKLOP
#define GR BR+SKLOP
#define GD GR+SKLOP
#define GL LL+SKLOP


//Zgornja stranica
#define CR RR+SKLOP
#define CD CR+SKLOP
#define CL CD+SKLOP
#define CU CL+SKLOP




//DEFINICIJE središč stranic za olajšanje dela PREFIX S_

//Sprednja stranica
#define S_FL FL+SKLOP/2+1
#define S_FU FU+SKLOP/2+1
#define S_FR FR+SKLOP/2+1
#define S_FD FD+SKLOP/2+1

//Leva stranica
#define S_LD LD+SKLOP/2+1
#define S_LR LR+SKLOP/2+1
#define S_LU LU+SKLOP/2+1
#define S_LL LL+SKLOP/2+1


//zadnja stranica
#define S_BD BD+SKLOP/2+1
#define S_BU BU+SKLOP/2+1
#define S_BL BL+SKLOP/2+1
#define S_BR BR+SKLOP/2+1



//Desna stranica
#define S_RD RD+SKLOP/2+1
#define S_RL RL+SKLOP/2+1
#define S_RU RU+SKLOP/2+1
#define S_RR RR+SKLOP/2+1

//Spodnja stranica
#define S_GU GU+SKLOP/2+1
#define S_GR GR+SKLOP/2+1
#define S_GD GD+SKLOP/2+1
#define S_GL GL+SKLOP/2+1


//Zgornja stranica
#define S_CR CR+SKLOP/2+1
#define S_CD CD+SKLOP/2+1
#define S_CL CL+SKLOP/2+1
#define S_CU CU+SKLOP/2+1




#define NEXT LL+SKLOP







int side = RD;
//Reciever
int receiver = 11;


IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'
// describing Remote IR codes 


void translateIR() // takes action based on IR code received
{

  switch(results.value)

  {
  case 0xFFA25D: Serial.println("POWER"); break;
  case 0xFFE21D: Serial.println("FUNC/STOP"); break;
  case 0xFF629D: Serial.println("VOL+"); break;
  case 0xFF22DD: Serial.println("FAST BACK");    break;
  case 0xFF02FD: Serial.println("PAUSE");    break;
  case 0xFFC23D: Serial.println("FAST FORWARD");   break;
  case 0xFFE01F: Serial.println("DOWN");    break;
  case 0xFFA857: Serial.println("VOL-");    break;
  case 0xFF906F: Serial.println("UP");    break;
  case 0xFF9867: Serial.println("EQ");    break;
  case 0xFFB04F: Serial.println("ST/REPT");    break;
  case 0xFF6897: Serial.println("0");mode = 0;    break;
  case 0xFF30CF: Serial.println("1");mode = 1;    break;
  case 0xFF18E7: Serial.println("2");mode = 2;    break;
  case 0xFF7A85: Serial.println("3");mode = 3;    break;
  case 0xFF10EF: Serial.println("4");mode = 4;    break;
  case 0xFF38C7: Serial.println("5");mode = 5;    break;
  case 0xFF5AA5: Serial.println("6");mode = 6;    break;
  case 0xFF42BD: Serial.println("7");mode = 7;    break;
  case 0xFF4AB5: Serial.println("8");mode = 8;    break;
  case 0xFF52AD: Serial.println("9");mode = 9;    break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

  default: 
    Serial.println(" other button   ");

  }// End Case
}





// Define the array of leds
CRGB leds[NUM_LEDS];
/*
int  sensorAnalogPin = A0;    // Select the Arduino input pin to accept the Sound Sensor's analog output 
int  sensorDigitalPin = 7;    // Select the Arduino input pin to accept the Sound Sensor's digital output
int  analogValue = 0;         // Define variable to store the analog value coming from the Sound Sensor
int  digitalValue; 
*/

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


void setup() {
      //srand(time(NULL));
Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver

    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;



      
      FastLED.setBrightness(5);

      FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  	  //FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
/*
      pinMode(sensorDigitalPin,INPUT);
      Serial.begin(9600);
      pinMode(13,OUTPUT);
      digitalWrite(13, HIGH);

      */
      //setup sequence
  for (int k = 0; k < 3; k++)
  {
    for(int i = 0; i < NUM_LEDS; i++)
      leds[i] = CRGB::Red;

     for (int i = 0; i< SKLOP; i++)
      leds[FD+i] = CRGB::Green;
      
    FastLED.show();
    delay(350);
    // Now turn the LED off, then pause
    for(int i = 0; i < NUM_LEDS;i++)
      leds[i] = CRGB::Black;
    FastLED.show();
    delay(350);
  }
      FastLED.setBrightness(BRIGHTNESS); 
   

}

void loop() { 
  /*
  analogValue = analogRead(sensorAnalogPin); // Read the value of the analog interface A0 assigned to digitalValue 
  digitalValue=digitalRead(sensorDigitalPin); // Read the value of the digital interface 7 assigned to digitalValue 
  Serial.println(analogValue);

  
*/
//leds[BD] = CRGB::Green;
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR(); 
    irrecv.resume();// receive the next value
  }  

  
  // Turn the LED on, then pause
  if (mode == 9)
  {
    for(int i = 0; i < SKLOP; i++)
      leds[side + i] = CRGB::Green;
    FastLED.show();
    delay(500);
    // Now turn the LED off, then pause
    for(int i = 0; i < SKLOP;i++)
      leds[side + i] = CRGB::Black;
    FastLED.show();
    if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR(); 
    irrecv.resume();// receive the next value
  }  
    delay(500);
  }


  
if (mode == 8)
{
  for(int i = 0; i < NUM_LEDS; i++)
  {
    leds[NUM_LEDS-i] = CRGB:: Blue;
    leds[i] = CRGB:: Red;

    FastLED.show();
    if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR(); 
    irrecv.resume();// receive the next value
  }  
    delay(10);
  } 
}



//Vse stranice enake
if (mode == 7)
{
CRGB stra[SKLOP]= {CRGB:: Green,CRGB:: Red,CRGB:: Blue, CRGB:: Blue,CRGB:: Purple, CRGB:: Blue, CRGB:: Blue, CRGB:: Red, CRGB:: Green};

for(int i = 0; i < 216;)
  for(int j = 0; j < 9; j++)
  {
     leds[i]=stra[j];
     i++;
  }  
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR(); 
    irrecv.resume();// receive the next value
  }  
FastLED.show();
}


//Minecraft tesseract

if (mode == 6)
{
  CRGB T_COLORS[23] = {0x020707, 0x020808, 0x091414, 0x0A1818, 0x0E3231, 0x0D2F2F, 0x0B1F1F, 0x0A1C1C, 0x0C2A2A, 0x091111, 0x0A1D1C, 0x091717, 0x070F0F, 0x091716, 0x091C1C, 0x08110F, 0x081C1C, 0x070D0C, 0x091111, 0x0B1F1F, 0x081312, 0x103938, 0x0E2626};
  for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = T_COLORS[random(23)%23];
  FastLED.show();
    
    if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR(); 
    irrecv.resume();// receive the next value
    delay(75);
  }  
}   


//sound reactive
if (mode == 5)
{
  CRGB stra[SKLOP];
  
for(int i = 0; i < SKLOP; i++)
 leds[i] = CRGB::Cyan;
/*
if(analogValue > 50)
  stra = {CRGB::Cyan, CRGB::Cyan, CRGB::Cyan, CRGB::Cyan, CRGB::Blue, CRGB::Cyan, CRGB::Cyan, CRGB::Cyan, CRGB::Cyan};
  
if(analogValue > 100)
  stra = {CRGB::Cyan, CRGB::Cyan, CRGB::Cyan, CRGB:: Blue, CRGB:: Blue, CRGB:: Blue, CRGB::Cyan, CRGB::Cyan, CRGB::Cyan};
  
if(analogValue > 150)
  stra = {CRGB::Cyan, CRGB::Cyan, CRGB:: DarkBlue, CRGB:: DarkBlue, CRGB:: DarkBlue, CRGB:: DarkBlue, CRGB:: DarkBlue, CRGB::Cyan, CRGB::Cyan}; 

if(analogValue > 250)
  stra = {CRGB:: Yellow, CRGB::Orange, CRGB::Orange, CRGB::Orange, CRGB::Orange, CRGB::Orange, CRGB::Orange, CRGB::Orange, CRGB::Yellow};

if(analogValue > 300)
  stra = {CRGB:: Red, CRGB:: Red, CRGB:: Red, CRGB:: Red, CRGB:: Red, CRGB:: Red, CRGB:: Red, CRGB:: Red, CRGB:: Red}
*/

for(int i = 0; i < 216;)
  for(int j = 0; j < 9; j++)
  {
     leds[i]=stra[j];
     i++;
  }  
FastLED.show();
if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR(); 
    irrecv.resume();// receive the next value
  }  
delay(50);
}



if (mode == 0)
{
    ChangePalettePeriodically();
    
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(10);
}


/*
CRGB plosk[36];
for(int i = 0;  i < 36 ; i++)
  {
    plosk[i] = CRGB::Blue;
    if(i)
      plosk [i-1] = CRGB :: DarkBlue;
  }



for (int i = 0; 36 > i;)
{
  for (int j = 0; j < SKLOP; j++)
    {
      leds[FR+j] = plosk[i];
      i++;
    }
    for (int j = 0; j < SKLOP; j++)
    {
      leds[FL+j] = plosk[i+18];
      i++;
    }
    for (int j = 0; j < SKLOP; j++)
    {
      leds[FU+j] = plosk[i+9];
      i++;
    }
    for (int j = 0; j < SKLOP; j++)
    {
      leds[FD+j] = plosk[i+27];
      i++;
    }
    FastLED.show();
    delay(200);
}
*/



}
void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
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
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
    }
}

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
