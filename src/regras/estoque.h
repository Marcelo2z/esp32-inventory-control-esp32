#pragma once

#include <Arduino.h>

namespace Estoque {

const int CAPACIDADE_MAXIMA = 20;

int disponivel(int indiceObjeto);

bool podeRetirar(int indiceObjeto, int quantidade);
bool podeDevolver(int indiceObjeto, int quantidade);

int totalAposRetirada(int indiceObjeto, int quantidade);
int totalAposDevolucao(int indiceObjeto, int quantidade);

}
