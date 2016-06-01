#include "quickAppController.hpp"

#include "meta_quickvtk.hpp"

#include "quickCompiler.hpp"
#include "quickErrors.hpp"
#include "quickSymbols.hpp"

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

                auto symbols = Symbols::GetInstance();

                if (expanded) {
                    this->m_symbolsWereVisible = symbols->isVisible();
                    symbols->setVisible(false);
                } else {
                    symbols->setVisible(this->m_symbolsWereVisible);
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

        auto Controller::getCompiler() -> Compiler* {
            return Compiler::instance;
        }

        auto Controller::getErrors() -> Errors* {
            return Errors::instance;
        }

        auto Controller::getSymbols() -> Symbols* {
            return Symbols::GetInstance();
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