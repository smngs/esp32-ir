#include <Arduino.h>
#include <ArduinoOTA.h>
#include <WebServer.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#include <ir_Panasonic.h>

#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRutils.h>

#include <ArduinoJson.h>


const char *ssid = "M_Wi-Fi-N2";
const char *password = "mine_ims3071w";

const uint32_t kBaudRate = 115200;

const uint16_t kRecvPin = 14;
const uint16_t kIrLedPin = 4;
const uint16_t kCaptureBufferSize = 1024;
const uint8_t kTimeout = 50;
const uint16_t kFrequency = 38000;
