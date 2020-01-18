#include "quickSampleDataMeshes.hpp"
#include <QGuiApplication>

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
    
        auto Meshes::GetInstance() -> Meshes* {
            return instance;
        }

        auto Meshes::makeDataPath(const QString& file) -> QString {
            auto path = QDir(QGuiApplication::applicationDirPath());

            #ifdef __APPLE__
            path.cdUp();
            #endif
            QString resourceDir = path.absolutePath() + "/Resources/";
            return resourceDir + "examples/data/meshes/" + file;
        }

        auto Meshes::getSuzanneSTL() -> QString {
            return this->makeDataPath("suzanne.stl");
        }
    
        auto Meshes::getDragonSTL() -> QString {
            return this->makeDataPath("dragon.stl");
        }

        auto Meshes::getBunnyPLY() -> QString {
            return this->makeDataPath("bunny.ply");
        }

        auto Meshes::getAOBJ() -> QString {
            return this->makeDataPath("a.obj");
        }

        auto Meshes::getBOBJ() -> QString {
            return this->makeDataPath("b.obj");
        }
    }
}
