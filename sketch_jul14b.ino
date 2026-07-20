#include <Keypad.h>
#include <LiquidCrystal.h>

#include "config.h"
#include "recurso.h"
#include "api.h"

LiquidCrystal lcd_1(23, 22, 19, 18, 5, 4);

const byte LINHAS = 4;
const byte COLUNAS = 4;

int n = 0;
int estado = 0;
int pagina = 0;
int dia;
int mes;
int objN;
int TRN;
int Save;

int recursoIdSel = 0;

unsigned long ultimoTempo = 0;

String Qnt = "";
String Sdia = "";
String Smes = "";

String idBuscado = "";
String profLog = "";
String modSelecionado = "";
String objSelecionado = "";
String qntSelecionada = "";
String dtSelecionada = "";
String trnSelecionado = "";
String hrSelecionado = "";

int diasMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

String mod[] = {"Retirada", "Agendamento", "Devolucao", "Voltar"};

struct cargaH {
  String trn;
  int qntHr;
  String hr[7];
};

cargaH turno[] = {
  {"Intermediario", 7, {"aula 1", "aula 2", "aula 3", "aula 4", "aula 5", "aula 6", "aula 7"}},
  {"Vespertino", 5, {"aula 1", "aula 2", "aula 3", "aula 4", "aula 5"}},
  {"Matutino", 5, {"aula 1", "aula 2", "aula 3", "aula 4", "aula 5"}}
};

Recurso recursos[MAX_RECURSOS];
int qtdRecursos = 0;

char teclas[LINHAS][COLUNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pinosLinhas[LINHAS] = {13, 14, 33, 32};
byte pinosColunas[COLUNAS] = {26, 25, 27, 21};

Keypad teclado = Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS);

int turnoDaApi(int indiceLocal) {
  if (indiceLocal == 0) return 2;
  if (indiceLocal == 1) return 3;
  return 1;
}

void mostrar(const String &linha1, const String &linha2, int espera) {
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print(linha1);
  lcd_1.setCursor(0, 1);
  lcd_1.print(linha2);
  delay(espera);
}

void enviarParaApi() {
  int quantidade = qntSelecionada.toInt();

  if (modSelecionado == "Retirada") {
    ResultadoMovimentacao r = registrarRetirada(idBuscado, recursoIdSel, quantidade);
    if (r.status == 200)      mostrar("Retirada OK", "Restam:" + String(r.restante), 2500);
    else if (r.status == 409) mostrar("Indisponivel", "Tem:" + String(r.restante), 2500);
    else if (r.status == 401) mostrar("Acesso negado", "", 2500);
    else                      mostrar("Erro", String(r.status), 2500);
  }
  else if (modSelecionado == "Devolucao") {
    ResultadoMovimentacao r = registrarDevolucao(idBuscado, recursoIdSel, quantidade);
    if (r.status == 200)      mostrar("Devolucao OK", "Disp:" + String(r.restante), 2500);
    else if (r.status == 401) mostrar("Acesso negado", "", 2500);
    else                      mostrar("Erro", String(r.status), 2500);
  }
  else if (modSelecionado == "Agendamento") {
    ResultadoAgendamento r = registrarAgendamento(
      idBuscado, recursoIdSel, quantidade, turnoDaApi(TRN), dtSelecionada, hrSelecionado);
    if (r.status == 201)      mostrar("Agendado", "#" + String(r.id), 2500);
    else if (r.status == 400) mostrar("Dados invalidos", "", 2500);
    else if (r.status == 401) mostrar("Acesso negado", "", 2500);
    else                      mostrar("Erro", String(r.status), 2500);
  }
}

void setup() {
  Serial.begin(9600);
  delay(1000);
  lcd_1.begin(16, 2);

  mostrar("Conectando WiFi", "", 0);
  conectarWiFi();

  if (wifiConectado()) {
    mostrar("Carregando...", "", 0);
    qtdRecursos = carregarRecursos(recursos, MAX_RECURSOS);
  } else {
    mostrar("Sem WiFi", "", 2000);
  }

  lcd_1.clear();
}

