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
            
            std::cout << "\n\ndone!" << std::endl;
            
            return 0;
        }
        
        return 1;
    }

    auto APIGenerator::init() -> bool {
        
        quick::Qml::Register::Init();
        
        doc_dir.cdUp();         // cdUp to 'bin'
        doc_dir.cdUp();         // cdUp to project root directory 'QuickVtk'
        doc_dir.cd("doc");      // cd to 'doc'

        if (!doc_dir.exists(json_path) && !doc_dir.mkpath(json_path)) {
            std::cerr << "unable to create directory '" << json_path << std::endl;
            return false;
        }
        
        if (!doc_dir.exists(docs_path) && !doc_dir.mkpath(docs_path)) {
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
        
        output_root_dir = doc_dir.absolutePath();
        
        return true;
    }
    
    auto APIGenerator::generateAPIJson() -> void {
        
        auto filePath = output_root_dir + "/" + json_path + "/api.json";
        
        std::cout << "generate api.json at '" << filePath.toStdString() << "'" << std::endl;
        
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
        
        QJsonObject json;
        
        json[Key::Namespace] = prefix;
        json[Key::Name] = name;
        json[Key::Type] = type;
        
        if (type.compare("class") == 0 || type.compare("abstract") == 0) {
            generateClassJson(static_cast<quick::TypeInfo::Class*>(symbol), json);
        }
                            
        root[identifier] = json;
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
        
        if (classType->getPrefix().compare("Vtk") == 0) {
            root[Key::VtkType] = "vtk" + classType->getName();
        }
        
        if (!propertiesJson.isEmpty()) {
            root[Key::Properties] = propertiesJson;
        }
        
        if (!methodsJson.isEmpty()) {
            root[Key::Properties] = methodsJson;
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
        
        doc_dir.cd(docs_path);
        
        for (auto type : typeList) {
            generateDocFile (type);
        }
    }

    auto APIGenerator::generateDocFile(TypeInfo::Symbol* symbol) -> void {
        
        auto prefix = symbol->getPrefix();
        
        if (prefix.isNull() || prefix.isEmpty()) {
            return;
        }
        
        auto name = symbol->getName();
        auto dir_path = doc_dir.absolutePath() + "/" + prefix;
        
        std::cout << "generate " << name.toStdString() << ".md at '" << dir_path.toStdString() << "'" << std::endl;
        
        if (!doc_dir.exists(prefix) && !doc_dir.mkpath(prefix)) {
            std::cerr << "unable to create directory '" << dir_path.toStdString() << std::endl;
            return;
        }
        
        auto filePath = dir_path + "/" + name + ".md";
        
        QFile file(filePath);
        
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            std::cerr << "unable to open file '" << filePath.toStdString() << "'" << std::endl;
            return;
        }
        
        QString content = "---\nlayout: api\ncategory: api\n\ntype: " + prefix + "." + name + "\n---";
        
        file.write(content.toUtf8());
    }
}
