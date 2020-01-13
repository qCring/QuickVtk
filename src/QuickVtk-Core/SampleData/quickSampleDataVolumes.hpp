#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace SampleData {

        class Volumes : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString brain1DIR READ getBrain1DIR CONSTANT);
            Q_PROPERTY(QString brain2DIR READ getBrain2DIR CONSTANT);
        private:
            auto makeDataPath(const QString&) -> QString;
            static Volumes* instance;
        public:
            static Qml::Register::Class<Volumes> Register;
            static auto GetInstance() -> Volumes*;
            static auto Create() -> void;
            auto getBrain1DIR() -> QString;
            auto getBrain2DIR() -> QString;
        };
    }
}
