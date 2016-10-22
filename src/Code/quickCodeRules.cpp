#include "quickCodeRules.hpp"

#include "quickIO.hpp"
#include "quickAppInstance.hpp"

namespace quick {

    namespace Code {

        QList<Rules::HighlightRule> Rules::highlightRules;

        auto Rules::Init() -> void {
            auto json       = IO::Read::JsonFromUrl(App::Instance::GetResourceDir() + "/config/schemes/qml.json");
            auto schemeObj  = json["scheme"].toObject();
            auto hlArray    = schemeObj["highlight"].toArray();

            QTextCharFormat format;
            HighlightRule rule;
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
                
                highlightRules.append(rule);
            }
        }
    }
}
