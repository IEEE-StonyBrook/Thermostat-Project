// Some parts copyright, Peter H Anderson, Baltimore, MD, Nov, '11
// Updated and library-ified by Frederick Brunn 2015

#if defined(ARDUINO) && ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#define HIH6130_ADDRESS 0x27
#include <Wire.h>

class HIH6130 {

public:
  HIH6130();
  
  byte fetch_humidity_temperature(unsigned int *p_H_dat, unsigned int *p_T_dat);
};

