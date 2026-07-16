#include "teclado.h"

#include <Keypad.h>

namespace {

const byte LINHAS = 4;
const byte COLUNAS = 4;

char mapaTeclas[LINHAS][COLUNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pinosLinhas[LINHAS] = {13, 14, 33, 32};
byte pinosColunas[COLUNAS] = {26, 25, 27, 21};

Keypad teclado = Keypad(
  makeKeymap(mapaTeclas),
  pinosLinhas,
  pinosColunas,
  LINHAS,
  COLUNAS
);

}

char lerTecla() {
  return teclado.getKey();
}

bool acrescentarDigito(char tecla, String& destino, uint8_t maxDigitos) {
  if (tecla < '0' || tecla > '9') {
    return false;
  }
  if (destino.length() >= maxDigitos) {
    return false;
  }
  destino += tecla;
  return true;
}

bool moverSelecao(char tecla, uint8_t totalOpcoes, int& indice) {
  if (tecla < '1' || tecla > '9') {
    return false;
  }
  uint8_t escolha = tecla - '1';
  if (escolha >= totalOpcoes) {
    return false;
  }
  indice = escolha;
  return true;
}
