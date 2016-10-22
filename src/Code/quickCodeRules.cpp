#include "quickCodeRules.hpp"

#include "quickIO.hpp"
#include "quickAppInstance.hpp"

namespace quick {

    namespace Code {

        QList<Rules::HighlightRule> Rules::highlightRules;

        const QString Rules::Key::highlight = "highlight";
        const QString Rules::Key::scheme = "scheme";
        const QString Rules::Key::italic = "italic";
        const QString Rules::Key::color = "color";
        const QString Rules::Key::match = "match";
        const QString Rules::Key::bold = "bold";

        auto Rules::Init() -> void {
            auto json       = IO::Read::JsonFromUrl(App::Instance::GetResourceDir() + "/config/schemes/qml.json");
            auto schemeObj  = json[Key::scheme].toObject();
            auto hlArray    = schemeObj[Key::highlight].toArray();

            QTextCharFormat format;
            HighlightRule rule;
            QJsonObject hlObj;

            for (auto i = 0; i < hlArray.count(); ++i) {
                hlObj = hlArray.at(i).toObject();

                if (hlObj[Key::bold].toBool(false)) {
                    format.setFontWeight(QFont::Bold);
                }
                else {
                    format.setFontWeight(QFont::Normal);
                }

                if (hlObj[Key::italic].toBool(false)) {
                    format.setFontItalic(true);
                }
                else {
                    format.setFontItalic(false);
                }

                format.setForeground(QColor(hlObj[Key::color].toString("#fff")));

                rule.pattern    = QRegExp(hlObj[Key::match].toString());
                rule.format     = format;
                
                highlightRules.append(rule);
            }
        }
    }
}
