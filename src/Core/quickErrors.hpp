#pragma once

#include "quickQmlRegister.hpp"
#include "quickError.hpp"

#include <QAbstractListModel>

namespace quick {
    class Errors : public QAbstractListModel {
        Q_OBJECT
    public:
        enum Roles {
            LineRole = Qt::UserRole + 1,
            ColumnRole,
            MessageRole
        };
    private:
        QList<Error> m_errors;
        Errors();
    public:
        static Qml::Register::Controller<Errors> Register;
        static Errors* instance;
        static auto Create() -> void;
        auto rowCount(const QModelIndex& = QModelIndex()) const -> int;
        auto data(const QModelIndex&, int) const -> QVariant;
        auto roleNames() const -> QHash<int, QByteArray>;
        ~Errors() = default;
    public slots:
        void add(int, int, const QString&);
        void clear();
    };
}
