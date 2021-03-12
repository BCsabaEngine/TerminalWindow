# TerminalWindow
Arduino TerminalWindow on ANSI/VT220 screens.

If you're having trouble configuring your Arduino without uploading new code, here's the solution!

I often face the fact that I would have to set something up without modifying the Arduino sketch. I do not want to use a potentiometer or DIP switches for this. I simply enter the COM port and set up the data I need.

# Usage

Just connect your Arduino devices to the COM port, open a terminal window (putty or SmarTTY) and use the keyboard to adjust the parameters. Utilizing the capabilities of the VT220, you can easily create simple parameterization windows for your Arduino devices. You can also create buttons, check boxes, number entry fields, and new windows in the user interface.

![Usage](https://github.com/BCsabaEngine/TerminalWindow/blob/main/docs/demo.gif?raw=true)

You can read the settings from EEPROM or SD card and write them back there. This is your business.

# Usable components

You can use the following components with these parameters and methods:
```
TerminalButton btn1 = TerminalButton(byte x, byte y, byte width, String text);
btn1.addLabel(String text, LabelPos labelpos); // Add label for control (top or left)
btn1.setClickHandler([](TerminalButton * button) { /*insert event code here */ });
btn1.setText(String text);

TerminalCheckbox cb1 = TerminalCheckbox(byte x, byte y, byte width, String ontext = "x", String offtext = " ");
cb1.addLabel(String text, LabelPos labelpos);
cb1.setChangeHandler([](TerminalCheckbox * checkbox, bool value) { /*insert event code here */ });
cb1.getValue();
cb1.setValue(bool value);

TerminalLabel label1 = TerminalLabel(byte x, byte y, byte width, String text, HAlign halign = hAlignLeft);
label1.setText(String text);

TerminalNumEdit num1 = TerminalNumEdit(byte x, byte y, byte width);
num1.addLabel(String text, LabelPos labelpos);
num1.setChangeHandler([](TerminalNumEdit * numedit, int value) { /*insert event code here */ });
num1.setMinMax(int min, int max);
num1.getValue();
num1.setValue(int value);
num1.incValue(int increment = 1);
num1.decValue(int decrement = 1);
```

In event handler you can access the control, the window and the screen system:
```
btn1.setClickHandler([](TerminalButton * button) {
  // Set button text
  button.setText("New text");

  // Close button's windows
  button->getWindow()->close();

  // Create a new window on button's window's screen (THE screen)
  button->getWindow()->getScreen()->addWindow(new LedWindow(3));
  // ... or shorter access
  button->getScreen()->addWindow(new LedWindow(3));
});
```

In the directory you can freely set how you allow the user to navigate: you can move with the up / down arrows or the TAB. Use the Space and Enter keys to set the checkboxes. Close the window with ESC. etc...
```
#define WINDOW_CLOSE_ESC
#define CONTROL_MOVE_UP_DOWN
#define CONTROL_MOVE_LEFT_RIGHT
#define CONTROL_MOVE_TAB
#define CONTROL_BUTTON_SPACE
#define CONTROL_BUTTON_ENTER
#define CONTROL_CHECKBOX_SPACE
#define CONTROL_CHECKBOX_ENTER
#define CONTROL_CHECKBOX_UP_DOWN
#define CONTROL_CHECKBOX_LEFT_RIGHT
#define CONTROL_EDIT_UP_DOWN
#define CONTROL_EDIT_LEFT_RIGHT
```

# Created by
Csaba Balazs, March 08, 2021
