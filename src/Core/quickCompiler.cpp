#include "quickCompiler.hpp"
#include "quickUtilIO.hpp"

namespace quick {
    Compiler* Compiler::instance = nullptr;

    Qml::Register::Controller<Compiler> Compiler::Register = Qml::Register::Controller<Compiler>();

    Compiler::Compiler() {
        if (instance) {
            throw std::runtime_error("instance already existing");
        }

        this->m_modified = false;
        instance = this;

        this->m_fileWatcher = new QFileSystemWatcher();
        QObject::connect(this->m_fileWatcher, SIGNAL(fileChanged(const QString&)), this, SLOT(onFileChanged(const QString&)));
    }

    auto Compiler::Create() -> void {
        instance = new Compiler();
    }

    auto Compiler::setModified(bool modified) -> void {
        if (this->m_modified != modified) {
            this->m_modified = modified;
            emit this->modifiedChanged();
        }
    }

    auto Compiler::isModified() -> bool {
        return this->m_modified;
    }

    auto Compiler::updateSource() -> void {
        if (this->m_fileName.length()) {
            this->m_source = Util::IO::ReadTextFromFile(this->m_fileName);
            emit this->sourceChanged();
        }
    }

    auto Compiler::getSource() -> QString {
        return this->m_source;
    }

    auto Compiler::onFileChanged(const QString&) -> void {
        this->setModified(true);
    }

    auto Compiler::finished() -> void {
        this->setModified(false);
    }

    auto Compiler::openFile() -> void {

        if (this->m_fileName.length() > 0) {
            this->m_fileWatcher->removePath(this->m_fileName);
        }

        this->m_fileName = Util::IO::FileFromDialog("Load QML File", "*.qml*");
        emit this->fileNameChanged();

        if (this->m_fileName.length() > 0) {
            this->m_fileWatcher->addPath(this->m_fileName);
        }

        this->updateSource();
        emit this->compile();
    }

    auto Compiler::getFileName() -> QString {
        return this->m_fileName;
    }
}