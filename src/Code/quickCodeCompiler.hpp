#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace Code {
        
        class Compiler : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString source READ getSource NOTIFY sourceChanged);
            Q_PROPERTY(bool failed READ getFailed WRITE setFailed NOTIFY failedChanged);
        private:
            static Qml::Register::Controller<Compiler> Register;
            QString m_source;
            bool m_failed;
            Compiler();
        public:
            static Compiler* instance;
            static auto Create() -> void;
            auto setSource(const QString&) -> void;
            auto getSource() -> QString;
            auto setFailed(bool) -> void;
            auto getFailed() -> bool;
        signals:
            void sourceChanged();
            void failedChanged();
        };
    }
}