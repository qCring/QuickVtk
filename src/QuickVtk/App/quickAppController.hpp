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

    namespace Menu {
        class Controller;
    }

    namespace App {

        class Settings;
        class Details;

        class Controller : public QObject {
            Q_OBJECT
            Q_PROPERTY(bool debugBuild READ isDebugBuild CONSTANT);
            Q_PROPERTY(QString version READ getVersion CONSTANT);
            Q_PROPERTY(quick::App::Settings* settings READ getSettings CONSTANT);
            Q_PROPERTY(quick::App::Details* details READ getDetails CONSTANT);
            Q_PROPERTY(quick::Document::Controller* document READ getDocumentController CONSTANT);
            Q_PROPERTY(quick::Console::Controller* console READ getConsoleController CONSTANT);
            Q_PROPERTY(quick::Menu::Controller* menu READ getMenuController CONSTANT);
            Q_PROPERTY(quick::TypeInfo::List* typeList READ getTypeList CONSTANT);
        private:
            QString m_version;
            Controller() = default;
        public:
            static Qml::Register::Controller<Controller> Register;
            static Controller* instance;
            static auto Create() -> void;
            auto getVersion() -> QString;
            auto isDebugBuild() -> bool;
            auto getTypeList() -> TypeInfo::List*;
            auto getSettings() -> Settings*;
            auto getDetails() -> Details*;
            auto getConsoleController() -> Console::Controller*;
            auto getMenuController() -> Menu::Controller*;
            auto getDocumentController() -> Document::Controller*;
            auto setShowInspector(bool) -> void;
            auto getShowInspector() -> bool;
        };
    }
}
