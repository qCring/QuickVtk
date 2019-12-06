#include "quickAppController.hpp"

#include "meta_quickvtk.hpp"

#include "quickTypeInfoList.hpp"

#include "quickEditorController.hpp"
#include "quickDocumentController.hpp"
#include "quickAppSettings.hpp"
#include "quickConsoleController.hpp"
#include "quickAppMenu.hpp"

namespace quick {
    namespace App {

        Controller* Controller::instance = nullptr;

        Qml::Register::Controller<Controller> Controller::Register;

        Controller::Controller() {
            if (instance) {
                throw std::runtime_error("instance already existing");
            }
        }

        auto Controller::setExpanded(bool expanded) -> void {
            if (this->m_expanded != expanded) {
                this->m_expanded = expanded;
                emit this->expandedChanged();

                auto typeList = TypeInfo::List::GetInstance();

                if (expanded) {
                    this->m_showList = typeList->isVisible();
                    typeList->setVisible(false);
                } else {
                    typeList->setVisible(this->m_showList);
                }
            }
        }

        auto Controller::isExpanded() -> bool {
            return this->m_expanded;
        }

        auto Controller::Create() -> void {
            instance = new Controller();
        }

        auto Controller::getVersion() -> QString {
            return Meta::versionString;
        }

        auto Controller::getTypeList() -> TypeInfo::List* {
            return TypeInfo::List::GetInstance();
        }

        auto Controller::getEditor() -> Editor::Controller* {
            return Editor::Controller::instance;
        }

        auto Controller::getConsole() -> Console::Controller* {
            return Console::Controller::GetInstance();
        }

        auto Controller::getSettings() -> Settings* {
            return Settings::instance;
        }

        auto Controller::getMenu() -> Menu* {
            return Menu::GetInstance();
        }
    
        auto Controller::getDocumentController() -> Document::Controller* {
            return Document::Controller::instance;
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
