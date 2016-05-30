#include "quickCompiler.hpp"
#include "quickUtilIO.hpp"

namespace quick {
    Compiler* Compiler::instance = nullptr;

    Qml::Register::Controller<Compiler> Compiler::Register = Qml::Register::Controller<Compiler>();

    Compiler::Compiler() {
        if (instance) {
            throw std::runtime_error("instance already existing");
        }

        this->m_autocompile = false;
        this->m_modified = false;
        this->m_failed = false;
        this->m_ready = false;
        instance = this;

        this->m_fileWatcher = new QFileSystemWatcher();
        QObject::connect(this->m_fileWatcher, SIGNAL(fileChanged(const QString&)), this, SLOT(onFileChanged(const QString&)));
    }

    auto Compiler::Create() -> void {
        instance = new Compiler();
    }

    auto Compiler::setReady(bool ready) -> void {
        if (this->m_ready != ready) {
            this->m_ready = ready;
            emit this->readyChanged();
        }
    }

    auto Compiler::isReady() -> bool {
        return this->m_ready;
    }

    auto Compiler::setModified(bool modified) -> void {
        if (this->m_modified != modified) {
            this->m_modified = modified;
            emit this->modifiedChanged();

            if (modified && this->m_autocompile) {
                this->updateSource();
                emit this->compile();
            }
        }
    }

    auto Compiler::isModified() -> bool {
        return this->m_modified;
    }

    auto Compiler::updateSource() -> void {
        if (this->m_filePath.length()) {
            this->m_source = Util::IO::ReadTextFromFile(this->m_filePath);
            emit this->sourceChanged();
        }
    }

    auto Compiler::setFailed(bool failed) -> void {
        if (this->m_failed != failed) {
            this->m_failed = failed;
            emit this->failedChanged();
        }
    }

    auto Compiler::getFailed() -> bool {
        return this->m_failed;
    }

    auto Compiler::setAutocompile(bool autocompile) -> void {
        if (this->m_autocompile != autocompile) {
            this->m_autocompile = autocompile;
            emit this->autocompileChanged();

            if (autocompile && this->m_modified) {
                this->updateSource();
                emit this->compile();
            }
        }
    }

    auto Compiler::getAutocompile() -> bool {
        return this->m_autocompile;
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

    auto Compiler::linkFile() -> void {

        if (this->m_filePath.length() > 0) {
            this->m_fileWatcher->removePath(this->m_filePath);
        }

        this->m_filePath = Util::IO::FileFromDialog("Load QML File", "*.qml*");
        emit this->filePathChanged();

        if (this->m_filePath.length() > 0) {
            this->m_fileWatcher->addPath(this->m_filePath);
            this->setReady(true);
        } else {
            this->setReady(false);
        }

        this->updateSource();
        emit this->compile();
    }

    auto Compiler::getFilePath() -> QString {
        return this->m_filePath;
    }
}