#pragma once

#include "quickQmlRegister.hpp"

namespace quick::Document {
    
    class File;
    
    class Controller : public QObject {
        Q_OBJECT
        Q_PROPERTY(quick::Document::File* file READ getFile NOTIFY fileChanged);
        Q_PROPERTY(QQmlListProperty<quick::Document::File> files READ getFilesList NOTIFY filesChanged);
        Q_PROPERTY(bool showSource READ getShowSource WRITE setShowSource NOTIFY showSourceChanged);
    private:
        File* m_file;
        QList<File*> m_files;
        static Qml::Register::Controller<Controller> Register;
        bool m_showSource = false;
    private:
        auto ProcessObjectInfo(const QObject*) -> void;
    public:
        static Controller* instance;
        static auto Create() -> void;
        auto setFile(File*) -> void;
        auto getFile() -> File*;
        auto getFilesList() -> QQmlListProperty<File>;
        static auto fileCount(QQmlListProperty<File>*) -> int;
        static auto fileAt(QQmlListProperty<File>*, int) -> File*;
        auto openFile(const QString&) -> void;
        auto closeFile(File*) -> void;
        auto selectFile(File*) -> void;
        auto getFile(const QString&) -> File*;
        auto setShowSource(bool) -> void;
        auto getShowSource() -> bool;
        auto fileChangedExternally(File*) -> void;
    public slots:
        void run();
        void preRun();
        void postRun();
        void selectNext();
        void selectPrevious();
    signals:
        void fileChanged();
        void filesChanged();
        void createComponent();
        void showSourceChanged();
        void destroyComponent(quick::Document::File* file);
        void selectComponent(quick::Document::File* file);
    };
}
