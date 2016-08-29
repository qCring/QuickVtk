#pragma once

#include "quickQmlRegister.hpp"

#include <QAbstractListModel>

namespace quick {

    namespace Code {

        struct Issue {
            bool isError = false;
            bool isWarning = false;
            bool isInfo = false;
            unsigned int line;
            unsigned int column;
            QString message;
        };

        class Issues : public QAbstractListModel {
            Q_OBJECT
            Q_PROPERTY(int errorCount READ getErrorCount NOTIFY errorCountChanged);
            Q_PROPERTY(int warningCount READ getWarningCount NOTIFY warningCountChanged);
        public:
            enum Roles {
                LineRole = Qt::UserRole + 1,
                ColumnRole,
                MessageRole,
                IsErrorRole,
                IsWarningRole,
                IsInfoRole
            };
        private:
            QList<Issue> m_issues;
            int m_errorCount = 0;
            int m_warningCount = 0;
            Issues();
        public:
            static Qml::Register::Controller<Issues> Register;
            static Issues* instance;
            static auto Create() -> void;
            auto rowCount(const QModelIndex& = QModelIndex()) const -> int;
            auto data(const QModelIndex&, int) const -> QVariant;
            auto roleNames() const -> QHash<int, QByteArray>;
            auto getErrorCount() -> int;
            auto getWarningCount() -> int;
            ~Issues() = default;
        public slots:
            void addError(int, int, const QString&);
            void addWarning(const QString&);
            void addInfo(const QString&);
            void clear();
        signals:
            void errorCountChanged();
            void warningCountChanged();
        };
    }
}