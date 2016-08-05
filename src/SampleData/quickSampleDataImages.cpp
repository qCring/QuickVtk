#include "quickSampleDataImages.hpp"
#include "quickAppWindow.hpp"

namespace quick {

    namespace SampleData {

        Images* Images::instance = nullptr;

        Qml::Register::Class<Images> Images::Register;

        auto Images::Create() -> void {
            if (instance) {
                throw std::runtime_error("instance already existing");
            }

            instance = new Images();
        }

        auto Images::makeDataPath(const QString& file) -> QString {
            return App::Window::instance->getResourceDir() + "examples/data/images/" + file;
        }

        auto Images::getLenaPNG() -> QString {
            return makeDataPath("lena.png");
        }

        auto Images::getLenaJPG() -> QString {
            return makeDataPath("lena.jpg");
        }
    }
}