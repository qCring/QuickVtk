#include "quickCodeSearch.hpp"

#include <iostream>
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
        
        auto Search::setFindString(const QString& findString) -> void {
            std::cout << "find: " << findString.toStdString() << std::endl;
            this->m_findString = findString;
            emit this->findStringChanged();
        }

        auto Search::getFindString() -> QString {
            return this->m_findString;
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
