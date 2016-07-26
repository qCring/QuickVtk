#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace SampleData {

        class Images : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString lena READ getLena CONSTANT);
        private:
            auto makeDataPath(const QString&) -> QString;
        public:
            static Qml::Register::Class<Images> Register;
            static Images* instance;
            static auto Create() -> void;
            auto getLena() -> QString;
        };
    }
}