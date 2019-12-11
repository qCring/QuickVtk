#pragma once

#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace quick {

    namespace IO {

        enum class FileSuffix {
            On,
            Off
        };

        namespace FromDialog {
            auto SelectSaveFileUrl(const QString& title = "Save File") -> const QString;
            auto SelectOpenFileUrl(const QString& filter, const QString& title = "Open File") -> const QString;
        }

        namespace Read {
            auto JsonFromUrl(const QString&) -> QJsonObject;
            auto TextFromUrl(const QString&) -> QString;
        }

        namespace Write {
            auto TextToFile(const QString& text, const QString& url) -> bool;
        }

        auto FileNameFromPath(const QString& path) -> QString;
        auto FileUrlsFromDir(const QString& dir, QStringList filters, FileSuffix) -> QStringList;
        auto FileNamesFromDir(const QString& dir, QStringList filters, FileSuffix) -> QStringList;
        auto FileExists(const QString& filePath) -> bool;
    }
}
