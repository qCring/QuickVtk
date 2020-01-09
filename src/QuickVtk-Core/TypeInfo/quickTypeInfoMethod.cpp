#include "quickTypeInfoMethod.hpp"
#include "quickTypeInfoSymbol.hpp"

namespace quick {

    namespace TypeInfo {

        Qml::Register::Type<Method> Method::Register;

        auto Method::Create(QMetaMethod metaMethod, Type type) -> Method* {
            auto name = QString(metaMethod.name());
            auto paramTypes = QString();
            auto sequence = false;

            if (name == "deleteLater") {
                return nullptr;
            }

            auto returnType = Symbol::PrettifyTypeName(metaMethod.typeName());

            auto paramTypeList = metaMethod.parameterTypes();
            auto separator = QString(", ");

            for (auto paramType : paramTypeList) {
                paramTypes.append(Symbol::PrettifyTypeName(paramType)).append(separator);
            }

            if (paramTypeList.count() > 0) {
                paramTypes.remove(paramTypes.length() - separator.length(), paramTypes.length());
            }

            if (paramTypeList.count() == 0) {
                paramTypes = "void";
            }

            if (returnType.contains("List")) {
                sequence = true;
            }

            auto method = new Method();

            method->m_returnType = returnType;
            method->m_paramTypes = paramTypes;
            method->m_name = name;
            method->m_sequence = sequence;
            method->m_inherited = type == Type::BaseMethod;

            return method;
        }

        auto Method::getReturnType() -> QString {
            return this->m_returnType;
        }

        auto Method::getParamTypes() -> QString {
            return this->m_paramTypes;
        }

        auto Method::isSequence() -> bool {
            return this->m_sequence;
        }
    
        auto Method::isInherited() -> bool {
            return this->m_inherited;
        }

        auto Method::getName() -> QString {
            return this->m_name;
        }
    }
}
