#include "Windows.h"

#include <TerminalWindow.h>
#include <TerminalControl.h>
#include <TerminalLabel.h>
#include <TerminalButton.h>

MainWindow::MainWindow(): TerminalWindow(F("Main page")) {
  this->buttonServo.setClickHandler([](TerminalButton * button) {
    if (button->getWindow() && button->getWindow()->getScreen())
      button->getWindow()->getScreen()->addWindow(new ServoWindow());
  });

  this->buttonLed1.setClickHandler([](TerminalButton * button) {
    if (button->getWindow() && button->getWindow()->getScreen())
      button->getWindow()->getScreen()->addWindow(new LedWindow(1));
  });

  this->buttonLed2.setClickHandler([](TerminalButton * button) {
    if (button->getWindow() && button->getWindow()->getScreen())
      button->getWindow()->getScreen()->addWindow(new LedWindow(2));
  });

  this->buttonLed3.setClickHandler([](TerminalButton * button) {
    if (button->getWindow() && button->getWindow()->getScreen())
      button->getWindow()->getScreen()->addWindow(new LedWindow(3));
  });

  this->buttonReboot.setClickHandler([](TerminalButton * button) {
    if (button->getWindow())
      button->getWindow()->close();
  });

  //  this->checkEnabled.addLabel("Kapcs: ", labelPosLeft);
  //  this->numElapsed.addLabel("Szam: ", labelPosLeft);
  //  this->numElapsed.setMinMax(1, 2000);

  this->addControl(&this->buttonServo);
  this->addControl(&this->buttonLed1);
  this->addControl(&this->buttonLed2);
  this->addControl(&this->buttonLed3);
  this->addControl(&this->buttonReboot);
}

ServoWindow::ServoWindow(): TerminalWindow(F("Servo settings")) {

  this->checkUsage.addLabel(F("Usage: "), labelPosLeft);
  this->checkEnabled.addLabel(F("Enabled: "), labelPosLeft);
  this->numElapsed.addLabel(F("Rotation: "), labelPosLeft);

  this->addControl(&this->checkUsage);
  this->addControl(&this->checkEnabled);
  this->addControl(&this->numElapsed);
  this->addControl(&this->buttonSave);
  this->addControl(&this->buttonCancel);

  this->buttonSave.setClickHandler([](TerminalButton * button) {
    // save settings here!
  });

  this->buttonCancel.setClickHandler([](TerminalButton * button) {
    if (button->getWindow())
      button->getWindow()->close();
  });
}

LedWindow::LedWindow(int index): TerminalWindow(String("LED settings for #") + String(index)) {
  this->index = index;

  this->checkUsage.addLabel(F("Usage: "), labelPosLeft);

  this->addControl(&this->checkUsage);
  this->addControl(&this->buttonSave);
  this->addControl(&this->buttonCancel);

  this->buttonSave.setClickHandler([](TerminalButton * button) {
    // save settings here!
  });

  this->buttonCancel.setClickHandler([](TerminalButton * button) {
    if (button->getWindow())
      button->getWindow()->close();
  });
}
