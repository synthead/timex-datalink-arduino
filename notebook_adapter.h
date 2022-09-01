#ifndef NOTEBOOK_ADAPTER_H
#define NOTEBOOK_ADAPTER_H

#include <Arduino.h>

namespace NotebookAdapter {
  void emulate_command_mode(uint8_t serial_byte);
  void emulate_data_mode(uint8_t serial_byte);
  void emulate(uint8_t serial_byte);
}

#endif
