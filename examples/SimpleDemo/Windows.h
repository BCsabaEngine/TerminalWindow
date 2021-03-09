#ifndef Windows_h
#define Windows_h

#include <TerminalWindow.h>
#include <TerminalControl.h>
#include <TerminalLabel.h>
#include <TerminalButton.h>
#include <TerminalCheckbox.h>
#include <TerminalNumEdit.h>

class MainWindow : public TerminalWindow {
  private:
    TerminalButton buttonServo = TerminalButton(4, 1, 12, "Servos");
    TerminalButton buttonLed1 = TerminalButton(4, 3, 12, "LED #1");
    TerminalButton buttonLed2 = TerminalButton(4, 5, 12, "LED #2");
    TerminalButton buttonLed3 = TerminalButton(4, 7, 12, "LED #3");
    TerminalButton buttonReboot = TerminalButton(4, 9, 12, "Reboot");
  public:
    MainWindow();
    virtual ~MainWindow() {}
};

class ServoWindow : public TerminalWindow {
  private:
    TerminalCheckbox checkUsage = TerminalCheckbox(12, 1, 4);
    TerminalCheckbox checkEnabled = TerminalCheckbox(12, 3, 10, "Enabled", "Disabled");
    TerminalNumEdit numElapsed = TerminalNumEdit(12, 5, 4);

    TerminalButton buttonSave = TerminalButton(4, 8, 8, "Save");
    TerminalButton buttonCancel = TerminalButton(18, 8, 8, "Cancel");
  public:
    ServoWindow();
    virtual ~ServoWindow() {}
};

class LedWindow : public TerminalWindow {
  private:
    int index;

    TerminalCheckbox checkUsage = TerminalCheckbox(12, 1, 4);

    TerminalButton buttonSave = TerminalButton(4, 8, 8, "Save");
    TerminalButton buttonCancel = TerminalButton(18, 8, 8, "Cancel");
  public:
    LedWindow(int index);
    virtual ~LedWindow() {}
};

#endif
