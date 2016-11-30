#pragma once

#include <QRegExp>
#include <QTextCharFormat>

namespace quick {

    namespace Code {

        class Scheme {
        private:
            struct JsonKey {
                static const QString highlight;
                static const QString scheme;
                static const QString italic;
                static const QString color;
                static const QString match;
                static const QString bold;
            };
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
