#include "quickCodeDocument.hpp"

namespace quick {

    namespace Code {

        auto Document::bindQTextDocument(QTextDocument* document) -> void {
            this->m_document = document;
        }
    }
}
