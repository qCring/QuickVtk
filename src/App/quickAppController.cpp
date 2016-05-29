#include "quickAppController.hpp"

#include "meta_quickvtk.hpp"

namespace quick {
    namespace App {

        Controller* Controller::instance = nullptr;

        Controller::Controller() {
            if (instance) {
                throw std::runtime_error("instance already existing");
            }

            instance = this;
        }

        auto Controller::init() -> void {
        }

        auto Controller::Create() -> Controller* {
            return new Controller();
        }

        auto Controller::getVersion() -> QString {
            return Meta::versionString;
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