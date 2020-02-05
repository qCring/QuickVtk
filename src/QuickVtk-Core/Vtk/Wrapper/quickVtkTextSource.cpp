#include "quickVtkTextSource.hpp"

namespace quick::Vtk {

    Qml::Register::Class<TextSource> TextSource::Register(true);

    TextSource::TextSource() : PolyDataAlgorithm(vtkSmartPointer<vtkTextSource>::New()) {
        this->m_vtkObject = vtkTextSource::SafeDownCast(Algorithm::getVtkObject());
    }

    auto TextSource::setText(const QString& text) -> void {
        this->m_vtkObject->SetText(text.toStdString().c_str());
        this->update();
        emit this->textChanged();
    }

    auto TextSource::getText() -> QString {
        return this->m_vtkObject->GetText();
    }

    auto TextSource::setBacking(bool backing) -> void {
        this->m_vtkObject->SetBacking(backing);
        this->update();
        emit this->backingChanged();
    }

    auto TextSource::getBacking() -> bool {
        return this->m_vtkObject->GetBacking();
    }

    auto TextSource::setForegroundColor(const QColor& foregroundColor) -> void {
        this->m_foregroundColor = foregroundColor;
        this->m_vtkObject->SetForegroundColor(foregroundColor.redF(), foregroundColor.greenF(), foregroundColor.blueF());
        this->update();
        emit this->foregroundColorChanged();
    }

    auto TextSource::getForegroundColor() -> QColor {
        return this->m_foregroundColor;
    }

    auto TextSource::setBackgroundColor(const QColor& backgroundColor) -> void {
            this->m_backgroundColor = backgroundColor;
            this->m_vtkObject->SetBackgroundColor(backgroundColor.redF(), backgroundColor.greenF(), backgroundColor.blueF());
            this->update();
            emit this->backgroundColorChanged();
        }

    auto TextSource::getBackgroundColor() -> QColor {
        return this->m_backgroundColor;
    }

}
