#define ARDUINOJSON_USE_LONG_LONG 1
#include "header.h"
#include <secret.h>

WebServer server(80); // HTTP を 80 番で待機する．
decode_results results;

void setup() {
  irSetup();
  Serial.begin(kBaudRate, SERIAL_8N1); // Serial 通信のスタート．

  // ボタン入力．GPIO 0 (Boot SW) を INPUT_PULLUP とする．
  pinMode(0, INPUT_PULLUP);

  WiFiSetup(); // Wi-Fi に接続．
  OTASetup();

  offAircon();
}

void loop() {
  // サーバーの情報更新．
  ArduinoOTA.handle();
  server.handleClient();
  recievedIR();
  sendIRTest();
}
