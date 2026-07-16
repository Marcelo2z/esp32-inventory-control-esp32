#include "src/hardware/tela.h"
#include "src/hardware/teclado.h"
#include "src/nucleo/estados.h"
#include "src/nucleo/navegacao.h"
#include "src/telas/telas.h"

void setup() {
  Serial.begin(9600);
  delay(1000);
  Tela::iniciar();
}

void loop() {
  const char tecla = lerTecla();

  switch (estadoAtual) {
    case ESTADO_LOGIN:         telaLogin(tecla);        break;
    case ESTADO_MENU_MODO:     telaMenuModo(tecla);     break;
    case ESTADO_MENU_OBJETO:   telaMenuObjeto(tecla);   break;
    case ESTADO_QUANTIDADE:    telaQuantidade(tecla);   break;
    case ESTADO_CONFIRMACAO:   telaConfirmacao(tecla);  break;
    case ESTADO_FINALIZACAO:   telaFinalizacao(tecla);  break;
    case ESTADO_DIA:           telaDia(tecla);          break;
    case ESTADO_MES:           telaMes(tecla);          break;
    case ESTADO_CONFIRMA_DATA: telaConfirmaData(tecla); break;
    case ESTADO_MENU_TURNO:    telaMenuTurno(tecla);    break;
    case ESTADO_MENU_AULA:     telaMenuAula(tecla);     break;
    case ESTADO_REINICIAR:     telaReiniciar(tecla);    break;
  }
}
