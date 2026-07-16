#pragma once

#include <Arduino.h>

const char TECLA_CONFIRMA  = 'A';
const char TECLA_NEGA      = 'B';
const char TECLA_REINICIAR = 'C';
const char TECLA_VOLTAR    = 'D';
const char TECLA_LIMPAR    = '#';

char lerTecla();
bool acrescentarDigito(char tecla, String& destino, uint8_t maxDigitos);
bool moverSelecao(char tecla, uint8_t totalOpcoes, int& indice);
