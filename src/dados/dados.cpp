#include "dados.h"

const char* const MODO_RETIRADA    = "Retirada";
const char* const MODO_AGENDAMENTO = "Agendamento";
const char* const MODO_DEVOLUCAO   = "Devolucao";
const char* const MODO_VOLTAR      = "Voltar";

Professor professores[] = {
  {"01", "Marcelo"},
  {"02", "Rhian"},
  {"03", "Arthur"},
  {"04", "Matheus"}
};
const uint8_t TOTAL_PROFESSORES = sizeof(professores) / sizeof(professores[0]);

Objeto objetos[] = {
  {20, "Caneta 3D"},
  {20, "Tablet"},
  {20, "VR"},
  {20, "CrhomeBook"}
};
const uint8_t TOTAL_OBJETOS = sizeof(objetos) / sizeof(objetos[0]);

Turno turnos[] = {
  {"Intermediario", 7,
   {"aula 1", "aula 2", "aula 3", "aula 4", "aula 5", "aula 6", "aula 7"}},
  {"Vespertino", 5,
   {"aula 1", "aula 2", "aula 3", "aula 4", "aula 5"}},
  {"Matutino", 5,
   {"aula 1", "aula 2", "aula 3", "aula 4", "aula 5"}}
};
const uint8_t TOTAL_TURNOS = sizeof(turnos) / sizeof(turnos[0]);

const String modos[] = {
  MODO_RETIRADA,
  MODO_AGENDAMENTO,
  MODO_DEVOLUCAO,
  MODO_VOLTAR
};
const uint8_t TOTAL_MODOS = sizeof(modos) / sizeof(modos[0]);

const uint8_t diasDoMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

const Professor* buscarProfessorPorId(const String& id) {
  for (uint8_t i = 0; i < TOTAL_PROFESSORES; i++) {
    if (professores[i].id == id) {
      return &professores[i];
    }
  }
  return nullptr;
}
