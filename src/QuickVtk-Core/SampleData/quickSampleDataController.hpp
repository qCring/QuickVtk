#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick::SampleData {

    class Images;
    class Meshes;
    class Volumes;

    class Controller : public QObject {
        Q_OBJECT
        Q_PROPERTY(quick::SampleData::Images* images READ getImages CONSTANT);
        Q_PROPERTY(quick::SampleData::Meshes* meshes READ getMeshes CONSTANT);
        Q_PROPERTY(quick::SampleData::Volumes* volumes READ getVolumes CONSTANT);
    private:
        static Controller* instance;
    public:
        static Qml::Register::Type<Controller> Register;
        static auto Create() -> Controller*;
        static auto GetInstance() -> Controller*;
        auto getImages() -> Images*;
        auto getMeshes() -> Meshes*;
        auto getVolumes() -> Volumes*;
    };
}
