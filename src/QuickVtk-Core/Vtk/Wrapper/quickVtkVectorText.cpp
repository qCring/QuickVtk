#include "quickVtkVectorText.hpp"

namespace quick::Vtk {

    Qml::Register::Class<VectorText> VectorText::Register(true);

    VectorText::VectorText() : PolyDataAlgorithm(vtkSmartPointer<vtkVectorText>::New()) {
        this->m_vtkObject = vtkVectorText::SafeDownCast(Algorithm::getVtkObject());
    }

    auto VectorText::setText(const QString& text) -> void {
        this->m_vtkObject->SetText(text.toStdString().c_str());
        this->update();
        emit this->textChanged();
    }

    auto VectorText::getText() -> QString {
        return this->m_vtkObject->GetText();
    }
}
