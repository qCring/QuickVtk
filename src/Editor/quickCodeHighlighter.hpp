#pragma once

#include <QSyntaxHighlighter>
#include <QString>

namespace quick {

    namespace Code {

        class Editor;

        class Highlighter : public QSyntaxHighlighter {
        private:
            Editor* m_editor;
            QTextDocument* m_doc;
        public:
            Highlighter() = delete;
            Highlighter(Editor* editor);
            auto highlightBlock(const QString&) -> void override;
        };
    }
}
