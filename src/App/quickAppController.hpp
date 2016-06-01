#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    class Compiler;
    class Errors;
    class Symbols;

    namespace App {

        class Controller : public QObject {
            Q_OBJECT
            Q_PROPERTY(bool expanded READ isExpanded WRITE setExpanded NOTIFY expandedChanged);
            Q_PROPERTY(bool debugBuild READ isDebugBuild CONSTANT);
            Q_PROPERTY(QString version READ getVersion CONSTANT);
            Q_PROPERTY(quick::Compiler* compiler READ getCompiler CONSTANT);
            Q_PROPERTY(quick::Symbols* symbols READ getSymbols CONSTANT);
            Q_PROPERTY(quick::Errors* errors READ getErrors CONSTANT);
        private:
            bool m_symbolsWereVisible = false;
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
            auto getCompiler() -> Compiler*;
            auto getErrors() -> Errors*;
            auto getSymbols() -> Symbols*;
        signals:
            void expandedChanged();
        };
    }
}