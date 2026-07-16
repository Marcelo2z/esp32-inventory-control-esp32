#include "telas.h"

#include "../dados/dados.h"
#include "../nucleo/navegacao.h"
#include "../nucleo/sessao.h"
#include "../hardware/tela.h"
#include "../hardware/teclado.h"

void telaLogin(char tecla) {
  Tela::escrever(0, 0, "Digite seu id");

  if (acrescentarDigito(tecla, sessao.idDigitado, TAMANHO_ID)) {
    Tela::substituirLinha(1, sessao.idDigitado);
  }

  if (tecla == TECLA_LIMPAR) {
    sessao.idDigitado = "";
    Tela::limpar();
  }

  if (tecla == TECLA_CONFIRMA) {
    const Professor* professor = buscarProfessorPorId(sessao.idDigitado);

    if (professor != nullptr) {
      sessao.professorEncontrado = true;
      Tela::mensagemTemporaria(professor->nome, 2000);
      sessao.professor = professor->nome;
      estadoAtual = ESTADO_MENU_MODO;
    }

    if (!sessao.professorEncontrado) {
      Tela::mensagemTemporaria("Id inexistente", 1000);
      sessao.idDigitado = "";
    }
  }
}

void telaMenuModo(char tecla) {
  if (desviouParaReinicio(tecla)) {
    return;
  }

  Tela::escrever(0, 0, "Escolha o Modo");
  Tela::escrever(0, 1, modos[indiceMenu]);

  if (moverSelecao(tecla, TOTAL_MODOS, indiceMenu)) {
    Tela::limpar();
  }

  if (tecla != TECLA_CONFIRMA) {
    return;
  }

  sessao.modo = modos[indiceMenu];
  Tela::mensagemTemporaria(sessao.modo, 2000);

  if (sessao.modo == MODO_AGENDAMENTO) {
    estadoAtual = ESTADO_DIA;
  } else if (sessao.modo == MODO_VOLTAR) {
    sessao.deslogar();
    estadoAtual = ESTADO_LOGIN;
  } else {
    estadoAtual = ESTADO_MENU_OBJETO;
  }

  indiceMenu = 0;
}
