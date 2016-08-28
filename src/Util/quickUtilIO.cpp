#include "quickUtilIO.hpp"

#include <QDirIterator>
#include <QTextStream>
#include <QFileDialog>

namespace quick {

    namespace Util {

        namespace IO {

            namespace FromDialog {

                auto SelectSaveFileUrl(const QString& filter, const QString& title) -> const QString {
                    return QFileDialog::getSaveFileName(0, title, 0, filter);
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

                auto TextToFile(const QString& text, const QString& url) -> void {
                    QFile file(url);

                    if (file.exists() && file.open(QIODevice::WriteOnly)) {
                        QTextStream stream (&file);
                        stream << text;
                        file.close();
                    }
                }
            }

            auto FileUrlsFromDir(const QString& dir, QStringList filters) -> QStringList {
                QDirIterator it(dir, filters, QDir::Files);
                QStringList fileList;

                while (it.hasNext())
                {
                    auto path = it.next();
                    auto file = it.fileName();

                    fileList.append(path);
                }
                
                return fileList;
            }

            auto FileExists(const QString& filePath) -> bool {
                QFile file(filePath);
                return file.exists();
            }
        }
    }
}