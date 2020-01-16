#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"
#include "quickMathVector3.hpp"

#include <vtkTubeFilter.h>

namespace quick {

    namespace Vtk {

        class TubeFilter : public PolyDataAlgorithm {
            Q_OBJECT
        public:
            enum VaryRadius {
                VaryRadiusOff = VTK_VARY_RADIUS_OFF,
                VaryRadiusByScalar = VTK_VARY_RADIUS_BY_SCALAR,
                VaryRadiusByVector = VTK_VARY_RADIUS_BY_VECTOR,
                VaryRadiusByAbsoluteSclar = VTK_VARY_RADIUS_BY_ABSOLUTE_SCALAR
            };
            enum TCoords {
                TCoordsOff = VTK_TCOORDS_OFF,
                TCoordsFromNormalizedLength = VTK_TCOORDS_FROM_NORMALIZED_LENGTH,
                TCoordsFromLength = VTK_TCOORDS_FROM_LENGTH,
                TCoordsFromScalars = VTK_TCOORDS_FROM_SCALARS
            };
        private:
            Q_ENUM(VaryRadius);
            Q_ENUM(TCoords);
            Q_PROPERTY(VaryRadius varyRadius READ getVaryRadius WRITE setVaryRadius NOTIFY varyRadiusChanged);
            Q_PROPERTY(TCoords generateTCoords READ getGenerateTCoords WRITE setGenerateTCoords NOTIFY generateTCoordsChanged);
            Q_PROPERTY(quick::Math::Vector3* defaultNormal READ getDefaultNormal CONSTANT);
            Q_PROPERTY(qreal radius READ getRadius WRITE setRadius NOTIFY radiusChanged);
            Q_PROPERTY(qreal radiusFactor READ getRadiusFactor WRITE setRadiusFactor NOTIFY radiusFactorChanged);
            Q_PROPERTY(qreal textureLength READ getTextureLength WRITE setTextureLength NOTIFY textureLengthChanged);
            Q_PROPERTY(bool useDefaultNormal READ getUseDefaultNormal WRITE setUseDefaultNormal NOTIFY useDefaultNormalChanged);
            Q_PROPERTY(bool sidesShareVertices READ getSidesShareVertices WRITE setSidesShareVertices NOTIFY sidesShareVerticesChanged);
            Q_PROPERTY(bool capping READ getCapping WRITE setCapping NOTIFY cappingChanged);
            Q_PROPERTY(int numberOfSides READ getNumberOfSides WRITE setNumberOfSides NOTIFY numberOfSidesChanged);
            Q_PROPERTY(int onRatio READ getOnRatio WRITE setOnRatio NOTIFY onRatioChanged);
            Q_PROPERTY(int offset READ getOffset WRITE setOffset NOTIFY offsetChanged);
        private:
            static Qml::Register::Class<TubeFilter> Register;
            vtkSmartPointer<vtkTubeFilter> m_vtkObject = nullptr;
            Math::Vector3* m_defaultNormal = nullptr;
        public:
            TubeFilter();
            auto setVaryRadius(VaryRadius) -> void;
            auto getVaryRadius() -> VaryRadius;
            auto setGenerateTCoords(TCoords) -> void;
            auto getGenerateTCoords() -> TCoords;
            auto getDefaultNormal() -> Math::Vector3*;
            auto setRadius(qreal) -> void;
            auto getRadius() -> qreal;
            auto setRadiusFactor(qreal) -> void;
            auto getRadiusFactor() -> qreal;
            auto setTextureLength(qreal) -> void;
            auto getTextureLength() -> qreal;
            auto setUseDefaultNormal(bool) -> void;
            auto getUseDefaultNormal() -> bool;
            auto setSidesShareVertices(bool) -> void;
            auto getSidesShareVertices() -> bool;
            auto setCapping(bool) -> void;
            auto getCapping() -> bool;
            auto setNumberOfSides(int) -> void;
            auto getNumberOfSides() -> int;
            auto setOnRatio(int) -> void;
            auto getOnRatio() -> int;
            auto setOffset(int) -> void;
            auto getOffset() -> int;
        signals:
            void varyRadiusChanged();
            void radiusChanged();
            void numberOfSidesChanged();
            void radiusFactorChanged();
            void useDefaultNormalChanged();
            void sidesShareVerticesChanged();
            void cappingChanged();
            void onRatioChanged();
            void offsetChanged();
            void generateTCoordsChanged();
            void textureLengthChanged();
        };
    }
}
