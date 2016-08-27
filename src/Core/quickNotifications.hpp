#pragma once

#include "quickQmlRegister.hpp"
#include "quickNotification.hpp"

#include <QAbstractListModel>

namespace quick {
    class Notifications : public QAbstractListModel {
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
        QList<Notification> m_notifications;
        int m_errorCount = 0;
        int m_warningCount = 0;
        Notifications();
    public:
        static Qml::Register::Controller<Notifications> Register;
        static Notifications* instance;
        static auto Create() -> void;
        auto rowCount(const QModelIndex& = QModelIndex()) const -> int;
        auto data(const QModelIndex&, int) const -> QVariant;
        auto roleNames() const -> QHash<int, QByteArray>;
        auto getErrorCount() -> int;
        auto getWarningCount() -> int;
        ~Notifications() = default;
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
