#include "quickVtkStructuredPointsReader.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<StructuredPointsReader> StructuredPointsReader::Register;

        StructuredPointsReader::StructuredPointsReader() : DataReader(this) {
            this->m_vtkStructuredPointsReader = vtkSmartPointer<vtkStructuredPointsReader>::New();
            DataReader::setVtkDataReader(m_vtkStructuredPointsReader);
        }

        StructuredPointsReader::~StructuredPointsReader() {
            this->m_vtkStructuredPointsReader = nullptr;
        }
    }
}
