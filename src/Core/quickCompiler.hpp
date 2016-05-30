#pragma once

#include "quickQmlRegister.hpp"

#include <QFileSystemWatcher>
#include <QObject>

namespace quick {
    class Compiler : public QObject {
        Q_OBJECT
        Q_PROPERTY(QString filePath READ getFilePath NOTIFY filePathChanged);
        Q_PROPERTY(QString source READ getSource NOTIFY sourceChanged);
        Q_PROPERTY(bool autocompile READ getAutocompile WRITE setAutocompile NOTIFY autocompileChanged);
        Q_PROPERTY(bool modified READ isModified NOTIFY modifiedChanged);
        Q_PROPERTY(bool failed READ getFailed WRITE setFailed NOTIFY failedChanged);
        Q_PROPERTY(bool ready READ isReady NOTIFY readyChanged);
    private:
        static Qml::Register::Controller<Compiler> Register;
        QFileSystemWatcher* m_fileWatcher;
        QString m_filePath;
        QString m_source;
        bool m_autocompile;
        bool m_modified;
        bool m_failed;
        bool m_ready;
        Compiler();
    public:
        static Compiler* instance;
        static auto Create() -> void;
        auto getSource() -> QString;
        auto setModified(bool) -> void;
        auto isModified() -> bool;
        auto getFilePath() -> QString;
        auto setAutocompile(bool) -> void;
        auto getAutocompile() -> bool;
        auto setFailed(bool) -> void;
        auto getFailed() -> bool;
        auto setReady(bool) -> void;
        auto isReady() -> bool;
    public slots:
        void linkFile();
        void finished();
        void updateSource();
        void onFileChanged(const QString&);
    signals:
        void autocompileChanged();
        void filePathChanged();
        void modifiedChanged();
        void sourceChanged();
        void failedChanged();
        void readyChanged();
        void compile();
    };
}