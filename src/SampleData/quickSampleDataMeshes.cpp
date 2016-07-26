#include "quickSampleDataMeshes.hpp"
#include "quickAppWindow.hpp"

namespace quick {

    namespace SampleData {

        Meshes* Meshes::instance = nullptr;

        Qml::Register::Class<Meshes> Meshes::Register;

        auto Meshes::Create() -> void {
            if (instance) {
                throw std::runtime_error("instance already existing");
            }

            instance = new Meshes();
        }

        auto Meshes::makeDataPath(const QString& file) -> QString {
            return App::Window::instance->getResourceDir() + "examples/data/meshes/" + file;
        }

        auto Meshes::getSuzanne() -> QString {
            return this->makeDataPath("suzanne");
        }
    }
}