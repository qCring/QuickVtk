#include "quickSampleDataImages.hpp"
#include "quickAppWindow.hpp"

namespace quick {

    namespace SampleData {

        Images* Images::instance = nullptr;

        Qml::Register::Class<Images> Images::Register;

        auto Images::makeDataPath(const QString& file) -> QString {
            return App::Window::instance->getResourceDir() + "examples/data/image/" + file;
        }

        auto Images::Create() -> void {
            if (instance) {
                throw std::runtime_error("instance already existing");
            }

            instance = new Images();
        }

        auto Images::getLena() -> QString {
            return makeDataPath("lena");
        }
    }
}