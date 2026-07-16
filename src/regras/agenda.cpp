#include "agenda.h"

#include "../dados/dados.h"

namespace Agenda {

bool mesValido(int mes) {
  return mes >= 1 && mes <= 12;
}

bool diaValido(int dia, int mes) {
  if (!mesValido(mes)) {
    return false;
  }
  return dia >= 1 && dia <= diasDoMes[mes - 1];
}

String formatarData(const String& dia, const String& mes) {
  return dia + "/" + mes;
}

}
