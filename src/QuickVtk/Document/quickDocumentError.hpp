#pragma once

#include "quickQmlRegister.hpp"

#include <QAbstractListModel>

namespace quick {
    namespace Document {

        class Error : public QObject {
            Q_OBJECT
            Q_PROPERTY(int line READ getLine CONSTANT);
            Q_PROPERTY(int column READ getColumn CONSTANT);
            Q_PROPERTY(QString message READ getMessage CONSTANT);
        private:
            static Qml::Register::Type<Error> Register;
            int m_line;
            int m_column;
            QString m_message;
        public:
            Error(int, int, const QString&);
            auto getLine() -> int;
            auto getColumn() -> int;
            auto getMessage() -> QString;
        };
    }
}
