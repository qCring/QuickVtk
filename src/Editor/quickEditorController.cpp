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
            
            instance->m_fileWatcher = new QFileSystemWatcher();
            QObject::connect(instance->m_fileWatcher, SIGNAL(fileChanged(const QString&)), instance, SLOT(observedFileChanged(const QString&)));
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
        
        auto Controller::setAutorun(bool value) -> void {
            if (this->m_autorun != value) {
                this->m_autorun = value;
                emit this->autorunChanged();
            }
        }
        
        auto Controller::getAutorun() -> bool {
            return this->m_autorun;
        }
        
        auto Controller::copyToClipboard(const QString& text) -> void {
            QGuiApplication::clipboard()->setText(text);
        }

        auto Controller::getModified() -> bool {
            return this->m_modified;
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

        auto Controller::observeFile(const QString& fileUrl) -> void {
            
            if (IO::FileExists(fileUrl)) {
                
                if (this->m_fileUrl.length() > 0) {
                    this->m_fileWatcher->removePath(this->m_fileUrl);
                }
                
                this->m_fileWatcher->addPath(fileUrl);
                this->setFileUrl(fileUrl);
                this->loadSourceFromFile();

                this->run();
            }
        }
        
        auto Controller::loadSourceFromFile() -> void {
            if (IO::FileExists(this->m_fileUrl)) {
                Search::instance->invalidate();
                Errors::instance->clear();
                
                this->m_document->textDocument()->setPlainText(IO::Read::TextFromUrl(this->m_fileUrl));
                this->setModified(false);
            }
        }
                
        auto Controller::loadExample(const QString& fileUrl) -> void {
            if (IO::FileExists(fileUrl)) {
                Search::instance->invalidate();
                Errors::instance->clear();
                
                this->m_document->textDocument()->setPlainText(IO::Read::TextFromUrl(fileUrl));
                this->setModified(false);
                this->setFileUrl(nullptr);
                
                this->run();
            }
        }
        
        void Controller::observedFileChanged(const QString& fileUrl) {
            
            loadSourceFromFile();
            
            if (this->m_autorun) {
                this->run();
            } else {
                this->setModified(true);
            }
        }

        void Controller::run() {
            this->setModified(false);
            emit this->compile();
        }

        void Controller::loadFile() {
            this->observeFile(IO::FromDialog::SelectOpenFileUrl("*.qml"));
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
