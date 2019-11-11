#include "quickQmlRegister.hpp"

#include "quickTypeInfoSymbol.hpp"
#include "quickTypeInfoList.hpp"

namespace quick {

    namespace Qml {

        auto RegisterTypes() -> void {

            for (auto initializer : Register::Initializers::GetList()) {
                initializer();
            }

            TypeInfo::List::GetInstance()->init();
        }

        namespace Register {

            auto Initializers::GetList() -> QList<std::function<void(void)>>& {
                static QList<std::function<void(void)>> List;
                return List;
            }
        }
    }
}
