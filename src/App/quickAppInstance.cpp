#include "quickAppInstance.hpp"

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

namespace quick {

    namespace App {

        Instance* Instance::instance = nullptr;

        Instance::Instance() {
        }

        auto Instance::init() -> void {
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
            AddFontDir(resourceDir + "fonts/vera/");
            AddFontDir(resourceDir + "fonts/font-awesome/");

            this->m_view = new QQuickView();
            this->m_view->setTitle(QGuiApplication::applicationName());

            auto engine = this->m_view->engine();
            auto context = engine->rootContext();

            engine->addImportPath(resourceDir + "qml");
            context->setContextProperty("App", Controller::instance);
            context->setContextProperty("SampleData", SampleData::Controller::Create());

            this->m_view->setSource(QUrl::fromLocalFile(resourceDir + "qml/App/window.qml"));
            this->m_view->setResizeMode(QQuickView::SizeRootObjectToView);
            this->m_view->showMaximized();
        }
        
        auto Instance::Execute(int argc, char** argv) -> int {
            QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
            QApplication application(argc, argv);

            if (!instance) {
                instance = new Instance();
                instance->init();
                return application.exec();
            }

            return -1;
        }

        auto Instance::AddFontDir(const QString& directory) -> void {
            auto fontUrls = Util::IO::FileUrlsFromDir(directory, {"*.ttf", "*.otf"});

            for (auto fontUrl : fontUrls) {
                QFontDatabase::addApplicationFont(fontUrl);
            }
        }

        auto Instance::GetResourceDir() -> QString {
            return instance->resourceDir;
        }
    }
}
