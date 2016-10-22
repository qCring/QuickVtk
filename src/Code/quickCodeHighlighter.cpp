#include "quickCodeHighlighter.hpp"
#include "quickCodeEditor.hpp"
#include "quickCodeRules.hpp"

#include <QTextBlock>

namespace quick {

    namespace Code {

        Highlighter::Highlighter(Editor* editor) : QSyntaxHighlighter(editor->getDocument()->textDocument()) {
            this->m_doc         = editor->getDocument()->textDocument();
            this->m_editor      = editor;

            Rules::Init();
        }

        auto Highlighter::highlightBlock(const QString& text) -> void {
            for (auto rule : Rules::highlightRules) {
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
