#include "quickAppMenu.hpp"

#include "quickEditorController.hpp"
#include "quickAppInstance.hpp"
#include "quickAppMenuItem.hpp"
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
            
            auto menu_file = new MenuItem("File");
            auto menu_edit = new MenuItem("Edit");
            auto menu_view = new MenuItem("View");
            auto menu_help = new MenuItem("Help");
            
            menu_file->add(new MenuItem("Open"));
            menu_file->add(new MenuItem("Open Recent"));
            menu_file->add(new MenuItem("Quit"));
            
            menu_help->add(new MenuItem("About"));
            menu_help->add(new MenuItem("Website"));
            
            this->m_items.append(menu_file);
            this->m_items.append(menu_edit);
            this->m_items.append(menu_view);
            this->m_items.append(menu_help);
        }
    
        auto Menu::getItemList() -> QQmlListProperty<MenuItem> {
            return QQmlListProperty<MenuItem>(this, nullptr, &itemCount, &itemAt);
        }
    
        auto Menu::itemCount(QQmlListProperty<MenuItem>* list) -> int {
            auto parent = qobject_cast<Menu*>(list->object);
            
            if (parent) {
                return parent->m_items.count();
            }
            
            return 0;
        }
        
        auto Menu::itemAt(QQmlListProperty<MenuItem>* list, int index) -> MenuItem* {
            auto parent = qobject_cast<Menu*>(list->object);
            
            if (parent) {
                return parent->m_items.at(index);
            }
            
            return nullptr;
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
    
        void Menu::select(MenuItem* item) {
            qDebug() << item->getName();
        }
    }
}
