#include <QObject>
#include <QQuickView>

namespace quick {
    class App : public QObject {
    private:
        QQuickView* m_view = nullptr;
        QString m_versionString;
        QString m_resourceDir;
        QString m_resourceFile;
        QString m_orgName;
        QString m_orgDomain;
        QString m_appName;
    public:
        static App* instance;
        App();
        auto setVersionString(const QString&) -> void;
        auto setResourceFile(const QString&) -> void;
        auto setOrgName(const QString&) -> void;
        auto setOrgDomain(const QString&) -> void;
        auto setAppName(const QString&) -> void;
        auto getView() -> QQuickView*;
        auto getResourceDir() -> QString;
        auto exec(int, char**) -> int;
    };
}
