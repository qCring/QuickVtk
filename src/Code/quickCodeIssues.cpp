#include "quickCodeIssues.hpp"

namespace quick {

    namespace Code {

        Issues* Issues::instance = nullptr;

        Qml::Register::Controller<Issues> Issues::Register;

        Issues::Issues() {
            if (instance) {
                throw std::runtime_error("instance already existing");
            }
        }

        auto Issues::Create() -> void {
            instance = new Issues();
        }

        void Issues::addError(int line, int column, const QString& message) {
            auto index = this->m_issues.count();

            Issue issue;
            issue.line = line;
            issue.isError = true;
            issue.column = column;
            issue.message = message;

            beginInsertRows(QModelIndex(), index, index);
            this->m_issues.append(issue);
            endInsertRows();

            ++this->m_errorCount;
            emit this->errorCountChanged();
        }

        void Issues::addWarning(const QString& message) {
            auto index = this->m_issues.count();

            Issue issue;
            issue.isWarning = true;
            issue.message = message;

            beginInsertRows(QModelIndex(), index, index);
            this->m_issues.append(issue);
            endInsertRows();

            ++this->m_warningCount;
            emit this->warningCountChanged();
        }

        void Issues::addInfo(const QString& message) {
            auto index = this->m_issues.count();

            Issue issue;
            issue.isInfo = true;
            issue.message = message;

            beginInsertRows(QModelIndex(), index, index);
            this->m_issues.append(issue);
            endInsertRows();
        }

        auto Issues::clear() -> void {
            beginResetModel();
            this->m_issues.clear();
            endResetModel();

            this->m_errorCount = this->m_warningCount = 0;

            emit this->errorCountChanged();
            emit this->warningCountChanged();
        }

        auto Issues::roleNames() const -> QHash<int, QByteArray> {
            QHash<int, QByteArray> roles;
            roles[LineRole] = "line";
            roles[ColumnRole] = "column";
            roles[MessageRole] = "message";
            roles[IsErrorRole] = "isError";
            roles[IsWarningRole] = "isWarning";
            roles[IsInfoRole] = "isInfo";

            return roles;
        }

        auto Issues::data(const QModelIndex& index, int role) const -> QVariant {
            QVariant var;

            if (index.isValid()) {
                if (role == LineRole) {
                    var.setValue(this->m_issues.at(index.row()).line);
                } else if (role == ColumnRole) {
                    var.setValue(this->m_issues.at(index.row()).column);
                } else if (role == MessageRole) {
                    var.setValue(this->m_issues.at(index.row()).message);
                } else if (role == IsErrorRole) {
                    var.setValue(this->m_issues.at(index.row()).isError);
                } else if (role == IsWarningRole) {
                    var.setValue(this->m_issues.at(index.row()).isWarning);
                } else if (role == IsInfoRole) {
                    var.setValue(this->m_issues.at(index.row()).isInfo);
                }
            }
            
            return var;
        }
        
        auto Issues::rowCount(const QModelIndex&) const -> int {
            return this->m_issues.size();
        }
        
        auto Issues::getErrorCount() -> int {
            return this->m_errorCount;
        }
        
        auto Issues::getWarningCount() -> int {
            return this->m_warningCount;
        }
    }
}