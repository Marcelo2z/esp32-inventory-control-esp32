#pragma once

#include <Arduino.h>
#include "recurso.h"

struct ResultadoLogin {
  bool autorizado;
  String professor;
};

struct ResultadoMovimentacao {
  int status;
  int restante;
};

struct ResultadoAgendamento {
  int status;
  int id;
};

void conectarWiFi();
bool wifiConectado();

int carregarRecursos(Recurso destino[], int maximo);

ResultadoLogin autenticarProfessor(const String &codigo);

ResultadoMovimentacao registrarRetirada(const String &codigo, int recursoId, int quantidade);
ResultadoMovimentacao registrarDevolucao(const String &codigo, int recursoId, int quantidade);

ResultadoAgendamento registrarAgendamento(
  const String &codigo,
  int recursoId,
  int quantidade,
  int turno,
  const String &dia,
  const String &aula
);
