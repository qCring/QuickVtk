#include "quickTypeInfoSymbol.hpp"
#include "quickTypeInfoList.hpp"
#include "quickTypeInfoEnum.hpp"
#include "quickTypeInfoEnumItem.hpp"
#include "quickTypeInfoClass.hpp"

#include <QMetaEnum>

namespace quick {

    namespace TypeInfo {

        auto Symbol::Get::ClassName(QMetaObject metaObject) -> QString {
            return QString(metaObject.className()).section("::", 2, 2);
        }

        auto Symbol::Get::ClassPrefix(QMetaObject metaObject) -> QString {
            return QString(metaObject.className()).section("::", 1, 1);
        }

        auto Symbol::Get::EnumName(QMetaEnum metaEnum) -> QString {
            return metaEnum.name();
        }

        auto Symbol::Get::EnumPrefix(QMetaEnum metaEnum) -> QString {
            return QString(metaEnum.scope()).section("::", 1, 1);
        }

        Qml::Register::Type<Symbol> Symbol::Register;

        auto Symbol::GetEnums() -> QStringList& {
            static QStringList Enums { "TransformOrigin" };
            return Enums;
        }

        auto Symbol::setSelected(bool selected) -> void {
            if (this->m_selected != selected) {
                this->m_selected = selected;
                emit this->selectedChanged();
            }
        }

        auto Symbol::MakeEnum(QMetaEnum metaEnum) -> void {
            auto name = metaEnum.name();

            if (GetEnums().contains(name)) {
                return;
            }

            auto symbol = new Enum();

            symbol->m_prefix = Get::EnumPrefix(metaEnum);
            symbol->m_name = name;
            symbol->m_type = "Enum";
            symbol->m_color = "#B75711";

            for (auto i = 0; i < metaEnum.keyCount(); ++i) {
                symbol->add(new EnumItem(metaEnum.key(i), metaEnum.value(i)));
            }

            GetEnums().append(name);

            List::Add(symbol);
        }

        auto Symbol::MakeClass(QMetaObject metaObject) -> void {
            auto symbol = new Class();

            symbol->m_prefix = Get::ClassPrefix(metaObject);
            symbol->m_name = Get::ClassName(metaObject);
            symbol->m_type = "Class";
            symbol->m_color = "#319CD3";

            for (auto i = 0; i < metaObject.propertyCount(); ++i) {
                symbol->addProperty(metaObject.property(i));
            }

            List::Add(symbol);
        }

        auto Symbol::MakeAbstractClass(QMetaObject metaObject) -> void {
            auto symbol = new Class();

            symbol->m_prefix = Get::ClassPrefix(metaObject);
            symbol->m_name = Get::ClassName(metaObject);
            symbol->m_type = "Abstract";
            symbol->m_color = "#6E7582";

            symbol->setAbstract(true);

            for (auto i = 0; i < metaObject.propertyCount(); ++i) {
                symbol->addProperty(metaObject.property(i));
            }

            List::Add(symbol);
        }

        auto Symbol::isSelected() -> bool {
            return this->m_selected;
        }

        auto Symbol::matches(const QString& filter) -> bool {
            QStringList words = filter.simplified().split(" ", QString::SkipEmptyParts);

            bool match = false;

            for (auto word : words) {
                match = this->m_name.contains(word, Qt::CaseInsensitive) ||
                    this->m_type.contains(word, Qt::CaseInsensitive) ||
                    this->m_prefix.contains(word, Qt::CaseInsensitive);

                if (!match) return false;
            }

            return true;
        }

        auto Symbol::getName() -> QString {
            return this->m_name;
        }

        auto Symbol::getPrefix() -> QString {
            return this->m_prefix;
        }

        auto Symbol::getType() -> QString {
            return this->m_type;
        }

        auto Symbol::getColor() -> QColor {
            return this->m_color;
        }

        void Symbol::select() {
            List::GetInstance()->selectItem(this);
        }
    }
}