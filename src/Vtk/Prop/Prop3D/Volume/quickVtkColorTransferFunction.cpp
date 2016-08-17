#include "quickVtkColorTransferFunction.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::UncreatableClass<ColorTransferFunction> ColorTransferFunction::Register;

        ColorTransferFunction::ColorTransferFunction(cb_t&& callback) : m_callback(callback) {
        }

        auto ColorTransferFunction::getX(int i) -> double {
            return i < this->m_xValues.length() && i >= 0 ? this->m_xValues.at(i) : 0;
        }

        auto ColorTransferFunction::getColor(int i) -> QColor {
            return i < this->m_colors.length() && i >= 0 ? QColor(this->m_colors.at(i)) : QColor("#ff00ff");
        }

        auto ColorTransferFunction::notify() -> void {
            this->m_callback.operator()();
        }

        auto ColorTransferFunction::setXValues(QList<double> xValues) -> void {
            this->m_xValues = xValues;
            emit this->xValuesChanged();
            this->notify();
        }

        auto ColorTransferFunction::getXValues() -> QList<double> {
            return this->m_xValues;
        }

        auto ColorTransferFunction::setColors(QStringList colors) -> void {
            this->m_colors = colors;
            emit this->colorsChanged();
            this->notify();
        }

        auto ColorTransferFunction::getColors() -> QStringList {
            return this->m_colors;
        }

        auto ColorTransferFunction::getLength() -> int {
            return std::min(this->m_xValues.length(), this->m_colors.length());
        }
    }
}
