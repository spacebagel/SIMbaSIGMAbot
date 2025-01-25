void updateh(fb::Update& u) {
  Serial.println("NEW MESSAGE");
  Serial.println(u.message().from().username());
  Serial.println(u.message().text());
}

void botConfig() {
  bot.attachUpdate(updateh);
  bot.setToken(F(BOT_TOKEN));
  bot.setPollMode(fb::Poll::Long, 20000);
  bot.sendMessage(fb::Message("The SIMba system is running!", CHAT_ID));
}

void sendSMSToBot(String message) {
  bot.sendMessage(fb::Message(message, CHAT_ID));
}