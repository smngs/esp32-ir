
IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, false);
IRsend irsend(kIrLedPin);

void irSetup() {
  irrecv.enableIRIn();
  irsend.begin();
}

void sendSony() {
  // ここらへん，もっときれいにする余地がある．
  String postResponse = server.arg("plain");
  const size_t capacity = 1536; // 適当に大きく取ったけど，Overflow するかも．注意．
  DynamicJsonDocument jsonResponse(capacity);

  // JSON の deserialize．
  DeserializationError error = deserializeJson(jsonResponse, postResponse);

  // if (!error) {
    uint64_t data = jsonResponse["data"].as<uint64_t>(); // data は 10 進数でなきゃいけない．めんどくさいね．
    uint16_t nbits = jsonResponse["nbits"].as<uint16_t>();

    irsend.sendSony(data, nbits, 5); // 5 回リピートする．テストだけど．
    String message = "{\"result\": \"done\"}";
    Serial.println(message);
    server.send(200, "application/json", message);

  // } else {
    // エラー時の処理．
  //   String message = "{\"error\": \"Response is invaild\"}";
  //   Serial.println(message);
  //   server.send(503, "application/json", message);
  // }
}

void sendAircon() {
  String postResponse = server.arg("plain");
  const size_t capacity = 1536; // 適当に大きく取ったけど，Overflow するかも．注意．
  DynamicJsonDocument jsonResponse(capacity);

  // JSON の deserialize．
  DeserializationError error = deserializeJson(jsonResponse, postResponse);

  String message;
  int status;

  if(jsonResponse["power"] == "off") {
    offAircon();
    message = "{\"result\": \"done\"}";
    status = 200;
  } else {
    message = "{\"result\": \"power is invaild\"}";
    status = 503;
  }

  if (jsonResponse["power"] == "on") {
    if (jsonResponse["mode"] == "heat") {
      heatAircon(jsonResponse["temp"]);
      message = "{\"result\": \"done\"}";
      status = 200;
    }
    else if (jsonResponse["mode"] == "cool") {
      coolAircon(jsonResponse["temp"]);
      message = "{\"result\": \"done\"}";
      status = 200;
    }
    else {
      message = "{\"result\": \"mode not found\"}";
      status = 503;
    }
  }

    server.send(status, "application/json", message);
  }

void sendRaw() {
  String postResponse = server.arg("plain");
  const size_t capacity = 1536; // 適当に大きく取ったけど，Overflow するかも．注意．
  DynamicJsonDocument jsonResponse(capacity);

  // JSON の deserialize．
  DeserializationError error = deserializeJson(jsonResponse, postResponse);

  // ここでエラーハンドリングする．
  if (!error) {
    // IRDataLength の取得と IRData の確保．
    uint16_t IRDataLength = jsonResponse["IRDataLength"].as<uint16_t>();
    uint16_t IRData[IRDataLength];

    // deserialize した結果を，要素ごとに配列 IRData に書き込む．
    for (int i = 0; i < IRDataLength; i++) {
      IRData[i] = jsonResponse["IRData"][i].as<uint16_t>();
    }

    irsend.sendRaw(IRData, IRDataLength, kFrequency);

    String message = "{\"result\": \"done\"}";
    Serial.println(message);
    server.send(200, "application/json", message);

  } else {
    // エラー時の処理．
    String message = "{\"error\": \"Response is invaild\"}";
    Serial.println(message);
    server.send(503, "application/json", message);
  }
}

void recievedIR() {
  if (irrecv.decode(&results)) {
    StaticJsonDocument<1536> recievedIRjson;

    recievedIRjson["decodeType"] = typeToString(results.decode_type);
    recievedIRjson["hexCode"] = resultToHexidecimal(&results);
    recievedIRjson["codeLength"] = results.bits;

    Serial.println(serializeJson(recievedIRjson, Serial));
    // Serial.println(resultToTimingInfo(&results));

    irrecv.resume();
  }
}

void sendIRTest() {
  if (digitalRead(0) ==
      LOW) { // INPUT_PULLUP に設定したため，論理値が逆になっている．注意．
    // 自身が発信した信号を再び受け取って，想定外の動作をする．動作確認用．
    irsend.sendRaw(resultToRawArray(&results), getCorrectedRawLength(&results),
                   kFrequency);
    Serial.println("Send previous IR data.");
  }
}

