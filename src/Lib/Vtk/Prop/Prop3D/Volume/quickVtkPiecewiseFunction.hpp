#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>
#include <QList>

#include <vtkSmartPointer.h>
#include <vtkPiecewiseFunction.h>

namespace quick {

    namespace Vtk {

        class PiecewiseFunction : public QObject {
            Q_OBJECT
            Q_PROPERTY(int size READ getSize NOTIFY sizeChanged);
        private:
            using cb_t = std::function<void()>;
            using vtk_t = vtkSmartPointer<vtkPiecewiseFunction>;
            vtk_t m_vtkObject;
            cb_t m_callback;
            QList<double> m_xValues;
            QList<double> m_yValues;
        public:
            static Qml::Register::Symbol::UncreatableClass<PiecewiseFunction> Register;
            PiecewiseFunction(vtk_t, cb_t&&);
            auto update() -> void;
            auto getSize() -> int;
            auto setClamping(bool) -> void;
            auto getClamping() -> bool;
        public slots:
            void clear();
            void add(double, double);
            double getX(int);
            double getY(int);
        signals:
            void sizeChanged();
            void clampingChanged();
        };
    }
}