void telaDeLogin(char tecla) {
  lcd_1.setCursor(0, 0);
  lcd_1.print("Digite seu id");

  if (tecla >= '0' && tecla <= '9') {
    if (idBuscado.length() < 5) {
      idBuscado += tecla;
      lcd_1.setCursor(0, 1);
      lcd_1.print(idBuscado);
      lcd_1.setCursor(idBuscado.length(), 1);
      lcd_1.print("                ");
    }
  }

  if (tecla == '#') {
    idBuscado = "";
    lcd_1.clear();
  }

  if (tecla == 'A') {
    mostrar("Verificando...", "", 0);
    ResultadoLogin login = autenticarProfessor(idBuscado);

    if (login.autorizado) {
      profLog = login.professor;
      mostrar(profLog, "", 2000);
      lcd_1.clear();
      estado = 1;
    } else {
      mostrar("Id inexistente", "", 1500);
      lcd_1.clear();
      idBuscado = "";
    }
  }
}

void escolhaMod(char tecla) {
  if (tecla == 'C') {
    lcd_1.clear();
    Save = estado;
    estado = 11;
    return;
  }

  lcd_1.setCursor(0, 0);
  lcd_1.print("Escolha o Modo");
  lcd_1.setCursor(0, 1);
  lcd_1.print(mod[n]);

  if (tecla == '1') { lcd_1.clear(); n = 0; }
  if (tecla == '2') { lcd_1.clear(); n = 1; }
  if (tecla == '3') { lcd_1.clear(); n = 2; }
  if (tecla == '4') { lcd_1.clear(); n = 3; }

  if (tecla == 'A') {
    mostrar(mod[n], "", 2000);
    lcd_1.clear();
    modSelecionado = mod[n];

    if (n == 0)      estado = 2;
    else if (n == 1) estado = 6;
    else if (n == 2) estado = 2;
    else {
      estado = 0;
      idBuscado = "";
      profLog = "";
      modSelecionado = "";
    }
    n = 0;
  }
}

void escolhaObj(char tecla) {
  if (tecla == 'C') {
    lcd_1.clear();
    Save = estado;
    estado = 11;
    return;
  }

  if (qtdRecursos == 0) {
    lcd_1.setCursor(0, 0);
    lcd_1.print("Sem recursos");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Verifique a API");
    return;
  }

  if (n >= qtdRecursos) n = 0;

  lcd_1.setCursor(0, 0);
  lcd_1.print("Escolha o Objeto");
  lcd_1.setCursor(0, 1);
  lcd_1.print(recursos[n].nome);

  if (tecla >= '1' && tecla <= '9') {
    int indice = tecla - '1';
    if (indice < qtdRecursos) {
      lcd_1.clear();
      n = indice;
    }
  }

  if (tecla == 'A') {
    lcd_1.clear();
    estado = 3;
    objSelecionado = recursos[n].nome;
    objN = n;
    recursoIdSel = recursos[n].id;
  }
}

void escolhaQnt(char tecla) {
  if (tecla == 'C') {
    lcd_1.clear();
    Save = estado;
    estado = 11;
    return;
  }

  lcd_1.setCursor(0, 0);
  lcd_1.print("Quantidade");
  lcd_1.setCursor(8, 1);
  lcd_1.print("max:");
  lcd_1.setCursor(12, 1);
  lcd_1.print(recursos[objN].disponivel);

  if (tecla >= '0' && tecla <= '9') {
    if (Qnt.length() < 2) {
      Qnt += tecla;
      lcd_1.setCursor(0, 1);
      lcd_1.print(Qnt);
      lcd_1.setCursor(Qnt.length(), 1);
      lcd_1.print("      ");
    }
  }

  if (tecla == '#') {
    Qnt = "";
    lcd_1.clear();
  }

  if (tecla == 'A') {
    int q = Qnt.toInt();
    bool valida = (modSelecionado == "Devolucao")
                    ? (q > 0)
                    : (q > 0 && q <= recursos[objN].disponivel);

    if (valida) {
      if (modSelecionado != "Devolucao") {
        mostrar("Restam:", String(recursos[objN].disponivel - q), 2000);
      }
      lcd_1.clear();
      estado = 4;
      qntSelecionada = Qnt;
    } else {
      mostrar("Quantidade", "Indisponivel", 1500);
      lcd_1.clear();
      Qnt = "";
    }
  }
}

