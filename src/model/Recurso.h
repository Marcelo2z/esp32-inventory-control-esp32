#pragma once

#include <Arduino.h>

const int MAX_RECURSOS = 10;

struct Recurso {
  int id;
  String nome;
  int disponivel;
};
