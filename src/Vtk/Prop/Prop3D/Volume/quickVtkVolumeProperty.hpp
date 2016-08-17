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

        class VolumeProperty : public QObject {
            Q_OBJECT
            Q_PROPERTY(bool shade READ getShade WRITE setShade NOTIFY shadeChanged);
        private:
            static Qml::Register::UncreatableClass<VolumeProperty> Register;
            quick::Vtk::Volume* m_volume = nullptr;
            vtkSmartPointer<vtkVolume> m_vtkVolume = nullptr;
        private:
            void update();
            auto setShade(bool) -> void;
            auto getShade() -> bool;
        public:
            VolumeProperty() = delete;
            VolumeProperty(Volume*);
        signals:
            void shadeChanged();
        };
    }
}
