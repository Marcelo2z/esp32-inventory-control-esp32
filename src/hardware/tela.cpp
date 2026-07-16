#include "tela.h"

#include <LiquidCrystal.h>

namespace {
LiquidCrystal lcd(23, 22, 19, 18, 5, 4);
}

namespace Tela {

void iniciar() {
  lcd.begin(COLUNAS, LINHAS);
  lcd.clear();
}

void limpar() {
  lcd.clear();
}

void escrever(uint8_t coluna, uint8_t linha, const String& texto) {
  lcd.setCursor(coluna, linha);
  lcd.print(texto);
}

void substituirLinha(uint8_t linha, const String& texto) {
  escrever(0, linha, texto);
  for (uint8_t coluna = texto.length(); coluna < COLUNAS; coluna++) {
    lcd.print(' ');
  }
}

void mensagemTemporaria(const String& texto, unsigned long duracaoMs) {
  mensagemTemporaria(texto, "", duracaoMs);
}

void mensagemTemporaria(const String& linha0, const String& linha1, unsigned long duracaoMs) {
  lcd.clear();
  escrever(0, 0, linha0);
  if (linha1.length() > 0) {
    escrever(0, 1, linha1);
  }
  delay(duracaoMs);
  lcd.clear();
}

}
