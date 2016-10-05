#pragma once

#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace quick {

    namespace IO {

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

        auto FileUrlsFromDir(const QString& dir, QStringList filters) -> QStringList;
        auto FileExists(const QString& filePath) -> bool;
    }
}
