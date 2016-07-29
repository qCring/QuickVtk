#include "quickAppWindow.hpp"

#include "quickUtilIO.hpp"
#include "meta_quickvtk.hpp"
#include "quickQmlRegister.hpp"
#include "quickAppController.hpp"
#include "quickSampleDataController.hpp"

#include <QFontDatabase>
#include <QApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QDir>

#include <iostream>
namespace quick {
    namespace App {
        Window* Window::instance = nullptr;

        Window::Window() {
            if (instance) {
                throw std::runtime_error("instance already existing");
            }

            instance = this;
        }

        auto Window::init() -> void {
            QApplication::setOrganizationName(Meta::orgName);
            QApplication::setOrganizationDomain(Meta::orgDomain);
            QApplication::setApplicationName(Meta::appName);
            QApplication::setApplicationVersion(Meta::versionString);

            Qml::Register::Init();

            auto path = QDir(QGuiApplication::applicationDirPath());

#ifndef _MSC_VER
            path.cdUp();
#endif

            resourceDir = path.absolutePath() + "/Resources/";

            AddFontDir(resourceDir + "fonts/roboto/");
            AddFontDir(resourceDir + "fonts/font-awesome/");

            this->m_view = new QQuickView();
            this->m_view->setTitle(QGuiApplication::applicationName());

            auto engine = this->m_view->engine();
            auto context = engine->rootContext();

            engine->addImportPath(resourceDir + "Modules");
            context->setContextProperty("App", Controller::instance);
            context->setContextProperty("SampleData", SampleData::Controller::Create());

            this->m_view->setSource(QUrl::fromLocalFile(resourceDir + "qml/App/window.qml"));
            this->m_view->setResizeMode(QQuickView::SizeRootObjectToView);
            this->m_view->showMaximized();
        }
        
        auto Window::start(int argc, char** argv) -> int {
            QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
            QApplication application(argc, argv);

            this->init();

            return application.exec();
        }

        auto Window::AddFontDir(const QString& directory) -> void {
            auto fontList = Util::IO::FilesFromDir(directory, {"*.ttf", "*.otf"});

            for (auto font : fontList) {
                QFontDatabase::addApplicationFont(font);
            }
        }

        auto Window::getResourceDir() -> QString {
            return this->resourceDir;
        }
    }
}
