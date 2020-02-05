#include "quickDocumentError.hpp"

namespace quick::Document {
    
    Qml::Register::Type<Error> Error::Register;

    Error::Error(int line, int column, const QString& message) : m_line(line), m_column(column), m_message(message) {
    }

    auto Error::getLine() -> int {
        return this->m_line;
    }

    auto Error::getColumn() -> int {
        return this->m_column;
    }

    auto Error::getMessage() -> QString {
        return this->m_message;
    }
}
