#include "Ui.h"

static const byte LINHAS = 4;
static const byte COLUNAS = 4;

static char teclas[LINHAS][COLUNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
static byte pinosLinhas[LINHAS] = {13, 14, 33, 32};
static byte pinosColunas[COLUNAS] = {26, 25, 27, 21};

static const char* MODOS[] = {"Retirada", "Agendamento", "Devolucao", "Voltar"};

struct Turno {
  String nome;
  int aulas;
  String horarios[7];
};

static Turno TURNOS[] = {
  {"Intermediario", 7, {"aula 1", "aula 2", "aula 3", "aula 4", "aula 5", "aula 6", "aula 7"}},
  {"Vespertino", 5, {"aula 1", "aula 2", "aula 3", "aula 4", "aula 5"}},
  {"Matutino", 5, {"aula 1", "aula 2", "aula 3", "aula 4", "aula 5"}}
};

static int diasDoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static bool ehDigito(char tecla) {
  return tecla >= '0' && tecla <= '9';
}

Ui::Ui(Display &display, ApiClient &api)
  : display(display),
    api(api),
    teclado(makeKeymap(teclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS),
    qtdRecursos(0),
    tela(LOGIN),
    telaAnterior(LOGIN),
    cursor(0),
    paginaConfirmacao(0),
    ultimoGiro(0) {
}

void Ui::iniciar() {
  display.iniciar();

  display.mensagem("Conectando WiFi", "", 0);
  api.conectar();

  if (api.conectado()) {
    display.mensagem("Carregando...", "", 0);
    qtdRecursos = api.carregarRecursos(recursos, MAX_RECURSOS);
  } else {
    display.mensagem("Sem WiFi", "", 2000);
  }
  display.limpar();
}

void Ui::atualizar() {
  char tecla = teclado.getKey();

  if (tela == ENVIAR) {
    enviar();
    return;
  }
  if (tecla == 'C' && tela != LOGIN && tela != REINICIAR) {
    telaAnterior = tela;
    irPara(REINICIAR);
    return;
  }

  switch (tela) {
    case LOGIN:               login(tecla);              break;
    case MENU_MODO:           menuModo(tecla);           break;
    case MENU_OBJETO:         menuObjeto(tecla);         break;
    case INFORMAR_QUANTIDADE: informarQuantidade(tecla); break;
    case CONFIRMAR:           confirmar(tecla);          break;
    case INFORMAR_DIA:        informarDia(tecla);        break;
    case INFORMAR_MES:        informarMes(tecla);        break;
    case CONFIRMAR_DATA:      confirmarData(tecla);      break;
    case MENU_TURNO:          menuTurno(tecla);          break;
    case MENU_AULA:           menuAula(tecla);           break;
    case REINICIAR:           reiniciar(tecla);          break;
    default:                                             break;
  }
}

void Ui::irPara(Tela destino) {
  tela = destino;
  cursor = 0;
  paginaConfirmacao = 0;
  ultimoGiro = millis();
  display.limpar();
}

void Ui::limparOperacao(bool manterLogin) {
  String codigo = op.codigo;
  String professor = op.professor;
  op = Operacao{};
  recursoAtual = Recurso{};
  entradaDia = "";
  entradaMes = "";
  if (manterLogin) {
    op.codigo = codigo;
    op.professor = professor;
  }
}

int Ui::turnoParaApi(int indice) {
  if (indice == 0) return 2;
  if (indice == 1) return 3;
  return 1;
}

void Ui::login(char tecla) {
  display.linha(0, "Digite seu id");

  if (ehDigito(tecla) && op.codigo.length() < 5) {
    op.codigo += tecla;
    display.linha(1, op.codigo);
  }
  if (tecla == '#') {
    op.codigo = "";
    display.limpar();
  }
  if (tecla == 'A') {
    display.mensagem("Verificando...", "", 0);
    ResultadoLogin resultado = api.autenticarProfessor(op.codigo);
    if (resultado.autorizado) {
      op.professor = resultado.professor;
      display.mensagem(op.professor, "", 2000);
      irPara(MENU_MODO);
    } else {
      display.mensagem("Id inexistente", "", 1500);
      op.codigo = "";
      irPara(LOGIN);
    }
  }
}

void Ui::menuModo(char tecla) {
  display.linha(0, "Escolha o Modo");
  display.linha(1, MODOS[cursor]);

  if (tecla >= '1' && tecla <= '4') cursor = tecla - '1';

  if (tecla == 'A') {
    op.modo = MODOS[cursor];
    display.mensagem(op.modo, "", 2000);

    if (cursor == 0) irPara(MENU_OBJETO);
    else if (cursor == 1) irPara(INFORMAR_DIA);
    else if (cursor == 2) irPara(MENU_OBJETO);
    else {
      limparOperacao(false);
      irPara(LOGIN);
    }
  }
}

void Ui::menuObjeto(char tecla) {
  if (qtdRecursos == 0) {
    display.linha(0, "Sem recursos");
    display.linha(1, "Verifique a API");
    return;
  }
  if (cursor >= qtdRecursos) cursor = 0;

  display.linha(0, "Escolha o Objeto");
  display.linha(1, recursos[cursor].nome);

  if (tecla >= '1' && tecla <= '9') {
    int indice = tecla - '1';
    if (indice < qtdRecursos) cursor = indice;
  }
  if (tecla == 'A') {
    recursoAtual = recursos[cursor];
    irPara(INFORMAR_QUANTIDADE);
  }
}

void Ui::informarQuantidade(char tecla) {
  display.linha(0, "Qtd  max:" + String(recursoAtual.disponivel));

  if (ehDigito(tecla) && op.quantidade.length() < 2) {
    op.quantidade += tecla;
    display.linha(1, op.quantidade);
  }
  if (tecla == '#') {
    op.quantidade = "";
    display.linha(1, "");
  }
  if (tecla == 'A') {
    int quantidade = op.quantidade.toInt();
    bool valida = (op.modo == "Devolucao")
                    ? quantidade > 0
                    : quantidade > 0 && quantidade <= recursoAtual.disponivel;

    if (valida) {
      if (op.modo != "Devolucao") {
        display.mensagem("Restam:", String(recursoAtual.disponivel - quantidade), 2000);
      }
      irPara(CONFIRMAR);
    } else {
      display.mensagem("Quantidade", "Indisponivel", 1500);
      op.quantidade = "";
      display.limpar();
    }
  }
}

void Ui::confirmar(char tecla) {
  if (tecla == 'A') {
    irPara(ENVIAR);
    return;
  }

  int totalPaginas = (op.modo == "Agendamento") ? 4 : 2;
  if (millis() - ultimoGiro >= 2000) {
    ultimoGiro = millis();
    paginaConfirmacao = (paginaConfirmacao + 1) % totalPaginas;
  }

  if (paginaConfirmacao == 0) {
    display.linha(0, op.professor);
    display.linha(1, op.modo);
  } else if (op.modo == "Agendamento" && paginaConfirmacao == 1) {
    display.linha(0, "Data");
    display.linha(1, op.data);
  } else if (op.modo == "Agendamento" && paginaConfirmacao == 2) {
    display.linha(0, op.turno);
    display.linha(1, op.aula);
  } else {
    display.linha(0, recursoAtual.nome);
    display.linha(1, op.quantidade);
  }
}

void Ui::enviar() {
  display.mensagem("Enviando...", "", 0);
  int quantidade = op.quantidade.toInt();

  if (op.modo == "Retirada") {
    ResultadoMovimentacao r = api.registrarRetirada(op.codigo, recursoAtual.id, quantidade);
    if (r.status == 200)      display.mensagem("Retirada OK", "Restam:" + String(r.restante), 2500);
    else if (r.status == 409) display.mensagem("Indisponivel", "Tem:" + String(r.restante), 2500);
    else if (r.status == 401) display.mensagem("Acesso negado", "", 2500);
    else                      display.mensagem("Erro", String(r.status), 2500);
  } else if (op.modo == "Devolucao") {
    ResultadoMovimentacao r = api.registrarDevolucao(op.codigo, recursoAtual.id, quantidade);
    if (r.status == 200)      display.mensagem("Devolucao OK", "Disp:" + String(r.restante), 2500);
    else if (r.status == 401) display.mensagem("Acesso negado", "", 2500);
    else                      display.mensagem("Erro", String(r.status), 2500);
  } else {
    ResultadoAgendamento r = api.registrarAgendamento(
      op.codigo, recursoAtual.id, quantidade, turnoParaApi(op.turnoIndice), op.data, op.aula);
    if (r.status == 201)      display.mensagem("Agendado", "#" + String(r.id), 2500);
    else if (r.status == 400) display.mensagem("Dados invalidos", "", 2500);
    else if (r.status == 401) display.mensagem("Acesso negado", "", 2500);
    else                      display.mensagem("Erro", String(r.status), 2500);
  }

  display.mensagem("Finalizado", "", 2000);
  qtdRecursos = api.carregarRecursos(recursos, MAX_RECURSOS);
  limparOperacao(false);
  irPara(LOGIN);
}

void Ui::informarDia(char tecla) {
  display.linha(0, "Informe o Dia");

  if (ehDigito(tecla) && entradaDia.length() < 2) {
    entradaDia += tecla;
    display.linha(1, entradaDia);
  }
  if (tecla == '#') {
    entradaDia = "";
    display.linha(1, "");
  }
  if (tecla == 'A') irPara(INFORMAR_MES);
}

void Ui::informarMes(char tecla) {
  display.linha(0, "Informe o Mes");

  if (ehDigito(tecla) && entradaMes.length() < 2) {
    entradaMes += tecla;
    display.linha(1, entradaMes);
  }
  if (tecla == '#') {
    entradaMes = "";
    display.linha(1, "");
  }
  if (tecla == 'A') irPara(CONFIRMAR_DATA);
  if (tecla == 'D') {
    entradaDia = "";
    entradaMes = "";
    irPara(INFORMAR_DIA);
  }
}

void Ui::confirmarData(char tecla) {
  int mes = entradaMes.toInt();
  int dia = entradaDia.toInt();

  if (mes < 1 || mes > 12) {
    display.mensagem("Mes invalido", "", 2000);
    entradaDia = "";
    entradaMes = "";
    irPara(INFORMAR_DIA);
    return;
  }
  if (dia < 1 || dia > diasDoMes[mes - 1]) {
    display.mensagem("Dia invalido", "", 2000);
    entradaDia = "";
    entradaMes = "";
    irPara(INFORMAR_DIA);
    return;
  }

  op.data = entradaDia + "/" + entradaMes;
  display.linha(0, "Confirmar Data");
  display.linha(1, op.data);

  if (tecla == 'A') irPara(MENU_TURNO);
  if (tecla == 'D') {
    entradaDia = "";
    entradaMes = "";
    irPara(INFORMAR_DIA);
  }
}

void Ui::menuTurno(char tecla) {
  display.linha(0, "Informe o Turno");
  display.linha(1, TURNOS[cursor].nome);

  if (tecla >= '1' && tecla <= '3') cursor = tecla - '1';

  if (tecla == 'A') {
    op.turnoIndice = cursor;
    op.turno = TURNOS[cursor].nome;
    display.mensagem(op.turno, "", 2000);
    irPara(MENU_AULA);
  }
}

void Ui::menuAula(char tecla) {
  int totalAulas = TURNOS[op.turnoIndice].aulas;

  display.linha(0, "Informe a Aula");
  if (cursor < totalAulas) display.linha(1, TURNOS[op.turnoIndice].horarios[cursor]);

  if (tecla >= '1' && tecla <= '7') {
    int indice = tecla - '1';
    if (indice < totalAulas) cursor = indice;
  }
  if (tecla == 'A' && cursor < totalAulas) {
    op.aula = TURNOS[op.turnoIndice].horarios[cursor];
    display.mensagem(op.aula, "", 2000);
    irPara(MENU_OBJETO);
  }
}

void Ui::reiniciar(char tecla) {
  display.linha(0, "Qer reiniciar?");
  display.linha(1, "A - Sim  B - Nao");

  if (tecla == 'A') {
    limparOperacao(true);
    irPara(MENU_MODO);
  }
  if (tecla == 'B') irPara(telaAnterior);
}
