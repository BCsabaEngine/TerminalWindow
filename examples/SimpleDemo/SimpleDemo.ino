#include <TerminalScreen.h>
#include "Windows.h"

TerminalScreen screen("ModuleController/Lights");

void setup() {
  Serial.begin(115200);

  screen.addWindow(new MainWindow());

}

void loop() {
  // Do anything

  // Call loop as possible to handle redraw and keyboard input
  screen.loop();

  delay(100);
}
