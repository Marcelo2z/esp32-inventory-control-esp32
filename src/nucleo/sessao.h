#pragma once

#include <Arduino.h>

struct Sessao {
  String professor;
  String modo;
  String objeto;
  String quantidade;
  String data;
  String turno;
  String aula;

  String idDigitado;
  String quantidadeDigitada;
  String diaDigitado;
  String mesDigitado;

  int indiceObjeto;
  int indiceTurno;

  bool professorEncontrado;
  bool quantidadeValida;

  void encerrar();
  void deslogar();
  void limparEscolhas();
};

extern Sessao sessao;

const uint8_t TAMANHO_ID = 2;
const uint8_t MAX_DIGITOS_QUANTIDADE = 2;
const uint8_t MAX_DIGITOS_DATA = 2;
