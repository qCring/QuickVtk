#include <stdlib.h>
#include <stdio.h>

#include "quickAppEngine.hpp"

auto main(int argc, char *argv[]) -> int {

#ifdef _MSC_VER
    _putenv("QML_BAD_GUI_RENDER_LOOP=1");
    _putenv("QT_AUTO_SCREEN_SCALE_FACTOR=1");
    _putenv("QML_USE_GLYPHCACHE_WORKAROUND=1");
#else
    setenv("QML_BAD_GUI_RENDER_LOOP", "1", 1);
    setenv("QML_USE_GLYPHCACHE_WORKAROUND", "1", 1);
#endif

    return quick::App::Engine::Execute(argc, argv);
}
