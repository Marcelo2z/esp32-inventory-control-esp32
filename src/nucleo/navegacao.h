#pragma once

#include "estados.h"

extern Estado estadoAtual;
extern Estado estadoAntesDoReinicio;
extern int indiceMenu;
extern int paginaDoResumo;

void reiniciarNavegacao();
bool desviouParaReinicio(char tecla);
