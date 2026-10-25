#pragma once

#include <Arduino.h>

class AtualizadorOta {
public:
  AtualizadorOta(int versaoAtual, const String &manifestUrl, const String &firmwareUrl);

  bool haNovaVersao();
  bool atualizar();

private:
  int versaoAtual;
  String manifestUrl;
  String firmwareUrl;

  int versaoDisponivel();
};
