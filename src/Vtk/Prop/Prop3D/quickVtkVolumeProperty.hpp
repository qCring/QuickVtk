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
            static Qml::Register::Class<VolumeProperty> Register;
            quick::Vtk::Volume* m_volume = nullptr;
            vtkSmartPointer<vtkVolume> m_vtkVolume = nullptr;
        private:
            void update();
            auto setShade(bool) -> void;
            auto getShade() -> bool;
        public:
            VolumeProperty();
            VolumeProperty(Volume*);
            auto setVolume(Volume*) -> void;
            ~VolumeProperty();
        signals:
            void shadeChanged();
        };
    }
}
