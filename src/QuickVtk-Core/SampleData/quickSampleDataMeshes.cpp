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

        auto Meshes::getSuzanneOBJ() -> QString {
            return this->makeDataPath("suzanne.obj");
        }

        auto Meshes::getSuzanneSTL() -> QString {
            return this->makeDataPath("suzanne.stl");
        }

        auto Meshes::getTeapotOFF() -> QString {
            return this->makeDataPath("teapot.off");
        }

        auto Meshes::getBunnyPLY() -> QString {
            return this->makeDataPath("bunny.ply");
        }

        auto Meshes::getBunnyOBJ() -> QString {
            return this->makeDataPath("bunny.obj");
        }

        auto Meshes::getBunnySTL() -> QString {
            return this->makeDataPath("bunny.stl");
        }

        auto Meshes::getAOBJ() -> QString {
            return this->makeDataPath("a.obj");
        }

        auto Meshes::getASTL() -> QString {
            return this->makeDataPath("a.stl");
        }

        auto Meshes::getBOBJ() -> QString {
            return this->makeDataPath("b.obj");
        }

        auto Meshes::getBSTL() -> QString {
            return this->makeDataPath("b.stl");
        }
    }
}
