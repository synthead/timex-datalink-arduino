#include "led_blaster.h"
#include "notebook_adapter.h"

void setup() {
  Serial.begin(9600);
  LedBlaster::setup();
}

void loop() {
  int serial_byte = Serial.read();

  if (serial_byte != -1) {
    NotebookAdapter::emulate(serial_byte);
    LedBlaster::emit_byte(serial_byte);
  }
}
