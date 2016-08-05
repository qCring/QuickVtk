#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace SampleData {

        class Images : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString lenaPNG READ getLenaPNG CONSTANT);
            Q_PROPERTY(QString lenaJPG READ getLenaJPG CONSTANT);
        private:
            auto makeDataPath(const QString&) -> QString;
        public:
            static Qml::Register::Class<Images> Register;
            static Images* instance;
            static auto Create() -> void;
            auto getLenaPNG() -> QString;
            auto getLenaJPG() -> QString;
        };
    }
}