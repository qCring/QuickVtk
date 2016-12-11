#include "quickEditorController.hpp"

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

        auto Controller::openFile(const QString&) -> void {
            
        }

        auto Controller::run() -> void {

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

        }

        auto Controller::resetFontSize() -> void {

        }

        auto Controller::increaseFontSize() -> void {

        }

        auto Controller::decreaseFontSize() -> void {
            
        }
    }
}
