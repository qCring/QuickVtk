#include "quickMenuController.hpp"
#include "quickAppSettings.hpp"
#include "quickAppInstance.hpp"
#include "quickMenuItem.hpp"

#include "quickConsoleController.hpp"
#include "quickDocumentController.hpp"
#include "quickDocumentFile.hpp"
#include "quickEditorController.hpp"
#include "quickIO.hpp"

#include <iostream>
#include <QMenuBar>
#include <QDesktopServices>

namespace quick {
    namespace Menu {

        Controller* Controller::instance = nullptr;
        Qml::Register::Controller<Controller> Controller::Register;

        Controller::Controller() {
            if (instance) {
                throw std::runtime_error("instance already existing");
            }

            instance = this;
        }

        auto Controller::Create() -> void {
            instance = new Controller();
        }

        auto Controller::Init() -> void {
            auto menu_file = new Item("File");
            auto menu_edit = new Item("Edit");
            auto menu_view = new Item("View");
            auto menu_help = new Item("Help");
            
            instance->m_recentFiles = new Item("Open Recent", Item::Action::File_Open_Recent);
            
            auto recentFiles = App::Settings::GetRecentFiles();
            
            for (const auto& entry : recentFiles) {
                auto menuItem = new Item(entry, Item::Action::File_Open_Recent);
                menuItem->setData(entry);
                instance->m_recentFiles->add(menuItem);
            }
            
            menu_file->add(new Item("Open...", "fa_folder_open_o", Item::Action::File_Open));
            menu_file->add(instance->m_recentFiles);
            menu_file->add(new Item("Close", Item::Action::File_Close));
            menu_file->add(new Item("Quit", "fa_power_off", Item::Action::File_Quit));
            
            menu_edit->add(new Item("Settings", "fa_cog", Item::Action::Edit_Settings));
            
            menu_view->add(new Item("Toggle Console", "fa_terminal", Item::Action::View_Console));
            menu_view->add(new Item("Toggle Context View", Item::Action::View_Context));
            
            menu_help->add(new Item("About", Item::Action::Help_About));
            menu_help->add(new Item("Website", "fa_globe", Item::Action::Help_Website));
            
            instance->m_items.append(menu_file);
            instance->m_items.append(menu_edit);
            instance->m_items.append(menu_view);
            instance->m_items.append(menu_help);
        }
    
        auto Controller::getItemList() -> QQmlListProperty<Item> {
            return QQmlListProperty<Item>(this, nullptr, &itemCount, &itemAt);
        }
    
        auto Controller::itemCount(QQmlListProperty<Item>* list) -> int {
            auto parent = qobject_cast<Controller*>(list->object);
            
            if (parent) {
                return parent->m_items.count();
            }
            
            return 0;
        }
        
        auto Controller::itemAt(QQmlListProperty<Item>* list, int index) -> Item* {
            auto parent = qobject_cast<Controller*>(list->object);
            
            if (parent) {
                return parent->m_items.at(index);
            }
            
            return nullptr;
        }

        void Controller::select(Item* item) {
            switch (item->action) {
                case Item::Action::File_Open: OnFileOpen(); break;
                case Item::Action::File_Open_Recent: OnFileOpenRecent(item->getData()); break;
                case Item::Action::File_Close: OnFileClose(); break;
                case Item::Action::File_Quit: OnFileQuit(); break;
                case Item::Action::Edit_Settings: OnEditSettings(); break;
                case Item::Action::View_Console: OnViewConsole(); break;
                case Item::Action::View_Context: OnViewContext(); break;
                case Item::Action::Help_Website: OnHelpWebsite(); break;
                case Item::Action::Help_About: OnHelpAbout(); break;
                default: break;
            }
        }
    
        auto Controller::OnFileOpen() -> void {
            auto filePath = IO::FromDialog::SelectOpenFileUrl("*.qml");
            auto file = Document::Controller::instance->getFile(filePath);
            
            if (file != nullptr) {
                file->select();
            } else if (IO::FileExists(filePath)) {
                auto menuItem = new Item(filePath, Item::Action::File_Open_Recent);
                menuItem->setData(filePath);
                
                this->m_recentFiles->add(menuItem);
                App::Settings::AddRecentFile(filePath);
                
                Document::Controller::instance->openFile(filePath);
            }
            // TODO: handle invalid file urls
        }
    
        auto Controller::OnFileOpenRecent(const QString& path) -> void {
            auto file = Document::Controller::instance->getFile(path);
            
            if (file != nullptr) {
                file->select();
            } else if (IO::FileExists(path)) {
                Document::Controller::instance->openFile(path);
            } else {
                this->m_recentFiles->removeItem(path);
                App::Settings::RemoveRecentFile(path);
            }
        }
    
        auto Controller::OnFileClose() -> void {
            auto file = Document::Controller::instance->getFile();
            
            if (file != nullptr) {
                file->close();
            }
        }
        
        auto Controller::OnFileQuit() -> void {
            QCoreApplication::quit();
        }
        
        auto Controller::OnEditSettings() -> void {
            App::Settings::instance->setVisible(true);
        }
    
        auto Controller::OnViewConsole() -> void {
            Console::Controller::instance->toggle();
        }
        
        auto Controller::OnViewContext() -> void {
            
        }
    
        auto Controller::OnHelpAbout() -> void {
            qDebug() << "Help > About";
        }
        
        auto Controller::OnHelpWebsite() -> void {
            qDebug() << "Help > Website";
        }
    
        auto Controller::clearRecentFiles() -> void {
            this->m_recentFiles->removeItems();
        }
    }
}
