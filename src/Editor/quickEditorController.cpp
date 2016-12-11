#include "quickEditorController.hpp"

#include "quickEditorSelection.hpp"
#include "quickEditorSearch.hpp"

#include <QTextOption>

namespace quick {

    namespace Editor {

        Controller* Controller::instance = nullptr;
        Qml::Register::Controller<Controller> Controller::Register;

        auto Controller::Create() -> void {
            instance = new Controller();
        }

        auto Controller::setDocument(QQuickTextDocument* document) -> void {
            this->m_document = document;

            auto options = document->textDocument()->defaultTextOption();
            options.setTabStop(20);
            document->textDocument()->setDefaultTextOption(options);

            Selection::instance->setDocument(document->textDocument());

            emit this->documentChanged();
        }

        auto Controller::getExpanded() -> bool {
            return this->m_expanded;
        }

        auto Controller::toggleExpanded() -> void {
            this->m_expanded = !this->m_expanded;
            emit this->expandedChanged();
        }

        auto Controller::getDocument() -> QQuickTextDocument* {
            return this->m_document;
        }

        auto Controller::getSearch() -> Search* {
            return Search::instance;
        }

        auto Controller::getSelection() -> Selection* {
            return Selection::instance;
        }

        auto Controller::openFile(const QString&) -> void {
            
        }

        auto Controller::run() -> void {
            emit this->compile();
        }

        auto Controller::saveFile() -> void {

        }

        auto Controller::format() -> void {

        }

        auto Controller::saveFileAs() -> void {

        }

        auto Controller::newFile() -> void {

        }

        auto Controller::openFile() -> void {

        }

        auto Controller::showSearch() -> void {
            Search::instance->show();
        }

        auto Controller::resetFontSize() -> void {
            this->m_fontSize = 11;
            emit this->fontSizeChanged();
        }

        auto Controller::increaseFontSize() -> void {
            if (this->m_fontSize < this->m_fontSizeMax) {
                this->m_fontSize += 2;
                emit this->fontSizeChanged();
            }
        }

        auto Controller::decreaseFontSize() -> void {
            if (this->m_fontSize > this->m_fontSizeMin) {
                this->m_fontSize -= 2;
                emit this->fontSizeChanged();
            }
        }

        auto Controller::getFontSize() -> int {
            return this->m_fontSize;
        }
    }
}
