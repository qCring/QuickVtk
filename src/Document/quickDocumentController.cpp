#include "quickDocumentController.hpp"
#include "quickDocumentFile.hpp"

namespace quick {
    namespace Document {

        Controller* Controller::instance = nullptr;
        Qml::Register::Controller<Controller> Controller::Register;

        auto Controller::Create() -> void {
            instance = new Controller();
        }
    
        auto Controller::setFile(File* file) -> void {
            if (this->m_file != file) {
                this->m_file = file;
                emit this->fileChanged();
                emit this->selectComponent(file);
            }
        }
    
        auto Controller::getFile() -> File* {
            return this->m_file;
        }
    
        auto Controller::getFilesList() -> QQmlListProperty<quick::Document::File> {
            return QQmlListProperty<File>(this, nullptr, &fileCount, &fileAt);
        }
    
        auto Controller::fileCount(QQmlListProperty<File>* list) -> int {
            auto parent = qobject_cast<Controller*>(list->object);

            if (parent) {
                return parent->m_files.count();
            }

            return 0;
        }

        auto Controller::fileAt(QQmlListProperty<File>* list, int i) -> File* {
            auto parent = qobject_cast<Controller*>(list->object);

            if (parent) {
                return parent->m_files.at(i);
            }

            return 0;
        }
    
        auto Controller::openFile(const QString& path) -> void {
            File* file = File::Create(path);
            
            if (file != nullptr) {
                this->m_files.append(file);
                this->setFile(file);
                
                emit this->filesChanged();
                emit this->createComponent();
            }
        }
    
        auto Controller::removeFile(File* file) -> void {
            this->m_files.removeOne(file);
            
            if (this->m_files.count() > 0) {
                this->m_file = this->m_files.at(0);
            } else {
                this->m_file = nullptr;
            }
                
            emit this->filesChanged();
            emit this->fileChanged();
            emit this->destroyComponent(file);
        }
    
        auto Controller::selectFile(File* file) -> void {
            this->setFile(file);
        }
    
        void Controller::run() {
            if (this->m_file != nullptr) {
                this->m_file->clearErrors();
            }
            
            if (this->m_file != nullptr) {
                emit this->m_file->errorsChanged();
            }
        }
    }
}
