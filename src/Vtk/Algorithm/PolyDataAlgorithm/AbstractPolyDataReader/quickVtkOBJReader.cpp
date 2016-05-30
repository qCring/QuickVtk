#include "quickVtkOBJReader.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::VtkClass<OBJReader> OBJReader::Register;

        OBJReader::OBJReader() : AbstractPolyDataReader(this) {
            this->m_vtkOBJReader = vtkSmartPointer<vtkOBJReader>::New();
            AbstractPolyDataReader::setVtkAbstractPolyDataReader(m_vtkOBJReader);
        }

        OBJReader::~OBJReader() {
        }
    }
}
