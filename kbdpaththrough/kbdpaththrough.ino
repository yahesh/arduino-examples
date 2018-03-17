#include <hidboot.h>

class KbdRptParser : public KeyboardReportParser {
    private:
        void handleModifiers(uint8_t mod);
    protected:
        virtual void OnKeyDown(uint8_t mod, uint8_t key);
        virtual void OnKeyUp(uint8_t mod, uint8_t key);
        virtual void OnKeyPressed(uint8_t key);
};

void KbdRptParser::handleModifiers(uint8_t mod) {
    MODIFIERKEYS modifier;
    *((uint8_t*)&modifier) = mod;

    if (modifier.bmLeftCtrl == 1) {
        Keyboard.pressKeycode(KEYCODE_LEFT_CTRL, false);
    } else {
        Keyboard.releaseKeycode(KEYCODE_LEFT_CTRL, false);
    }
    if (modifier.bmLeftShift == 1) {
        Keyboard.pressKeycode(KEYCODE_LEFT_SHIFT, false);
    } else {
        Keyboard.releaseKeycode(KEYCODE_LEFT_SHIFT, false);
    }
    if (modifier.bmLeftAlt == 1) {
        Keyboard.pressKeycode(KEYCODE_LEFT_ALT, false);
    } else {
        Keyboard.releaseKeycode(KEYCODE_LEFT_ALT, false);
    }
    if (modifier.bmLeftGUI == 1) {
        Keyboard.pressKeycode(KEYCODE_LEFT_GUI, false);
    } else {
        Keyboard.releaseKeycode(KEYCODE_LEFT_GUI, false);
    }
    
    if (modifier.bmRightCtrl == 1) {
        Keyboard.pressKeycode(KEYCODE_RIGHT_CTRL, false);
    } else {
        Keyboard.releaseKeycode(KEYCODE_RIGHT_CTRL, false);
    }
    if (modifier.bmRightShift == 1) {
        Keyboard.pressKeycode(KEYCODE_RIGHT_SHIFT, false);
    } else {
        Keyboard.releaseKeycode(KEYCODE_RIGHT_SHIFT, false);
    }
    if (modifier.bmRightAlt == 1) {
        Keyboard.pressKeycode(KEYCODE_RIGHT_ALT, false);
    } else {
        Keyboard.releaseKeycode(KEYCODE_RIGHT_ALT, false);
    }
    if (modifier.bmRightGUI == 1) {
        Keyboard.pressKeycode(KEYCODE_RIGHT_GUI, false);
    } else {
        Keyboard.releaseKeycode(KEYCODE_RIGHT_GUI, false);
    }
}

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key) {
    if (digitalRead(2) == LOW) {
        handleModifiers(mod);
        Keyboard.pressKeycode(key, true);
    }
}

void KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key)    
{
    if (digitalRead(2) == LOW) {
        handleModifiers(mod);
        Keyboard.releaseKeycode(key, true);
    }  
}

void KbdRptParser::OnKeyPressed(uint8_t key)    
{
    // do nothing
};

USB                            HidUsb;
HIDBoot<HID_PROTOCOL_KEYBOARD> HidKeyboard(&HidUsb);
KbdRptParser                   HidKeyboardParser;

void setup() {
    if (HidUsb.Init() != -1) {
        // activate Arduino Leonardo HID keyboard driver
        Keyboard.begin();

        // enable security pin
        // will only work when
        // PIN 2 is connected to ground
        pinMode(2, INPUT);
        digitalWrite(2, HIGH);

        HidKeyboard.SetReportParser(0, (HIDReportParser*)&HidKeyboardParser);
    }
}

void loop() {
    HidUsb.Task();
}
