#pragma once

#include "quickQmlRegister.hpp"

#include <QColor>
#include <QObject>

#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkActor.h>

namespace quick {

    namespace Vtk {

        class Actor;

        class Property : public QObject {
            Q_OBJECT
        public:
            enum Interpolation {
                Flat = VTK_FLAT,
                Gouraud = VTK_GOURAUD,
                Phong = VTK_PHONG
            };
            enum Representation {
                Points = VTK_POINTS,
                Wireframe = VTK_WIREFRAME,
                Surface = VTK_SURFACE
            };
        private:
            Q_ENUM(Interpolation);
            Q_ENUM(Representation);
            Q_PROPERTY(Interpolation interpolation READ getInterpolation WRITE setInterpolation NOTIFY interpolationChanged);
            Q_PROPERTY(Representation representation READ getRepresentation WRITE setRepresentation NOTIFY representationChanged);
            Q_PROPERTY(float opacity READ getOpacity WRITE setOpacity NOTIFY opacityChanged);
            Q_PROPERTY(float lineWidth READ getLineWidth WRITE setLineWidth NOTIFY lineWidthChanged);
            Q_PROPERTY(float pointSize READ getPointSize WRITE setPointSize NOTIFY pointSizeChanged);
            Q_PROPERTY(bool shading READ getShading WRITE setShading NOTIFY shadingChanged);
            Q_PROPERTY(bool lighting READ getLighting WRITE setLighting NOTIFY lightingChanged);
            Q_PROPERTY(bool edgeVisibility READ getEdgeVisibility WRITE setEdgeVisibility NOTIFY edgeVisibilityChanged);
            Q_PROPERTY(bool backfaceCulling READ getBackfaceCulling WRITE setBackfaceCulling NOTIFY backfaceCullingChanged);
            Q_PROPERTY(bool frontfaceCulling READ getFrontfaceCulling WRITE setFrontfaceCulling NOTIFY frontfaceCullingChanged);
            Q_PROPERTY(QColor specularColor READ getSpecularColor WRITE setSpecularColor NOTIFY specularColorChanged);
            Q_PROPERTY(QColor diffuseColor READ getDiffuseColor WRITE setDiffuseColor NOTIFY diffuseColorChanged);
            Q_PROPERTY(QColor ambientColor READ getAmbientColor WRITE setAmbientColor NOTIFY ambientColorChanged);
            Q_PROPERTY(QColor edgeColor READ getEdgeColor WRITE setEdgeColor NOTIFY edgeColorChanged);
            Q_PROPERTY(float ambient READ getAmbient WRITE setAmbient NOTIFY ambientChanged);
            Q_PROPERTY(float diffuse READ getDiffuse WRITE setDiffuse NOTIFY diffuseChanged);
            Q_PROPERTY(float specular READ getSpecular WRITE setSpecular NOTIFY specularChanged);
            Q_PROPERTY(float specularPower READ getSpecularPower WRITE setSpecularPower NOTIFY specularPowerChanged);
        private:
            static Qml::Register::Class<Property> Register;
            quick::Vtk::Actor* m_actor = nullptr;
            vtkSmartPointer<vtkActor> m_vtkActor = nullptr;
            QColor m_specularColor;
            QColor m_diffuseColor;
            QColor m_ambientColor;
            QColor m_edgeColor;
        private:
            void update();
        public:
            Property();
            Property(Actor*);
            auto setActor(Actor*) -> void;
            auto setInterpolation(Interpolation) -> void;
            auto setRepresentation(Representation) -> void;
            auto setSpecularColor(QColor) -> void;
            auto setDiffuseColor(QColor) -> void;
            auto setAmbientColor(QColor) -> void;
            auto setEdgeColor(QColor) -> void;
            auto setFrontfaceCulling(bool) -> void;
            auto setBackfaceCulling(bool) -> void;
            auto setEdgeVisibility(bool) -> void;
            auto setLighting(bool) -> void;
            auto setShading(bool) -> void;
            auto setOpacity(float) -> void;
            auto setPointSize(float) -> void;
            auto setLineWidth(float) -> void;
            auto setAmbient(float) -> void;
            auto setDiffuse(float) -> void;
            auto setSpecular(float) -> void;
            auto setSpecularPower(float) -> void;
            auto getSpecularColor() -> QColor;
            auto getDiffuseColor() -> QColor;
            auto getAmbientColor() -> QColor;
            auto getEdgeColor() -> QColor;
            auto getFrontfaceCulling() -> bool;
            auto getBackfaceCulling() -> bool;
            auto getEdgeVisibility() -> bool;
            auto getShading() -> bool;
            auto getLighting() -> bool;
            auto getOpacity() -> float;
            auto getLineWidth() -> float;
            auto getPointSize() -> float;
            auto getInterpolation() -> Interpolation;
            auto getRepresentation() -> Representation;
            auto getAmbient() -> float;
            auto getDiffuse() -> float;
            auto getSpecular() -> float;
            auto getSpecularPower() -> float;
            ~Property();
        signals:
            void opacityChanged();
            void interpolationChanged();
            void representationChanged();
            void lineWidthChanged();
            void pointSizeChanged();
            void shadingChanged();
            void colorChanged();
            void lightingChanged();
            void ambientChanged();
            void diffuseChanged();
            void specularChanged();
            void specularPowerChanged();
            void specularColorChanged();
            void diffuseColorChanged();
            void ambientColorChanged();
            void edgeColorChanged();
            void edgeVisibilityChanged();
            void frontfaceCullingChanged();
            void backfaceCullingChanged();
        };
    }
}
