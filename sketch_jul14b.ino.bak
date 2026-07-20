#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd_1(23, 22, 19, 18, 5, 4);

const byte LINHAS = 4;
const byte COLUNAS = 4;
  
bool encontrou = false;
bool Quantidade = false;

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

unsigned long ultimoTempo = 0;
  
String Qnt = "";
String Sdia = "";
String Smes = "";
String numero = "";

String idBuscado = "";
String profLog = "";
String modSelecionado = "";
String objSelecionado = "";
String qntSelecionada = "";
String dtSelecionada = "";
String trnSelecionado = "";
String hrSelecionado = "";

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

String mod[] = {
  "Retirada",
  "Agendamento",
  "Devolucao",
  "Voltar"
};

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

char teclas[LINHAS][COLUNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pinosLinhas[LINHAS] = {13, 14, 33, 32};
byte pinosColunas[COLUNAS] = {26, 25, 27, 21};

Keypad teclado = Keypad(
  makeKeymap(teclas),
  pinosLinhas,
  pinosColunas,
  LINHAS,
  COLUNAS
);
  
void setup() {
  Serial.begin(9600);

  delay(1000);
  lcd_1.begin(16, 2);
  lcd_1.clear(); 

}

void telaDeLogin(char tecla){

  lcd_1.setCursor(0, 0);
  lcd_1.print("Digite seu id");

  if (tecla >= '0' && tecla <= '9'){  

    if (idBuscado.length() < 2){  
      idBuscado += tecla;

      lcd_1.setCursor(0, 1);
      lcd_1.print(idBuscado);
      lcd_1.setCursor(idBuscado.length(), 1);
      lcd_1.print("                                           ");
    }
  }
  
  if (tecla){  

    if (tecla == '#'){  
      idBuscado = "";
      lcd_1.setCursor(0, 1);
      lcd_1.clear();
    }
  }
    

  if (tecla){  

    if (tecla == 'A'){  

      for (int i = 0; i < sizeof(professores) / sizeof(professores[0]); i++){  

        if(professores[i].id == idBuscado){   
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

      if (!encontrou) {  
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
  

void escolhaMod(char tecla){
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

    if(tecla == 'A'){  

        
      if (n == 0){  
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print(mod[n]);
        delay(2000);
        lcd_1.clear();
        modSelecionado = mod[n];
        estado = 2;
        n = 0;
      }
      if (n == 1){  
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print(mod[n]);
        delay(2000);
        lcd_1.clear();
        modSelecionado = mod[n];
        estado = 6;
        n = 0;
      }
      if (n == 2){  
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print(mod[n]);
        delay(2000);
        lcd_1.clear();
        modSelecionado = mod[n];
        estado = 2;
        n = 0;
      }
      if (n == 3){  
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

}  

void escolhaObj(char tecla){
  if (tecla == 'C') {  
    lcd_1.clear();
    Save = estado;
    estado = 11;
    return;
  }
  lcd_1.setCursor(0, 0);
  lcd_1.print("Escolha o Objeto");
  lcd_1.setCursor(0, 1);
  lcd_1.print(opc[n].opObj);
    

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

    if (tecla == 'A'){  
    lcd_1.clear();
    estado = 3;
    objSelecionado = opc[n].opObj;
    objN = n;
   }
  }
}  

void escolhaQnt(char tecla){
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
  lcd_1.print(opc[objN].opQnt);
    

  if (tecla >= '0' && tecla <= '9'){  

    if (Qnt.length() < 2){  
      Qnt += tecla;

      lcd_1.setCursor(0, 1);
      lcd_1.print(Qnt);
      lcd_1.setCursor(Qnt.length(), 1);
      lcd_1.print("                                           ");

    }
  }

  if (tecla){  

    if (tecla == '#'){
      Qnt = "";
      lcd_1.setCursor(0, 1);
      lcd_1.clear();
    }
  }

  if (modSelecionado == "Devolucao"){  
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
        if (!Quantidade){  
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

  else if (tecla && modSelecionado != "Devolucao" ){  
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
      if (!Quantidade){  
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

void confirmSet(char tecla){
  if (tecla == 'C') {  
    lcd_1.clear();
    Save = estado;
    estado = 11;
    return;
  }
  if (modSelecionado == "Agendamento"){  
    if (tecla == 'A') {
        estado = 5;   
        return;
    }
    if (millis() - ultimoTempo >= 2000) {  
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
    if (tecla == 'A') {  
          estado = 5;   
          return;
      }
      if (millis() - ultimoTempo >= 2000) {  
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
  
}  

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
    

}  

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
}  

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
}  

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
  
}  

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
}  

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
}  

void reiniciarEscolhas(char tecla) {
  lcd_1.setCursor(0, 0);
  lcd_1.print("Qer reiniciar?");
  lcd_1.setCursor(0, 1);
  lcd_1.print("A - Sim");
  lcd_1.setCursor(8, 1);
  lcd_1.print("B - Nao");
    

  if (tecla){
    if (tecla == 'A')   
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
    if (tecla == 'B')  
    estado = Save;
    lcd_1.clear();
  }
}  

void loop() {

    char tecla = teclado.getKey();

  switch (estado){
    
    case 0:
      telaDeLogin(tecla);   
      break;
    case 1:
      escolhaMod(tecla);   
      break;
    case 2:
      escolhaObj(tecla);   
      break;
    case 3:
      escolhaQnt(tecla);   
      break;
    case 4: 
      confirmSet(tecla);   
      break;
    case 5:
      final(tecla);   
      break;
    case 6:
      escolhaDia(tecla);   
      break;
    case 7:
      escolhaMes(tecla);   
      break;
    case 8:
      dataConfirm(tecla);   
      break;
    case 9:
      escolhaTurno(tecla);   
      break;
    case 10:
      escolhaAula(tecla);   
      break;
    case 11:
      reiniciarEscolhas(tecla);   
      break;
    }
}