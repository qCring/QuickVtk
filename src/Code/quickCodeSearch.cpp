#include "quickCodeSearch.hpp"

namespace quick {

    namespace Code {

        Search* Search::instance = nullptr;
        Qml::Register::Controller<Search> Search::Register;

        Search::Search() {
            if (instance) {
                throw std::runtime_error("instance already existing");
            }
        }

        auto Search::Create() -> void {
            instance = new Search();
        }

        auto Search::GetInstance() -> Search* {
            return instance ? instance : new Search();
        }
        
        auto Search::setSearchString(const QString& searchString) -> void {
            this->m_searchString = searchString;
            emit this->searchStringChanged();
        }

        auto Search::getSearchString() -> QString {
            return this->m_searchString;
        }

        auto Search::setVisible(bool visible) -> void {
            if (this->m_visible != visible) {
                this->m_visible = visible;
                emit this->visibleChanged();
            }
        }

        auto Search::getVisible() -> bool {
            return this->m_visible;
        }
    }
}
