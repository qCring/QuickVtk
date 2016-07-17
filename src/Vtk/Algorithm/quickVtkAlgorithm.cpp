#include "quickVtkAlgorithm.hpp"

#include "quickVtkProp.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<Algorithm> Algorithm::Register;

        Algorithm::Algorithm() {
            this->m_prop = 0;
        }

        Algorithm::Algorithm(Algorithm* other) {
            this->m_prop = 0;
        }

        auto Algorithm::setVtkAlgorithm(vtkSmartPointer<vtkAlgorithm> vtkAlgorithm) -> void {
            this->m_vtkAlgorithm = vtkAlgorithm;
        }

        auto Algorithm::getVtkAlgorithm() -> vtkSmartPointer<vtkAlgorithm> {
            return this->m_vtkAlgorithm;
        }

        auto Algorithm::setProp(Prop *prop) -> void {
            this->m_prop = prop;

            for (auto alg : this->m_input) {
                alg->setProp(prop);
            }
        }

        auto Algorithm::update() -> void {
            if (this->m_input.empty() && this->readyToUpdate()) {
                if (this->m_prop) {
                    this->m_prop->update();
                }
            } else {
                for (Algorithm* alg : this->m_input) {
                    alg->update();
                }
            }
        }

        auto Algorithm::readyToUpdate() -> bool {
            return true;
        }

        auto Algorithm::getInput() -> QQmlListProperty<Algorithm> {
            return QQmlListProperty<Algorithm>(this, 0, &appendInput, &inputCount, &inputAt, &clearInputs);
        }

        auto Algorithm::appendInput(QQmlListProperty<Algorithm>* list, Algorithm* algorithm) -> void {
            auto parent = qobject_cast<Algorithm*>(list->object);

            if(parent && algorithm) {
                parent->m_input.append(algorithm);
                int count = parent->m_input.count() - 1;

                parent->getVtkAlgorithm()->SetInputConnection(count, algorithm->getVtkAlgorithm()->GetOutputPort());

                emit parent->inputChanged();

                parent->setProp(algorithm->m_prop);
            }

            parent->update();
        }

        auto Algorithm::inputCount(QQmlListProperty<Algorithm>* list) -> int {
            auto parent = qobject_cast<Algorithm*>(list->object);

            if (parent) {
                return parent->m_input.count();
            }

            return 0;
        }

        auto Algorithm::inputAt(QQmlListProperty<Algorithm>* list, int i) -> Algorithm* {
            auto parent = qobject_cast<Algorithm*>(list->object);

            if (parent) {
                return parent->m_input.at(i);
            }

            return 0;
        }

        auto Algorithm::clearInputs(QQmlListProperty<Algorithm>* list) -> void {

            auto parent = qobject_cast<Algorithm*>(list->object);

            if (parent) {
                parent->m_input.clear();
                emit parent->inputChanged();
            }

            parent->update();
        }

        Algorithm::~Algorithm() {
            this->m_prop = 0;
        }
    }
}