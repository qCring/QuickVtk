#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    class Compiler;
    class Errors;

    namespace App {

        class Controller : public QObject {
            Q_OBJECT
            Q_PROPERTY(bool debugBuild READ isDebugBuild CONSTANT);
            Q_PROPERTY(QString version READ getVersion CONSTANT);
            Q_PROPERTY(quick::Compiler* compiler READ getCompiler CONSTANT);
            Q_PROPERTY(quick::Errors* errors READ getErrors CONSTANT);
        private:
            QString m_version;
        private:
            Controller();
        public:
            static Qml::Register::Controller<Controller> Register;
            static Controller* instance;
            static auto Create() -> void;
            auto init() -> void;
            auto getVersion() -> QString;
            auto isDebugBuild() -> bool;
            auto getCompiler() -> Compiler*;
            auto getErrors() -> Errors*;
        };
    }
}