#include "quickDocumentFile.hpp"
#include "quickDocumentController.hpp"
#include "quickDocumentError.hpp"
#include "quickIO.hpp"

#include <QDebug>
#include <QTime>

namespace quick::Document {

    Qml::Register::Type<File> File::Register;

    auto File::Create(const QString& path) -> File* {
        if (!IO::FileExists(path)) {
            return nullptr;
        }
        
        auto file = new File();
        
        file->m_path = path;
        file->m_title = IO::FileNameFromPath(path);
        file->m_modified = false;
        file->m_content = IO::Read::TextFromUrl(path);
        file->m_fileWatcher = new QFileSystemWatcher({ path });
        
        QObject::connect(file->m_fileWatcher, SIGNAL(fileChanged(const QString&)), file, SLOT(fileChanged(const QString&)));
        
        return file;
    }

    auto File::getErrorList() -> QQmlListProperty<Error> {
        return QQmlListProperty<Error>(this, nullptr, &errorCount, &errorAt);
    }

    auto File::errorCount(QQmlListProperty<Error>* list) -> int {
        auto parent = qobject_cast<File*>(list->object);

        if (parent) {
            return parent->m_errors.count();
        }

        return 0;
    }

    auto File::errorAt(QQmlListProperty<Error>* list, int i) -> Error* {
        auto parent = qobject_cast<File*>(list->object);

        if (parent) {
            return parent->m_errors.at(i);
        }

        return 0;
    }

    auto File::fileChanged(const QString& path) -> void {
        this->setContent(IO::Read::TextFromUrl(path));
        this->setModified(true);
        Controller::instance->fileChangedExternally(this);
    }

    auto File::setPath(const QString& path) -> void {
        this->m_path = path;
        emit this->pathChanged();
    }

    auto File::getPath() -> QString {
        return this->m_path;
    }
    
    auto File::setTitle(const QString& title) -> void {
        this->m_title = title;
        emit this->titleChanged();
    }
    
    auto File::getTitle() -> QString {
        return this->m_title;
    }

    auto File::setContent(const QString& content) -> void {
        this->m_content = content;
        emit this->contentChanged();
    }
    
    auto File::getContent() -> QString {
        return this->m_content;
    }

    auto File::setModified(bool modified) -> void {
        this->m_modified = modified;
        emit this->modifiedChanged();
    }

    auto File::getModified() -> bool {
        return this->m_modified;
    }

    auto File::getTimeStamp() -> QString {
        return this->m_timeStamp;
    }

    auto File::setSelected(bool selected) -> void {
        if (this->m_selected != selected) {
            this->m_selected = selected;
            emit this->selectedChanged();
        }
    }

    auto File::getSelected() -> bool {
        return this->m_selected;
    }

    auto File::close() -> void {
        Controller::instance->closeFile(this);
    }

    auto File::select() -> void {
        Controller::instance->selectFile(this);
    }

    auto File::setComponent(QObject* component) -> void {
        this->m_component = component;
        emit this->componentChanged();
    }

    auto File::getComponent() -> QObject* {
        return this->m_component;
    }

    auto File::clearErrors() -> void {
        this->m_errors.clear();
        emit this->errorsChanged();
    }

    auto File::addError(int line, int column, const QString& message) -> void {
        auto error = new Error(line, column, QString(message).remove('\n'));
        this->m_errors.append(error);
    }

    auto File::updateTimeStamp() -> void {
        this->m_timeStamp = QTime::currentTime().toString();
        emit this->timeStampChanged();
    }
}
