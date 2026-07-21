#include "src/Config.h"
#include "src/api/ApiClient.h"
#include "src/ui/Display.h"
#include "src/ui/Ui.h"

ApiClient api(WIFI_SSID, WIFI_SENHA, API_BASE);
Display display;
Ui ui(display, api);

void setup() {
  ui.iniciar();
}

void loop() {
  ui.atualizar();
}
