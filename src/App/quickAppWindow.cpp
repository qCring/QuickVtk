#include "quickAppWindow.hpp"

#include "quickUtilIO.hpp"
#include "meta_quickvtk.hpp"
#include "quickAppController.hpp"

#include <QFontDatabase>
#include <QApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QDir>

namespace quick {
    namespace App {
        Window* Window::instance = nullptr;

        Window::Window() {
            if (instance) {
                throw std::runtime_error("instance already existing");
            }

            instance = this;
        }

        auto Window::start(int argc, char ** argv) -> int {
            QApplication application(argc, argv);

            QApplication::setOrganizationName(Meta::orgName);
            QApplication::setOrganizationDomain(Meta::orgDomain);
            QApplication::setApplicationName(Meta::appName);
            QApplication::setApplicationVersion(Meta::versionString);

            auto path = QDir(QGuiApplication::applicationDirPath());
            path.cdUp();

            resourceDir = path.absolutePath() + "/Resources/";

            AddFontDir(resourceDir + "fonts/roboto/");
            AddFontDir(resourceDir + "fonts/font-awesome/");

            auto controller = Controller::Create();

            this->m_view = new QQuickView();
            this->m_view->setTitle(QGuiApplication::applicationName());
            this->m_view->engine()->rootContext()->setContextProperty("App", controller);
            this->m_view->setSource(QUrl::fromLocalFile(resourceDir + "qml/window.qml"));
            this->m_view->setResizeMode(QQuickView::SizeRootObjectToView);
            this->m_view->showMaximized();

            return application.exec();
        }

        auto Window::AddFontDir(const QString& directory) -> void {
            auto fontList = Util::IO::FilesFromDir(directory, {"*.ttf", "*.otf"});

            for (auto font : fontList) {
                QFontDatabase::addApplicationFont(font);
            }
        }
    }
}
