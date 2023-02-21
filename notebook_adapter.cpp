#define COMMAND_PING 'x'
#define COMMAND_QUERY '?'
#define COMMAND_TRANSMIT 'U'
#define COMMAND_QUERY_PAYLOAD "?107\r M764 rev 764100"

#define DATA_MODE_TIMEOUT_MS 1000

#include <Arduino.h>

namespace NotebookAdapter {
  unsigned long last_data_ms = 0;
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
    if (millis() - last_data_ms > DATA_MODE_TIMEOUT_MS) {
      command_mode = true;
    }

    Serial.write(serial_byte);

    last_data_ms = millis();
  }

  void emulate(uint8_t serial_byte) {
    void(*function)(uint8_t) = command_mode ? emulate_command_mode : emulate_data_mode;

    function(serial_byte);
  }
}
