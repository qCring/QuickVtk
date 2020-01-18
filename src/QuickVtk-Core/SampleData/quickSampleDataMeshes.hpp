#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {
    namespace SampleData {

        class Meshes : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString suzanneSTL READ getSuzanneSTL CONSTANT);
            Q_PROPERTY(QString bunnyPLY READ getBunnyPLY CONSTANT);
            Q_PROPERTY(QString dragonSTL READ getDragonSTL CONSTANT);
            Q_PROPERTY(QString aOBJ READ getAOBJ CONSTANT);
            Q_PROPERTY(QString bOBJ READ getBOBJ CONSTANT);
        private:
            auto makeDataPath(const QString&) -> QString;
            static Meshes* instance;
        public:
            static Qml::Register::Class<Meshes> Register;
            static auto Create() -> void;
            static auto GetInstance() -> Meshes*;
            auto getSuzanneSTL() -> QString;
            auto getBunnyPLY() -> QString;
            auto getDragonSTL() -> QString;
            auto getAOBJ() -> QString;
            auto getBOBJ() -> QString;
        };
    }
}
