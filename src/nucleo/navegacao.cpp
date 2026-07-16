#include "navegacao.h"

#include "../hardware/tela.h"
#include "../hardware/teclado.h"

Estado estadoAtual = ESTADO_LOGIN;
Estado estadoAntesDoReinicio = ESTADO_LOGIN;
int indiceMenu = 0;
int paginaDoResumo = 0;

void reiniciarNavegacao() {
  estadoAtual = ESTADO_LOGIN;
  estadoAntesDoReinicio = ESTADO_LOGIN;
  indiceMenu = 0;
  paginaDoResumo = 0;
}

bool desviouParaReinicio(char tecla) {
  if (tecla != TECLA_REINICIAR) {
    return false;
  }
  Tela::limpar();
  estadoAntesDoReinicio = estadoAtual;
  estadoAtual = ESTADO_REINICIAR;
  return true;
}
