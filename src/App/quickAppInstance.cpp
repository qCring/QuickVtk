#include "quickAppInstance.hpp"

#include "quickIO.hpp"
#include "meta_quickvtk.hpp"
#include "quickQmlRegister.hpp"
#include "quickAppController.hpp"
#include "quickSampleDataController.hpp"
#include "quickConsoleController.hpp"

#include <QWindow>
#include <QFontDatabase>
#include <QApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QDir>
#include <iostream>

namespace quick {

    namespace App {

        Instance* Instance::instance = nullptr;

        Instance::Instance() {
        }

        auto Instance::HandleMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg) -> void {
            std::cout << msg.toStdString() << std::endl;

            if (instance->m_messageHandled.localData()) {
                return;
            }

            QScopedValueRollback<bool> roll(instance->m_messageHandled.localData(), true);
            
            switch(type) {
                case QtMsgType::QtDebugMsg: Console::Controller::GetInstance()->addDebugMsg(msg); break;
                case QtMsgType::QtInfoMsg: Console::Controller::GetInstance()->addInfoMsg(msg); break;
                case QtMsgType::QtWarningMsg: Console::Controller::GetInstance()->addWarningMsg(msg); break;
                default: Console::Controller::GetInstance()->addErrorMsg(msg); break;
            }
        }

        auto Instance::init() -> void {
            QApplication::setOrganizationName(Meta::orgName);
            QApplication::setOrganizationDomain(Meta::orgDomain);
            QApplication::setApplicationName(Meta::appName);
            QApplication::setApplicationVersion(Meta::versionString);

            Qml::RegisterTypes();

            auto path = QDir(QGuiApplication::applicationDirPath());

#ifdef __APPLE__
            path.cdUp();
#endif
            resourceDir = path.absolutePath() + "/Resources/";

            AddFontDir(resourceDir + "fonts/roboto/");
            AddFontDir(resourceDir + "fonts/vera/");
            AddFontDir(resourceDir + "fonts/font-awesome/");

            auto engine = new QQmlApplicationEngine ();

            auto context = engine->rootContext();
            context->setContextProperty("Controllers", Controller::instance);
            context->setContextProperty("SampleData", SampleData::Controller::Create());

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

        auto Instance::Execute(int argc, char** argv) -> int {
            qInstallMessageHandler(HandleMessage);

            QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
            QApplication application(argc, argv);

            if (!instance) {
                instance = new Instance();
                instance->init();
                return application.exec();
            }

            return 1;
        }

        auto Instance::AddFontDir(const QString& directory) -> void {
            auto fontUrls = IO::FileUrlsFromDir(directory, {"*.ttf", "*.otf"}, IO::FileSuffix::On);

            for (auto fontUrl : fontUrls) {
                QFontDatabase::addApplicationFont(fontUrl);
            }
        }

        auto Instance::GetResourceDir() -> QString {
            return instance->resourceDir;
        }
    }
}
