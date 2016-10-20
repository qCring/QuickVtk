#include "quickVtkPiecewiseFunction.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::UncreatableClass<PiecewiseFunction> PiecewiseFunction::Register;

        PiecewiseFunction::PiecewiseFunction(vtk_t vtkObject, cb_t&& callback) : m_vtkObject(vtkObject), m_callback(callback) {
        }

        auto PiecewiseFunction::update() -> void {
            this->m_callback.operator()();
        }

        void PiecewiseFunction::clear() {
            this->m_xValues.clear();
            this->m_yValues.clear();

            emit this->sizeChanged();
            this->m_vtkObject->RemoveAllPoints();
            this->update();
        }

        void PiecewiseFunction::add(double x, double y) {
            this->m_xValues.append(x);
            this->m_yValues.append(y);

            emit this->sizeChanged();
            this->m_vtkObject->AddPoint(x, y);
            this->update();
        }

        auto PiecewiseFunction::getX(int i) -> double {
            return i < this->m_xValues.length() && i >= 0 ? this->m_xValues.at(i) : 0;
        }

        auto PiecewiseFunction::getY(int i) -> double {
            return i < this->m_yValues.length() && i >= 0 ? this->m_yValues.at(i) : 0;
        }

        auto PiecewiseFunction::setClamping(bool clamping) -> void {
            this->m_vtkObject->SetClamping(clamping);
            this->update();
        }

        auto PiecewiseFunction::getClamping() -> bool {
            return this->m_vtkObject->GetClamping();
        }
        
        auto PiecewiseFunction::getSize() -> int {
            return this->m_xValues.length();
        }
    }
}
