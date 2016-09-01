#pragma once

#include "quickVtkVolumeMapper.hpp"

#include <vtkGPUVolumeRayCastMapper.h>

namespace quick {

    namespace Vtk {

        class GPUVolumeRayCastMapper : public VolumeMapper {
            Q_OBJECT
            Q_PROPERTY(bool autoAdjustSampleDistances READ getAutoAdjustSampleDistances WRITE setAutoAdjustSampleDistances NOTIFY autoAdjustSampleDistancesChanged);
            Q_PROPERTY(bool useJittering READ getUseJittering WRITE setUseJittering NOTIFY useJitteringChanged);
            Q_PROPERTY(bool useDepthPass READ getUseDepthPass WRITE setUseDepthPass NOTIFY useDepthPassChanged);
            Q_PROPERTY(float sampleDistance READ getSampleDistance WRITE setSampleDistance NOTIFY sampleDistanceChanged);
            Q_PROPERTY(float imageSampleDistance READ getImageSampleDistance WRITE setImageSampleDistance NOTIFY imageSampleDistanceChanged);
            Q_PROPERTY(float minimumImageSampleDistance READ getMinimumImageSampleDistance WRITE setMinimumImageSampleDistance NOTIFY minimumImageSampleDistanceChanged);
            Q_PROPERTY(float maximumImageSampleDistance READ getMaximumImageSampleDistance WRITE setMaximumImageSampleDistance NOTIFY maximumImageSampleDistanceChanged);
            Q_PROPERTY(float finalColorWindow READ getFinalColorWindow WRITE setFinalColorWindow NOTIFY finalColorWindowChanged);
            Q_PROPERTY(float finalColorLevel READ getFinalColorLevel WRITE setFinalColorLevel NOTIFY finalColorLevelChanged);
        private:
            static Qml::Register::Class<GPUVolumeRayCastMapper> Register;
            vtkSmartPointer<vtkGPUVolumeRayCastMapper> m_vtkObject = nullptr;
        public:
            GPUVolumeRayCastMapper();
            auto setAutoAdjustSampleDistances(bool) -> void;
            auto getAutoAdjustSampleDistances() -> bool;
            auto setUseJittering(bool) -> void;
            auto getUseJittering() -> bool;
            auto setUseDepthPass(bool) -> void;
            auto getUseDepthPass() -> bool;
            auto setSampleDistance(float) -> void;
            auto getSampleDistance() -> float;
            auto setImageSampleDistance(float) -> void;
            auto getImageSampleDistance() -> float;
            auto setMinimumImageSampleDistance(float) -> void;
            auto getMinimumImageSampleDistance() -> float;
            auto setMaximumImageSampleDistance(float) -> void;
            auto getMaximumImageSampleDistance() -> float;
            auto setFinalColorWindow(float) -> void;
            auto getFinalColorWindow() -> float;
            auto setFinalColorLevel(float) -> void;
            auto getFinalColorLevel() -> float;
        signals:
            void minimumImageSampleDistanceChanged();
            void maximumImageSampleDistanceChanged();
            void autoAdjustSampleDistancesChanged();
            void imageSampleDistanceChanged();
            void finalColorWindowChanged();
            void finalColorLevelChanged();
            void sampleDistanceChanged();
            void useJitteringChanged();
            void useDepthPassChanged();
        };
    }
}