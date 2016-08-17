#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>
#include <QColor>
#include <QList>

#include <vtkSmartPointer.h>
#include <vtkColorTransferFunction.h>

namespace quick {

    namespace Vtk {

        class ColorTransferFunction : public QObject {
            Q_OBJECT
            Q_PROPERTY(int size READ getSize NOTIFY sizeChanged);
        private:
            using cb_t = std::function<void()>;
            using vtk_t = vtkSmartPointer<vtkColorTransferFunction>;
            vtk_t m_vtkObject;
            cb_t m_callback;
            QList<double> m_values;
            QList<QColor> m_colors;
        public:
            static Qml::Register::UncreatableClass<ColorTransferFunction> Register;
            ColorTransferFunction(vtk_t, cb_t&&);
            auto notify() -> void;
            auto getSize() -> int;
            auto getValues() -> QList<double>;
            auto getColors() -> QList<QColor>;
        public slots:
            void clear();
            void add(double, QColor);
            double getValue(int);
            QColor getColor(int);
        signals:
            void sizeChanged();
        };
    }
}
