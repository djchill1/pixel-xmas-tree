// NeoPixel Christmas Tree powered by a nodeMCU.


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// must be prefixed by a "D" for nodeMCUs, but just a number for Arduino.
#define LED_PIN    D4

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 150
#define NUM_LEDS 150

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


long red_rand;
long blue_rand;
long green_rand;


// setup() function -- runs once at startup --------------------------------

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {

  meteorRain(strip.Color(random(0, 255),   random(0, 255),   random(0, 255)), 10, 64, true, 20);
  meteorRain(strip.Color(random(0, 255),   random(0, 255),   random(0, 255)), 10, 64, true, 20);
  meteorRain(strip.Color(random(0, 255),   random(0, 255),   random(0, 255)), 10, 64, true, 20);
  meteorRain(strip.Color(random(0, 255),   random(0, 255),   random(0, 255)), 10, 64, true, 20);
  meteorRain(strip.Color(random(0, 255),   random(0, 255),   random(0, 255)), 10, 64, true, 20);

  //CylonBounce(0xff, 0, 0xff, 4, 10, 50);
  Sparkle(strip.Color(0, 255, 255), 0, 1000);
  //meteorRain(0xff,0xff,0xff,10, 64, true, 30);
  dissolveIn(strip.Color(random(0, 255),   random(0, 255),   random(0, 255)), 0, 1000);
  dissolveIn(strip.Color(random(0, 255),   random(0, 255),   random(0, 255)), 0, 1000);
  dissolveIn(strip.Color(random(0, 255),   random(0, 255),   random(0, 255)), 0, 1000);

  // Fill along the length of the strip in various colors...
  colorWipe(strip.Color(random(0, 255),   random(0, 255),   random(0, 255)), 15);
  colorWipeDown(strip.Color(random(0, 255),   random(0, 255),   random(0, 255)), 15);
  colorWipe(strip.Color(random(0, 255),   random(0, 255),   random(0, 255)), 15);
  colorWipeDown(strip.Color(random(0, 255),   random(0, 255),   random(0, 255)), 30);
  colorWipe(strip.Color(random(0, 255),   random(0, 255),   random(0, 255)), 30);
  colorWipeDown(strip.Color(random(0, 255),   random(0, 255),   random(0, 255)), 30);

  rainbow(10);             // Flowing rainbow cycle along the whole strip
  // shimmer(strip.Color(198,80,231),strip.Color(236,200,54),20000,25); // shimmer time.

  shimmer(strip.Color(random(0, 255),   random(0, 255),   random(0, 255)), strip.Color(random(0, 255),   random(0, 255),   random(0, 255)), 20000, 25);
  shimmer(strip.Color(random(0, 255),   random(0, 255),   random(0, 255)), strip.Color(random(0, 255),   random(0, 255),   random(0, 255)), 20000, 25);

  red_rand = random(0, 255);
  green_rand = random(0, 255);
  blue_rand = random(0, 255);
  fade(strip.Color(random(0, 255),   random(0, 255),   random(0, 255)), strip.Color(red_rand, green_rand, blue_rand), 5000);
  fade(strip.Color(red_rand, green_rand, blue_rand), strip.Color(0, 0, 0), 5000); // fade to black

  //fade(strip.Color(198,80,231),strip.Color(72,209,204),5000); // fade purple to turquoise.
  //fade(strip.Color(72,209,204),strip.Color(0,0,0),5000); // fade to black.
}


// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}


void colorWipeDown(uint32_t color, int wait) {
  for (int i = strip.numPixels(); i >= 0; i--) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}


void shimmer(uint32_t c_base, uint32_t c_shimmer, uint32_t duration, uint32_t amount)
{
  uint32_t shimmer_pixel_num[amount];
  float    shimmer_pixel_percent[amount];
  uint32_t elapsed_time = 0;

  for (uint16_t i = 0; i < amount; i++)
  {
    shimmer_pixel_num[i] = 0;
  }

  for (uint16_t i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, c_base);
  }

  while (elapsed_time < duration)
  {
    // See if we should start a shimmer
    for (uint16_t i = 0; i < amount; i++)
    {
      if (shimmer_pixel_num[i] == 0 & random(10) > 8)
      { shimmer_pixel_num[i] = random(199) + 1;
        shimmer_pixel_percent[i] = 0.0;
      }
      if (shimmer_pixel_num[i] > 0)
      {
        if (i % 2 == 0)
        {
          shimmer_pixel_percent[i] += 0.02;
        }
        else
        {
          shimmer_pixel_percent[i] += 0.04;
        }
        if (shimmer_pixel_percent[i] >= 2.0)
        {
          strip.setPixelColor(shimmer_pixel_num[i], c_base);
          shimmer_pixel_num[i] = 0;
        }
        else
        {
          strip.setPixelColor(shimmer_pixel_num[i], colorSlope(c_shimmer, c_base, abs(1.0 - shimmer_pixel_percent[i])));
        }
      }
    }

    strip.show();
    delay(50);
    elapsed_time += 50 + 5 ;
  }

  for (uint16_t i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, c_base);
  }
  strip.show();

}

