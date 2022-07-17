IRPanasonicAc ac(kIrLedPin);

void offAircon() {
  ac.setModel(kPanasonicLke);
  ac.off();
  ac.send();
}

void heatAircon(int temp) {
  ac.setModel(kPanasonicLke);
  ac.on();

  ac.setFan(kPanasonicAcFanAuto);
  ac.setMode(kPanasonicAcHeat);
  ac.setTemp(temp);

  ac.send();
}

void coolAircon(int temp) {
  ac.setModel(kPanasonicLke);
  ac.on();

  ac.setFan(kPanasonicAcFanAuto);
  ac.setMode(kPanasonicAcCool);
  ac.setTemp(temp);

  ac.send();
}

void testAircon() {
  ac.begin();

  // 寝室のエアコンは kPanasonicLke で動作確認 OK．
  ac.setModel(kPanasonicLke);
  ac.on();
  ac.setFan(kPanasonicAcFanAuto);
  ac.setMode(kPanasonicAcCool);
  ac.setTemp(26);
  ac.setSwingVertical(kPanasonicAcSwingVAuto);
  ac.setSwingHorizontal(kPanasonicAcSwingHAuto);

  ac.send();
  Serial.println("sended");

  delay(5000);

  ac.setOnTimer(60, true);
  ac.send();
  Serial.println(ac.isOnTimerEnabled());

  delay(5000);

  ac.off();
  ac.send();
  Serial.println(ac.isOnTimerEnabled());
}

