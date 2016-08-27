#include "quickCompiler.hpp"
#include "quickUtilIO.hpp"

namespace quick {
    Compiler* Compiler::instance = nullptr;

    Qml::Register::Controller<Compiler> Compiler::Register;

    Compiler::Compiler() {
        if (instance) {
            throw std::runtime_error("instance already existing");
        }

        this->m_failed = false;
        instance = this;
    }

    auto Compiler::Create() -> void {
        instance = new Compiler();
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

    auto Compiler::setSource(const QString& source) -> void {
        this->m_source = source;
        emit this->sourceChanged();
    }

    auto Compiler::getSource() -> QString {
        return this->m_source;
    }
}