#include <stdlib.h>

#include "quickAppWindow.hpp"

auto main(int argc, char *argv[]) -> int {

#ifdef  __APPLE__
    setenv("QML_BAD_GUI_RENDER_LOOP", "1", 1);
#endif

#ifdef _MSC_VER
    _putenv("QML_BAD_GUI_RENDER_LOOP=1");
    _putenv("QT_AUTO_SCREEN_SCALE_FACTOR=1");
#endif

    auto appWindow = new quick::App::Window();
    return appWindow->start(argc, argv);
}
