#pragma once

#include "quickQmlRegister.hpp"

#include <QFileSystemWatcher>
#include <QObject>

namespace quick {
    class Compiler : public QObject {
        Q_OBJECT
        Q_PROPERTY(QString fileName READ getFileName NOTIFY fileNameChanged);
        Q_PROPERTY(QString source READ getSource NOTIFY sourceChanged);
        Q_PROPERTY(bool autocompile READ getAutocompile WRITE setAutocompile NOTIFY autocompileChanged);
        Q_PROPERTY(bool modified READ isModified NOTIFY modifiedChanged);
    private:
        static Qml::Register::Controller<Compiler> Register;
        QFileSystemWatcher* m_fileWatcher;
        QString m_fileName;
        QString m_source;
        bool m_autocompile;
        bool m_modified;
        Compiler();
    public:
        static Compiler* instance;
        static auto Create() -> void;
        auto getSource() -> QString;
        auto setModified(bool) -> void;
        auto isModified() -> bool;
        auto getFileName() -> QString;
        auto setAutocompile(bool) -> void;
        auto getAutocompile() -> bool;
    public slots:
        void openFile();
        void finished();
        void updateSource();
        void onFileChanged(const QString&);
    signals:
        void autocompileChanged();
        void fileNameChanged();
        void modifiedChanged();
        void sourceChanged();
        void compile();
    };
}