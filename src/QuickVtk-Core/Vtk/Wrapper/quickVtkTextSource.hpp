#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkTextSource.h>

#include <QColor>

namespace quick {
    namespace Vtk {

        class TextSource : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged);
            Q_PROPERTY(bool backing READ getBacking WRITE setBacking NOTIFY backingChanged);
            Q_PROPERTY(QColor foregroundColor READ getForegroundColor WRITE setForegroundColor NOTIFY foregroundColorChanged);
            Q_PROPERTY(QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged);
        private:
            static Qml::Register::Class<TextSource> Register;
            vtkSmartPointer<vtkTextSource> m_vtkObject = nullptr;
            QColor m_foregroundColor;
            QColor m_backgroundColor;
        public:
            TextSource();
            auto setText(const QString&) -> void;
            auto getText() -> QString;
            auto setBacking(bool) -> void;
            auto getBacking() -> bool;
            auto setForegroundColor(const QColor&) -> void;
            auto getForegroundColor() -> QColor;
            auto setBackgroundColor(const QColor&) -> void;
            auto getBackgroundColor() -> QColor;
        signals:
            void textChanged();
            void backingChanged();
            void foregroundColorChanged();
            void backgroundColorChanged();
        };
    }
}
