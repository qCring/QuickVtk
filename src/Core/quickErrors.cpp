#include "quickErrors.hpp"

namespace quick {

    Errors* Errors::instance = nullptr;

    Qml::Register::Controller<Errors> Errors::Register;

    Errors::Errors() {
        if (instance) {
            throw std::runtime_error("instance already existing");
        }
    }

    auto Errors::Create() -> void {
        instance = new Errors();
    }

    auto Errors::add(int line, int column, const QString& message) -> void {
        auto index = this->m_errors.count();

        Error error;
        error.line = line;
        error.column = column;
        error.message = message;

        beginInsertRows(QModelIndex(), index, index);
        this->m_errors.append(error);
        endInsertRows();
    }

    auto Errors::clear() -> void {
        beginResetModel();
        this->m_errors.clear();
        endResetModel();
    }

    auto Errors::roleNames() const -> QHash<int, QByteArray> {
        QHash<int, QByteArray> roles;
        roles[LineRole] = "line";
        roles[ColumnRole] = "column";
        roles[MessageRole] = "message";

        return roles;
    }

    auto Errors::data(const QModelIndex& index, int role) const -> QVariant {
        QVariant var;

        if (index.isValid()) {
            if (role == LineRole) {
                var.setValue(this->m_errors.at(index.row()).line);
            } else if (role == ColumnRole) {
                var.setValue(this->m_errors.at(index.row()).column);
            } else if (role == MessageRole) {
                var.setValue(this->m_errors.at(index.row()).message);
            }
        }

        return var;
    }

    auto Errors::rowCount(const QModelIndex&) const -> int {
        return this->m_errors.size();
    }
}
