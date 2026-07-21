#pragma once

#include <Arduino.h>
#include <Keypad.h>

#include "Display.h"
#include "../api/ApiClient.h"
#include "../model/Recurso.h"

class Ui {
public:
  Ui(Display &display, ApiClient &api);

  void iniciar();
  void atualizar();

private:
  enum Tela {
    LOGIN,
    MENU_MODO,
    MENU_OBJETO,
    INFORMAR_QUANTIDADE,
    CONFIRMAR,
    ENVIAR,
    INFORMAR_DIA,
    INFORMAR_MES,
    CONFIRMAR_DATA,
    MENU_TURNO,
    MENU_AULA,
    REINICIAR
  };

  struct Operacao {
    String codigo;
    String professor;
    String modo;
    String quantidade;
    String data;
    int turnoIndice;
    String turno;
    String aula;
  };

  Display &display;
  ApiClient &api;
  Keypad teclado;

  Recurso recursos[MAX_RECURSOS];
  int qtdRecursos;

  Tela tela;
  Tela telaAnterior;
  int cursor;
  int paginaConfirmacao;
  unsigned long ultimoGiro;

  Operacao op;
  Recurso recursoAtual;
  String entradaDia;
  String entradaMes;

  void irPara(Tela destino);
  void limparOperacao(bool manterLogin);
  int turnoParaApi(int indice);

  void login(char tecla);
  void menuModo(char tecla);
  void menuObjeto(char tecla);
  void informarQuantidade(char tecla);
  void confirmar(char tecla);
  void enviar();
  void informarDia(char tecla);
  void informarMes(char tecla);
  void confirmarData(char tecla);
  void menuTurno(char tecla);
  void menuAula(char tecla);
  void reiniciar(char tecla);
};
