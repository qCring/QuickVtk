#include "quickVtkPointSource.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<PointSource> PointSource::Register(true);

        PointSource::PointSource() : PolyDataAlgorithm(vtkSmartPointer<vtkPointSource>::New()) {
            this->m_vtkObject = vtkPointSource::SafeDownCast(Algorithm::getVtkObject());

            this->m_center = new Math::Vector3([this](){
                this->m_vtkObject->SetCenter(this->m_center->getValues().data());
                this->update();
            });
        }

        auto PointSource::setDistribution(Distribution distribution) -> void {
            this->m_vtkObject->SetDistribution(distribution);
            emit this->distributionChanged();
            this->update();
        }

        auto PointSource::getDistribution() -> Distribution {
            return (Distribution) this->m_vtkObject->GetDistribution();
        }

        auto PointSource::setNumberOfPoints(int numberOfPoints) -> void {
            this->m_vtkObject->SetNumberOfPoints(numberOfPoints);
            emit this->numberOfPointsChanged();
            this->update();
        }

        auto PointSource::getNumberOfPoints() -> int {
            return this->m_vtkObject->GetNumberOfPoints();
        }

        auto PointSource::setRadius(qreal radius) -> void {
            this->m_vtkObject->SetRadius(radius);
            emit this->radiusChanged();
            this->update();
        }

        auto PointSource::getRadius() -> qreal {
            return this->m_vtkObject->GetRadius();
        }
        
        auto PointSource::getCenter() -> Math::Vector3* {
            return this->m_center;
        }
    }
}
