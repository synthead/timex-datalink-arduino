#ifndef NOTEBOOK_ADAPTER_H
#define NOTEBOOK_ADAPTER_H

#define COMMAND_PING 'x'
#define COMMAND_QUERY '?'
#define COMMAND_TRANSMIT 'U'
#define COMMAND_QUERY_PAYLOAD "M764"

#define PING_EXPIRE_MS 1000

#include <Arduino.h>

namespace NotebookAdapter {
  unsigned long last_ping_ms = 0;
  bool command_mode = true;

  void emulate_command_mode(uint8_t serial_byte) {
    switch(serial_byte) {
      case COMMAND_PING:
        Serial.write(COMMAND_PING);

        break;

      case COMMAND_QUERY:
        Serial.print(COMMAND_QUERY_PAYLOAD);
        Serial.write(0);

        break;

      case COMMAND_TRANSMIT:
        Serial.write(COMMAND_TRANSMIT);
        command_mode = false;

        break;
    }
  }

  void emulate_data_mode(uint8_t serial_byte) {
    if (millis() - last_ping_ms > PING_EXPIRE_MS) {
      command_mode = true;
    }

    Serial.write(serial_byte);

    last_ping_ms = millis();
  }

  void emulate(uint8_t serial_byte) {
    void(*function)(uint8_t) = command_mode ? emulate_command_mode : emulate_data_mode;

    function(serial_byte);
  }
}

#endif
