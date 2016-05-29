#pragma once

#include <QObject>

namespace quick {
    namespace App {
        class Controller : public QObject {
            Q_OBJECT
            Q_PROPERTY(bool debugBuild READ isDebugBuild CONSTANT);
            Q_PROPERTY(QString version READ getVersion CONSTANT);
        private:
            QString m_version;
        public:
            static Controller* instance;
            static auto Create() -> Controller*;
            Controller();
            auto init() -> void;
            auto getVersion() -> QString;
            auto isDebugBuild() -> bool;
        };
    }
}