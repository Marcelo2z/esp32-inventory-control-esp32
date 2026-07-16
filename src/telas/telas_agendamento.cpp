#include "telas.h"

#include "../regras/agenda.h"
#include "../dados/dados.h"
#include "../nucleo/navegacao.h"
#include "../nucleo/sessao.h"
#include "../hardware/tela.h"
#include "../hardware/teclado.h"

namespace {

void voltarParaDia() {
  Tela::limpar();
  sessao.diaDigitado = "";
  sessao.mesDigitado = "";
  estadoAtual = ESTADO_DIA;
}

}

void telaDia(char tecla) {
  if (desviouParaReinicio(tecla)) {
    return;
  }

  Tela::escrever(0, 0, "Informe o Dia");

  if (acrescentarDigito(tecla, sessao.diaDigitado, MAX_DIGITOS_DATA)) {
    Tela::substituirLinha(1, sessao.diaDigitado);
  }

  if (tecla == TECLA_LIMPAR) {
    sessao.diaDigitado = "";
    Tela::limpar();
  }

  if (tecla == TECLA_CONFIRMA) {
    Tela::limpar();
    estadoAtual = ESTADO_MES;
  }
}

void telaMes(char tecla) {
  if (desviouParaReinicio(tecla)) {
    return;
  }

  Tela::escrever(0, 0, "Informe o Mes");

  if (acrescentarDigito(tecla, sessao.mesDigitado, MAX_DIGITOS_DATA)) {
    Tela::substituirLinha(1, sessao.mesDigitado);
  }

  if (tecla == TECLA_LIMPAR) {
    sessao.mesDigitado = "";
    Tela::limpar();
  }

  if (tecla == TECLA_CONFIRMA) {
    Tela::limpar();
    estadoAtual = ESTADO_CONFIRMA_DATA;
  }

  if (tecla == TECLA_VOLTAR) {
    voltarParaDia();
  }
}

void telaConfirmaData(char tecla) {
  if (desviouParaReinicio(tecla)) {
    return;
  }

  const int dia = sessao.diaDigitado.toInt();
  const int mes = sessao.mesDigitado.toInt();
  sessao.data = Agenda::formatarData(sessao.diaDigitado, sessao.mesDigitado);

  if (!Agenda::mesValido(mes)) {
    // Comportamento original preservado: a tela e limpa antes da espera,
    // entao a mensagem de erro nao chega a ser lida.
    Tela::escrever(0, 0, "Mes invalido");
    Tela::limpar();
    delay(2000);
    voltarParaDia();
  } else if (!Agenda::diaValido(dia, mes)) {
    Tela::escrever(0, 0, "Dia invalido");
    Tela::limpar();
    delay(2000);
    voltarParaDia();
  } else {
    Tela::escrever(0, 0, "Confirmar Data");
    Tela::escrever(0, 1, sessao.data);

    if (tecla == TECLA_CONFIRMA) {
      estadoAtual = ESTADO_MENU_TURNO;
    }
  }

  if (tecla == TECLA_VOLTAR) {
    voltarParaDia();
  }
}

void telaMenuTurno(char tecla) {
  if (desviouParaReinicio(tecla)) {
    return;
  }

  Tela::escrever(0, 0, "Informe o Turno");
  Tela::escrever(0, 1, turnos[indiceMenu].nome);

  if (moverSelecao(tecla, TOTAL_TURNOS, indiceMenu)) {
    Tela::limpar();
  }

  if (tecla == TECLA_CONFIRMA) {
    Tela::mensagemTemporaria(turnos[indiceMenu].nome, 2000);
    sessao.turno = turnos[indiceMenu].nome;
    sessao.indiceTurno = indiceMenu;
    estadoAtual = ESTADO_MENU_AULA;
    indiceMenu = 0;
  }
}

void telaMenuAula(char tecla) {
  if (desviouParaReinicio(tecla)) {
    return;
  }

  const Turno& turno = turnos[sessao.indiceTurno];

  Tela::escrever(0, 0, "Informe a Aula");
  if (indiceMenu < turno.totalAulas) {
    Tela::escrever(0, 1, turno.aulas[indiceMenu]);
  }

  if (moverSelecao(tecla, turno.totalAulas, indiceMenu)) {
    Tela::limpar();
  }

  if (tecla == TECLA_CONFIRMA) {
    Tela::mensagemTemporaria(turno.aulas[indiceMenu], 2000);
    sessao.aula = turno.aulas[indiceMenu];
    estadoAtual = ESTADO_MENU_OBJETO;
    indiceMenu = 0;
  }
}
