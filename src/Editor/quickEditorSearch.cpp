#include "quickEditorSearch.hpp"

namespace quick {

    namespace Editor {

        Search* Search::instance = nullptr;
        Qml::Register::Controller<Search> Search::Register;
        
        Search::Search() {
            if (instance) {
                throw "instance already existing";
            }
        }

        auto Search::Create() -> void {
            instance = new Search();
        }

        auto Search::getVisible() -> bool {
            return this->m_visible;
        }

        auto Search::show() -> void {
            this->m_visible = true;
            emit this->visibleChanged();
        }

        auto Search::hide() -> void {
            this->m_visible = false;
            emit this->visibleChanged();
        }
    }
}
