#pragma once

#include "quickVtkDataSetAlgorithm.hpp"

#include <vtkTextureMapToCylinder.h>

namespace quick::Vtk {

    class TextureMapToCylinder : public DataSetAlgorithm {
        Q_OBJECT
    private:
        static Qml::Register::Class<TextureMapToCylinder> Register;
        vtkSmartPointer<vtkTextureMapToCylinder> m_vtkObject = nullptr;
    public:
        TextureMapToCylinder();
    };
}
