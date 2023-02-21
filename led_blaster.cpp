#define LED_PIN 13

#define LED_ON_MS_NORMAL 15
#define LED_OFF_MS_NORMAL 450

#define LED_ON_MS_FAST 6
#define LED_OFF_MS_FAST 408

#include <Arduino.h>

namespace LedBlaster {
  uint16_t led_on_ms;
  uint16_t led_off_ms;

  void enable_fast_mode(bool fast_mode_enabled) {
    if (fast_mode_enabled) {
      led_on_ms = LED_ON_MS_FAST;
      led_off_ms = LED_OFF_MS_FAST;
    } else {
      led_on_ms = LED_ON_MS_NORMAL;
      led_off_ms = LED_OFF_MS_NORMAL;
    }
  }

  void setup() {
    pinMode(LED_PIN, OUTPUT);
    enable_fast_mode(false);
  }

  void emit_0() {
    digitalWrite(LED_PIN, HIGH);
    delayMicroseconds(led_on_ms);

    digitalWrite(LED_PIN, LOW);
    delayMicroseconds(led_off_ms);
  }

  void emit_1() {
    delayMicroseconds(led_on_ms + led_off_ms);
  }

  void emit_byte(uint8_t serial_byte) {
    emit_0();

    for (int i = 0; i < 8; i++) {
      bitRead(serial_byte, i) ? emit_1() : emit_0();
    }
  }
}
