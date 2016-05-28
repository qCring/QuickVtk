#pragma once

#include <QObject>

namespace quick {
    class AppController : public QObject {
        Q_OBJECT
        Q_PROPERTY(bool debugBuild READ isDebugBuild CONSTANT);
        Q_PROPERTY(QString version READ getVersion CONSTANT);
    private:
        QString m_version;
    public:
        static AppController* instance;
        static auto Create() -> AppController*;
        AppController();
        auto init() -> void;
        auto setVersion(const QString&) -> void;
        auto getVersion() -> QString;
        auto isDebugBuild() -> bool;
    };
}