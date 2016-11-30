#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace Code {

        class Settings : public QObject {
            Q_OBJECT
            Q_PROPERTY(bool autoIndent READ getAutoIndent WRITE setAutoIndent NOTIFY autoIndentChanged);
            Q_PROPERTY(bool autoIndentOnPaste READ getAutoIndentOnPaste WRITE setAutoIndentOnPaste NOTIFY autoIndentOnPasteChanged);
        private:
            bool m_autoIndent = false;
            bool m_autoIndentOnPaste = false;
        public:
            static Qml::Register::Type<Settings> Register;
            auto setAutoIndent(bool) -> void;
            auto getAutoIndent() -> bool;
            auto setAutoIndentOnPaste(bool) -> void;
            auto getAutoIndentOnPaste() -> bool;
        signals:
            void autoIndentChanged();
            void autoIndentOnPasteChanged();
        };
    }
}
