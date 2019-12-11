#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace TypeInfo {
        class List;
    }

    namespace Editor {
        class Controller;
    }

    namespace Document {
        class Controller;
    }

    namespace Console {
        class Controller;
    }

    namespace App {

        class Settings;
        class Menu;

        class Controller : public QObject {
            Q_OBJECT
            Q_PROPERTY(bool expanded READ isExpanded WRITE setExpanded NOTIFY expandedChanged);
            Q_PROPERTY(bool debugBuild READ isDebugBuild CONSTANT);
            Q_PROPERTY(QString version READ getVersion CONSTANT);
            Q_PROPERTY(quick::App::Settings* settings READ getSettings CONSTANT);
            Q_PROPERTY(quick::TypeInfo::List* typeList READ getTypeList CONSTANT);
            Q_PROPERTY(quick::Document::Controller* document READ getDocumentController CONSTANT);
            Q_PROPERTY(quick::Editor::Controller* editor READ getEditor CONSTANT);
            Q_PROPERTY(quick::Console::Controller* console READ getConsole CONSTANT);
            Q_PROPERTY(quick::App::Menu* menu READ getMenu CONSTANT);
        private:
            bool m_showList = false;
            bool m_expanded = false;
            QString m_version;
        private:
            Controller();
        public:
            static Qml::Register::Controller<Controller> Register;
            static Controller* instance;
            static auto Create() -> void;
            auto setExpanded(bool) -> void;
            auto isExpanded() -> bool;
            auto getVersion() -> QString;
            auto isDebugBuild() -> bool;
            auto getTypeList() -> TypeInfo::List*;
            auto getEditor() -> Editor::Controller*;
            auto getSettings() -> Settings*;
            auto getConsole() -> Console::Controller*;
            auto getMenu() -> Menu*;
            auto getDocumentController() -> Document::Controller*;
        signals:
            void expandedChanged();
        };
    }
}
