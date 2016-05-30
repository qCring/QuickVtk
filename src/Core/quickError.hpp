#pragma once

#include <QString>

namespace quick {
    struct Error {
        unsigned int line;
        unsigned int column;
        QString message;
    };
}