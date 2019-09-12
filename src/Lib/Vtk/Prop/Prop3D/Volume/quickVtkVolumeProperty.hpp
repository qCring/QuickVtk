#pragma once

#include "quickQmlRegister.hpp"

#include <QColor>
#include <QObject>

#include <vtkSmartPointer.h>
#include <vtkVolumeProperty.h>
#include <vtkVolume.h>

namespace quick {

    namespace Vtk {

        class Volume;
        class PiecewiseFunction;
        class ColorTransferFunction;

        class VolumeProperty : public QObject {
            Q_OBJECT
            Q_PROPERTY(bool shade READ getShade WRITE setShade NOTIFY shadeChanged);
            Q_PROPERTY(quick::Vtk::PiecewiseFunction* scalarOpacityFunction READ getScalarOpacityFunction CONSTANT);
            Q_PROPERTY(quick::Vtk::PiecewiseFunction* gradientOpacityFunction READ getGradientOpacityFunction CONSTANT);
            Q_PROPERTY(quick::Vtk::ColorTransferFunction* transferFunction READ getTransferFunction CONSTANT);
            Q_PROPERTY(qreal ambient READ getAmbient WRITE setAmbient NOTIFY ambientChanged);
            Q_PROPERTY(qreal diffuse READ getDiffuse WRITE setDiffuse NOTIFY diffuseChanged);
            Q_PROPERTY(qreal specular READ getSpecular WRITE setSpecular NOTIFY specularChanged);
            Q_PROPERTY(qreal specularPower READ getSpecularPower WRITE setSpecularPower NOTIFY specularPowerChanged);
        private:
            static Qml::Register::Symbol::UncreatableClass<VolumeProperty> Register;
            Volume* m_volume = nullptr;
            PiecewiseFunction* m_gradientOpacityFunction = nullptr;
            PiecewiseFunction* m_scalarOpacityFunction = nullptr;
            ColorTransferFunction* m_transferFunction = nullptr;
            vtkSmartPointer<vtkVolume> m_vtkVolume = nullptr;
        private:
            void update();
        public:
            VolumeProperty() = delete;
            VolumeProperty(Volume*);
            auto setShade(bool) -> void;
            auto getShade() -> bool;
            auto setAmbient(qreal) -> void;
            auto getAmbient() -> qreal;
            auto setDiffuse(qreal) -> void;
            auto getDiffuse() -> qreal;
            auto setSpecular(qreal) -> void;
            auto getSpecular() -> qreal;
            auto setSpecularPower(qreal) -> void;
            auto getSpecularPower() -> qreal;
            auto getGradientOpacityFunction() -> PiecewiseFunction*;
            auto getScalarOpacityFunction() -> PiecewiseFunction*;
            auto getTransferFunction() -> ColorTransferFunction*;
        signals:
            void shadeChanged();
            void ambientChanged();
            void diffuseChanged();
            void specularChanged();
            void specularPowerChanged();
        };
    }
}
