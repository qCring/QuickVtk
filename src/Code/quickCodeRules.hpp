#pragma once

#include <QRegExp>
#include <QTextCharFormat>

namespace quick {

    namespace Code {

        class Rules {
        public:
            struct HighlightRule {
                QRegExp pattern;
                QTextCharFormat format;
            };

            static QList<HighlightRule> highlightRules;
            static auto Init() -> void;
        };
    }
}
