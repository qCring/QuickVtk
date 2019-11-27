#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace App {

        class MenuItem;
    
        class Menu : public QObject {
            Q_OBJECT
            Q_PROPERTY(QStringList examples READ getExamples CONSTANT);
            Q_PROPERTY(QQmlListProperty<quick::App::MenuItem> items READ getItemList);
        private:
            static Menu* instance;
            QList<MenuItem*> m_items;
            QStringList m_examples;
            static Qml::Register::Type<Menu> Register;
            auto init() -> void;
            Menu();
        public:
            static auto GetInstance() -> Menu*;
            auto getExamples() -> QStringList;
            auto getItemList() -> QQmlListProperty<MenuItem>;
            static auto itemCount(QQmlListProperty<MenuItem>*) -> int;
            static auto itemAt(QQmlListProperty<MenuItem>*, int) -> MenuItem*;
        public slots:
            void select(quick::App::MenuItem*);
            void OnFileLoad();
            
            void OnFindFind();

            void OnCodeRun();

            void OnViewIncreaseFontSize();
            void OnViewDecreaseFontSize();
            void OnViewResetFontSize();
            void OnViewToggleEditor();

            void OnHelpVisitOnGitHub();
            void OnHelpSendFeedback();
            void OnHelpExample(const QString&);
        };
    }
}
