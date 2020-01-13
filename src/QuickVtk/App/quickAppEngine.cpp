#include "quickAppEngine.hpp"
#include "quickAppController.hpp"

#include "quickMenuController.hpp"
#include "quickSampleDataController.hpp"
#include "quickConsoleController.hpp"

#include "quickIO.hpp"
#include "meta_quickvtk.hpp"
#include "quickQmlRegister.hpp"

#include <QWindow>
#include <QFontDatabase>
#include <QApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QDir>
#include <iostream>

namespace quick {
    namespace App {
    
        Engine* Engine::instance = nullptr;

        auto Engine::HandleMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg) -> void {
            qDebug() << "  > " << msg;

            if (instance->m_messageHandled.localData()) {
                return;
            }

            QScopedValueRollback<bool> roll(instance->m_messageHandled.localData(), true);
            
            switch(type) {
                case QtMsgType::QtDebugMsg: Console::Controller::instance->addDebugMsg(msg); break;
                case QtMsgType::QtInfoMsg: Console::Controller::instance->addInfoMsg(msg); break;
                case QtMsgType::QtWarningMsg: Console::Controller::instance->addWarningMsg(msg); break;
                default: Console::Controller::instance->addErrorMsg(msg); break;
            }
        }

        auto Engine::init() -> void {
            QApplication::setOrganizationName(Meta::OrgName);
            QApplication::setOrganizationDomain(Meta::OrgDomain);
            QApplication::setApplicationName(Meta::AppName);
            QApplication::setApplicationVersion(Meta::AppVersion);

            Qml::RegisterTypes();
            
            SampleData::Controller::Create();
            Menu::Controller::Init();

            auto path = QDir(QGuiApplication::applicationDirPath());

    #ifdef __APPLE__
            path.cdUp();
    #endif
            resourceDir = path.absolutePath() + "/Resources/";

            AddFontDir(resourceDir + "fonts/Roboto/");
            AddFontDir(resourceDir + "fonts/font-awesome/");

            auto engine = new QQmlApplicationEngine ();

            auto context = engine->rootContext();
            context->setContextProperty("App", Controller::instance);
            context->setContextProperty("SampleData", SampleData::Controller::instance);

            engine->addImportPath(resourceDir + "qml");
            engine->load(QUrl::fromLocalFile(resourceDir + "qml/App/window.qml"));

            auto rootObject = engine->rootObjects().at(0);
            auto window = static_cast<QWindow*>(rootObject);

            QSurfaceFormat format;
            format.setMajorVersion(3);
            format.setMinorVersion(2);
            format.setDepthBufferSize(1);
            format.setStencilBufferSize(1);
            format.setProfile(QSurfaceFormat::CoreProfile);

            window->setFormat(format);
            window->showMaximized();
        }

        auto Engine::Execute(int argc, char** argv) -> int {
            qInstallMessageHandler(HandleMessage);

            QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
            QApplication application(argc, argv);

            if (!instance) {
                instance = new Engine();
                instance->init();
                return application.exec();
            }

            return 1;
        }

        auto Engine::AddFontDir(const QString& directory) -> void {
            auto fontUrls = IO::FileUrlsFromDir(directory, {"*.ttf", "*.otf"}, IO::FileSuffix::On);

            for (const auto& fontUrl : fontUrls) {
                QFontDatabase::addApplicationFont(fontUrl);
            }
        }

        auto Engine::GetResourceDir() -> QString {
            return instance->resourceDir;
        }
    }
}
