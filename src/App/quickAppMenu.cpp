#include "quickAppMenu.hpp"

#include "quickCodeEditor.hpp"
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

        void Menu::OnFileNew() {
            Code::Editor::instance->newFile();
        }

        void Menu::OnFileOpen() {
            Code::Editor::instance->openFile();
        }

        void Menu::OnFileSave() {
            Code::Editor::instance->saveFile();
        }

        void Menu::OnFileSaveAs() {
            Code::Editor::instance->saveFile();
        }

        void Menu::OnFindFind() {
            Code::Editor::instance->showSearch();
        }

        void Menu::OnCodeRun() {
            Code::Editor::instance->run();
        }

        void Menu::OnCodeFormat() {
            Code::Editor::instance->format();
        }

        void Menu::OnViewIncreaseFontSize() {
            Code::Editor::instance->increaseFontSize();
        }

        void Menu::OnViewDecreaseFontSize() {
            Code::Editor::instance->decreaseFontSize();
        }

        void Menu::OnViewResetFontSize() {
            Code::Editor::instance->resetFontSize();
        }

        void Menu::OnViewToggleEditor() {
            Code::Editor::instance->toggleExpanded();
        }

        void Menu::OnHelpAbout() {
            //
        }

        void Menu::OnHelpDocumentation() {
            //
        }

        void Menu::OnHelpPreferences() {
            //
        }

        void Menu::OnHelpVisitOnGitHub() {
            QDesktopServices::openUrl(QUrl("https://github.com/qCring/QuickVtk", QUrl::TolerantMode));
        }

        void Menu::OnHelpSendFeedback() {
            QDesktopServices::openUrl(QUrl("mailto:qCring@gmail.com?subject=QuickVtk Feedback", QUrl::TolerantMode));
        }

        void Menu::OnHelpExample(const QString& exampleName) {
            Code::Editor::instance->open(Instance::GetResourceDir() + "examples/qml/simple/" + exampleName + ".qml");
        }
    }
}
