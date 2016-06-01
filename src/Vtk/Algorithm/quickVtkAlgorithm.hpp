#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>
#include <QQmlListProperty>

#include <vtkSmartPointer.h>
#include <vtkAlgorithm.h>

namespace quick {

    namespace Vtk {

        class Prop;
        class DataObject;

        class Algorithm : public QObject {
            Q_OBJECT
            Q_PROPERTY(QQmlListProperty<quick::Vtk::Algorithm> input READ getInput NOTIFY inputChanged);
            Q_CLASSINFO("DefaultProperty", "input");
        private:
            static Qml::Register::VtkAbstractClass<Algorithm> Register;
            QList<Algorithm*> m_input;
            vtkSmartPointer<vtkAlgorithm> m_vtkAlgorithm;
            Prop* m_prop;
        public:
            Algorithm();
            Algorithm(Algorithm*);
            auto setProp(Prop*) -> void;
            auto setVtkAlgorithm(vtkSmartPointer<vtkAlgorithm>) -> void;
            auto getInput() -> QQmlListProperty<Algorithm>;
            auto update() -> void;
            auto getVtkAlgorithm() -> vtkSmartPointer<vtkAlgorithm>;
            virtual auto onInputAdded(Algorithm*) -> void;
            static auto appendInput(QQmlListProperty<Algorithm>*, Algorithm*) -> void;
            static auto inputCount(QQmlListProperty<Algorithm>*) -> int;
            static auto inputAt(QQmlListProperty<Algorithm>*, int) -> Algorithm*;
            static auto clearInputs(QQmlListProperty<Algorithm>*) -> void;
            ~Algorithm();
        signals:
            void inputChanged();
        };
    }
}