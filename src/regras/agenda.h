#pragma once

#include <Arduino.h>

namespace Agenda {

bool mesValido(int mes);
bool diaValido(int dia, int mes);
String formatarData(const String& dia, const String& mes);

}
