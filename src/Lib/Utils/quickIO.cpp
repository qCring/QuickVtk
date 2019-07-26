#include "quickIO.hpp"

#include <QDirIterator>
#include <QTextStream>
#include <QFileDialog>

namespace quick {

    namespace IO {

        namespace FromDialog {

            auto SelectSaveFileUrl(const QString& title) -> const QString {
                auto ret = QFileDialog::getSaveFileName(0, title, 0);
                return ret;
            }

            auto SelectOpenFileUrl(const QString& filter, const QString& title) -> const QString {
                return QFileDialog::getOpenFileName(0, title, 0, filter);
            }
        }

        namespace Read {

            auto JsonFromUrl(const QString& url) -> QJsonObject {
                QFile file(url);

                if (file.open(QIODevice::ReadOnly)) {
                    return QJsonDocument::fromJson(file.readAll()).object();
                }

                return QJsonObject();
            }

            auto TextFromUrl(const QString& url) -> QString {
                QString text;
                QFile file(url);

                if (file.exists() && file.open(QIODevice::ReadOnly)) {
                    QTextStream stream(&file);
                    text = file.readAll();
                    file.close();
                }

                return text;
            }
        }

        namespace Write {

            auto TextToFile(const QString& text, const QString& url) -> bool {
                QFile file(url);

                if (file.open(QIODevice::WriteOnly)) {
                    QTextStream stream (&file);
                    stream << text;
                    file.close();

                    return true;
                }

                return false;
            }
        }

        auto FileNamesFromDir(const QString& dir, QStringList filters, FileSuffix option) -> QStringList {
            QDirIterator it(dir, filters, QDir::Files);
            QStringList names;

            if (option == FileSuffix::On) {
                while (it.hasNext()) {
                    it.next();
                    names.append(it.fileInfo().fileName());
                }
            } else {
                while (it.hasNext()) {
                    it.next();
                    names.append(it.fileInfo().baseName());
                }
            }

            return names;
        }

        auto FileUrlsFromDir(const QString& dir, QStringList filters, FileSuffix option) -> QStringList {

            QDirIterator it(dir, filters, QDir::Files);
            QStringList urls;
            QString path = dir + "/";

            if (option == FileSuffix::On) {
                while (it.hasNext()) {
                    urls.append(it.next());
                }
            } else {
                while (it.hasNext()) {
                    it.next();
                    urls.append(path + it.fileInfo().baseName());
                }
            }

            return urls;
        }

        auto FileExists(const QString& filePath) -> bool {
            QFile file(filePath);
            return file.exists();
        }
    }
}