void confirmSet(char tecla) {
  if (tecla == 'C') {
    lcd_1.clear();
    Save = estado;
    estado = 11;
    return;
  }

  if (tecla == 'A') {
    estado = 5;
    return;
  }

  int totalPaginas = (modSelecionado == "Agendamento") ? 4 : 2;

  if (millis() - ultimoTempo >= 2000) {
    ultimoTempo = millis();
    pagina = (pagina + 1) % totalPaginas;
    lcd_1.clear();
  }

  if (pagina == 0) {
    lcd_1.setCursor(0, 0);
    lcd_1.print(profLog);
    lcd_1.setCursor(0, 1);
    lcd_1.print(modSelecionado);
  } else if (modSelecionado == "Agendamento" && pagina == 1) {
    lcd_1.setCursor(0, 0);
    lcd_1.print("Data");
    lcd_1.setCursor(0, 1);
    lcd_1.print(dtSelecionada);
  } else if (modSelecionado == "Agendamento" && pagina == 2) {
    lcd_1.setCursor(0, 0);
    lcd_1.print(trnSelecionado);
    lcd_1.setCursor(0, 1);
    lcd_1.print(hrSelecionado);
  } else {
    lcd_1.setCursor(0, 0);
    lcd_1.print(objSelecionado);
    lcd_1.setCursor(0, 1);
    lcd_1.print(qntSelecionada);
  }
}

void final(char tecla) {
  mostrar("Enviando...", "", 0);
  enviarParaApi();
  mostrar("Finalizado", "", 2000);

  qtdRecursos = carregarRecursos(recursos, MAX_RECURSOS);

  n = 0;
  estado = 0;
  pagina = 0;
  Save = 0;
  recursoIdSel = 0;

  Qnt = "";
  Sdia = "";
  Smes = "";
  idBuscado = "";
  profLog = "";
  modSelecionado = "";
  objSelecionado = "";
  qntSelecionada = "";
  dtSelecionada = "";
  trnSelecionado = "";
  hrSelecionado = "";

  lcd_1.clear();
}

void escolhaDia(char tecla) {
  if (tecla == 'C') {
    lcd_1.clear();
    Save = estado;
    estado = 11;
    return;
  }

  lcd_1.setCursor(0, 0);
  lcd_1.print("Informe o Dia");

  if (tecla >= '0' && tecla <= '9') {
    if (Sdia.length() < 2) {
      Sdia += tecla;
      lcd_1.setCursor(0, 1);
      lcd_1.print(Sdia);
      lcd_1.setCursor(Sdia.length(), 1);
      lcd_1.print("      ");
    }
  }

  if (tecla == '#') {
    Sdia = "";
    lcd_1.clear();
  }

  if (tecla == 'A') {
    lcd_1.clear();
    estado = 7;
  }
}

void escolhaMes(char tecla) {
  if (tecla == 'C') {
    lcd_1.clear();
    Save = estado;
    estado = 11;
    return;
  }

  lcd_1.setCursor(0, 0);
  lcd_1.print("Informe o Mes");

  if (tecla >= '0' && tecla <= '9') {
    if (Smes.length() < 2) {
      Smes += tecla;
      lcd_1.setCursor(0, 1);
      lcd_1.print(Smes);
      lcd_1.setCursor(Smes.length(), 1);
      lcd_1.print("      ");
    }
  }

  if (tecla == '#') {
    Smes = "";
    lcd_1.clear();
  }

  if (tecla == 'A') {
    lcd_1.clear();
    estado = 8;
  }

  if (tecla == 'D') {
    lcd_1.clear();
    Smes = "";
    Sdia = "";
    estado = 6;
  }
}

