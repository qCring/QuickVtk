#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {
    class Compiler : public QObject {
        Q_OBJECT
        Q_PROPERTY(QString fileName READ getFileName NOTIFY fileNameChanged);
    private:
        static Qml::Register::Controller<Compiler> Register;
        QString m_fileName;
        Compiler();
    public:
        static Compiler* instance;
        static auto Create() -> void;
        auto getFileName() -> QString;
    public slots:
        void compile();
        void openFile();
    signals:
        void fileNameChanged();
    };
}