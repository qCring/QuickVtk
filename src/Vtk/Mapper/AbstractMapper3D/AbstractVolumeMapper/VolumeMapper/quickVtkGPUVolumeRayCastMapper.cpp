#include "quickVtkGPUVolumeRayCastMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::Class<GPUVolumeRayCastMapper> GPUVolumeRayCastMapper::Register;

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

        auto GPUVolumeRayCastMapper::setSampleDistance(float sampleDistance) -> void {
            this->m_vtkObject->SetSampleDistance(sampleDistance);
            emit this->sampleDistanceChanged();
            this->update();
        }

        auto GPUVolumeRayCastMapper::getSampleDistance() -> float {
            return this->m_vtkObject->GetSampleDistance();
        }

        auto GPUVolumeRayCastMapper::setImageSampleDistance(float imageSampleDistance) -> void {
            this->m_vtkObject->SetImageSampleDistance(imageSampleDistance);
            emit this->imageSampleDistanceChanged();
            this->update();
        }

        auto GPUVolumeRayCastMapper::getImageSampleDistance() -> float {
            return this->m_vtkObject->GetImageSampleDistance();
        }

        auto GPUVolumeRayCastMapper::setMinimumImageSampleDistance(float minimumImageSampleDistance) -> void {
            this->m_vtkObject->SetMinimumImageSampleDistance(minimumImageSampleDistance);
            emit this->minimumImageSampleDistanceChanged();
            this->update();
        }

        auto GPUVolumeRayCastMapper::getMinimumImageSampleDistance() -> float {
            return this->m_vtkObject->GetMinimumImageSampleDistance();
        }

        auto GPUVolumeRayCastMapper::setMaximumImageSampleDistance(float maximumImageSampleDistance) -> void {
            this->m_vtkObject->SetMaximumImageSampleDistance(maximumImageSampleDistance);
            emit this->maximumImageSampleDistanceChanged();
            this->update();
        }

        auto GPUVolumeRayCastMapper::getMaximumImageSampleDistance() -> float {
            return this->m_vtkObject->GetMaximumImageSampleDistance();
        }

        auto GPUVolumeRayCastMapper::setFinalColorWindow(float finalColorWindow) -> void {
            this->m_vtkObject->SetFinalColorWindow(finalColorWindow);
            emit this->finalColorWindowChanged();
            this->update();
        }

        auto GPUVolumeRayCastMapper::getFinalColorWindow() -> float {
            return this->m_vtkObject->GetFinalColorWindow();
        }

        auto GPUVolumeRayCastMapper::setFinalColorLevel(float finalColorLevel) -> void {
            this->m_vtkObject->SetFinalColorLevel(finalColorLevel);
            emit this->finalColorLevelChanged();
            this->update();
        }

        auto GPUVolumeRayCastMapper::getFinalColorLevel() -> float {
            return this->m_vtkObject->GetFinalColorLevel();
        }
    }
}
