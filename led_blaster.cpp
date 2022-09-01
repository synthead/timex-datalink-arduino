#define LED_PIN 13

#define LED_ON_MS 35
#define LED_OFF_MS 460

#include <Arduino.h>

namespace LedBlaster {
  void setup() {
    pinMode(LED_PIN, OUTPUT);
  }

  void emit_0() {
    digitalWrite(LED_PIN, HIGH);
    delayMicroseconds(LED_ON_MS);

    digitalWrite(LED_PIN, LOW);
    delayMicroseconds(LED_OFF_MS);
  }

  void emit_1() {
    delayMicroseconds(LED_ON_MS + LED_OFF_MS);
  }

  void emit_byte(uint8_t serial_byte) {
    emit_0();

    for (int i = 0; i < 8; i++) {
      bitRead(serial_byte, i) ? emit_1() : emit_0();
    }
  }
}
