#include "estoque.h"

#include "../dados/dados.h"

namespace Estoque {

int disponivel(int indiceObjeto) {
  return objetos[indiceObjeto].quantidade;
}

bool podeRetirar(int indiceObjeto, int quantidade) {
  // Comportamento original preservado: usa "<" e nao "<=", entao nao e
  // possivel retirar o estoque inteiro.
  return quantidade > 0 && quantidade < disponivel(indiceObjeto);
}

bool podeDevolver(int indiceObjeto, int quantidade) {
  return quantidade > 0 &&
         disponivel(indiceObjeto) + quantidade <= CAPACIDADE_MAXIMA;
}

int totalAposRetirada(int indiceObjeto, int quantidade) {
  return disponivel(indiceObjeto) - quantidade;
}

int totalAposDevolucao(int indiceObjeto, int quantidade) {
  return disponivel(indiceObjeto) + quantidade;
}

}
