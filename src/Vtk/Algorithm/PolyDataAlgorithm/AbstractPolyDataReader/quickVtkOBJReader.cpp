#include "quickVtkOBJReader.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<OBJReader> OBJReader::Register;

        OBJReader::OBJReader() : AbstractPolyDataReader(this) {
            this->m_vtkOBJReader = vtkSmartPointer<vtkOBJReader>::New();
            AbstractPolyDataReader::setVtkAbstractPolyDataReader(m_vtkOBJReader);
        }

        auto OBJReader::getSuffix() -> QString {
            return ".obj";
        }
    }
}
