#include "AtualizadorOta.h"

#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <ArduinoJson.h>

AtualizadorOta::AtualizadorOta(int versaoAtual, const String &manifestUrl, const String &firmwareUrl)
  : versaoAtual(versaoAtual), manifestUrl(manifestUrl), firmwareUrl(firmwareUrl) {
}

int AtualizadorOta::versaoDisponivel() {
  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient https;
  https.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  https.begin(client, manifestUrl);
  int status = https.GET();
  String corpo = (status == 200) ? https.getString() : "";
  https.end();

  if (status != 200) {
    return -1;
  }

  JsonDocument doc;
  if (deserializeJson(doc, corpo) != DeserializationError::Ok) {
    return -1;
  }
  return doc["versao"] | -1;
}

bool AtualizadorOta::haNovaVersao() {
  return versaoDisponivel() > versaoAtual;
}

bool AtualizadorOta::atualizar() {
  WiFiClientSecure client;
  client.setInsecure();

  httpUpdate.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  httpUpdate.rebootOnUpdate(true);

  return httpUpdate.update(client, firmwareUrl) == HTTP_UPDATE_OK;
}
