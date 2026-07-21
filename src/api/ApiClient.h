#pragma once

#include <Arduino.h>
#include "../model/Recurso.h"

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

class ApiClient {
public:
  ApiClient(const String &ssid, const String &senha, const String &baseUrl);

  void conectar();
  bool conectado();

  int carregarRecursos(Recurso destino[], int maximo);
  ResultadoLogin autenticarProfessor(const String &codigo);
  ResultadoMovimentacao registrarRetirada(const String &codigo, int recursoId, int quantidade);
  ResultadoMovimentacao registrarDevolucao(const String &codigo, int recursoId, int quantidade);
  ResultadoAgendamento registrarAgendamento(const String &codigo, int recursoId, int quantidade,
                                            int turno, const String &dia, const String &aula);

private:
  String ssid;
  String senha;
  String baseUrl;

  void garantirConexao();
  int buscar(const String &caminho, String &corpo);
  int enviar(const String &caminho, const String &corpo, String &resposta);
  ResultadoMovimentacao movimentar(const String &caminho, const String &codigo, int recursoId, int quantidade);
};
