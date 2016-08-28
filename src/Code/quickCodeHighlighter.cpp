#include "quickCodeHighlighter.hpp"
#include "quickCodeEditor.hpp"
#include "quickAppInstance.hpp"
#include "quickUtilIO.hpp"

#include <QTextBlock>

namespace quick {

    namespace Code {

        Highlighter::Highlighter(Editor* editor) : QSyntaxHighlighter(editor->getDocument()->textDocument()) {
            this->m_doc         = editor->getDocument()->textDocument();
            this->m_editor      = editor;

            this->init();
        }

        auto Highlighter::init() -> void {
            auto json       = Util::IO::Read::JsonFromUrl(App::Instance::GetResourceDir() + "/config/schemes/qml.json");
            auto schemeObj  = json["scheme"].toObject();
            auto hlArray    = schemeObj["highlight"].toArray();

            QTextCharFormat format;
            Rule rule;
            QJsonObject hlObj;

            for (auto i = 0; i < hlArray.count(); ++i) {
                hlObj = hlArray.at(i).toObject();

                if (hlObj["bold"].toBool(false)) {
                    format.setFontWeight(QFont::Bold);
                }
                else {
                    format.setFontWeight(QFont::Normal);
                }

                if (hlObj["italic"].toBool(false)) {
                    format.setFontItalic(true);
                }
                else {
                    format.setFontItalic(false);
                }

                format.setForeground(QColor(hlObj["color"].toString("#fff")));

                rule.pattern    = QRegExp(hlObj["pattern"].toString());
                rule.format     = format;

                this->m_rules.append(rule);
            }
        }

        auto Highlighter::highlightBlock(const QString& text) -> void {
            for (auto rule : this->m_rules)
            {
                auto expression = QRegExp(rule.pattern);
                auto index = expression.indexIn(text);

                while (index >= 0)
                {
                    auto length = expression.matchedLength();
                    setFormat(index, length, rule.format);
                    index = expression.indexIn(text, index + length);
                }
            }
        }
    }
}
