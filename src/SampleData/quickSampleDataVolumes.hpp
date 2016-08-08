#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace SampleData {

        class Volumes : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString brainDIR READ getBrainDIR CONSTANT);
        private:
            auto makeDataPath(const QString&) -> QString;
        public:
            static Qml::Register::Class<Volumes> Register;
            static Volumes* instance;
            static auto Create() -> void;
            auto getBrainDIR() -> QString;
        };
    }
}