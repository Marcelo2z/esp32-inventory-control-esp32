#pragma once

#include <Arduino.h>

namespace Tela {

const uint8_t COLUNAS = 16;
const uint8_t LINHAS = 2;

void iniciar();
void limpar();
void escrever(uint8_t coluna, uint8_t linha, const String& texto);
void substituirLinha(uint8_t linha, const String& texto);
void mensagemTemporaria(const String& texto, unsigned long duracaoMs);
void mensagemTemporaria(const String& linha0, const String& linha1, unsigned long duracaoMs);

}
