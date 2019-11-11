#include "quickQmlRegister.hpp"

#include "quickTypeInfoSymbol.hpp"
#include "quickTypeInfoList.hpp"

namespace quick {

    namespace Qml {

        namespace Register {

            auto Init() -> void {

                for (auto func : Queue::GetList()) {
                    func();
                }

                TypeInfo::List::GetInstance()->init();
            }

            auto Queue::GetList()->QList<std::function<void(void)>>& {
                static QList<std::function<void(void)>> List;
                return List;
            }
        }
    }
}