// fade lights from colour a to b.
void fade(uint32_t c_from, uint32_t c_to, uint32_t duration)
{
  uint32_t elapsed_time = 0;
  uint32_t temp_color;


  while (elapsed_time < duration)
  {
    temp_color = colorSlope(c_from, c_to, float(elapsed_time) / float(duration));

    for (uint16_t i = 0; i < strip.numPixels(); i++)
    {
      strip.setPixelColor(i, temp_color);
    }

    strip.show();
    delay(50);
    elapsed_time += 55;

  }
  for (uint16_t i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, c_to);
  }
  strip.show();

}

uint32_t colorSlope(uint32_t c1, uint32_t c2, float percent)
{
  uint32_t temp_color, temp_c1_component, temp_c2_component;

  temp_color = 0;
  temp_c1_component = (c1 & 0x00ff0000) >> 16;
  temp_c2_component = (c2 & 0x00ff0000) >> 16;
  temp_color = uint32_t(temp_c1_component + (float(temp_c2_component) - float(temp_c1_component)) * percent);
  temp_color = temp_color << 8;

  temp_c1_component = (c1 & 0x0000ff00) >> 8;
  temp_c2_component = (c2 & 0x0000ff00) >> 8;
  temp_color += uint32_t(temp_c1_component + (float(temp_c2_component) - float(temp_c1_component)) * percent);
  temp_color = temp_color << 8;

  temp_c1_component = (c1 & 0x000000ff);
  temp_c2_component = (c2 & 0x000000ff);
  temp_color += uint32_t(temp_c1_component + (float(temp_c2_component) - float(temp_c1_component)) * percent);

  return temp_color;
}



void Sparkle(uint32_t sparkle_color, int SpeedDelay, int duration) {
  uint32_t elapsed_time = 0;

  while (elapsed_time < duration) {
    int Pixel = random(strip.numPixels());
    strip.setPixelColor(Pixel, sparkle_color);
    strip.show();
    delay(SpeedDelay);
    strip.setPixelColor(Pixel, strip.Color(0,0,0));
    elapsed_time += 1;
  }
}


void dissolveIn(uint32_t base_color, int SpeedDelay, int duration) {
  uint32_t elapsed_time = 0;

  while (elapsed_time < duration) {
    int Pixel = random(strip.numPixels());
    strip.show();
    delay(SpeedDelay);
    strip.setPixelColor(Pixel, base_color);
    elapsed_time += 1;
  }
}

void fadeToBlack(int ledNo, byte fadeValue) {
#ifdef ADAFRUIT_NEOPIXEL_H
  // NeoPixel
  uint32_t oldColor;
  uint8_t r, g, b;
  int value;

  oldColor = strip.getPixelColor(ledNo);
  r = (oldColor & 0x00ff0000UL) >> 16;
  g = (oldColor & 0x0000ff00UL) >> 8;
  b = (oldColor & 0x000000ffUL);

  r = (r <= 10) ? 0 : (int) r - (r * fadeValue / 256);
  g = (g <= 10) ? 0 : (int) g - (g * fadeValue / 256);
  b = (b <= 10) ? 0 : (int) b - (b * fadeValue / 256);

  strip.setPixelColor(ledNo, r, g, b);
#endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  leds[ledNo].fadeToBlackBy( fadeValue );
#endif
}




void meteorRain(uint32_t base_color, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
  strip.Color(0,0,0);
  
  for(int i = 0; i < strip.numPixels(); i++) {
    
    
    // fade brightness all LEDs one step
    for(int j=0; j<strip.numPixels(); j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
    
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <strip.numPixels()) && (i-j>=0) ) {
        strip.setPixelColor(i-j, base_color);
      } 
    }
   
    strip.show();
    delay(SpeedDelay);
  }
}
