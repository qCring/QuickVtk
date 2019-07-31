#include "quickAppMenu.hpp"

#include "quickEditorController.hpp"
#include "quickAppInstance.hpp"
#include "quickIO.hpp"

#include <QMenuBar>
#include <QDesktopServices>

namespace quick {

    namespace App {

        Menu* Menu::instance = nullptr;
        Qml::Register::Type<Menu> Menu::Register;

        Menu::Menu() {
            if (instance) {
                throw std::runtime_error("instance already existing");
            }

            this->init();

            instance = this;
        }

        auto Menu::GetInstance() -> Menu* {
            return instance ? instance : new Menu();
        }

        auto Menu::init() -> void {
            this->m_examples = IO::FileNamesFromDir(Instance::GetResourceDir() + "examples/qml/simple", {"*.qml"}, IO::FileSuffix::Off);
        }

        auto Menu::getExamples() -> QStringList {
            return this->m_examples;
        }

        void Menu::OnFileLoad() {
            Editor::Controller::instance->loadFile();
        }

        void Menu::OnFindFind() {
            Editor::Controller::instance->showSearch();
        }

        void Menu::OnCodeRun() {
            Editor::Controller::instance->run();
        }

        void Menu::OnViewIncreaseFontSize() {
            Editor::Controller::instance->increaseFontSize();
        }

        void Menu::OnViewDecreaseFontSize() {
            Editor::Controller::instance->decreaseFontSize();
        }

        void Menu::OnViewResetFontSize() {
            Editor::Controller::instance->resetFontSize();
        }

        void Menu::OnViewToggleEditor() {
            Editor::Controller::instance->toggleExpanded();
        }

        void Menu::OnHelpVisitOnGitHub() {
            QDesktopServices::openUrl(QUrl("https://github.com/qCring/QuickVtk", QUrl::TolerantMode));
        }

        void Menu::OnHelpSendFeedback() {
            QDesktopServices::openUrl(QUrl("mailto:qCring@gmail.com?subject=QuickVtk Feedback", QUrl::TolerantMode));
        }

        void Menu::OnHelpExample(const QString& exampleName) {
            Editor::Controller::instance->loadExample(Instance::GetResourceDir() + "examples/qml/simple/" + exampleName + ".qml");
        }
    }
}
