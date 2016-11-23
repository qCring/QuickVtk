#include "quickCodeHighlighter.hpp"
#include "quickCodeEditor.hpp"
#include "quickCodeScheme.hpp"

#include <QTextBlock>

namespace quick {

    namespace Code {

        Highlighter::Highlighter(Editor* editor) : QSyntaxHighlighter(editor->getEditorDocument()->textDocument()) {
            this->m_doc = editor->getEditorDocument()->textDocument();
            this->m_editor = editor;

            Scheme::Init();
        }

        auto Highlighter::highlightBlock(const QString& text) -> void {
            for (auto rule : Scheme::highlightRules) {
                auto expression = QRegExp(rule.pattern);
                auto index = expression.indexIn(text);

                while (index >= 0) {
                    auto length = expression.matchedLength();
                    setFormat(index, length, rule.format);
                    index = expression.indexIn(text, index + length);
                }
            }
        }
    }
}
