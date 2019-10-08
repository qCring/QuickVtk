#include "quickVtkBoxWidget2.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::Class<BoxWidget2> BoxWidget2::Register(true);

        BoxWidget2::BoxWidget2() : AbstractWidget(vtkSmartPointer<vtkBoxWidget2>::New()) {
            this->m_vtkObject = vtkBoxWidget2::SafeDownCast(this->getVtkObject());
        }
    }
}
