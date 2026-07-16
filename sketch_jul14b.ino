#include <Keypad.h>
#include <LiquidCrystal.h>
/*↑------BIBLIOTECAS------↑*/


LiquidCrystal lcd_1(23, 22, 19, 18, 5, 4);
/*↑------PORTAS-DA-TELA-LCD------↑*/


const byte LINHAS = 4;
const byte COLUNAS = 4;
/*↑------CONSTRUÇÃO PARA O VETOR DO TECLADO------↑*/


bool encontrou = false;
bool Quantidade = false;
/*↑------VARIAVEIS BOLEANAS TEMPORARIAS------↑*/

int modo = 0;
int n = 0;
int confirm = 0;
int estado = 0;
int pagina = 0;
int erro = 0;
int dia;
int mes;
int objN;
int TRN;
int Save;
/*↑------VARIAVEIS TEMPORARIAS PARA ESTADOS------↑*/

unsigned long ultimoTempo = 0;
/*↑------VARIAVEL PARA TIMER------↑*/

String Qnt = "";
String Sdia = "";
String Smes = "";
String numero = "";
/*↑------VARIAVEIS TEMPORARIAS PARA ESTADOS------↑*/

String idBuscado = "";
String profLog = "";
String modSelecionado = "";
String objSelecionado = "";
String qntSelecionada = "";
String dtSelecionada = "";
String trnSelecionado = "";
String hrSelecionado = "";
/*↑------VARIAVEIS TEMPORARIAS PARA GUARDAR INFORMAÇÕES------↑*/

int diasMes[] = {
  31, // Jan
  28, // Fev
  31, // Mar
  30, // Abr
  31, // Mai
  30, // Jun
  31, // Jul
  31, // Ago
  30, // Set
  31, // Out
  30, // Nov
  31  // Dez
};
/*↑------VETOR PARA OS DIAS CERTOS DE CADA MES------↑*/

String mod[] = {
  "Retirada",
  "Agendamento",
  "Devolucao",
  "Voltar"
};
/*↑------VETOR DE TODAS AS OPÇÕES DE MODOS------↑*/

struct cargaH{
  String trn;
  int qntHr;
  String hr[7];
};

cargaH turno[] = {
  {"Intermediario", 7, 
  {"aula 1", "aula 2", "aula 3", "aula 4", "aula 5", "aula 6", "aula 7"}},
  {"Vespertino", 5,
  {"aula 1", "aula 2", "aula 3", "aula 4", "aula 5"}},
  {"Matutino", 5,
  {"aula 1", "aula 2", "aula 3", "aula 4", "aula 5"}}
};
/*↑------VETOR E SEU STRUCT PAR AOS TURNOS E AULAS------↑*/

struct opcQnt{
  int opQnt;
  String opObj;
};

opcQnt opc[] = {
  {20, "Caneta 3D"},
  {20, "Tablet"},
  {20, "VR"},
  {20, "CrhomeBook"}
};
/*↑------VETOR E SEU STRUCT PARA OS OBJETOS E SUA QUANTIDADE------↑*/

struct professor{
  String id;
  String nome;
};

professor professores[] = {
    {"01", "Marcelo"},
    {"02", "Rhian"},
    {"03", "Arthur"},
    {"04", "Matheus"}

};
/*↑------VETOR E SEU STRUCT PARA OS IDs E OS PROFESSORES REGISTRADOS------↑*/

