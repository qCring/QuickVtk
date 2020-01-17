#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkVectorText.h>

namespace quick {
    namespace Vtk {

        class VectorText : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged);
        private:
            static Qml::Register::Class<VectorText> Register;
            vtkSmartPointer<vtkVectorText> m_vtkObject = nullptr;
        public:
            VectorText();
            auto setText(const QString&) -> void;
            auto getText() -> QString;
        signals:
            void textChanged();
        };
    }
}
