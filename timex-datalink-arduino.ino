#define LED_PIN 13

#define LED_ON_MS 35
#define LED_OFF_MS 460

#define COMMAND_PING 'x'
#define COMMAND_QUERY '?'
#define COMMAND_TRANSMIT 'U'
#define HANDSHAKE_PAYLOAD "M764"

#define PING_EXPIRE_MS 1000

unsigned long last_ping_ms = 0;
bool command_mode = true;

void led_emit_0() {
  digitalWrite(LED_PIN, HIGH);
  delayMicroseconds(LED_ON_MS);

  digitalWrite(LED_PIN, LOW);
  delayMicroseconds(LED_OFF_MS);
}

void led_emit_1() {
  delayMicroseconds(LED_ON_MS + LED_OFF_MS);
}

void led_emit_byte(uint8_t serial_byte) {
  led_emit_0();

  for (int i = 0; i < 8; i++) {
    bitRead(serial_byte, i) ? led_emit_1() : led_emit_0();
  }
}

void emulate_notebook_adapter_command(uint8_t serial_byte) {
  switch(serial_byte) {
    case COMMAND_PING:
      Serial.write(COMMAND_PING);

      break;

    case COMMAND_QUERY:
      Serial.print(HANDSHAKE_PAYLOAD);
      Serial.write(0);

      break;

    case COMMAND_TRANSMIT:
      Serial.write(COMMAND_TRANSMIT);
      command_mode = false;

      break;
  }
}

void emulate_notebook_adapter_data(uint8_t serial_byte) {
  if (millis() - last_ping_ms > PING_EXPIRE_MS) {
    command_mode = true;
  }

  Serial.write(serial_byte);

  last_ping_ms = millis();
}

void emulate_notebook_adapter(uint8_t serial_byte) {
  void(*function)(uint8_t) = command_mode ? emulate_notebook_adapter_command : emulate_notebook_adapter_data;

  function(serial_byte);
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int serial_byte = Serial.read();

  if (serial_byte == -1) {
    return;
  }

  led_emit_byte(serial_byte);
  emulate_notebook_adapter(serial_byte);
}
