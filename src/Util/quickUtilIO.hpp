#pragma once

#include <QStringList>

namespace quick {
    namespace Util {
        namespace IO {
            auto FilesFromDir(const QString& dir, QStringList filters) -> QStringList;
        }
    }
}