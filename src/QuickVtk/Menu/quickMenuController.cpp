#include "quickMenuController.hpp"
#include "quickMenuItem.hpp"
#include "quickConsoleController.hpp"
#include "quickDocumentController.hpp"
#include "quickDocumentFile.hpp"
#include "quickIO.hpp"
#include "quickAppSettings.hpp"
#include "quickAppEngine.hpp"

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
            auto menu_file = Item::Create::SimpleItem("File");
            auto menu_edit = Item::Create::SimpleItem("Edit");
            auto menu_view = Item::Create::SimpleItem("View");
            auto menu_help = Item::Create::SimpleItem("Help");
            
            instance->m_fileRecentFiles = Item::Create::SimpleItem("Open Recent", Action::File_Open_Recent);
            instance->m_viewToggleConsole = Item::Create::IconItem("Show Console", "fa_terminal", Action::View_Console);
            
            auto recentFiles = App::Settings::LoadRecentFiles();
            
            if (recentFiles.count() > 0) {
                instance->m_fileRecentFiles->add(Item::Create::SimpleItem("Clear File History", Action::File_Clear_History, Separator::On));
            } else {
                instance->m_fileRecentFiles->setEnabled(false);
            }
            
            for (const auto& entry : recentFiles) {
                auto menuItem = Item::Create::SimpleItem(entry, Action::File_Open_Recent);
                menuItem->setData(entry);
                instance->m_fileRecentFiles->add(menuItem);
            }
            
            menu_file->add(Item::Create::IconItem("Open...", "fa_folder_open_o", Action::File_Open));
            menu_file->add(instance->m_fileRecentFiles);
            menu_file->add(Item::Create::SimpleItem("Close", Action::File_Close, Separator::On));
            menu_file->add(Item::Create::IconItem("Quit", "fa_power_off", Action::File_Quit));
            
            menu_edit->add(Item::Create::IconItem("Settings", "fa_cog"));
            
            menu_view->add(instance->m_viewToggleConsole);
            menu_view->add(Item::Create::SimpleItem("Toggle Context View", Action::View_Context));
            menu_view->add(Item::Create::SimpleItem("Previous Tab", Action::View_Previous_Tab));
            menu_view->add(Item::Create::SimpleItem("Next Tab", Action::View_Next_Tab));
            
            menu_help->add(Item::Create::SimpleItem("About", Action::Help_About));
            menu_help->add(Item::Create::IconItem("Website", "fa_globe", Action::Help_Website));
            
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
                case Action::File_Open: OnFileOpen(); break;
                case Action::File_Open_Recent: OnFileOpenRecent(item->getData()); break;
                case Action::File_Close: OnFileClose(); break;
                case Action::File_Clear_History: OnFileClearHistory(); break;
                case Action::File_Quit: OnFileQuit(); break;
                case Action::View_Console: OnViewConsole(); break;
                case Action::View_Context: OnViewContext(); break;
                case Action::View_Previous_Tab: OnViewPreviousTab(); break;
                case Action::View_Next_Tab: OnViewNextTab(); break;
                case Action::Help_Website: OnHelpWebsite(); break;
                case Action::Help_About: OnHelpAbout(); break;
                default: break;
            }
        }
    
        auto Controller::OnFileOpen() -> void {
            auto filePath = IO::FromDialog::SelectOpenFileUrl("*.qml");
            auto file = Document::Controller::instance->getFile(filePath);
            
            if (file != nullptr) {
                file->select();
            } else if (IO::FileExists(filePath)) {
                bool addToRecentFiles = true;
                if (this->m_fileRecentFiles->isEmpty()) {
                    instance->m_fileRecentFiles->add(Item::Create::SimpleItem("Clear File History", Action::File_Clear_History, Separator::On));
                    instance->m_fileRecentFiles->setEnabled(true);
                } else {
                    for (const auto& file : instance->m_fileRecentFiles->getItems()) {
                        if (file->getData().compare(filePath) == 0) {
                            addToRecentFiles = false;
                            break;
                        }
                    }
                }
                
                if (addToRecentFiles) {
                    auto menuItem = Item::Create::SimpleItem(filePath, Action::File_Open_Recent);
                    menuItem->setData(filePath);
                    
                    this->m_fileRecentFiles->add(menuItem);
                    this->saveRecentFiles();
                }
                
                Document::Controller::instance->openFile(filePath);
            }
        }
    
        auto Controller::OnFileOpenRecent(const QString& path) -> void {
            auto file = Document::Controller::instance->getFile(path);
            
            if (file != nullptr) {
                file->select();
            } else if (IO::FileExists(path)) {
                Document::Controller::instance->openFile(path);
            } else {
                this->m_fileRecentFiles->removeItem(path);
                this->saveRecentFiles();
            }
        }
    
        auto Controller::OnFileClearHistory() -> void {
            this->m_fileRecentFiles->removeItems();
            this->m_fileRecentFiles->setEnabled(false);
            App::Settings::ClearRecentFiles();
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
    
        auto Controller::OnViewConsole() -> void {
            Console::Controller::instance->toggle();
        }
        
        auto Controller::OnViewContext() -> void {
            
        }
    
        auto Controller::OnViewPreviousTab() -> void {
            Document::Controller::instance->selectPrevious();
        }
        
        auto Controller::OnViewNextTab() -> void {
            Document::Controller::instance->selectNext();
        }
    
        auto Controller::OnHelpAbout() -> void {
            qDebug() << "Help > About";
        }
        
        auto Controller::OnHelpWebsite() -> void {
            qDebug() << "Help > Website";
        }
    
        auto Controller::updateViewConsoleMenu(bool visible) -> void {
            if (visible) {
                this->m_viewToggleConsole->setLabel("Hide Console");
            } else {
                this->m_viewToggleConsole->setLabel("Show Console");
            }
        }
    
        auto Controller::saveRecentFiles() -> void {
            QStringList list;
            
            for (const auto& file : this->m_fileRecentFiles->getItems()) {
                auto filePath = file->getData();
                
                if (!filePath.isEmpty()) {
                    list << file->getData();
                }
            }
            
            App::Settings::SaveRecentFiles(list);
        }
    }
}
