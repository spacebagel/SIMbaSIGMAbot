#include <SoftwareSerial.h>
#include <FastBot2.h>
#include "config.h"
#include "tgBot.h"
#include "converter.h"
#include "simModule.h"
#include "network.h"

void setup() {
  Serial.begin(115200);
  sim800l.begin(9600);

  connectWiFI();
  receiverConfig();
  botConfig();
}

void loop() {
  if (sim800l.available()) {
    String response = sim800l.readString();
    //Serial.println("Received: " + response);
    if (response.indexOf("+CMT:") != -1) processSMSResponse(response);
  }

  if (Serial.available()) sim800l.write(Serial.read());

  bot.tick();
}