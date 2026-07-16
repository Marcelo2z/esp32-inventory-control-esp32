#include "sessao.h"

Sessao sessao;

void Sessao::encerrar() {
  deslogar();
  limparEscolhas();
  quantidadeValida = false;
}

void Sessao::deslogar() {
  professor = "";
  modo = "";
  idDigitado = "";
  professorEncontrado = false;
}

void Sessao::limparEscolhas() {
  objeto = "";
  quantidade = "";
  data = "";
  turno = "";
  aula = "";

  quantidadeDigitada = "";
  diaDigitado = "";
  mesDigitado = "";
}
