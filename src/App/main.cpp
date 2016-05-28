#include <stdlib.h>
#include <iostream>

#include "quickApp.hpp"

auto main(int argc, char *argv[]) -> int {
    auto app = new quick::App();

    app->setAppName("QuickVtk");
    app->setVersionString("0.0.1");
    app->setResourceFile("/qml/window.qml");

    return app->exec(argc, argv);
}
