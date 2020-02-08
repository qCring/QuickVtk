#pragma once

#include "quickVtkVolumeMapper.hpp"

#include <vtkGPUVolumeRayCastMapper.h>

namespace quick::Vtk {

    class GPUVolumeRayCastMapper : public VolumeMapper {
        Q_OBJECT
        Q_PROPERTY(bool autoAdjustSampleDistances READ getAutoAdjustSampleDistances WRITE setAutoAdjustSampleDistances NOTIFY autoAdjustSampleDistancesChanged);
        Q_PROPERTY(bool useJittering READ getUseJittering WRITE setUseJittering NOTIFY useJitteringChanged);
        Q_PROPERTY(bool useDepthPass READ getUseDepthPass WRITE setUseDepthPass NOTIFY useDepthPassChanged);
        Q_PROPERTY(qreal sampleDistance READ getSampleDistance WRITE setSampleDistance NOTIFY sampleDistanceChanged);
        Q_PROPERTY(qreal imageSampleDistance READ getImageSampleDistance WRITE setImageSampleDistance NOTIFY imageSampleDistanceChanged);
        Q_PROPERTY(qreal minimumImageSampleDistance READ getMinimumImageSampleDistance WRITE setMinimumImageSampleDistance NOTIFY minimumImageSampleDistanceChanged);
        Q_PROPERTY(qreal maximumImageSampleDistance READ getMaximumImageSampleDistance WRITE setMaximumImageSampleDistance NOTIFY maximumImageSampleDistanceChanged);
        Q_PROPERTY(qreal finalColorWindow READ getFinalColorWindow WRITE setFinalColorWindow NOTIFY finalColorWindowChanged);
        Q_PROPERTY(qreal finalColorLevel READ getFinalColorLevel WRITE setFinalColorLevel NOTIFY finalColorLevelChanged);
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
        auto setSampleDistance(qreal) -> void;
        auto getSampleDistance() -> qreal;
        auto setImageSampleDistance(qreal) -> void;
        auto getImageSampleDistance() -> qreal;
        auto setMinimumImageSampleDistance(qreal) -> void;
        auto getMinimumImageSampleDistance() -> qreal;
        auto setMaximumImageSampleDistance(qreal) -> void;
        auto getMaximumImageSampleDistance() -> qreal;
        auto setFinalColorWindow(qreal) -> void;
        auto getFinalColorWindow() -> qreal;
        auto setFinalColorLevel(qreal) -> void;
        auto getFinalColorLevel() -> qreal;
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
