#define LED_PIN 13

#define LED_ON_MS 35
#define LED_OFF_MS 460

#define HANDSHAKE_STOP 'U'
#define HANDSHAKE_START '?'
#define HANDSHAKE_PAYLOAD "126\r M764 rev 764002"

#define PING_EXPIRE_MS 1000

unsigned long last_ping_ms = 0;
bool send_handshake = true;

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

void emulate_notebook_adapter(uint8_t serial_byte) {
  if (millis() - last_ping_ms > PING_EXPIRE_MS) {
    send_handshake = true;
  }

  Serial.write(serial_byte);

  switch(serial_byte) {
    case HANDSHAKE_START:
      if (send_handshake) {
        Serial.print(HANDSHAKE_PAYLOAD);
        Serial.write(0);
      }

      return;

    case HANDSHAKE_STOP:
      send_handshake = false;

      break;
  }

  last_ping_ms = millis();
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
