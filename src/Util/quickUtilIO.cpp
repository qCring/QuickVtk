#include "quickUtilIO.hpp"

#include <QDirIterator>
#include <QFileDialog>

namespace quick {
    namespace Util {
        namespace IO {
            auto FilesFromDir(const QString& dir, QStringList filters) -> QStringList {
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

            auto FileFromDialog(const QString &title, const QString &filter) -> QString
            {
                return QFileDialog::getOpenFileName(0, title, 0, filter);
            }
        }
    }
}