#pragma once

#include <QString>

namespace quick {
    struct Notification {
        bool isError = false;
        bool isWarning = false;
        bool isInfo = false;
        unsigned int line;
        unsigned int column;
        QString message;
    };
}