void dataConfirm(char tecla) {
  if (tecla == 'C') {
    lcd_1.clear();
    Save = estado;
    estado = 11;
    return;
  }

  mes = Smes.toInt();
  dia = Sdia.toInt();
  dtSelecionada = Sdia + "/" + Smes;

  if (mes < 1 || mes > 12) {
    mostrar("Mes invalido", "", 2000);
    Smes = "";
    Sdia = "";
    estado = 6;
  } else if (dia < 1 || dia > diasMes[mes - 1]) {
    mostrar("Dia invalido", "", 2000);
    Smes = "";
    Sdia = "";
    estado = 6;
  } else {
    lcd_1.setCursor(0, 0);
    lcd_1.print("Confirmar Data");
    lcd_1.setCursor(0, 1);
    lcd_1.print(dtSelecionada);

    if (tecla == 'A') estado = 9;
  }

  if (tecla == 'D') {
    lcd_1.clear();
    Smes = "";
    Sdia = "";
    estado = 6;
  }
}

void escolhaTurno(char tecla) {
  if (tecla == 'C') {
    lcd_1.clear();
    Save = estado;
    estado = 11;
    return;
  }

  lcd_1.setCursor(0, 0);
  lcd_1.print("Informe o Turno");
  lcd_1.setCursor(0, 1);
  lcd_1.print(turno[n].trn);

  if (tecla == '1') { lcd_1.clear(); n = 0; }
  if (tecla == '2') { lcd_1.clear(); n = 1; }
  if (tecla == '3') { lcd_1.clear(); n = 2; }

  if (tecla == 'A') {
    mostrar(turno[n].trn, "", 2000);
    lcd_1.clear();
    trnSelecionado = turno[n].trn;
    TRN = n;
    n = 0;
    estado = 10;
  }
}

void escolhaAula(char tecla) {
  if (tecla == 'C') {
    lcd_1.clear();
    Save = estado;
    estado = 11;
    return;
  }

  lcd_1.setCursor(0, 0);
  lcd_1.print("Informe a Aula");
  if (n < turno[TRN].qntHr) {
    lcd_1.setCursor(0, 1);
    lcd_1.print(turno[TRN].hr[n]);
  }

  if (tecla >= '1' && tecla <= '7') {
    int indice = tecla - '1';
    if (indice < turno[TRN].qntHr) {
      lcd_1.clear();
      n = indice;
    }
  }

  if (tecla == 'A' && n < turno[TRN].qntHr) {
    mostrar(turno[TRN].hr[n], "", 2000);
    lcd_1.clear();
    hrSelecionado = turno[TRN].hr[n];
    n = 0;
    estado = 2;
  }
}

void reiniciarEscolhas(char tecla) {
  lcd_1.setCursor(0, 0);
  lcd_1.print("Qer reiniciar?");
  lcd_1.setCursor(0, 1);
  lcd_1.print("A - Sim");
  lcd_1.setCursor(8, 1);
  lcd_1.print("B - Nao");

  if (tecla == 'A') {
    n = 0;
    pagina = 0;
    Qnt = "";
    Sdia = "";
    Smes = "";
    objSelecionado = "";
    qntSelecionada = "";
    dtSelecionada = "";
    trnSelecionado = "";
    hrSelecionado = "";
    estado = 1;
    lcd_1.clear();
  }

  if (tecla == 'B') {
    estado = Save;
    lcd_1.clear();
  }
}

void loop() {
  char tecla = teclado.getKey();

  switch (estado) {
    case 0:  telaDeLogin(tecla);       break;
    case 1:  escolhaMod(tecla);        break;
    case 2:  escolhaObj(tecla);        break;
    case 3:  escolhaQnt(tecla);        break;
    case 4:  confirmSet(tecla);        break;
    case 5:  final(tecla);             break;
    case 6:  escolhaDia(tecla);        break;
    case 7:  escolhaMes(tecla);        break;
    case 8:  dataConfirm(tecla);       break;
    case 9:  escolhaTurno(tecla);      break;
    case 10: escolhaAula(tecla);       break;
    case 11: reiniciarEscolhas(tecla); break;
  }
