#pragma once

#include <QObject>
#include <QTextDocument>

namespace quick {

    namespace Code {

        class Document : public QObject {
            Q_OBJECT
        private:
            QTextDocument* m_document = nullptr;
        public:
            auto bindQTextDocument(QTextDocument*) -> void;
        };
    }
}
