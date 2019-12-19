#include "quickDocumentController.hpp"
#include "quickDocumentFile.hpp"

namespace quick {
    namespace Document {

        Controller* Controller::instance = nullptr;
        Qml::Register::Controller<Controller> Controller::Register;

        auto Controller::Create() -> void {
            if (instance) {
                throw new std::runtime_error("instance already existing");
            }
            
            instance = new Controller();
        }
    
        auto Controller::setFile(File* file) -> void {
            if (this->m_file != file) {
                this->m_file = file;
                emit this->fileChanged();
                
                for (const auto& file : this->m_files) {
                    file->setSelected(false);
                }
                
                this->m_file->setSelected(true);
                emit this->selectComponent(this->m_file);
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
    
        auto Controller::getFile(const QString& filePath) -> File* {
            for (const auto& file : this->m_files) {
                if (file->getPath().compare(filePath) == 0) {
                    return file;
                }
            }
            
            return nullptr;
        }
    
        auto Controller::setShowSource(bool showSource) -> void {
            if (this->m_showSource != showSource) {
                this->m_showSource = showSource;
                emit this->showSourceChanged();
            }
        }
    
        auto Controller::getShowSource() -> bool {
            return this->m_showSource;
        }
    
        auto Controller::closeFile(File* file) -> void {
            this->m_files.removeOne(file);
            
            emit this->destroyComponent(file);
            emit this->filesChanged();
            
            if (this->m_files.count() > 0) {
                this->setFile(this->m_files.at(0));
            } else {
                this->m_file = nullptr;
                emit this->fileChanged();
            }
        }
    
        auto Controller::selectFile(File* file) -> void {
            this->setFile(file);
        }
    
        void Controller::preRun() {
            if (this->m_file != nullptr) {
                this->m_file->clearErrors();
            }
        }
    
        void Controller::postRun() {
            if (this->m_file != nullptr) {
                this->m_file->setModified(false);
                emit this->m_file->errorsChanged();
            }
        }
    
        void Controller::run() {
            
            if (this->m_file != nullptr) {
                emit this->createComponent();
            }
        }
    
        void Controller::selectNext() {
            auto count = this->m_files.count();
            
            if (this->m_file != nullptr && count > 1) {
                auto index = this->m_files.indexOf(this->m_file) + 1;
                
                if (index < count) {
                    this->setFile(this->m_files.at(index));
                }
            }
        }
    
        void Controller::selectPrevious() {
            if (this->m_file != nullptr && this->m_files.count() > 1) {
                auto index = this->m_files.indexOf(this->m_file) - 1;
                
                if (index < 0) {
                    return;
                }
                    
                this->setFile(this->m_files.at(index));
            }
        }
    }
}
