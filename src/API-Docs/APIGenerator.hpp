#pragma once

#include <QJsonDocument>
#include <QString>
#include <QList>

#include "quickTypeInfoSymbol.hpp"
#include "quickTypeInfoClass.hpp"
#include "quickTypeInfoEnum.hpp"
#include "quickTypeInfoEnumItem.hpp"
#include "quickTypeInfoMethod.hpp"
#include "quickTypeInfoProperty.hpp"

namespace quick {
    
    class APIGenerator {

        class Key {
        public:
            static constexpr auto Namespace = "namespace";
            static constexpr auto Properties = "properties";
            static constexpr auto Methods = "methods";
            static constexpr auto Base = "base";
            static constexpr auto Name = "name";
            static constexpr auto Type = "type";
            static constexpr auto Readonly = "readonly";
            static constexpr auto Args = "args";
            static constexpr auto Return = "return";
            static constexpr auto Wrapper = "wrapper";
        };
        
    private:
        static constexpr auto json_path = "_data";
        static constexpr auto docs_path = "content/_api";
        static constexpr auto JsonFormat = QJsonDocument::JsonFormat::Compact;
    private:
        QString output_root_dir;
        QList<TypeInfo::Symbol*> typeList;
        QDir docs_dir;
        QSet<QString> doc_dirs;
    private:
        auto init() -> bool;
        auto generateAPIJson() -> void;
        auto generateAPIDocs() -> void;
        auto generateTypeJson(TypeInfo::Symbol*, QJsonObject&) -> void;
        auto generateClassJson(TypeInfo::Class*, QJsonObject&) -> void;
        auto generatePropertyJson(TypeInfo::Property*, QJsonArray&) -> void;
        auto generateMethodJson(TypeInfo::Method*, QJsonArray&) -> void;
        auto generateDocFile(TypeInfo::Symbol*) -> void;
    public:
        auto execute() -> int;
    };
}
