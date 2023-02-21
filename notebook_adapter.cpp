#define COMMAND_QUERY '?'
#define COMMAND_TRANSMIT 'U'
#define COMMAND_QUERY_PAYLOAD "107\r M764 rev 764100"

#define DATA_MODE_TIMEOUT_MS 1000

#include <Arduino.h>

namespace NotebookAdapter {
  unsigned long last_data_ms = 0;
  bool command_mode = true;

  void emulate(uint8_t serial_byte) {
    if (millis() - last_data_ms > DATA_MODE_TIMEOUT_MS) {
      command_mode = true;
    }

    Serial.write(serial_byte);

    switch(serial_byte) {
      case COMMAND_QUERY:
        if (command_mode) {
          Serial.print(COMMAND_QUERY_PAYLOAD);
          Serial.write(0);
        }

        break;
      case COMMAND_TRANSMIT:
        command_mode = true;

        break;
    }

    last_data_ms = millis();
  }
}
