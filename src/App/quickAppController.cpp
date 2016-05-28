#include "quickAppController.hpp"

namespace quick {
    AppController* AppController::instance = nullptr;

    AppController::AppController() {
        if (instance) {
            throw std::runtime_error("instance already existing");
        }

        instance = this;
    }

    auto AppController::init() -> void {
    }

    auto AppController::Create() -> AppController* {
        return new AppController();
    }
    
    auto AppController::setVersion(const QString& version) -> void {
        this->m_version = version;
    }

    auto AppController::getVersion() -> QString {
        return this->m_version;
    }

    auto AppController::isDebugBuild() -> bool {
#ifdef NDEBUG
        return false;
#else
        return true;
#endif
    }
}
