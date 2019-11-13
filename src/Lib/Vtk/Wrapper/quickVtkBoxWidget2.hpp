#pragma once

#include "quickVtkAbstractWidget.hpp"

#include <vtkBoxWidget2.h>

namespace quick {

    namespace Vtk {

        class BoxWidget2 : public AbstractWidget {
            Q_OBJECT
        private:
            static Qml::Register::Class<BoxWidget2> Register;
            vtkSmartPointer<vtkAbstractWidget> m_vtkObject = nullptr;
        public:
            BoxWidget2();
        };
    }
}
