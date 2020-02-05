#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"
#include "quickMathVector3.hpp"

#include <vtkRibbonFilter.h>

namespace quick::Vtk {

    class RibbonFilter : public PolyDataAlgorithm {
        Q_OBJECT
    public:
        enum TCoords {
            TCoordsOff = VTK_TCOORDS_OFF,
            TCoordsFromNormalizedLength = VTK_TCOORDS_FROM_NORMALIZED_LENGTH,
            TCoordsFromLength = VTK_TCOORDS_FROM_LENGTH,
            TCoordsFromScalars = VTK_TCOORDS_FROM_SCALARS
        };
    private:
        Q_ENUM(TCoords);
        Q_PROPERTY(TCoords generateTCoords READ getGenerateTCoords WRITE setGenerateTCoords NOTIFY generateTCoordsChanged);
        Q_PROPERTY(quick::Math::Vector3* defaultNormal READ getDefaultNormal CONSTANT);
        Q_PROPERTY(qreal width READ getWidth WRITE setWidth NOTIFY widthChanged);
        Q_PROPERTY(qreal widthFactor READ getWidthFactor WRITE setWidthFactor NOTIFY widthFactorChanged);
        Q_PROPERTY(qreal textureLength READ getTextureLength WRITE setTextureLength NOTIFY textureLengthChanged);
        Q_PROPERTY(bool useDefaultNormal READ getUseDefaultNormal WRITE setUseDefaultNormal NOTIFY useDefaultNormalChanged);
        Q_PROPERTY(bool varyWidth READ getVaryWidth WRITE setVaryWidth NOTIFY varyWidthChanged);
    private:
        static Qml::Register::Class<RibbonFilter> Register;
        vtkSmartPointer<vtkRibbonFilter> m_vtkObject = nullptr;
        Math::Vector3* m_defaultNormal = nullptr;
    public:
        RibbonFilter();
        auto setGenerateTCoords(TCoords) -> void;
        auto getGenerateTCoords() -> TCoords;
        auto getDefaultNormal() -> Math::Vector3*;
        auto setWidth(qreal) -> void;
        auto getWidth() -> qreal;
        auto setWidthFactor(qreal) -> void;
        auto getWidthFactor() -> qreal;
        auto setTextureLength(qreal) -> void;
        auto getTextureLength() -> qreal;
        auto setVaryWidth(bool) -> void;
        auto getVaryWidth() -> bool;
        auto setUseDefaultNormal(bool) -> void;
        auto getUseDefaultNormal() -> bool;
    signals:
        void varyWidthChanged();
        void widthChanged();
        void widthFactorChanged();
        void useDefaultNormalChanged();
        void generateTCoordsChanged();
        void textureLengthChanged();
    };
}
