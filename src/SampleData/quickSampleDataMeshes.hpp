#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace SampleData {

        class Meshes : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString suzanneOBJ READ getSuzanneOBJ CONSTANT);
            Q_PROPERTY(QString suzanneSTL READ getSuzanneSTL CONSTANT);
        private:
            auto makeDataPath(const QString&) -> QString;
        public:
            static Qml::Register::Class<Meshes> Register;
            static Meshes* instance;
            static auto Create() -> void;
            auto getSuzanneOBJ() -> QString;
            auto getSuzanneSTL() -> QString;
        };
    }
}