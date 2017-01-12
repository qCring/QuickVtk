#include "quickEditorUtil.hpp"

#include "quickEditorController.hpp"
#include "quickEditorSelection.hpp"

#include <QTextBlock>

namespace quick {

    namespace Editor {

        QTextDocument* Util::document = nullptr;

        auto Util::GetLine(const int line) -> QString {
            auto block = document->findBlockByLineNumber(line);

            return block.isValid() ? block.text() : nullptr;
        }

        auto Util::GetCursor(const int position) -> QTextCursor {
            auto cursor = QTextCursor(document);

            cursor.setPosition(position);
            return cursor;
        }

        auto Util::GetChar(const int position) -> QChar {
            return document->characterAt(position);
        }
    }
}
