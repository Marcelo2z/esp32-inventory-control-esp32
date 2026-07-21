#include "Display.h"

Display::Display() : lcd(23, 22, 19, 18, 5, 4) {
}

void Display::iniciar() {
  lcd.begin(16, 2);
}

void Display::limpar() {
  lcd.clear();
}

void Display::linha(int indice, const String &texto) {
  String preenchido = texto;
  while (preenchido.length() < 16) preenchido += ' ';
  lcd.setCursor(0, indice);
  lcd.print(preenchido.substring(0, 16));
}

void Display::mensagem(const String &linha1, const String &linha2, int espera) {
  lcd.clear();
  linha(0, linha1);
  linha(1, linha2);
  delay(espera);
}
