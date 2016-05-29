#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {
    class Compiler : public QObject {
        Q_OBJECT
        Q_PROPERTY(QString fileName READ getFileName NOTIFY fileNameChanged);
        Q_PROPERTY(QString source READ getSource NOTIFY sourceChanged);
    private:
        static Qml::Register::Controller<Compiler> Register;
        QString m_fileName;
        QString m_source;
        Compiler();
    public:
        static Compiler* instance;
        static auto Create() -> void;
        auto getSource() -> QString;
        auto getFileName() -> QString;
    public slots:
        void compile();
        void openFile();
    signals:
        void fileNameChanged();
        void sourceChanged();
    };
}