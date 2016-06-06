#include <stdlib.h>

#include "quickAppWindow.hpp"

auto main(int argc, char *argv[]) -> int {

#ifdef  __APPLE__
    setenv("QML_BAD_GUI_RENDER_LOOP", "1", 1);
#endif
    
    auto appWindow = new quick::App::Window();
    return appWindow->start(argc, argv);
}
