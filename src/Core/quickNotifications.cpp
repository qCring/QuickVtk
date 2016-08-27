#include "quickNotifications.hpp"

namespace quick {

    Notifications* Notifications::instance = nullptr;

    Qml::Register::Controller<Notifications> Notifications::Register;

    Notifications::Notifications() {
        if (instance) {
            throw std::runtime_error("instance already existing");
        }
    }

    auto Notifications::Create() -> void {
        instance = new Notifications();
    }

    void Notifications::addError(int line, int column, const QString& message) {
        auto index = this->m_notifications.count();

        Notification notification;
        notification.line = line;
        notification.isError = true;
        notification.column = column;
        notification.message = message;

        beginInsertRows(QModelIndex(), index, index);
        this->m_notifications.append(notification);
        endInsertRows();

        ++this->m_errorCount;
        emit this->errorCountChanged();
    }

    void Notifications::addWarning(const QString& message) {
        auto index = this->m_notifications.count();

        Notification notification;
        notification.isWarning = true;
        notification.message = message;

        beginInsertRows(QModelIndex(), index, index);
        this->m_notifications.append(notification);
        endInsertRows();

        ++this->m_warningCount;
        emit this->warningCountChanged();
    }

    void Notifications::addInfo(const QString& message) {
        auto index = this->m_notifications.count();

        Notification notification;
        notification.isInfo = true;
        notification.message = message;

        beginInsertRows(QModelIndex(), index, index);
        this->m_notifications.append(notification);
        endInsertRows();
    }

    auto Notifications::clear() -> void {
        beginResetModel();
        this->m_notifications.clear();
        endResetModel();

        this->m_errorCount = this->m_warningCount = 0;

        emit this->errorCountChanged();
        emit this->warningCountChanged();
    }

    auto Notifications::roleNames() const -> QHash<int, QByteArray> {
        QHash<int, QByteArray> roles;
        roles[LineRole] = "line";
        roles[ColumnRole] = "column";
        roles[MessageRole] = "message";
        roles[IsErrorRole] = "isError";
        roles[IsWarningRole] = "isWarning";
        roles[IsInfoRole] = "isInfo";

        return roles;
    }

    auto Notifications::data(const QModelIndex& index, int role) const -> QVariant {
        QVariant var;

        if (index.isValid()) {
            if (role == LineRole) {
                var.setValue(this->m_notifications.at(index.row()).line);
            } else if (role == ColumnRole) {
                var.setValue(this->m_notifications.at(index.row()).column);
            } else if (role == MessageRole) {
                var.setValue(this->m_notifications.at(index.row()).message);
            } else if (role == IsErrorRole) {
                var.setValue(this->m_notifications.at(index.row()).isError);
            } else if (role == IsWarningRole) {
                var.setValue(this->m_notifications.at(index.row()).isWarning);
            } else if (role == IsInfoRole) {
                var.setValue(this->m_notifications.at(index.row()).isInfo);
            }
        }

        return var;
    }

    auto Notifications::rowCount(const QModelIndex&) const -> int {
        return this->m_notifications.size();
    }

    auto Notifications::getErrorCount() -> int {
        return this->m_errorCount;
    }

    auto Notifications::getWarningCount() -> int {
        return this->m_warningCount;
    }
}
