#include "quickSampleDataVolumes.hpp"
#include <QGuiApplication>

namespace quick::SampleData {

    Volumes* Volumes::instance = nullptr;

    Qml::Register::Class<Volumes> Volumes::Register;

    auto Volumes::Create() -> void {
        if (instance) {
            throw std::runtime_error("instance already existing");
        }

        instance = new Volumes();
    }

    auto Volumes::GetInstance() -> Volumes* {
        return instance;
    }

    auto Volumes::makeDataPath(const QString& file) -> QString {
        auto path = QDir(QGuiApplication::applicationDirPath());

        #ifdef __APPLE__
        path.cdUp();
        #endif
        QString resourceDir = path.absolutePath() + "/Resources/";
        return resourceDir + "examples/data/volumes/" + file;
    }

    auto Volumes::getBrain1DIR() -> QString {
        return this->makeDataPath("brain1");
    }

    auto Volumes::getBrain2DIR() -> QString {
        return this->makeDataPath("brain2");
    }
}
