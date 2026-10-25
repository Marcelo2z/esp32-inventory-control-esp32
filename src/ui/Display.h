#pragma once

#include <Arduino.h>
#include <LiquidCrystal.h>

class Display {
public:
  Display();

  void iniciar();
  void limpar();
  void linha(int indice, const String &texto);
  void mensagem(const String &linha1, const String &linha2, int espera);

private:
  LiquidCrystal lcd;
};
