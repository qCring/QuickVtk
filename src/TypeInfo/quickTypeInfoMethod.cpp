#include "quickTypeInfoMethod.hpp"

namespace quick {

    namespace TypeInfo {

        Qml::Register::Type<Method> Method::Register;

        auto Method::Create(QMetaMethod metaMethod) -> Method* {
            auto name = QString(metaMethod.name());
            auto paramTypes = QString();
            auto sequence = false;

            if (name == "deleteLater") {
                return nullptr;
            }

            auto returnType = QString(metaMethod.typeName()).remove("*").remove("quick::").replace("::", ".");

            auto paramTypeList = metaMethod.parameterTypes();
            auto separator = QString(", ");

            for (auto paramType : paramTypeList) {
                paramTypes.append(paramType).append(separator);
            }

            if (paramTypeList.count() > 0) {
                paramTypes.remove(paramTypes.length() - separator.length(), paramTypes.length());
            }

            if (paramTypeList.count() == 0) {
                paramTypes = "void";
            }

            if (returnType.contains("List")) {
                sequence = true;
                if (auto bracketIndex = returnType.lastIndexOf("<")) {
                    returnType.remove(0, bracketIndex + 1);
                    returnType = returnType.remove("<").remove(">");
                } else if (returnType.contains("string")) {
                    returnType = "string";
                }
            }

            if (returnType.startsWith("Q") && returnType.length() > 2) {
                QChar character = returnType.at(1);
                returnType = returnType.remove(0, 2);
                returnType.push_front(character.toLower());
            }

            auto method = new Method();

            method->m_returnType = returnType;
            method->m_paramTypes = paramTypes;
            method->m_name = name;
            method->m_sequence = sequence;

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

        auto Method::getName() -> QString {
            return this->m_name;
        }
    }
}
