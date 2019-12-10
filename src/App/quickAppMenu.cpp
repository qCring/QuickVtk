#include "quickAppMenu.hpp"
#include "quickAppSettings.hpp"
#include "quickAppInstance.hpp"
#include "quickAppMenuItem.hpp"

#include "quickConsoleController.hpp"
#include "quickDocumentController.hpp"
#include "quickDocumentFile.hpp"
#include "quickEditorController.hpp"
#include "quickIO.hpp"

#include <iostream>
#include <QMenuBar>
#include <QDesktopServices>

namespace quick {

    namespace App {

        Menu* Menu::instance = nullptr;
        Qml::Register::Controller<Menu> Menu::Register;

        Menu::Menu() {
            if (instance) {
                throw std::runtime_error("instance already existing");
            }

            instance = this;
        }

        auto Menu::Create() -> void {
            instance = new Menu();
        }

        auto Menu::Init() -> void {
            auto menu_file = new MenuItem("File");
            auto menu_edit = new MenuItem("Edit");
            auto menu_view = new MenuItem("View");
            auto menu_help = new MenuItem("Help");
            
            instance->m_recentFiles = new MenuItem("Open Recent", MenuItem::Action::File_Open_Recent);
            
            auto recentFiles = Settings::GetRecentFiles();
            
            for (const auto& entry : recentFiles) {
                auto menuItem = new MenuItem(entry, MenuItem::Action::File_Open_Recent);
                menuItem->setData(entry);
                instance->m_recentFiles->add(menuItem);
            }
            
            menu_file->add(new MenuItem("Open", "fa_folder_open_o", MenuItem::Action::File_Open));
            menu_file->add(instance->m_recentFiles);
            menu_file->add(new MenuItem("Close", MenuItem::Action::File_Close));
            menu_file->add(new MenuItem("Quit", "fa_power_off", MenuItem::Action::File_Quit));
            
            menu_edit->add(new MenuItem("Settings", "fa_cog", MenuItem::Action::Edit_Settings));
            
            menu_view->add(new MenuItem("Toggle Console", "fa_terminal", MenuItem::Action::View_Console));
            menu_view->add(new MenuItem("Toggle Context View", MenuItem::Action::View_Context));
            
            menu_help->add(new MenuItem("About", MenuItem::Action::Help_About));
            menu_help->add(new MenuItem("Website", "fa_globe", MenuItem::Action::Help_Website));
            
            instance->m_items.append(menu_file);
            instance->m_items.append(menu_edit);
            instance->m_items.append(menu_view);
            instance->m_items.append(menu_help);
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

        void Menu::select(MenuItem* item) {
            switch (item->action) {
                case MenuItem::Action::File_Open: OnFileOpen(); break;
                case MenuItem::Action::File_Open_Recent: OnFileOpenRecent(item->getData()); break;
                case MenuItem::Action::File_Close: OnFileClose(); break;
                case MenuItem::Action::File_Quit: OnFileQuit(); break;
                case MenuItem::Action::Edit_Settings: OnEditSettings(); break;
                case MenuItem::Action::View_Console: OnViewConsole(); break;
                case MenuItem::Action::View_Context: OnViewContext(); break;
                case MenuItem::Action::Help_Website: OnHelpWebsite(); break;
                case MenuItem::Action::Help_About: OnHelpAbout(); break;
                default: break;
            }
        }
    
        auto Menu::OnFileOpen() -> void {
            auto filePath = IO::FromDialog::SelectOpenFileUrl("*.qml");
            auto file = Document::Controller::instance->getFile(filePath);
            
            if (file != nullptr) {
                file->select();
            } else if (IO::FileExists(filePath)) {
                auto menuItem = new MenuItem(filePath, MenuItem::Action::File_Open_Recent);
                menuItem->setData(filePath);
                
                this->m_recentFiles->add(menuItem);
                Settings::AddRecentFile(filePath);
                
                Document::Controller::instance->openFile(filePath);
            }
            // TODO: handle invalid file urls
        }
    
        auto Menu::OnFileOpenRecent(const QString& path) -> void {
            auto file = Document::Controller::instance->getFile(path);
            
            if (file != nullptr) {
                file->select();
            } else if (IO::FileExists(path)) {
                Document::Controller::instance->openFile(path);
            } else {
                this->m_recentFiles->removeItem(path);
                Settings::RemoveRecentFile(path);
            }
        }
    
        auto Menu::OnFileClose() -> void {
            auto file = Document::Controller::instance->getFile();
            
            if (file != nullptr) {
                file->close();
            }
        }
        
        auto Menu::OnFileQuit() -> void {
            QCoreApplication::quit();
        }
        
        auto Menu::OnEditSettings() -> void {
            Settings::instance->setVisible(true);
        }
    
        auto Menu::OnViewConsole() -> void {
            Console::Controller::instance->toggle();
        }
        
        auto Menu::OnViewContext() -> void {
            
        }
    
        auto Menu::OnHelpAbout() -> void {
            qDebug() << "Help > About";
        }
        
        auto Menu::OnHelpWebsite() -> void {
            qDebug() << "Help > Website";
        }
    
        auto Menu::clearRecentFiles() -> void {
            this->m_recentFiles->removeItems();
        }
    }
}
