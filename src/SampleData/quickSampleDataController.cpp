#include "quickSampleDataController.hpp"
#include "quickSampleDataImages.hpp"
#include "quickSampleDataMeshes.hpp"

namespace quick {

    namespace SampleData {

        Controller* Controller::instance = nullptr;

        Qml::Register::Type<Controller> Controller::Register;

        auto Controller::Create() -> Controller* {
            if (instance) {
                throw std::runtime_error("instance already existing");
            }

            Images::Create();
            Meshes::Create();

            instance = new Controller();
            return instance;
        }

        auto Controller::getImages() -> Images* {
            return Images::instance;
        }

        auto Controller::getMeshes() -> Meshes* {
            return Meshes::instance;
        }
    }
}