#include "quickVtkGPUVolumeRayCastMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<GPUVolumeRayCastMapper> GPUVolumeRayCastMapper::Register(true);

        GPUVolumeRayCastMapper::GPUVolumeRayCastMapper() : VolumeMapper(vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New()) {
            this->m_vtkObject = vtkGPUVolumeRayCastMapper::SafeDownCast(this->getVtkObject());
        }

        auto GPUVolumeRayCastMapper::setAutoAdjustSampleDistances(bool autoAdjustSampleDistances) -> void {
            this->m_vtkObject->SetAutoAdjustSampleDistances(autoAdjustSampleDistances);
            emit this->autoAdjustSampleDistancesChanged();
            this->update();
        }

        auto GPUVolumeRayCastMapper::getAutoAdjustSampleDistances() -> bool {
            return this->m_vtkObject->GetAutoAdjustSampleDistances();
        }

        auto GPUVolumeRayCastMapper::setUseJittering(bool useJittering) -> void {
            this->m_vtkObject->SetUseJittering(useJittering);
            emit this->useJitteringChanged();
            this->update();
        }

        auto GPUVolumeRayCastMapper::getUseJittering() -> bool {
            return this->m_vtkObject->GetUseJittering();
        }

        auto GPUVolumeRayCastMapper::setUseDepthPass(bool useDepthPass) -> void {
            this->m_vtkObject->SetUseDepthPass(useDepthPass);
            emit this->useDepthPassChanged();
            this->update();
        }

        auto GPUVolumeRayCastMapper::getUseDepthPass() -> bool {
            return this->m_vtkObject->GetUseDepthPass();
        }

        auto GPUVolumeRayCastMapper::setSampleDistance(qreal sampleDistance) -> void {
            this->m_vtkObject->SetSampleDistance(sampleDistance);
            emit this->sampleDistanceChanged();
            this->update();
        }

        auto GPUVolumeRayCastMapper::getSampleDistance() -> qreal {
            return this->m_vtkObject->GetSampleDistance();
        }

        auto GPUVolumeRayCastMapper::setImageSampleDistance(qreal imageSampleDistance) -> void {
            this->m_vtkObject->SetImageSampleDistance(imageSampleDistance);
            emit this->imageSampleDistanceChanged();
            this->update();
        }

        auto GPUVolumeRayCastMapper::getImageSampleDistance() -> qreal {
            return this->m_vtkObject->GetImageSampleDistance();
        }

        auto GPUVolumeRayCastMapper::setMinimumImageSampleDistance(qreal minimumImageSampleDistance) -> void {
            this->m_vtkObject->SetMinimumImageSampleDistance(minimumImageSampleDistance);
            emit this->minimumImageSampleDistanceChanged();
            this->update();
        }

        auto GPUVolumeRayCastMapper::getMinimumImageSampleDistance() -> qreal {
            return this->m_vtkObject->GetMinimumImageSampleDistance();
        }

        auto GPUVolumeRayCastMapper::setMaximumImageSampleDistance(qreal maximumImageSampleDistance) -> void {
            this->m_vtkObject->SetMaximumImageSampleDistance(maximumImageSampleDistance);
            emit this->maximumImageSampleDistanceChanged();
            this->update();
        }

        auto GPUVolumeRayCastMapper::getMaximumImageSampleDistance() -> qreal {
            return this->m_vtkObject->GetMaximumImageSampleDistance();
        }

        auto GPUVolumeRayCastMapper::setFinalColorWindow(qreal finalColorWindow) -> void {
            this->m_vtkObject->SetFinalColorWindow(finalColorWindow);
            emit this->finalColorWindowChanged();
            this->update();
        }

        auto GPUVolumeRayCastMapper::getFinalColorWindow() -> qreal {
            return this->m_vtkObject->GetFinalColorWindow();
        }

        auto GPUVolumeRayCastMapper::setFinalColorLevel(qreal finalColorLevel) -> void {
            this->m_vtkObject->SetFinalColorLevel(finalColorLevel);
            emit this->finalColorLevelChanged();
            this->update();
        }

        auto GPUVolumeRayCastMapper::getFinalColorLevel() -> qreal {
            return this->m_vtkObject->GetFinalColorLevel();
        }
    }
}
