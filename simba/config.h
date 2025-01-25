// == SIM800 ==
#define SIM800L_RX 12
#define SIM800L_TX 13

SoftwareSerial sim800l(SIM800L_RX, SIM800L_TX);

// == wi-fi ==
#define SSID ""
#define PASSWORD ""

// == telegram ==
#define BOT_TOKEN ""
#define CHAT_ID ""

FastBot2 bot;