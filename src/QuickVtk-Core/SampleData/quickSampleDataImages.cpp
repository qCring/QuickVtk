#include "quickSampleDataImages.hpp"
#include <QGuiApplication>

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
    
        auto Images::GetInstance() -> Images* {
            return instance;
        }

        auto Images::makeDataPath(const QString& file) -> QString {
            auto path = QDir(QGuiApplication::applicationDirPath());

            #ifdef __APPLE__
            path.cdUp();
            #endif
            QString resourceDir = path.absolutePath() + "/Resources/";
            return resourceDir + "examples/data/images/" + file;
        }

        auto Images::getLenaPNG() -> QString {
            return makeDataPath("lena.png");
        }

        auto Images::getLenaJPG() -> QString {
            return makeDataPath("lena.jpg");
        }

        auto Images::getAPNG() -> QString {
            return makeDataPath("a.png");
        }

        auto Images::getAJPG() -> QString {
            return makeDataPath("a.jpg");
        }

        auto Images::getBPNG() -> QString {
            return makeDataPath("b.png");
        }

        auto Images::getBJPG() -> QString {
            return makeDataPath("b.jpg");
        }
    }
}
