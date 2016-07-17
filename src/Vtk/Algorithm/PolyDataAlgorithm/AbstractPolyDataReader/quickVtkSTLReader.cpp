#include "quickVtkSTLReader.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<STLReader> STLReader::Register;

        STLReader::STLReader() : AbstractPolyDataReader(this) {
            this->m_vtkSTLReader = vtkSmartPointer<vtkSTLReader>::New();
            AbstractPolyDataReader::setVtkAbstractPolyDataReader(m_vtkSTLReader);
        }

        STLReader::~STLReader() {
        }
    }
}
