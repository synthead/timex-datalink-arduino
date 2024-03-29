#ifndef LED_BLASTER_H
#define LED_BLASTER_H

#include <Arduino.h>

namespace LedBlaster {
  void setup();
  void enable_fast_mode(bool fast_mode_enabled);
  void emit_0();
  void emit_1();
  void emit_byte(uint8_t serial_byte);
}

#endif
