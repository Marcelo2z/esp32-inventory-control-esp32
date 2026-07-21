#include "ApiClient.h"

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

ApiClient::ApiClient(const String &ssid, const String &senha, const String &baseUrl)
  : ssid(ssid), senha(senha), baseUrl(baseUrl) {
}

void ApiClient::conectar() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), senha.c_str());

  unsigned long inicio = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - inicio < 20000) {
    delay(500);
  }
}

bool ApiClient::conectado() {
  return WiFi.status() == WL_CONNECTED;
}

void ApiClient::garantirConexao() {
  if (!conectado()) {
    conectar();
  }
}

int ApiClient::buscar(const String &caminho, String &corpo) {
  garantirConexao();

  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient https;
  https.begin(client, baseUrl + caminho);
  int status = https.GET();
  corpo = (status > 0) ? https.getString() : "";
  https.end();

  return status;
}

int ApiClient::enviar(const String &caminho, const String &corpo, String &resposta) {
  garantirConexao();

  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient https;
  https.begin(client, baseUrl + caminho);
  https.addHeader("Content-Type", "application/json");
  int status = https.POST(corpo);
  resposta = (status > 0) ? https.getString() : "";
  https.end();

  return status;
}

int ApiClient::carregarRecursos(Recurso destino[], int maximo) {
  String corpo;
  if (buscar("/api/recursos", corpo) != 200) {
    return 0;
  }

  JsonDocument doc;
  if (deserializeJson(doc, corpo) != DeserializationError::Ok) {
    return 0;
  }

  int total = 0;
  for (JsonObject item : doc["itens"].as<JsonArray>()) {
    if (total >= maximo) break;
    destino[total].id = item["id"] | 0;
    destino[total].nome = String((const char*)(item["nome"] | ""));
    destino[total].disponivel = item["disponivel"] | 0;
    total++;
  }
  return total;
}

ResultadoLogin ApiClient::autenticarProfessor(const String &codigo) {
  ResultadoLogin resultado{false, ""};
  if (codigo.length() == 0) {
    return resultado;
  }

  String corpo;
  if (buscar("/api/professores/" + codigo, corpo) != 200) {
    return resultado;
  }

  JsonDocument doc;
  if (deserializeJson(doc, corpo) != DeserializationError::Ok) {
    return resultado;
  }

  if (doc["acesso"] == true) {
    resultado.autorizado = true;
    resultado.professor = String((const char*)(doc["professor"] | ""));
  }
  return resultado;
}

ResultadoMovimentacao ApiClient::movimentar(const String &caminho, const String &codigo, int recursoId, int quantidade) {
  JsonDocument requisicao;
  requisicao["codigo"] = codigo;
  requisicao["recurso_id"] = recursoId;
  requisicao["quantidade"] = quantidade;

  String corpo;
  serializeJson(requisicao, corpo);

  String resposta;
  int status = enviar(caminho, corpo, resposta);

  JsonDocument doc;
  deserializeJson(doc, resposta);

  int restante = doc["restam"] | (doc["disponivel"] | 0);
  return ResultadoMovimentacao{status, restante};
}

ResultadoMovimentacao ApiClient::registrarRetirada(const String &codigo, int recursoId, int quantidade) {
  return movimentar("/api/retirada", codigo, recursoId, quantidade);
}

ResultadoMovimentacao ApiClient::registrarDevolucao(const String &codigo, int recursoId, int quantidade) {
  return movimentar("/api/devolucao", codigo, recursoId, quantidade);
}

ResultadoAgendamento ApiClient::registrarAgendamento(const String &codigo, int recursoId, int quantidade,
                                                     int turno, const String &dia, const String &aula) {
  JsonDocument requisicao;
  requisicao["codigo"] = codigo;
  requisicao["recurso_id"] = recursoId;
  requisicao["quantidade"] = quantidade;
  requisicao["turno"] = turno;
  requisicao["dia"] = dia;
  requisicao["aula"] = aula;

  String corpo;
  serializeJson(requisicao, corpo);

  String resposta;
  int status = enviar("/api/agendamento", corpo, resposta);

  JsonDocument doc;
  deserializeJson(doc, resposta);

  return ResultadoAgendamento{status, doc["id"] | 0};
}
