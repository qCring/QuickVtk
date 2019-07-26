#pragma once

#include "quickVtkDataSetAlgorithm.hpp"

#include <vtkTextureMapToCylinder.h>

namespace quick {

    namespace Vtk {

        class TextureMapToCylinder : public DataSetAlgorithm {
            Q_OBJECT
        private:
            static Qml::Register::Symbol::Class<TextureMapToCylinder> Register;
            vtkSmartPointer<vtkTextureMapToCylinder> m_vtkObject;
        public:
            TextureMapToCylinder();
        };
    }
}
