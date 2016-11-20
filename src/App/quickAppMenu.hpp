#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace App {

        class Menu : public QObject {
            Q_OBJECT
            Q_PROPERTY(QStringList examples READ getExamples CONSTANT);
        private:
            static Menu* instance;
            QStringList m_examples;
            static Qml::Register::Type<Menu> Register;
            auto init() -> void;
            Menu();
        public:
            static auto GetInstance() -> Menu*;
            auto getExamples() -> QStringList;
        public slots:
            void OnFileNew();
            void OnFileOpen();
            void OnFileSave();
            void OnFileSaveAs();
            void OnFindFind();

            void OnCodeRun();
            void OnCodeFormat();

            void OnViewIncreaseFontSize();
            void OnViewDecreaseFontSize();
            void OnViewResetFontSize();
            void OnViewToggleEditor();

            void OnHelpDocumentation();
            void OnHelpAbout();
            void OnHelpPreferences();
            void OnHelpVisitOnGitHub();
            void OnHelpSendFeedback();
            void OnHelpExample(const QString&);
        };
    }
}
