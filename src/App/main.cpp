#include <stdlib.h>

#include "quickAppWindow.hpp"

auto main(int argc, char *argv[]) -> int {
    auto appWindow = new quick::App::Window();
    return appWindow->start(argc, argv);
}
