#include "quickApp.hpp"

#include "quickAppController.hpp"

#include <QFontDatabase>
#include <QApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QDir>

namespace quick {
    App* App::instance = nullptr;

    App::App() {
        if (instance) {
            throw std::runtime_error("instance already existing");
        }

        instance = this;
    }

    auto App::setOrgName(const QString& orgName) -> void {
        this->m_orgName = orgName;
    }

    auto App::setAppName(const QString& appName) -> void {
        this->m_appName = appName;
    }

    auto App::setOrgDomain(const QString& orgDomain) -> void {
        this->m_orgDomain = orgDomain;
    }

    auto App::setResourceFile(const QString& resourceFile) -> void {
        this->m_resourceFile = resourceFile;
    }

    auto App::setVersionString(const QString& versionString) -> void {
        this->m_versionString = versionString;
    }

    auto App::exec(int argc, char **argv) -> int {
        QApplication::setOrganizationName(this->m_orgName);
        QApplication::setOrganizationDomain(this->m_orgDomain);
        QApplication::setApplicationName(this->m_appName);
        QApplication::setApplicationVersion(this->m_versionString);

        QApplication application(argc, argv);

        auto path = QDir(QGuiApplication::applicationDirPath());
        path.cdUp();

        this->m_resourceDir = path.absolutePath() + "/Resources";

        QFontDatabase::addApplicationFont(this->m_resourceDir + "/fonts/roboto/Roboto-Black.ttf");
        QFontDatabase::addApplicationFont(this->m_resourceDir + "/fonts/roboto/Roboto-BlackItalic.ttf");
        QFontDatabase::addApplicationFont(this->m_resourceDir + "/fonts/roboto/Roboto-Bold.ttf");
        QFontDatabase::addApplicationFont(this->m_resourceDir + "/fonts/roboto/Roboto-BoldItalic.ttf");
        QFontDatabase::addApplicationFont(this->m_resourceDir + "/fonts/roboto/Roboto-Italic.ttf");
        QFontDatabase::addApplicationFont(this->m_resourceDir + "/fonts/roboto/Roboto-Light.ttf");
        QFontDatabase::addApplicationFont(this->m_resourceDir + "/fonts/roboto/Roboto-LightItalic.ttf");
        QFontDatabase::addApplicationFont(this->m_resourceDir + "/fonts/roboto/Roboto-Medium.ttf");
        QFontDatabase::addApplicationFont(this->m_resourceDir + "/fonts/roboto/Roboto-MediumItalic.ttf");
        QFontDatabase::addApplicationFont(this->m_resourceDir + "/fonts/roboto/Roboto-Regular.ttf");
        QFontDatabase::addApplicationFont(this->m_resourceDir + "/fonts/roboto/Roboto-Thin.ttf");
        QFontDatabase::addApplicationFont(this->m_resourceDir + "/fonts/roboto/Roboto-ThinItalic.ttf");

        auto controller = AppController::Create();
        controller->setVersion(this->m_versionString);

        this->m_view = new QQuickView();
        this->m_view->setTitle(this->m_appName);
        this->m_view->engine()->rootContext()->setContextProperty("App", controller);
        this->m_view->setSource(QUrl::fromLocalFile(this->m_resourceDir + this->m_resourceFile));
        this->m_view->setResizeMode(QQuickView::SizeRootObjectToView);
        this->m_view->showMaximized();

        return application.exec();
    }
}