#include "quickAppController.hpp"

#include "meta_quickvtk.hpp"

#include "quickCompiler.hpp"
#include "quickErrors.hpp"

namespace quick {
    namespace App {

        Controller* Controller::instance = nullptr;

        Qml::Register::Controller<Controller> Controller::Register;

        Controller::Controller() {
            if (instance) {
                throw std::runtime_error("instance already existing");
            }
        }

        auto Controller::init() -> void {
        }

        auto Controller::Create() -> void {
            instance = new Controller();
        }

        auto Controller::getVersion() -> QString {
            return Meta::versionString;
        }

        auto Controller::getCompiler() -> Compiler* {
            return Compiler::instance;
        }

        auto Controller::getErrors() -> Errors* {
            return Errors::instance;
        }

        auto Controller::isDebugBuild() -> bool {
#ifdef NDEBUG
            return false;
#else
            return true;
#endif
        }
    }
}