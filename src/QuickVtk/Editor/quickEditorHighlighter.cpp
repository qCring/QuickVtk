#include "quickEditorHighlighter.hpp"

#include "quickIO.hpp"
#include "quickAppInstance.hpp"

#include <QTextBlock>

namespace quick {

    namespace Editor {

        Highlighter::Highlighter(QTextDocument* document) : QSyntaxHighlighter(document) {
            this->init();
        }

        auto Highlighter::init() -> void {
            auto json = IO::Read::JsonFromUrl(App::Instance::GetResourceDir() + "/config/schemes/qml.json");
            auto rootObject = json[Key::scheme].toObject();
            auto ruleObjects = rootObject[Key::highlight].toArray();

            QTextCharFormat format;
            Rule rule;
            QJsonObject ruleObject;

            for (auto i = 0; i < ruleObjects.count(); ++i) {
                ruleObject = ruleObjects.at(i).toObject();

                if (ruleObject[Key::bold].toBool(false)) {
                    format.setFontWeight(QFont::Bold);
                }
                else {
                    format.setFontWeight(QFont::Normal);
                }

                if (ruleObject[Key::italic].toBool(false)) {
                    format.setFontItalic(true);
                }
                else {
                    format.setFontItalic(false);
                }

                format.setForeground(QColor(ruleObject[Key::color].toString("#fff")));

                rule.pattern = QRegExp(ruleObject[Key::match].toString());
                rule.format = format;

                this->m_rules.append(rule);
            }
        }

        auto Highlighter::highlightBlock(const QString& text) -> void {
            for (auto rule : this->m_rules) {
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
