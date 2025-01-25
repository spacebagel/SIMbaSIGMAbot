void sendATCommand(String command) {
  Serial.println("Sending: " + command);
  sim800l.println(command);
  delay(4000);
  while (sim800l.available()) {
    Serial.write(sim800l.read());
  }
}

void receiverConfig() {
  Serial.println("Initializing SIM800L...");

  sendATCommand("AT");
  sendATCommand("AT+CMGF=1");
  sendATCommand("AT+CSCS=\"UCS2\"");
  sendATCommand("AT+CNMI=1,2,0,0,0");

  Serial.println("SIM800L is ready to receive SMS...");
}