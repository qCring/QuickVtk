#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace SampleData {

        class Images;
        class Meshes;

        class Controller : public QObject {
            Q_OBJECT
            Q_PROPERTY(quick::SampleData::Images* images READ getImages CONSTANT);
            Q_PROPERTY(quick::SampleData::Meshes* meshes READ getMeshes CONSTANT);
        public:
            static Qml::Register::Class<Controller> Register;
            static Controller* instance;
            static auto Create() -> Controller*;
            auto getImages() -> Images*;
            auto getMeshes() -> Meshes*;
        };
    }
}