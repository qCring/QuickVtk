#include "APIGenerator.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <QFile>
#include <QVariant>

#include "quickQmlRegister.hpp"
#include "quickTypeInfoList.hpp"

namespace quick {

    auto APIGenerator::execute() -> int {
        
        if (this->init()) {
            generateAPIJson();
            generateAPIDocs();
            
            std::cout << "\ndone." << std::endl;
            
            return 0;
        }
        
        return 1;
    }

    auto APIGenerator::init() -> bool {
        
        quick::Qml::Register::Init();
        
        docs_dir.cdUp();         // cdUp to 'bin'
        docs_dir.cdUp();         // cdUp to project root directory 'QuickVtk'
        docs_dir.cd("docs");     // cd to 'docs'

        if (!docs_dir.exists(json_path) && !docs_dir.mkpath(json_path)) {
            std::cerr << "unable to create directory '" << json_path << std::endl;
            return false;
        }
        
        if (!docs_dir.exists(docs_path) && !docs_dir.mkpath(docs_path)) {
            std::cerr << "unable to create directory '" << docs_path << std::endl;
            return false;
        }
        
        auto instance = quick::TypeInfo::List::GetInstance();
        
        if (instance == nullptr) {
            std::cerr << "unable to access TypeInfo" << std::endl;
            return false;
            
        }
        
        this->typeList = instance->getAllSymbols();
        
        if (this->typeList.isEmpty()) {
            std::cerr << "no types found" << std::endl;
            return false;
        }
        
        output_root_dir = docs_dir.absolutePath();
        
        return true;
    }
    
    auto APIGenerator::generateAPIJson() -> void {
        
        auto filePath = output_root_dir + "/" + json_path + "/api.json";
        
        std::cout << "generate " << filePath.toStdString() << std::endl;
        
        QFile file(filePath);
        
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            std::cerr << "unable to open file '" << filePath.toStdString() << "'" << std::endl;
            return;
        }

        QJsonObject jsonObject;
        
        for (auto type : typeList) {
            generateTypeJson (type, jsonObject);
        }
        
        QJsonDocument jsonDocument(jsonObject);
        file.write(jsonDocument.toJson(JsonFormat));
    }

    auto APIGenerator::generateTypeJson(TypeInfo::Symbol* symbol, QJsonObject& root) -> void {
        
        auto prefix = symbol->getPrefix();
        
        if (prefix.isNull() || prefix.isEmpty()) {
            return;
        }
        
        auto name = symbol->getName();
        auto type = symbol->getType();
        auto identifier = prefix + "." + name;
        
        if (type.compare("class") == 0 || type.compare("abstract") == 0) {
            QJsonObject json;
            
            if (!doc_dirs.contains(prefix)) {
                doc_dirs.insert(prefix);
            }
            
            json[Key::Namespace] = prefix;
            json[Key::Name] = name;
            json[Key::Type] = type;
            json[Key::Wrapper] = symbol->isWrapper();
            
            generateClassJson(static_cast<quick::TypeInfo::Class*>(symbol), json);
            
            root[identifier] = json;
        }
    }

    auto APIGenerator::generateClassJson(TypeInfo::Class* classType, QJsonObject& root) -> void {

        auto properties = classType->getAllProperties();
        auto methods = classType->getAllMethods();
        
        QJsonArray propertiesJson;
        QJsonArray methodsJson;
        
        for (auto prop : properties) {
            generatePropertyJson(prop, propertiesJson);
        }
        
        for (auto method : methods) {
            generateMethodJson(method, methodsJson);
        }
        
        if (!propertiesJson.isEmpty()) {
            root[Key::Properties] = propertiesJson;
        }
        
        if (!methodsJson.isEmpty()) {
            root[Key::Methods] = methodsJson;
        }
        
        root[Key::Base] = classType->getBase();
    }

    auto APIGenerator::generatePropertyJson(TypeInfo::Property* prop, QJsonArray& root) -> void {
        QJsonObject json;
        
        json[Key::Name] = prop->getName();
        json[Key::Type] = prop->getType();
        
        if (prop->isReadonly()) {
            json[Key::Readonly] = true;
        }
        
        root.append(json);
    }

    auto APIGenerator::generateMethodJson(TypeInfo::Method* method, QJsonArray& root) -> void {
        QJsonObject json;
        
        json[Key::Name] = method->getName();
        json[Key::Args] = method->getParamTypes();
        json[Key::Return] = method->getReturnType();
        
        root.append (json);
    }

    auto APIGenerator::generateAPIDocs() -> void {
        
        docs_dir.cd(docs_path);
        
        for (auto dir : doc_dirs) {
            
            if (docs_dir.exists(dir)) {
                QDir sub_dir(docs_dir.absolutePath() + "/" + dir);
                sub_dir.removeRecursively();
            }
            
            docs_dir.mkpath(dir);
        }
        
        for (auto type : typeList) {
            generateDocFile (type);
        }
    }

    auto APIGenerator::generateDocFile(TypeInfo::Symbol* symbol) -> void {
        
        auto prefix = symbol->getPrefix();
        
        if (prefix.isNull() || prefix.isEmpty()) {
            return;
        }
        
        if (symbol->getType().compare("enum") == 0) {
            return;
        }
        
        auto name = symbol->getName();
        auto file_path = docs_dir.absolutePath() + "/" + prefix + "/" + name + ".md";
        
        std::cout << "generate " << file_path.toStdString() << "'" << std::endl;
        
        QFile file(file_path);
        
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            std::cerr << "unable to open file '" << file_path.toStdString() << "'" << std::endl;
            return;
        }
        
        QString content = "---\nlayout: api\ncategory: api\n\ntype: " + prefix + "." + name + "\n---";
        
        file.write(content.toUtf8());
    }
}
