#include "telas.h"

#include "../dados/dados.h"
#include "../regras/estoque.h"
#include "../nucleo/navegacao.h"
#include "../nucleo/sessao.h"
#include "../hardware/tela.h"
#include "../hardware/teclado.h"

namespace {

const unsigned long INTERVALO_PAGINA = 2000;
unsigned long ultimaTrocaPagina = 0;

void mostrarResumo(int pagina) {
  if (sessao.modo == MODO_AGENDAMENTO) {
    switch (pagina) {
      case 0:
        Tela::escrever(0, 0, sessao.professor);
        Tela::escrever(0, 1, sessao.modo);
        break;
      case 1:
        Tela::escrever(0, 0, "Data");
        Tela::escrever(0, 1, sessao.data);
        break;
      case 2:
        Tela::escrever(0, 0, sessao.turno);
        Tela::escrever(0, 1, sessao.aula);
        break;
      default:
        Tela::escrever(0, 0, sessao.objeto);
        Tela::escrever(0, 1, sessao.quantidade);
        break;
    }
    return;
  }

  if (pagina == 0) {
    Tela::escrever(0, 0, sessao.professor);
    Tela::escrever(0, 1, sessao.modo);
  } else {
    Tela::escrever(0, 0, sessao.objeto);
    Tela::escrever(0, 1, sessao.quantidade);
  }
}

}

void telaMenuObjeto(char tecla) {
  if (desviouParaReinicio(tecla)) {
    return;
  }

  Tela::escrever(0, 0, "Escolha o Objeto");
  Tela::escrever(0, 1, objetos[indiceMenu].nome);

  if (moverSelecao(tecla, TOTAL_OBJETOS, indiceMenu)) {
    Tela::limpar();
  }

  if (tecla == TECLA_CONFIRMA) {
    Tela::limpar();
    sessao.objeto = objetos[indiceMenu].nome;
    sessao.indiceObjeto = indiceMenu;
    estadoAtual = ESTADO_QUANTIDADE;
  }
}

void telaQuantidade(char tecla) {
  if (desviouParaReinicio(tecla)) {
    return;
  }

  Tela::escrever(0, 0, "Quantidade");
  Tela::escrever(8, 1, "max:");
  Tela::escrever(12, 1, String(Estoque::disponivel(sessao.indiceObjeto)));

  if (acrescentarDigito(tecla, sessao.quantidadeDigitada, MAX_DIGITOS_QUANTIDADE)) {
    Tela::substituirLinha(1, sessao.quantidadeDigitada);
  }

  if (tecla == TECLA_LIMPAR) {
    sessao.quantidadeDigitada = "";
    Tela::limpar();
  }

  if (tecla != TECLA_CONFIRMA) {
    return;
  }

  const int quantidade = sessao.quantidadeDigitada.toInt();
  const bool devolvendo = (sessao.modo == MODO_DEVOLUCAO);

  const bool permitido = devolvendo
      ? Estoque::podeDevolver(sessao.indiceObjeto, quantidade)
      : Estoque::podeRetirar(sessao.indiceObjeto, quantidade);

  if (permitido) {
    const int restante = devolvendo
        ? Estoque::totalAposDevolucao(sessao.indiceObjeto, quantidade)
        : Estoque::totalAposRetirada(sessao.indiceObjeto, quantidade);

    sessao.quantidadeValida = true;
    Tela::limpar();
    Tela::escrever(0, 0, "Restam:" + String(restante));
    delay(2000);

    sessao.quantidade = sessao.quantidadeDigitada;
    estadoAtual = ESTADO_CONFIRMACAO;
  }

  if (!sessao.quantidadeValida) {
    Tela::mensagemTemporaria("Quantidade", "Indisponivel", 1000);
    sessao.quantidadeDigitada = "";
  }
}

void telaConfirmacao(char tecla) {
  if (desviouParaReinicio(tecla)) {
    return;
  }

  if (tecla == TECLA_CONFIRMA) {
    estadoAtual = ESTADO_FINALIZACAO;
    return;
  }

  const int totalPaginas = (sessao.modo == MODO_AGENDAMENTO) ? 4 : 2;

  if (millis() - ultimaTrocaPagina >= INTERVALO_PAGINA) {
    ultimaTrocaPagina = millis();
    paginaDoResumo = (paginaDoResumo + 1) % totalPaginas;
    Tela::limpar();
  }

  mostrarResumo(paginaDoResumo);
}

void telaFinalizacao(char tecla) {
  (void)tecla;

  Tela::limpar();
  Tela::escrever(0, 0, "Finalizado");
  delay(2000);

  sessao.encerrar();
  reiniciarNavegacao();
}
