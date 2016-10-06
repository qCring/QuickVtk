#pragma once

#include <QObject>
#include <QMenu>

namespace quick {

    namespace App {

        class Menu : public QObject {
            Q_OBJECT
        private:
            enum Type {
                FileNewFile,
                FileOpenFile,
                FileSaveFile,
                ViewIncreaseFontSize,
                ViewDecreaseFontSize,
                CodeRun,
                CodeFormat,
                HelpAbout,
                HelpDocs,
                HelpPrefs
            };
        private:
            auto add(QMenu*, Type type, const QString&, QString = nullptr) -> void;
            auto init() -> void;
            Menu();
        public:
            static Menu* instance;
            static auto Create() -> Menu*;
        public slots:
            void onAction(Type, const QString&);
        };
    }
}
