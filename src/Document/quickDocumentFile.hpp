#pragma once

#include "quickQmlRegister.hpp"

#include <QFileSystemWatcher>

namespace quick {
    namespace Document {
    
        class Error;

        class File : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString path READ getPath NOTIFY pathChanged);
            Q_PROPERTY(QString title READ getTitle NOTIFY titleChanged);
            Q_PROPERTY(QString content READ getContent NOTIFY contentChanged);
            Q_PROPERTY(bool modified READ getModified NOTIFY modifiedChanged);
            Q_PROPERTY(QQmlListProperty<quick::Document::Error> errors READ getErrorList NOTIFY errorsChanged);
            Q_PROPERTY(QObject* root READ getRoot WRITE setRoot NOTIFY rootChanged);
        private:
            QString m_path;
            QString m_title;
            QString m_content;
            bool m_modified;
            QObject* m_root = nullptr;
            QFileSystemWatcher* m_fileWatcher = nullptr;
            QList<Error*> m_errors;
            static Qml::Register::Type<File> Register;
        public:
            static auto Create(const QString&) -> File*;
            auto setPath(const QString&) -> void;
            auto getPath() -> QString;
            auto setTitle(const QString&) -> void;
            auto getTitle() -> QString;
            auto setContent(const QString&) -> void;
            auto getContent() -> QString;
            auto setModified(bool) -> void;
            auto getModified() -> bool;
            auto setRoot(QObject*) -> void;
            auto getRoot() -> QObject*;
            auto clearErrors() -> void;
            auto getErrorList() -> QQmlListProperty<Error>;
            static auto errorCount(QQmlListProperty<Error>*) -> int;
            static auto errorAt(QQmlListProperty<Error>*, int) -> Error*;
        public slots:
            void fileChanged(const QString&);
            void addError(int, int, const QString&);
            void close();
            void select();
        signals:
            void errorsChanged();
            void pathChanged();
            void rootChanged();
            void titleChanged();
            void contentChanged();
            void modifiedChanged();
            
            
        };
    }
}
