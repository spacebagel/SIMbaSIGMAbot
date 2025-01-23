#include <SoftwareSerial.h>
#include <FastBot2.h>
#include "config.h"
#include "converter.h"
#include "tgBot.h"

SoftwareSerial sim800l(SIM800L_RX, SIM800L_TX);
FastBot2 bot;

void sendATCommand(String command) {
  Serial.println("Sending: " + command);
  sim800l.println(command);
  delay(4000);
  while (sim800l.available()) {
    Serial.write(sim800l.read());
  }
}

void setup() {
  Serial.begin(115200);
  sim800l.begin(9600);

  Serial.println("Connecting Wi-Fi...");
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
  }
  Serial.println("WiFi connected");

  Serial.println("Initializing SIM800L...");
  
  sendATCommand("AT");
  sendATCommand("AT+CMGF=1");
  sendATCommand("AT+CSCS=\"UCS2\"");
  sendATCommand("AT+CNMI=1,2,0,0,0");

  Serial.println("SIM800L is ready to receive SMS...");

  bot.attachUpdate(updateh);   // подключить обработчик обновлений
  bot.setToken(F(BOT_TOKEN));  // установить токен
  bot.setPollMode(fb::Poll::Long, 20000);
  bot.sendMessage(fb::Message("The SIMba system is running!", CHAT_ID));
}

void loop() {
  if (sim800l.available()) {
    String response = sim800l.readString();
    Serial.println("Received: " + response);

    if (response.indexOf("+CMT:") != -1) {
      int index = response.indexOf("\"");
      String phoneNumber = response.substring(index + 1, response.indexOf("\"", index + 1));

      index = response.indexOf("\n");
      String message = response.substring(index + 1);

      index = message.indexOf("\n");
      message = message.substring(index + 1);
      Serial.println("Message Text: " + message);

      message.trim();
      String decodedMessage = convertUCS2ToString(message);

      bot.sendMessage(fb::Message(decodedMessage, CHAT_ID));

      Serial.println("Message From: " + phoneNumber);
      Serial.println("Decoded Message: " + decodedMessage);
    }
  }

  if (Serial.available()) {
    sim800l.write(Serial.read());
  }

  bot.tick();
}