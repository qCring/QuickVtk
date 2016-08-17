#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>
#include <QColor>
#include <QList>

namespace quick {

    namespace Vtk {

        class ColorTransferFunction : public QObject {
            Q_OBJECT
            Q_PROPERTY(QList<double> x READ getXValues WRITE setXValues NOTIFY xValuesChanged);
            Q_PROPERTY(QStringList colors READ getColors WRITE setColors NOTIFY colorsChanged);
        private:
            using cb_t = std::function<void()>;
            cb_t m_callback;
            QList<double> m_xValues;
            QStringList m_colors;
        public:
            static Qml::Register::UncreatableClass<ColorTransferFunction> Register;
            ColorTransferFunction(cb_t&&);
            auto notify() -> void;
            auto getX(int) -> double;
            auto getColor(int) -> QColor;
            auto setXValues(QList<double>) -> void;
            auto getXValues() -> QList<double>;
            auto setColors(QStringList) -> void;
            auto getColors() -> QStringList;
            auto getLength() -> int;
        signals:
            void xValuesChanged();
            void colorsChanged();
        };
    }
}
