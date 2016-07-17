#pragma once

#include "quickQmlRegister.hpp"
#include "quickNotification.hpp"

#include <QAbstractListModel>

namespace quick {
    class Notifications : public QAbstractListModel {
        Q_OBJECT
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
        Notifications();
    public:
        static Qml::Register::Controller<Notifications> Register;
        static Notifications* instance;
        static auto Create() -> void;
        auto rowCount(const QModelIndex& = QModelIndex()) const -> int;
        auto data(const QModelIndex&, int) const -> QVariant;
        auto roleNames() const -> QHash<int, QByteArray>;
        ~Notifications() = default;
    public slots:
        void addError(int, int, const QString&);
        void addWarning(const QString&);
        void addInfo(const QString&);
        void clear();
    };
}
