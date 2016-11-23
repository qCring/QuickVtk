#include "quickCodeDocument.hpp"

#include "quickCodeEditor.hpp"
#include "quickCodeSelection.hpp"

#include "quickIO.hpp"


#include <iostream>

namespace quick {

    namespace Code {

        Document* Document::current = nullptr;
        Qml::Register::Type<Document> Document::Register;

        Document::Document() {
            this->m_selection = new Selection();
        }

        auto Document::bindQTextDocument(QTextDocument* document) -> void {
            this->m_document = document;
            Document::current = this;

            this->m_selection->setTextDocument(document);

            this->connect(document, &QTextDocument::modificationChanged, this, &Document::onModified);
        }

        void Document::onModified(bool modified) {
            if (this->m_modified != modified) {
                this->m_modified = modified;
                emit this->modifiedChanged();
            }
        }

        auto Document::getSelection() -> Selection* {
            return this->m_selection;
        }
        
        auto Document::getModified() -> bool {
            return this->m_modified;
        }

        auto Document::getFileUrl() -> const QString {
            return this->m_fileUrl;
        }

        auto Document::saveAs() -> void {
            auto newPath = IO::FromDialog::SelectSaveFileUrl();

            if (newPath.isNull() || newPath.isEmpty()) {
                return;
            }

            if (Document::current == this) {
                this->m_text = this->m_document->toPlainText();
            }

            if (IO::Write::TextToFile(this->m_text, newPath)) {
                this->m_document->setModified(false);
                this->m_fileUrl = newPath;
                emit this->fileUrlChanged();
            }
        }

        auto Document::save() -> void {
            if (this->m_fileUrl.length() > 0 && IO::FileExists(this->m_fileUrl)) {
                if (this->m_modified) {

                    if (Document::current == this) {
                        this->m_text = this->m_document->toPlainText();
                    }

                    IO::Write::TextToFile(this->m_document->toPlainText(), this->m_fileUrl);
                    this->m_document->setModified(false);
                }
            } else {
                this->saveAs();
            }
        }
    }
}
