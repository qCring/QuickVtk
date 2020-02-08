#include "quickSampleDataController.hpp"
#include "quickSampleDataImages.hpp"
#include "quickSampleDataMeshes.hpp"
#include "quickSampleDataVolumes.hpp"

namespace quick::SampleData {

    Controller* Controller::instance = nullptr;

    Qml::Register::Type<Controller> Controller::Register;

    auto Controller::Create() -> Controller* {
        if (instance) {
            throw std::runtime_error("instance already existing");
        }

        Images::Create();
        Meshes::Create();
        Volumes::Create();

        instance = new Controller();
        return instance;
    }

    auto Controller::GetInstance() -> Controller* {
        return instance;
    }

    auto Controller::getImages() -> Images* {
        return Images::GetInstance();
    }

    auto Controller::getMeshes() -> Meshes* {
        return Meshes::GetInstance();
    }

    auto Controller::getVolumes() -> Volumes* {
        return Volumes::GetInstance();
    }
}
