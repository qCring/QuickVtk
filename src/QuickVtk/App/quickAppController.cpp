#include "quickAppController.hpp"
#include "quickAppSettings.hpp"
#include "quickAppDetails.hpp"

#include "meta_quickvtk.hpp"

#include "quickDocumentController.hpp"
#include "quickConsoleController.hpp"
#include "quickMenuController.hpp"

#include "quickTypeInfoList.hpp"

namespace quick {
    namespace App {

        Controller* Controller::instance = nullptr;

        Qml::Register::Controller<Controller> Controller::Register;

        auto Controller::Create() -> void {
            if (instance) {
                throw std::runtime_error("instance already existing");
            }
            
            instance = new Controller();
        }

        auto Controller::getVersion() -> QString {
            return Meta::AppVersion;
        }
    
        auto Controller::getSettings() -> Settings* {
            return Settings::instance;
        }

        auto Controller::getDetails() -> Details* {
            return Details::instance;
        }

        auto Controller::getConsoleController() -> Console::Controller* {
            return Console::Controller::instance;
        }

        auto Controller::getMenuController() -> Menu::Controller* {
            return Menu::Controller::instance;
        }

        auto Controller::getDocumentController() -> Document::Controller* {
            return Document::Controller::instance;
        }
    
        auto Controller::getTypeList() -> TypeInfo::List* {
            return TypeInfo::List::GetInstance();
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
