#include "quickCodeSettings.hpp"

namespace quick {

    namespace Code {

        Qml::Register::Type<Settings> Settings::Register;

        auto Settings::setAutoIndent(bool autoIndent) -> void {
            if (this->m_autoIndent != autoIndent) {
                this->m_autoIndent = autoIndent;
                emit this->autoIndentChanged();
            }
        }

        auto Settings::getAutoIndent() -> bool {
            return this->m_autoIndent;
        }

        auto Settings::setAutoIndentOnPaste(bool autoIndentOnPaste) -> void {
            if (this->m_autoIndentOnPaste != autoIndentOnPaste) {
                this->m_autoIndentOnPaste = autoIndentOnPaste;
                emit this->autoIndentOnPasteChanged();
            }
        }

        auto Settings::getAutoIndentOnPaste() -> bool {
            return this->m_autoIndentOnPaste;
        }
    }
}
