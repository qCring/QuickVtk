#pragma once

#include <QStringList>

namespace quick {
    namespace Util {
        namespace IO {
            auto FilesFromDir(const QString& dir, QStringList filters) -> QStringList;
            auto FileFromDialog(const QString &title, const QString &filter) -> QString;
            auto ReadTextFromFile(const QString& filePath) -> QString;
            auto FileExists(const QString& filePath) -> bool;
        }
    }
}