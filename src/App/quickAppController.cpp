#include "quickAppController.hpp"

#include "meta_quickvtk.hpp"

#include "quickCodeCompiler.hpp"
#include "quickTypeInfoList.hpp"
#include "quickCodeEditor.hpp"
#include "quickCodeSearch.hpp"
#include "quickAppLogger.hpp"

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

        auto Controller::getCompiler() -> Code::Compiler* {
            return Code::Compiler::instance;
        }

        auto Controller::getTypeList() -> TypeInfo::List* {
            return TypeInfo::List::GetInstance();
        }

        auto Controller::getEditor() -> Code::Editor* {
            return Code::Editor::instance;
        }

        auto Controller::getSearch() -> Code::Search* {
            return Code::Search::instance;
        }

        auto Controller::getLogger() -> Logger* {
            return Logger::GetInstance();
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
