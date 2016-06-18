#include "quickVtkDiskSource.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<DiskSource> DiskSource::Register;

        DiskSource::DiskSource() : PolyDataAlgorithm(this) {
            this->m_vtkDiskSource = vtkSmartPointer<vtkDiskSource>::New();
            this->m_vtkDiskSource->Update();

            PolyDataAlgorithm::setVtkPolyDataAlgorithm(m_vtkDiskSource);
        }

        auto DiskSource::setInnerRadius(float radius) -> void {
            this->m_vtkDiskSource->SetInnerRadius(radius);
            emit this->innerRadiusChanged();
            this->update();
        }

        auto DiskSource::setOuterRadius(float radius) -> void {
            this->m_vtkDiskSource->SetOuterRadius(radius);
            emit this->outerRadiusChanged();
            this->update();
        }

        auto DiskSource::setRadialResolution(int value) -> void {
            this->m_vtkDiskSource->SetRadialResolution(value);
            emit this->radialResolutionChanged();
            this->update();
        }

        auto DiskSource::setCircumferentialResolution(int value) -> void {
            this->m_vtkDiskSource->SetCircumferentialResolution(value);
            emit this->circumferentialResolutionChanged();
            this->update();
        }

        auto DiskSource::getInnerRadius() -> float {
            return this->m_vtkDiskSource->GetInnerRadius();
        }

        auto DiskSource::getOuterRadius() -> float {
            return this->m_vtkDiskSource->GetOuterRadius();
        }

        auto DiskSource::getRadialResolution() -> int {
            return this->m_vtkDiskSource->GetRadialResolution();
        }

        auto DiskSource::getCircumferentialResolution() -> int {
            return this->m_vtkDiskSource->GetCircumferentialResolution();
        }

        DiskSource::~DiskSource() {
            this->m_vtkDiskSource = 0;
        }
    }
}