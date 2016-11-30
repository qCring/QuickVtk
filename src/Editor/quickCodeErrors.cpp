#include "quickCodeErrors.hpp"

namespace quick {

    namespace Code {

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

        void Errors::add(int line, int column, const QString& message) {
            if (this->m_preList.count() > 0) {
                for (auto& error : this->m_preList) {
                    if (error.line == line) {
                        error.message += "; " + message;
                        return;
                    }
                }
            }

            Error error;
            error.line = line;
            error.column = column;
            error.message = message;
            this->m_preList.append(error);
        }

        void Errors::update() {
            for (auto i = 0; i < this->m_preList.count(); ++i) {
                auto error = this->m_preList.at(i);
                beginInsertRows(QModelIndex(), i, i);
                this->m_errors.append(error);
                endInsertRows();
            }

            this->m_preList.clear();

            emit this->countChanged();
        }

        auto Errors::clear() -> void {
            beginResetModel();
            this->m_errors.clear();
            endResetModel();

            emit this->countChanged();
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
        
        auto Errors::getCount() -> int {
            return this->m_errors.count();
        }
    }
}
