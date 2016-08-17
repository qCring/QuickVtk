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

        class VolumeProperty : public QObject {
            Q_OBJECT
            Q_PROPERTY(bool shade READ getShade WRITE setShade NOTIFY shadeChanged);
            Q_PROPERTY(quick::Vtk::PiecewiseFunction* scalarOpacity READ getScalarOpacity CONSTANT);
        private:
            static Qml::Register::UncreatableClass<VolumeProperty> Register;
            Volume* m_volume = nullptr;
            PiecewiseFunction* m_scalarOpacity = nullptr;
            vtkSmartPointer<vtkVolume> m_vtkVolume = nullptr;
        private:
            void update();
        public:
            VolumeProperty() = delete;
            VolumeProperty(Volume*);
            auto setShade(bool) -> void;
            auto getShade() -> bool;
            auto getScalarOpacity() -> PiecewiseFunction*;
        signals:
            void shadeChanged();
        };
    }
}
