#include "src/Config.h"
#include "src/api/ApiClient.h"
#include "src/ota/AtualizadorOta.h"
#include "src/ui/Display.h"
#include "src/ui/Ui.h"

ApiClient api(WIFI_SSID, WIFI_SENHA, API_BASE);
AtualizadorOta ota(FIRMWARE_VERSAO, OTA_MANIFEST_URL, OTA_FIRMWARE_URL);
Display display;
Ui ui(display, api, ota);

void setup() {
  ui.iniciar();
}

void loop() {
  ui.atualizar();
}
