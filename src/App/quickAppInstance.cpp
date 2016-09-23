#include "quickAppInstance.hpp"

#include "quickIO.hpp"
#include "meta_quickvtk.hpp"
#include "quickQmlRegister.hpp"
#include "quickAppController.hpp"
#include "quickSampleDataController.hpp"
#include "quickAppLogger.hpp"

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
            std::cout << "handle message: " << msg.toStdString() << std::endl;

            if (instance->m_messageHandled.localData()) {
                return;
            }

            QScopedValueRollback<bool> roll(instance->m_messageHandled.localData(), true);

            Logger::GetInstance()->addEntry(msg);
        }

        auto Instance::init() -> void {
            QApplication::setOrganizationName(Meta::orgName);
            QApplication::setOrganizationDomain(Meta::orgDomain);
            QApplication::setApplicationName(Meta::appName);
            QApplication::setApplicationVersion(Meta::versionString);

            Qml::Register::Init();

            auto path = QDir(QGuiApplication::applicationDirPath());

#ifdef __APPLE__
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


            QSurfaceFormat format;
            format.setMajorVersion(3);
            format.setMinorVersion(2);
            format.setDepthBufferSize(1);
            format.setStencilBufferSize(1);
            format.setProfile(QSurfaceFormat::CoreProfile);

            this->m_view->setFormat(format);
            this->m_view->setSource(QUrl::fromLocalFile(resourceDir + "qml/App/window.qml"));
            this->m_view->setResizeMode(QQuickView::SizeRootObjectToView);
            this->m_view->showMaximized();
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
            auto fontUrls = IO::FileUrlsFromDir(directory, {"*.ttf", "*.otf"});

            for (auto fontUrl : fontUrls) {
                QFontDatabase::addApplicationFont(fontUrl);
            }
        }

        auto Instance::GetResourceDir() -> QString {
            return instance->resourceDir;
        }
    }
}
