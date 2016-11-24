#include "quickCodeSearch.hpp"

#include "quickCodeEditor.hpp"
#include "quickCodeDocument.hpp"
#include "quickCodeSelection.hpp"

namespace quick {

    namespace Code {

        Qml::Register::Type<Search> Search::Register;

        auto Search::invalidate() -> void {
            this->m_valid = false;
        }

        void Search::replaceNext() {
            if (!this->m_valid) {
                this->processSearch();
                return;
            }

            if (this->m_matches.count() < 1) {
                return;
            }

            if (this->m_currentMatch == this->m_matches.count() - 1) {
                auto cursor = this->m_matches.at(this->m_currentMatch);
                cursor.insertText(this->m_replaceString);
                this->processSearch();
                return;
            }

            auto cursor = this->m_matches.at(this->m_currentMatch);
            cursor.insertText(this->m_replaceString);

            this->findNext();
        }

        void Search::replaceAll() {

        }

        auto Search::setRegexError(const QString& regexError) -> void {
            this->m_regexError = regexError;
            emit this->regexErrorChanged();
        }

        auto Search::getRegexError() -> QString {
            return this->m_regexError;
        }

        auto Search::setRegexValid(bool regexValid) -> void {
            if (this->m_regexValid != regexValid) {
                this->m_regexValid = regexValid;
                emit this->regexValidChanged();
            }
        }

        auto Search::getRegexValid() -> bool {
            return this->m_regexValid;
        }

        auto Search::setUseRegex(bool useRegex) -> void {
            if (this->m_useRegex != useRegex) {
                this->m_useRegex = useRegex;
                emit this->useRegexChanged();

                this->checkRegex();
                this->processSearch();
            }
        }

        auto Search::getUseRegex() -> bool {
            return this->m_useRegex;
        }

        auto Search::setCaseSensitive(bool caseSensitive) -> void {
            if (this->m_caseSensitive != caseSensitive) {
                this->m_caseSensitive = caseSensitive;
                emit this->caseSensitiveChanged();

                this->processSearch();
            }
        }

        auto Search::getCaseSensitive() -> bool {
            return this->m_caseSensitive;
        }

        auto Search::setReplaceString(const QString& replaceString) -> void {
            this->m_replaceString = replaceString;
            emit this->replaceStringChanged();
        }

        auto Search::getReplaceString() -> QString {
            return this->m_replaceString;
        }

        auto Search::checkRegex() -> void {
            if (this->m_useRegex) {
                if (this->m_findString.isEmpty()) {
                    this->setRegexValid(false);
                    this->setRegexError("regex is empty");
                } else {
                    auto regex = QRegularExpression(this->m_findString);
                    auto valid = regex.isValid();

                    if (!valid) {
                        this->setRegexError(regex.errorString());
                    } else {
                        this->setRegexError("");
                    }

                    this->setRegexValid(valid);
                }
            } else {
                this->setRegexValid(true);
                this->setRegexError("");
            }
        }

        auto Search::setFindString(const QString& findString) -> void {
            if (this->m_findString.compare(findString) != 0 || !this->m_valid) {
                this->m_findString = findString;
                emit this->findStringChanged();
                this->checkRegex();
                this->processSearch();
            } else {
                this->findNext();
            }
        }

        auto Search::getFindString() -> QString {
            return this->m_findString;
        }

        auto Search::setCurrentMatch(int currentMatch) -> void {
            if (this->m_currentMatch != currentMatch) {
                this->m_currentMatch = currentMatch;
                emit this->currentMatchChanged();
            }
        }

        auto Search::getCurrentMatch() -> int {
            return this->m_currentMatch;
        }

        auto Search::getMatchCount() -> int {
            return this->m_matches.count();
        }

        auto Search::processSearch() -> void {
            if (!Document::current || (this->m_useRegex && !this->m_regexValid)) {
                return;
            }

            this->setCurrentMatch(-1);
            this->m_matches.clear();

            auto selection = Document::current->getSelection()->getData();
            auto cursor = selection.cursor;

            cursor.setPosition(0);

            while (true) {
                if (this->m_useRegex) {
                    auto newCursor = Editor::instance->getEditorDocument()->textDocument()->find(QRegularExpression(this->m_findString), cursor);
                    if (newCursor.position() == cursor.position()) {
                        //TODO: this is a quick hack to prevent the app from getting stuck for certain expressions (for example "^^")
                        return;
                    }

                    cursor = newCursor;
                } else {
                    if (this->m_caseSensitive) {
                        cursor = Editor::instance->getEditorDocument()->textDocument()->find(this->m_findString, cursor, QTextDocument::FindCaseSensitively);
                    } else {
                        cursor = Editor::instance->getEditorDocument()->textDocument()->find(this->m_findString, cursor);
                    }
                }

                if (cursor.position() > -1) {
                    this->m_matches.append(cursor);
                } else {
                    break;
                }
            }

            this->m_valid = true;
            emit this->matchCountChanged();

            this->findNext();

        }

        auto Search::findNext() -> void {
            if (!this->m_valid) {
                this->processSearch();
                return;
            }

            if (this->m_matches.count() < 1) {
                return;
            }

            this->setCurrentMatch((this->m_currentMatch + 1) % this->m_matches.count());

            if (Document::current) {
                auto match = this->m_matches.at(this->m_currentMatch);
                emit Document::current->select(match.selectionStart(), match.selectionEnd());
            }
        }

        auto Search::findPrevious() -> void {
            if (!this->m_valid) {
                this->processSearch();
                return;
            }

            if (this->m_matches.count() < 1) {
                return;
            }

            this->setCurrentMatch((this->m_currentMatch - 1) % this->m_matches.count());

            if (Document::current) {
                auto match = this->m_matches.at(this->m_currentMatch);
                emit Document::current->select(match.selectionStart(), match.selectionEnd());
            }
        }
    }
}
