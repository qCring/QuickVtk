#pragma once

#include <QSyntaxHighlighter>
#include <QString>

namespace quick {

    namespace Editor {

        class Highlighter : public QSyntaxHighlighter {
        private:
            struct Key {
                static constexpr auto highlight = "highlight";
                static constexpr auto scheme = "scheme";
                static constexpr auto italic = "italic";
                static constexpr auto color = "color";
                static constexpr auto match = "match";
                static constexpr auto bold = "bold";
            };
            struct Rule {
                QRegExp pattern;
                QTextCharFormat format;
            };
            QList<Rule> m_rules;
        public:
            Highlighter(QTextDocument*);
            auto init() -> void;
            auto highlightBlock(const QString&) -> void override;
        };
    }
}
