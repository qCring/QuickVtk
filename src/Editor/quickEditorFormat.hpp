#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace Editor {

        class Format : public QObject {
            Q_OBJECT
            Q_PROPERTY(QList<int> indents READ getIndents NOTIFY indentsChanged);
        private:
            QList<int> m_indents;
        public:
            static Qml::Register::Type<Format> Register;
            Format();
            auto getIndents() -> QList<int>;
            auto clear() -> void;
        public slots:
            void onBackspace();
            void onNewline();
            void onDelete();
            void onPaste();
            void onCut();
        signals:
            void indentsChanged();
        };
    }
}
