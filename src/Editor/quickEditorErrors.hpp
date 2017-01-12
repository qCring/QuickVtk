#pragma once

#include "quickQmlRegister.hpp"

#include <QAbstractListModel>

namespace quick {

    namespace Editor {

        struct Error {
            unsigned int line;
            unsigned int column;
            QString message;
        };

        class Errors : public QAbstractListModel {
            Q_OBJECT
            Q_PROPERTY(int count READ getCount NOTIFY countChanged);
        public:
            enum Roles {
                LineRole = Qt::UserRole + 1,
                ColumnRole,
                MessageRole
            };
        private:
            QList<Error> m_preList;
            QList<Error> m_errors;
            Errors();
        public:
            static Qml::Register::Controller<Errors> Register;
            static Errors* instance;
            static auto Create() -> void;
            auto rowCount(const QModelIndex& = QModelIndex()) const -> int;
            auto data(const QModelIndex&, int) const -> QVariant;
            auto roleNames() const -> QHash<int, QByteArray>;
            auto getCount() -> int;
            public slots:
            void update();
            void add(int, int, const QString&);
            void clear();
        signals:
            void countChanged();
        };
    }
}
