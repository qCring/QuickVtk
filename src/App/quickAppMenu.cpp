#include "quickAppMenu.hpp"

#include "quickDocumentController.hpp"
#include "quickEditorController.hpp"
#include "quickAppInstance.hpp"
#include "quickAppMenuItem.hpp"
#include "quickIO.hpp"

#include <iostream>
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
            auto menu_file = new MenuItem("File");
            auto menu_edit = new MenuItem("Edit");
            auto menu_view = new MenuItem("View");
            auto menu_help = new MenuItem("Help");
            
            this->m_recentFiles = new MenuItem("Open Recent", MenuItem::Action::File_Open_Recent);
            
            menu_file->add(new MenuItem("Open", "fa_folder_open_o", MenuItem::Action::File_Open));
            menu_file->add(this->m_recentFiles);
            menu_file->add(new MenuItem("Quit", "fa_power_off", MenuItem::Action::File_Quit));
            
            menu_help->add(new MenuItem("About", MenuItem::Action::Help_About));
            menu_help->add(new MenuItem("Website", "fa_globe", MenuItem::Action::Help_Website));
            
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

        void Menu::select(MenuItem* item) {
            switch (item->action) {
                case MenuItem::Action::File_Open: OnFileOpen(); break;
                case MenuItem::Action::File_Open_Recent: OnFileOpenRecent(item->getData()); break;
                case MenuItem::Action::File_Quit: OnFileQuit(); break;
                case MenuItem::Action::Help_Website: OnHelpWebsite(); break;
                case MenuItem::Action::Help_About: OnHelpAbout(); break;
            }
        }
    
        auto Menu::OnFileOpen() -> void {
            auto filePath = IO::FromDialog::SelectOpenFileUrl("*.qml");
            
            if (IO::FileExists(filePath)) {
                auto menuItem = new MenuItem(filePath);
                menuItem->setData(filePath);
                
                this->m_recentFiles->add(menuItem);
            }
            
            Document::Controller::instance->openFile(filePath);
        }
    
        auto Menu::OnFileOpenRecent(const QString& path) -> void {
            if (IO::FileExists(path)) {
                Document::Controller::instance->openFile(path);
            } else {
                // remove from recent files
            }
        }
        
        auto Menu::OnFileQuit() -> void {
            qDebug() << "File Quit";
        }
        
        auto Menu::OnHelpAbout() -> void {
            qDebug() << "Help About";
        }
        
        auto Menu::OnHelpWebsite() -> void {
            qDebug() << "Help Website";
        }
    }
}
