#include "telas.h"

#include "../nucleo/navegacao.h"
#include "../nucleo/sessao.h"
#include "../hardware/tela.h"
#include "../hardware/teclado.h"

void telaReiniciar(char tecla) {
  Tela::escrever(0, 0, "Quer reiniciar?");
  Tela::escrever(0, 1, "A - Sim");
  Tela::escrever(8, 1, "B - Nao");

  if (!tecla) {
    return;
  }

  // Comportamento original preservado: so a volta ('B') e condicional, entao
  // qualquer tecla diferente de 'B' reinicia as escolhas, nao apenas o 'A'.
  if (tecla == TECLA_CONFIRMA) {
    indiceMenu = 0;
  }

  paginaDoResumo = 0;
  sessao.limparEscolhas();
  estadoAtual = ESTADO_MENU_MODO;

  if (tecla == TECLA_NEGA) {
    estadoAtual = estadoAntesDoReinicio;
  }

  Tela::limpar();
}
