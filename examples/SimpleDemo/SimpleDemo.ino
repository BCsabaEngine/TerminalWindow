#include <TerminalScreen.h>
#include "Windows.h"

#define LED PC13

TerminalScreen* screen;

void setup() {
  Serial.begin(115200);

  pinMode(LED, OUTPUT);

  screen = new TerminalScreen("ModuleController/Lights");

  screen->addWindow(new MainWindow());
}

void loop() {
  // Do anything
  digitalWrite(LED, !digitalRead(PC13));

  // Call loop as possible to handle redraw and keyboard input
  screen->loop();

  delay(100);
}
