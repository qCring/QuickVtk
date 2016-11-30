#include "quickCodeScheme.hpp"

#include "quickIO.hpp"
#include "quickAppInstance.hpp"

namespace quick {

    namespace Code {

        QList<Scheme::HighlightRule> Scheme::highlightRules;

        const QString Scheme::JsonKey::highlight = "highlight";
        const QString Scheme::JsonKey::scheme = "scheme";
        const QString Scheme::JsonKey::italic = "italic";
        const QString Scheme::JsonKey::color = "color";
        const QString Scheme::JsonKey::match = "match";
        const QString Scheme::JsonKey::bold = "bold";

        auto Scheme::Init() -> void {
            auto json       = IO::Read::JsonFromUrl(App::Instance::GetResourceDir() + "/config/schemes/qml.json");
            auto schemeObj  = json[JsonKey::scheme].toObject();
            auto hlArray    = schemeObj[JsonKey::highlight].toArray();

            QTextCharFormat format;
            HighlightRule rule;
            QJsonObject hlObj;

            for (auto i = 0; i < hlArray.count(); ++i) {
                hlObj = hlArray.at(i).toObject();

                if (hlObj[JsonKey::bold].toBool(false)) {
                    format.setFontWeight(QFont::Bold);
                }
                else {
                    format.setFontWeight(QFont::Normal);
                }

                if (hlObj[JsonKey::italic].toBool(false)) {
                    format.setFontItalic(true);
                }
                else {
                    format.setFontItalic(false);
                }

                format.setForeground(QColor(hlObj[JsonKey::color].toString("#fff")));

                rule.pattern    = QRegExp(hlObj[JsonKey::match].toString());
                rule.format     = format;
                
                highlightRules.append(rule);
            }
        }
    }
}
