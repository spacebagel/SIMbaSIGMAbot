bool checkNotNumber(String value) {
  for (size_t i = 0; i < value.length(); ++i) {
    char c = value[i];
    if (!isxdigit(c)) return true;
  }
  return false;
}

String ucs2ToUtf8(uint16_t ucs2_char) {
  String result;
  // 1-byte UTF-8
  if (ucs2_char <= 0x7F) result += (char)ucs2_char;
  // 2-byte UTF-8
  else if (ucs2_char <= 0x7FF) {
    result += (char)(0xC0 | (ucs2_char >> 6));
    result += (char)(0x80 | (ucs2_char & 0x3F));
  }
  // 3-byte UTF-8
  else {
    result += (char)(0xE0 | (ucs2_char >> 12));
    result += (char)(0x80 | ((ucs2_char >> 6) & 0x3F));
    result += (char)(0x80 | (ucs2_char & 0x3F));
  }
  return result;
}

String convertUCS2ToString(String message) {
  if (message.length() % 4 != 0) {
    Serial.println("Error");
    return "Error. Incorrect length.";
  }

  String result;
  for (size_t i = 0; i < message.length(); i += 4) {
    String cur = message.substring(i, i + 4);
    
    if (checkNotNumber(cur)) return "Error. Wrong symbol.";
    
    uint16_t hex = strtol(cur.c_str(), nullptr, 16);
    char16_t ucs2_char = static_cast<char16_t>(hex);

    result += ucs2ToUtf8(ucs2_char);
  }
  return result;
}