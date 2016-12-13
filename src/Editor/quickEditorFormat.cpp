#include "quickEditorFormat.hpp"

#include "quickEditorSelection.hpp"

#include <QTextCursor>
#include <iostream>

namespace quick {

    namespace Editor {

        Qml::Register::Type<Format> Format::Register;

        Format::Format() {
            this->m_indents.append(0);
        }

        auto Format::getIndents() -> QList<int> {
            return this->m_indents;
        }

        auto Format::clear() -> void {
            this->m_indents.clear();
            this->m_indents.append(0);
            emit this->indentsChanged();
        }

        void Format::onNewline() {
            auto s = Selection::instance->m_startLine;
            auto e = Selection::instance->m_endLine;

            for (int i = s; i < e; ++i) {
                this->m_indents.removeAt(s);
            }

            this->m_indents.insert(s + 1, s);

            emit this->indentsChanged();
        }

        void Format::onBackspace() {
            auto s = Selection::instance->m_startLine;
            auto e = Selection::instance->m_endLine;

            if (s == e) {
                if (s > 0) {
                    auto cursor = Selection::instance->getCursor(Selection::instance->m_startPosition);

                    if (cursor.atBlockStart()) {
                        this->m_indents.removeAt(s);
                    }
                }
            } else {
                for (auto i = s; i < e; ++i) {
                    this->m_indents.removeAt(s);
                }
            }
            emit this->indentsChanged();
        }

        void Format::onDelete() {
            auto s = Selection::instance->m_startLine;
            auto e = Selection::instance->m_endLine;

            if (s == e) {
                auto cursor = Selection::instance->getCursor(Selection::instance->m_startPosition);

                if (cursor.atBlockEnd() && s < this->m_indents.length() - 1) {
                    this->m_indents.removeAt(s + 1);
                }
            } else {
                for (auto i = s; i < e; ++i) {
                    this->m_indents.removeAt(s);
                }
            }
            emit this->indentsChanged();
        }

        void Format::onPaste() {
            std::cout << "onPaste\n";
        }

        void Format::onCut() {
            std::cout << "onCut\n";
        }
    }
}
