#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>
#include <QList>

namespace quick {

    namespace Vtk {

        class PiecewiseFunction : public QObject {
            Q_OBJECT
            Q_PROPERTY(QList<double> x READ getXValues WRITE setXValues NOTIFY xValuesChanged);
            Q_PROPERTY(QList<double> y READ getYValues WRITE setYValues NOTIFY yValuesChanged);
        private:
            using cb_t = std::function<void()>;
            cb_t m_callback;
            QList<double> m_xValues;
            QList<double> m_yValues;
        public:
            static Qml::Register::UncreatableClass<PiecewiseFunction> Register;
            PiecewiseFunction(cb_t&&);
            auto notify() -> void;
            auto getX(int) -> double;
            auto getY(int) -> double;
            auto setXValues(QList<double>) -> void;
            auto getXValues() -> QList<double>;
            auto setYValues(QList<double>) -> void;
            auto getYValues() -> QList<double>;
            auto getLength() -> int;
        signals:
            void xValuesChanged();
            void yValuesChanged();
        };
    }
}
