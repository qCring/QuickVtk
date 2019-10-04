#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <QFile>
#include <QVariant>
#include <QJsonDocument>

#include "quickQmlRegister.hpp"
#include "quickTypeInfoList.hpp"

#include "quickTypeInfoSymbol.hpp"
#include "quickTypeInfoClass.hpp"
#include "quickTypeInfoEnum.hpp"
#include "quickTypeInfoEnumItem.hpp"
#include "quickTypeInfoMethod.hpp"
#include "quickTypeInfoProperty.hpp"

auto generateAPIJson(QString path, QList<quick::TypeInfo::Symbol*> typeList) -> void {
    
    auto filePath = path + "/api.json";
    
    std::cout << "generate api json at '" << filePath.toStdString() << std::endl;
    
    QFile file(filePath);
    
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        std::cout << "unable to create file 'api.json'" << std::endl;
        return;
    }

    QJsonObject jsonObject;
    
    for (auto item : typeList) {
        
        auto prefix = item->getPrefix();
        
        if (prefix.isNull() || prefix.isEmpty()) {
            continue;
        }
        
        auto name = item->getName();
        auto type = item->getType();
        auto identifier = prefix + "." + name;
        
        QJsonObject typeJson;
        
        std::cout << "prefix: '" << prefix.toStdString() << "' name: '" << name.toStdString() << "'" << std::endl;
        
        typeJson["namespace"] = prefix;
        typeJson["name"] = name;
        typeJson["type"] = type;
        
        if (type.compare("class") == 0 || type.compare("abstract") == 0) {
            auto classItem = static_cast<quick::TypeInfo::Class*>(item);
            auto properties = classItem->getAllProperties();
            
            QJsonObject propertiesJson;
            
            for (auto prop : properties) {
                QJsonObject propertyJson;
                
                propertyJson ["type"] = prop->getType();
                propertyJson ["readonly"] = prop->isReadonly();
                
                propertiesJson[prop->getName()] = propertyJson;
            }
            
            typeJson["properties"] = propertiesJson;
            typeJson["base"] = classItem->getBase();
        }
                            
        jsonObject[identifier] = typeJson;
    }
    
    QJsonDocument jsonDocument(jsonObject);
    file.write(jsonDocument.toJson());
    
    std::cout << "successfully generated 'api.json'" << std::endl;
}

auto generateAPIDocs(QString path, QList<quick::TypeInfo::Symbol*> typeList) -> void {
    
    std::cout << "generate api docs at '" << path.toStdString() << std::endl;
}

auto main(int argc, char *argv[]) -> int {
    
    quick::Qml::Register::Init();
    
    auto doc_dir = QDir(); // starting from 'build'
    
    const auto json_dir = "_data";
    const auto docs_dir = "content/_api";
    
    doc_dir.cdUp(); // cdUp to 'bin'
    doc_dir.cdUp(); // cdUp to project root directory 'QuickVtk'
    doc_dir.cd("doc"); // cd to 'doc'

    if (!doc_dir.exists(json_dir)) {
        std::cout << doc_dir.mkpath(json_dir) << std::endl;
    }
    
    if (!doc_dir.exists(docs_dir)) {
        std::cout << doc_dir.mkpath(docs_dir) << std::endl;
    }
    
    auto instance = quick::TypeInfo::List::GetInstance();
    auto typeList = instance->getAllSymbols();
    
    std::cout << doc_dir.absolutePath().toStdString() << std::endl;
    
    generateAPIJson(doc_dir.absolutePath() + "/" + json_dir, typeList);
    generateAPIDocs(doc_dir.absolutePath() + "/" + docs_dir, typeList);
}
