#include "quickEditorController.hpp"

#include "quickIO.hpp"
#include "quickEditorHighlighter.hpp"
#include "quickEditorSelection.hpp"
#include "quickEditorErrors.hpp"
#include "quickEditorSearch.hpp"
#include "quickEditorUtil.hpp"

#include <QGuiApplication>
#include <QClipboard>
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

            auto textDocument = document->textDocument();
            auto options = textDocument->defaultTextOption();
            options.setTabStopDistance(20);
            textDocument->setDefaultTextOption(options);

            this->m_highlighter = new Highlighter(textDocument);

            Util::document = textDocument;
            Selection::instance->setDocument(textDocument);
            Search::instance->setDocument(textDocument);

            emit this->documentChanged();
        }

        auto Controller::setModified(bool modified) -> void {
            if (this->m_modified != modified) {
                this->m_modified = modified;
                emit this->modifiedChanged();
            }
        }
        
        auto Controller::copyToClipboard(QString text) -> void {
            QGuiApplication::clipboard()->setText(text);
        }

        auto Controller::getModified() -> bool {
            return this->m_modified;
        }

        auto Controller::setFileName(const QString& fileName) -> void {
            this->m_fileName = fileName;
            emit this->fileNameChanged();
        }

        auto Controller::getFileName() -> QString {
            return this->m_fileName;
        }

        auto Controller::setFileUrl(const QString& fileUrl) -> void {
            this->m_fileUrl = fileUrl;
            emit this->fileUrlChanged();
        }

        auto Controller::getFileUrl() -> QString {
            return this->m_fileUrl;
        }
        
        auto Controller::getExpanded() -> bool {
            return this->m_expanded;
        }

        void Controller::toggleExpanded() {
            this->m_expanded = !this->m_expanded;
            emit this->expandedChanged();
        }

        auto Controller::getDocument() -> QQuickTextDocument* {
            return this->m_document;
        }

        auto Controller::getErrors() -> Errors* {
            return Errors::instance;
        }

        auto Controller::getSearch() -> Search* {
            return Search::instance;
        }

        auto Controller::getSelection() -> Selection* {
            return Selection::instance;
        }

        auto Controller::openFile(const QString& fileUrl) -> void {
            if (IO::FileExists(fileUrl)) {
                Search::instance->invalidate();
                Errors::instance->clear();
                this->m_document->textDocument()->setPlainText(IO::Read::TextFromUrl(fileUrl));
                this->setModified(false);
                this->setFileUrl(fileUrl);

                this->run();
            }
        }

        void Controller::run() {
            emit this->compile();
        }

        void Controller::openFile() {
            this->openFile(IO::FromDialog::SelectOpenFileUrl("*.qml"));
        }

        void Controller::showSearch() {
            Search::instance->setVisible(true);
        }

        void Controller::resetFontSize() {
            this->m_fontSize = 11;
            emit this->fontSizeChanged();
        }

        void Controller::increaseFontSize() {
            if (this->m_fontSize < this->m_fontSizeMax) {
                this->m_fontSize += 2;
                emit this->fontSizeChanged();
            }
        }

        void Controller::decreaseFontSize() {
            if (this->m_fontSize > this->m_fontSizeMin) {
                this->m_fontSize -= 2;
                emit this->fontSizeChanged();
            }
        }

        auto Controller::getFontSize() -> int {
            return this->m_fontSize;
        }

        auto Controller::getText() -> QString {
            return this->m_document->textDocument()->toPlainText();
        }

        Controller::~Controller() {
            delete this->m_highlighter;
            this->m_highlighter = nullptr;
        }
    }
}
