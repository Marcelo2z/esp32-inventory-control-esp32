#pragma once

#include <Arduino.h>

struct Professor {
  String id;
  String nome;
};

struct Objeto {
  int quantidade;
  String nome;
};

struct Turno {
  String nome;
  int totalAulas;
  String aulas[7];
};

extern Professor professores[];
extern const uint8_t TOTAL_PROFESSORES;

extern Objeto objetos[];
extern const uint8_t TOTAL_OBJETOS;

extern Turno turnos[];
extern const uint8_t TOTAL_TURNOS;

extern const String modos[];
extern const uint8_t TOTAL_MODOS;

extern const char* const MODO_RETIRADA;
extern const char* const MODO_AGENDAMENTO;
extern const char* const MODO_DEVOLUCAO;
extern const char* const MODO_VOLTAR;

extern const uint8_t diasDoMes[12];

const Professor* buscarProfessorPorId(const String& id);
