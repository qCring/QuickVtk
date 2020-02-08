#include "quickTypeInfoSymbol.hpp"
#include "quickTypeInfoList.hpp"
#include "quickTypeInfoEnum.hpp"
#include "quickTypeInfoEnumItem.hpp"
#include "quickTypeInfoClass.hpp"

#include <QMetaEnum>
#include <QString>

namespace quick::TypeInfo {

    auto Symbol::Get::ClassName(QMetaObject metaObject) -> QString {
        return QString(metaObject.className()).section("::", 2, 2);
    }

    auto Symbol::Get::ClassPrefix(QMetaObject metaObject) -> QString {
        return QString(metaObject.className()).section("::", 1, 1);
    }

    auto Symbol::Get::EnumName(QMetaEnum metaEnum) -> QString {
        return QString(metaEnum.scope()).section("::", 2, 2) + "." + metaEnum.name();
    }

    auto Symbol::Get::EnumPrefix(QMetaEnum metaEnum) -> QString {
        return QString(metaEnum.scope()).section("::", 1, 1);
    }

    auto Symbol::Get::BaseString(QMetaObject metaObject) -> QString {
        auto base = *metaObject.superClass();
        auto baseName = Get::ClassName(base);
        auto retVal = QString();

        if (!baseName.isEmpty()) {
            auto basePrefix = Get::ClassPrefix(base);

            if (!basePrefix.isEmpty()) {
                retVal = basePrefix + "." + baseName;
            }
        } else {
            retVal = base.className();
        }

        return retVal;
    }

    Qml::Register::Type<Symbol> Symbol::Register;

    auto Symbol::GetEnums() -> QStringList& {
        static QStringList Enums { ".TransformOrigin" };
        return Enums;
    }

    auto Symbol::PrettifyTypeName(QString typeName) -> QString {
        auto prettyTypeName = typeName.remove("*").remove("quick::").replace("::", ".");

        if (prettyTypeName.contains("List")) {
            auto bracketOpenIndex = prettyTypeName.lastIndexOf("<");
            auto bracketCloseIndex = prettyTypeName.lastIndexOf(">");
            
            if (bracketOpenIndex && bracketCloseIndex) {
                prettyTypeName = "List <" + PrettifyType(prettyTypeName.mid(bracketOpenIndex + 1, bracketCloseIndex - bracketOpenIndex - 1)) + ">";
            }
        } else {
            prettyTypeName = PrettifyType(prettyTypeName);
        }
        
        return prettyTypeName;
    }

    auto Symbol::PrettifyType(QString typeString) -> QString {
        if (typeString.compare("QString") == 0) {
            typeString = "string";
        } else if (typeString.compare("QColor") == 0) {
            typeString = "color";
        } else if (typeString.compare("double") == 0) {
            typeString = "real";
        }
        
        return typeString;
    }

    auto Symbol::MakeEnum(QMetaEnum metaEnum) -> void {
        auto name = Get::EnumName(metaEnum);
        auto prefix = Get::EnumPrefix(metaEnum);

        if (GetEnums().contains(name) || prefix.isEmpty()) {
            return;
        }

        auto symbol = new Enum();

        symbol->m_prefix = prefix;
        symbol->m_name = name;
        symbol->m_type = 2;

        for (auto i = 0; i < metaEnum.keyCount(); ++i) {
            symbol->add(new EnumItem(metaEnum.key(i), metaEnum.value(i)));
        }

        GetEnums().append(name);

        List::EnumLookup.insert(symbol->getPrefix() + "." + name, symbol);
        List::Add(symbol);
    }

    auto Symbol::MakeClass(QMetaObject metaObject, bool isWrapper) -> void {
        auto symbol = new Class();

        symbol->setBase(Get::BaseString(metaObject));
        symbol->m_prefix = Get::ClassPrefix(metaObject);
        symbol->m_name = Get::ClassName(metaObject);
        symbol->m_type = 1;
        symbol->m_isWrapper = isWrapper;
        
        for (auto i = metaObject.enumeratorOffset(); i < metaObject.enumeratorCount(); ++i) {
            auto metaEnum = metaObject.enumerator(i);
            
            symbol->addEnumDefinition(Symbol::Get::EnumPrefix(metaEnum), Symbol::Get::EnumName(metaEnum));
        }
        
        for (auto i = metaObject.propertyOffset(); i < metaObject.propertyCount(); ++i) {
            symbol->addClassProperty(metaObject.property(i));
        }
        
        for (auto i = 0; i < metaObject.propertyOffset(); ++i) {
            symbol->addBaseProperty(metaObject.property(i));
        }

        for (auto i = 0; i < metaObject.methodOffset(); ++i) {
            auto method = metaObject.method(i);
            
            if (method.methodType() == QMetaMethod::MethodType::Slot && method.access() == QMetaMethod::Access::Public) {
                symbol->addBaseMethod(metaObject.method(i));
            }
        }
        
        for (auto i = metaObject.methodOffset(); i < metaObject.methodCount(); ++i) {
            auto method = metaObject.method(i);
            
            if (method.methodType() == QMetaMethod::MethodType::Slot && method.access() == QMetaMethod::Access::Public) {
                symbol->addClassMethod(metaObject.method(i));
            }
        }

        List::Add(symbol);
    }

    auto Symbol::MakeAbstractClass(QMetaObject metaObject, bool isWrapper) -> void {
        auto symbol = new Class();

        symbol->setBase(Get::BaseString(metaObject));
        symbol->m_prefix = Get::ClassPrefix(metaObject);
        symbol->m_name = Get::ClassName(metaObject);
        symbol->m_type = 0;
        symbol->m_isWrapper = isWrapper;

        symbol->setAbstract(true);
        
        for (auto i = metaObject.propertyOffset(); i < metaObject.propertyCount(); ++i) {
            symbol->addClassProperty(metaObject.property(i));
        }
        
        for (auto i = 0; i < metaObject.propertyOffset(); ++i) {
            symbol->addBaseProperty(metaObject.property(i));
        }

        List::Add(symbol);
    }

    auto Symbol::matches(const QString& filter) -> bool {
        QStringList words = filter.simplified().split(" ", QString::SkipEmptyParts);

        bool match = false;

        for (auto word : words) {
            match = this->m_name.contains(word, Qt::CaseInsensitive) ||
                this->m_prefix.contains(word, Qt::CaseInsensitive);

            if (!match) return false;
        }

        return true;
    }

    auto Symbol::operator < (const Symbol& other) -> const bool {
        return this->m_name < other.m_name;
    }

    auto Symbol::getName() -> QString {
        return this->m_name;
    }

    auto Symbol::getPrefix() -> QString {
        return this->m_prefix;
    }

    auto Symbol::getType() -> int {
        return this->m_type;
    }

    auto Symbol::isWrapper() -> bool {
        return this->m_isWrapper;
    }
}