char teclas[LINHAS][COLUNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
/*↑------VETOR PARA O MAPEAMENTO DE TRECLAS------↑*/

byte pinosLinhas[LINHAS] = {13, 14, 33, 32};
byte pinosColunas[COLUNAS] = {26, 25, 27, 21};
/*↑------DEFINIÇÃO DOS PINOS DO TECLADO------↑*/

Keypad teclado = Keypad(
  makeKeymap(teclas),
  pinosLinhas,
  pinosColunas,
  LINHAS,
  COLUNAS
);
/*↑------FUNÇÃO PARA O RECONHECIMENTO DAS TECLAS PRESSIONADAS------↑*/

void setup() {
  Serial.begin(9600);

  delay(1000);
  lcd_1.begin(16, 2);
  lcd_1.clear(); 

}
/*↑------FUNÇÃO DE SETUP (INICIALIZAÇÃO DO ESP)------↑*/

void telaDeLogin(char tecla){

  lcd_1.setCursor(0, 0);
  lcd_1.print("Digite seu id");
  /*↑------PRIMEIRA AÇÃO QUE A FUNÇÃO IRA FAZER ATE O FINAL------↑*/

  if (tecla >= '0' && tecla <= '9'){/*------CONDICIONAL PARA LIMITAR O USO APENAS PARA AS TECLAS NUMERICAS------*/

    if (idBuscado.length() < 2){/*------CONDICIONAL PARA EXIBIR O NUMERO DIGITADO E LIMITAR O NUMERO EM 2 CARACTERES------*/
      idBuscado += tecla;

      lcd_1.setCursor(0, 1);
      lcd_1.print(idBuscado);
      lcd_1.setCursor(idBuscado.length(), 1);
      lcd_1.print("                                           ");
    }
  }
  
  if (tecla){/*------CONDICIONAL PARA VERIFICAR SE ALGUMA TECLA FORA DO TECLADO NUMERICO FOI PRESSIONADO------*/

    if (tecla == '#'){/*------CONDICIONAL PARA VERIFICAR SE A TECLA FOI O SIMBOLO #------*/
      idBuscado = "";
      lcd_1.setCursor(0, 1);
      lcd_1.clear();
    }
  }
  /*↑------CONDICIONAL PARA LIMPAR O NUMERO DIGITADO------↑*/

  if (tecla){/*------CONDICIONAL PARA VERIFICAR SE ALGUMA TECLA FORA DO TECLADO NUMERICO FOI PRESSIONADO------*/

    if (tecla == 'A'){/*------CONDICIONAL PARA VERIFICAR SE A TECLA FOI A LETRA A------*/

      for (int i = 0; i < sizeof(professores) / sizeof(professores[0]); i++){/*------LAÇO DE REPETIÇÃO PARA PECORRER TODO O VETOR E VERIFICAR OS IDs------*/

        if(professores[i].id == idBuscado){ /*------CONDICIONAL DE SUCESSO CASO O PROFESSOR FOI ENCONCTRADO------*/
          encontrou = true;

          lcd_1.clear();
          lcd_1.print(professores[i].nome);
          delay(2000);
          lcd_1.clear();
          profLog = professores[i].nome;
          estado = 1;
          break;
        }
      }

      if (!encontrou) {/*↑------CONDICIONAL PARA O ERRO DE NÃO ENCONTRAR O ID------↑*/
        lcd_1.setCursor(0, 1);
        lcd_1.clear();
        lcd_1.print("Id inexistente");
        delay(1000);
        lcd_1.clear();
        idBuscado = "";
      }
    }
  }
}
/*↑------FUNÇÃO TELA DE LOGIN------↑*/

void escolhaMod(char tecla){
  if (tecla == 'C') {/*------CONDICIONAL PARA O REINICIAMENTO DO PROCESSO------*/
    lcd_1.clear();
    Save = estado;
    estado = 11;
    return;
  }

  lcd_1.setCursor(0, 0);
  lcd_1.print("Escolha o Modo");
  lcd_1.setCursor(0, 1);
  lcd_1.print(mod[n]);
  /*↑------PRIMEIRA AÇÃO QUE A FUNÇÃO IRA FAZER ATE O FINAL------↑*/

  if (tecla){/*↑------CONDICIONAL PARA QUANDO UMA TECLA FOR PRESSIONADA------↑*/

    if (tecla == '1'){/*↓------CONDICIONAIS PARA MUDAR A OPÇÃO EXIBIDA NO TECLADO------↓*/
      lcd_1.clear();
      n = 0;
    }
    if (tecla == '2'){
      lcd_1.clear();
      n = 1;
    }
    if (tecla == '3'){
      lcd_1.clear();
      n = 2;
    }
    if (tecla == '4'){
      lcd_1.clear();
      n = 3;
    }

    if(tecla == 'A'){/*------CONDICIONAL PARA QUANDO A TECLA 'A' FOR PRESSIONADA------*/

      /*↓------CONDICIONAIS PARA MUDAR PARA IR PARA CADA TELA DESEJADA------↓*/
      if (n == 0){/*------TELA DE RETIRADA------*/
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print(mod[n]);
        delay(2000);
        lcd_1.clear();
        modSelecionado = mod[n];
        estado = 2;
        n = 0;
      }
      if (n == 1){/*------TELA DE AGENDAMENTO------*/
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print(mod[n]);
        delay(2000);
        lcd_1.clear();
        modSelecionado = mod[n];
        estado = 6;
        n = 0;
      }
      if (n == 2){/*------TELA DE DEVOLUÇÃO------*/
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print(mod[n]);
        delay(2000);
        lcd_1.clear();
        modSelecionado = mod[n];
        estado = 2;
        n = 0;
      }
      if (n == 3){/*------OPÇÃO DE VOLTA------*/
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print(mod[n]);
        delay(2000);
        lcd_1.clear();
        modSelecionado = mod[n];
        estado = 0;
        n = 0;
        encontrou = false;
        
        idBuscado = "";
        profLog = "";
        modSelecionado = "";

      }

    }
  }

}/*↑------FUNÇÃO TELA DE ESCOLHA DE MODO------↑*/

void escolhaObj(char tecla){
  if (tecla == 'C') {/*------CONDICIONAL PARA O REINICIAMENTO DO PROCESSO------*/
    lcd_1.clear();
    Save = estado;
    estado = 11;
    return;
  }
  lcd_1.setCursor(0, 0);
  lcd_1.print("Escolha o Objeto");
  lcd_1.setCursor(0, 1);
  lcd_1.print(opc[n].opObj);
  /*↑------PRIMEIRA AÇÃO QUE A FUNÇÃO IRA FAZER ATE O FINAL------↑*/

  if (tecla){/*↓------CONDICIONAIS PARA MUDAR A OPÇÃO EXIBIDA NO TECLADO------↓*/

    if (tecla == '1'){
      lcd_1.clear();
      n = 0;
    }
    if (tecla == '2'){
      lcd_1.clear();
      n = 1;
    }
    if (tecla == '3'){
      lcd_1.clear();
      n = 2;
    }
    if (tecla == '4'){
      lcd_1.clear();
      n = 3;
    }

    if (tecla == 'A'){/*------CONDICIONAL PARA QUANDO A TECLA 'A' FOR PRESSIONADA------*/
    lcd_1.clear();
    estado = 3;
    objSelecionado = opc[n].opObj;
    objN = n;
   }
  }
}/*↑------FUNÇÃO TELA DE ESCOLHA DE OBJETO------↑*/

void escolhaQnt(char tecla){
  if (tecla == 'C') {/*------CONDICIONAL PARA O REINICIAMENTO DO PROCESSO------*/
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
  lcd_1.print(opc[objN].opQnt);
  /*↑------PRIMEIRA AÇÃO QUE A FUNÇÃO IRA FAZER ATE O FINAL------↑*/

  if (tecla >= '0' && tecla <= '9'){/*------CONDICIONAL PARA LIMITAR O USO APENAS PARA AS TECLAS NUMERICAS------*/

    if (Qnt.length() < 2){/*------CONDICIONAL VERIFICAR E LIMITAR AS TECLAS EM 2 CARACTERES------*/
      Qnt += tecla;

      lcd_1.setCursor(0, 1);
      lcd_1.print(Qnt);
      lcd_1.setCursor(Qnt.length(), 1);
      lcd_1.print("                                           ");

    }
  }

  if (tecla){/*↓------CONDICIONAIS PARA MUDAR A OPÇÃO EXIBIDA NO TECLADO------↓*/

    if (tecla == '#'){
      Qnt = "";
      lcd_1.setCursor(0, 1);
      lcd_1.clear();
    }
  }

  if (modSelecionado == "Devolucao"){/*------CONDICIONAIS PARA CASO O MODO ESCOLHIDO SEJA "DEVOLUÇÃO"------*/
    if (tecla){
      if (tecla == 'A'){
        if (opc[objN].opQnt + Qnt.toInt() <= 20 && Qnt.toInt() > 0){
          Quantidade = true;

          lcd_1.clear();
          lcd_1.setCursor(0, 0);
          lcd_1.print("Restam:");
          lcd_1.print(opc[objN].opQnt + Qnt.toInt());
          delay(2000);
          estado = 4;
          qntSelecionada = Qnt;
          erro = 1;
        }
        if (!Quantidade){/*------CONDICIONAIS PARA CASO O NUMERO DE ITENS DEVOLVIDOS SEJAM MAIORES DOQUE O DE ESTOQUE------*/
          lcd_1.setCursor(0, 1);
          lcd_1.clear();
          lcd_1.print("Quantidade");
          lcd_1.setCursor(0, 1);
          lcd_1.print("Indisponivel");
          delay(1000);
          lcd_1.clear();
          Qnt = "";
        }
      }
    }
  }

  else if (tecla && modSelecionado != "Devolucao" ){/*------CONDICIONAIS PARA CASO O MODO ESCOLHIDO NÃO SEJA "DEVOLUÇÃO"------*/
    if (tecla == 'A'){
      if(Qnt.toInt() < opc[objN].opQnt && Qnt.toInt() > 0){
        Quantidade = true;
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Restam:");
        lcd_1.print(opc[objN].opQnt - Qnt.toInt());
        delay(2000);
        estado = 4;
        qntSelecionada = Qnt;
      }
      if (!Quantidade){/*------CONDICIONAIS PARA CASO A QUANTIDADE DE RETIRADA SEJA MAIOR QUE A DE ESTOQUE OU QUE NÃO AJA MAIS ESTOQUE------*/
        lcd_1.setCursor(0, 1);
        lcd_1.clear();
        lcd_1.print("Quantidade");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Indisponivel");
        delay(1000);
        lcd_1.clear();
        Qnt = "";
      }

    }
  }
}/*↑------FUNÇÃO TELA DE QUANTIDADE------↑*/

void confirmSet(char tecla){
  if (tecla == 'C') {/*------CONDICIONAL PARA O REINICIAMENTO DO PROCESSO------*/
    lcd_1.clear();
    Save = estado;
    estado = 11;
    return;
  }
  if (modSelecionado == "Agendamento"){/*------CASO SEJA 'AGENDAMENTO' EXIBIR MAIS TELAS------*/
    if (tecla == 'A') {
        estado = 5;   
        return;
    }
    if (millis() - ultimoTempo >= 2000) {/*------TIMER PARA A ALTERNANCIA DE TELAS, MOSTRANDO TODAS AS OPÇÕES POSSIVEIS------*/
        ultimoTempo = millis();
        pagina++;
        if (pagina > 3)
            pagina = 0;
        lcd_1.clear();
    }
    if (pagina == 0) {
        lcd_1.setCursor(0,0);
        lcd_1.print(profLog);
        lcd_1.setCursor(0,1);
        lcd_1.print(modSelecionado);
    } 
    else if (pagina == 2){
      lcd_1.setCursor(0,0);
        lcd_1.print(trnSelecionado);
        lcd_1.setCursor(0,1);
        lcd_1.print(hrSelecionado);
    }
    else if (pagina == 1){
      lcd_1.setCursor(0,0);
        lcd_1.print("Data");
        lcd_1.setCursor(0,1);
        lcd_1.print(dtSelecionada);
    }
    else {
        lcd_1.setCursor(0,0);
        lcd_1.print(objSelecionado);
        lcd_1.setCursor(0,1);
        lcd_1.print(qntSelecionada);
  }
  }
  else {
    if (tecla == 'A') {/*------CASO NÃO SEJA 'AGENDAMENTO' EXIBIR A QUANTIDADE PADRÃO DE TELAS------*/
          estado = 5;   
          return;
      }
      if (millis() - ultimoTempo >= 2000) {/*------TIMER PARA A ALTERNANCIA DE TELAS, MOSTRANDO TODAS AS OPÇÕES POSSIVEIS------*/
          ultimoTempo = millis();
          pagina++;
          if (pagina > 1)
              pagina = 0;
          lcd_1.clear();
      }
      if (pagina == 0) {
          lcd_1.setCursor(0,0);
          lcd_1.print(profLog);
          lcd_1.setCursor(0,1);
          lcd_1.print(modSelecionado);
      } 
      else {
          lcd_1.setCursor(0,0);
          lcd_1.print(objSelecionado);
          lcd_1.setCursor(0,1);
          lcd_1.print(qntSelecionada);
    }
  }
  
}/*↑------FUNÇÃO TELA DE CONFIRMAÇÃO------↑*/

void final(char tecla){
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Finalizado");
  delay(2000);
  encontrou = false;
  Quantidade = false;

  modo = 0;
  n = 0;
  confirm = 0;
  estado = 0;
  pagina = 0;
  erro = 0;
  Save = 0;

  Qnt = "";
  Sdia = "";
  Smes = "";
  numero = "";
  idBuscado = "";
  profLog = "";
  modSelecionado = "";
  objSelecionado = "";
  qntSelecionada = "";
  dtSelecionada = "";
  trnSelecionado = "";
  hrSelecionado = "";
  /*↑------REINICIA TODAS AS VARIAVEIS PARA O PROSSIMO REGISTRO------↑*/

}/*↑------FUNÇÃO TELA DE FINALIZAÇÃO------↑*/

void escolhaDia(char tecla){
  if (tecla == 'C') {
    lcd_1.clear();
    Save = estado;
    estado = 11;
    return;
  }
  lcd_1.setCursor(0, 0);
  lcd_1.print("Informe o Dia");
  if (tecla >= '0' && tecla <= '9'){
    if (Sdia.length() < 2){
      Sdia += tecla;

      lcd_1.setCursor(0, 1);
      lcd_1.print(Sdia);
      lcd_1.setCursor(Sdia.length(), 1);
      lcd_1.print("                                           ");
    }
  }
  if (tecla){
    if (tecla == '#'){
      Sdia = "";
      lcd_1.setCursor(0, 1);
      lcd_1.clear();
    }
  }
  if (tecla){
    if (tecla == 'A'){
      lcd_1.setCursor(0, 1);
      lcd_1.clear();
        estado = 7;
      }
    }
}/*↑------FUNÇÃO TELA DE ESCOLHA DE DIA------↑*/

void escolhaMes(char tecla){
  if (tecla == 'C') {
    lcd_1.clear();
    Save = estado;
    estado = 11;
    return;
  }
  lcd_1.setCursor(0, 0);
  lcd_1.print("Informe o Mes");
  if (tecla >= '0' && tecla <= '9'){
    if (Smes.length() < 2){
      Smes += tecla;

      lcd_1.setCursor(0, 1);
      lcd_1.print(Smes);
      lcd_1.setCursor(Smes.length(), 1);
      lcd_1.print("                                           ");
    }
  }
  if (tecla){
    if (tecla == '#'){
      Smes = "";
      lcd_1.setCursor(0, 1);
      lcd_1.clear();
    }
  }
  if (tecla){
    if (tecla == 'A'){
      lcd_1.setCursor(0, 1);
      lcd_1.clear();
        estado = 8;
      }
  }

  if (tecla){
    if (tecla == 'D'){
      lcd_1.setCursor(0, 1);
      lcd_1.clear();
      Smes = "";
      Sdia = "";
      estado = 6;
      }
    }
}/*↑------FUNÇÃO TELA DE ESCOLHA DE MÊS------↑*/

void dataConfirm(char tecla){
  if (tecla == 'C') {
    lcd_1.clear();
    Save = estado;
    estado = 11;
    return;
  }
  mes = Smes.toInt();;
  dia = Sdia.toInt();
  dtSelecionada = Sdia + "/" + Smes;

  if (mes < 1 || mes > 12) {
    lcd_1.setCursor(0, 0);
    lcd_1.print("Mes invalido");
    lcd_1.clear();
    delay(2000);
    Smes = "";
    Sdia = "";
    estado = 6;

  }
  else if (dia < 1 || dia > diasMes[mes - 1]) {
    lcd_1.setCursor(0, 0);
    lcd_1.print("Dia invalido");
    lcd_1.clear();
    delay(2000);
    Smes = "";
    Sdia = "";
    estado = 6;
  }
  else {
    dtSelecionada = Sdia + "/" + Smes;

    lcd_1.setCursor(0, 0);
    lcd_1.print("Confirmar Data");
    lcd_1.setCursor(0, 1);
    lcd_1.print(dtSelecionada);

    if(tecla){
      if (tecla == 'A'){
        estado = 9;
      }
    }

  }
  if (tecla){
    if (tecla == 'D'){
      lcd_1.setCursor(0, 1);
      lcd_1.clear();
      Smes = "";
      Sdia = "";
        estado = 6;
      }
  }
  
}/*↑------FUNÇÃO TELA DE CONFIRMAÇÃO DE DATA------↑*/

void escolhaTurno(char tecla){
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
  if (tecla){
      if (tecla == '1'){
        lcd_1.clear();
        n = 0;
      }
      if (tecla == '2'){
        lcd_1.clear();
        n = 1;
      }
      if (tecla == '3'){
        lcd_1.clear();
        n = 2;
      }
      if(tecla == 'A'){
        if (n == 0){
          lcd_1.clear();
          lcd_1.setCursor(0, 0);
          lcd_1.print(turno[n].trn);
          delay(2000);
          lcd_1.clear();
          trnSelecionado = turno[n].trn;
          estado = 10;
          TRN = n;
          n = 0;
        }
        if (n == 1){
          lcd_1.clear();
          lcd_1.setCursor(0, 0);
          lcd_1.print(turno[n].trn);
          delay(2000);
          lcd_1.clear();
          trnSelecionado = turno[n].trn;
          estado = 10;
          TRN = n;
          n = 0;
        }
        if (n == 2){
          lcd_1.clear();
          lcd_1.setCursor(0, 0);
          lcd_1.print(turno[n].trn);
          delay(2000);
          lcd_1.clear();
          trnSelecionado = turno[n].trn;
          estado = 10;
          TRN = n;
          n = 0;
        }
      }
  }
}/*↑------FUNÇÃO TELA DE ESCOLHA DE TURNO------↑*/

void escolhaAula(char tecla){
  if (tecla == 'C') {
    lcd_1.clear();
    Save = estado;
    estado = 11;
    return;
  }
  lcd_1.setCursor(0, 0);
  lcd_1.print("Informe a Aula");
  if (n < turno[TRN].qntHr){
    lcd_1.setCursor(0, 1);
    lcd_1.print(turno[TRN].hr[n]);
  }
  if (tecla){
      if (tecla == '1'){
        lcd_1.clear();
        n = 0;
      }
      if (tecla == '2'){
        lcd_1.clear();
        n = 1;
      }
      if (tecla == '3'){
        lcd_1.clear();
        n = 2;
      }
      if (tecla == '4'){
        lcd_1.clear();
        n = 3;
      }
      if (tecla == '5'){
        lcd_1.clear();
        n = 4;
      }
      if (tecla == '6' && turno[TRN].qntHr >= 6){
        lcd_1.clear();
        n = 5;
      }
      if (tecla == '7' && turno[TRN].qntHr >= 7){
        lcd_1.clear();
        n = 6;
      }
      if(tecla == 'A'){
        if (n == 0){
          lcd_1.clear();
          lcd_1.setCursor(0, 0);
          lcd_1.print(turno[TRN].hr[n]);
          delay(2000);
          lcd_1.clear();
          hrSelecionado = turno[TRN].hr[n];
          estado = 2;
          n = 0;
        }
        if (n == 1){
          lcd_1.clear();
          lcd_1.setCursor(0, 0);
          lcd_1.print(turno[TRN].hr[n]);
          delay(2000);
          lcd_1.clear();
          hrSelecionado = turno[TRN].hr[n];
          estado = 2;
          n = 0;
        }
        if (n == 2){
          lcd_1.clear();
          lcd_1.setCursor(0, 0);
          lcd_1.print(turno[TRN].hr[n]);
          delay(2000);
          lcd_1.clear();
          hrSelecionado = turno[TRN].hr[n];
          estado = 2;
          n = 0;
        }
        if (n == 3){
          lcd_1.clear();
          lcd_1.setCursor(0, 0);
          lcd_1.print(turno[TRN].hr[n]);
          delay(2000);
          lcd_1.clear();
          hrSelecionado = turno[TRN].hr[n];
          estado = 2;
          n = 0;
        }
        if (n == 4){
          lcd_1.clear();
          lcd_1.setCursor(0, 0);
          lcd_1.print(turno[TRN].hr[n]);
          delay(2000);
          lcd_1.clear();
          hrSelecionado = turno[TRN].hr[n];
          estado = 2;
          n = 0;
        }
        if (n == 5){
          lcd_1.clear();
          lcd_1.setCursor(0, 0);
          lcd_1.print(turno[TRN].hr[n]);
          delay(2000);
          lcd_1.clear();
          hrSelecionado = turno[TRN].hr[n];
          estado = 2;
          n = 0;
        }
        if (n == 6){
          lcd_1.clear();
          lcd_1.setCursor(0, 0);
          lcd_1.print(turno[TRN].hr[n]);
          delay(2000);
          lcd_1.clear();
          hrSelecionado = turno[TRN].hr[n];
          estado = 2;
          n = 0;
        }
      }
  }
}/*↑------FUNÇÃO TELA DE ESCOLHA DE AULA------↑*/

void reiniciarEscolhas(char tecla) {
  lcd_1.setCursor(0, 0);
  lcd_1.print("Qer reiniciar?");
  lcd_1.setCursor(0, 1);
  lcd_1.print("A - Sim");
  lcd_1.setCursor(8, 1);
  lcd_1.print("B - Nao");
  /*↑------TELA DE CONFIRMAÇÃO PARA REINICIAMENTO DAS ESCOLHAS------↑*/

  if (tecla){
    if (tecla == 'A') /*------OPÇÃO DE CONFIRMAÇÃO------*/
      n = 0;
      pagina = 0;
      erro = 0;

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
    if (tecla == 'B')/*------OPÇÃO DE NEGAÇÃO------*/
    estado = Save;
    lcd_1.clear();
  }
}/*↑------FUNÇÃO DE REINICIAÇÃO------↑*/

void loop() {

    char tecla = teclado.getKey();

  switch (estado){
    
    case 0:
      telaDeLogin(tecla); /*------CHAMADA DA FUNÇÃO DE TELA DE LOGIN------*/
      break;
    case 1:
      escolhaMod(tecla); /*------CHAMADA DA FUNÇÃO DE TELA DE ESCOLHA DE MODO------*/
      break;
    case 2:
      escolhaObj(tecla); /*------CHAMADA DA FUNÇÃO DE TELA DE ESCOLHA DE OBJETO------*/
      break;
    case 3:
      escolhaQnt(tecla); /*------CHAMADA DA FUNÇÃO DE TELA DE ESCOLHA DE QUANTIDADE------*/
      break;
    case 4: 
      confirmSet(tecla); /*------CHAMADA DA FUNÇÃO DE TELA DE CONFIRMAÇÃO DAS OPÇÕES SELECIONADAS------*/
      break;
    case 5:
      final(tecla); /*------CHAMADA DA FUNÇÃO DE TELA DE FINALIZAÇÃO------*/
      break;
    case 6:
      escolhaDia(tecla); /*------CHAMADA DA FUNÇÃO DE TELA DE ESCOLHA DO DIA------*/
      break;
    case 7:
      escolhaMes(tecla); /*------CHAMADA DA FUNÇÃO DE TELA DE ESCOLHA DO MÊS------*/
      break;
    case 8:
      dataConfirm(tecla); /*------CHAMADA DA FUNÇÃO DE TELA DE CONFIRMAÇÃO DA DATA------*/
      break;
    case 9:
      escolhaTurno(tecla); /*------CHAMADA DA FUNÇÃO DE TELA DE ESCOLHA DO TURNO------*/
      break;
    case 10:
      escolhaAula(tecla); /*------CHAMADA DA FUNÇÃO DE TELA DE ESCOLHA DA AULA------*/
      break;
    case 11:
      reiniciarEscolhas(tecla); /*------CHAMADA DA FUNÇÃO DE TELA DE REINICIALIZAÇÃO------*/
      break;
    }
}/*↑------FUNÇÃO DE LOOPING------↑*/