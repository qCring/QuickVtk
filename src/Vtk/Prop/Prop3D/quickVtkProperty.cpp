#include "quickVtkProperty.hpp"
#include "quickVtkActor.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<Property> Property::Register;

        Property::Property() {

        }

        Property::Property(Actor* actor) : m_actor(actor) {
            this->m_vtkActor = 0;
            this->m_vtkActor = this->m_actor->getVtkActor();
        }

        auto Property::setActor(Actor* actor) -> void {
            this->m_vtkActor = actor->getVtkActor();
        }

        auto Property::update() -> void {
            this->m_actor->update();
        }

        auto Property::setColor(QColor color) -> void {
            this->m_color = color;

            this->m_vtkActor->GetProperty()->SetColor(color.redF(), color.greenF(), color.blueF());
            this->update();

            emit this->colorChanged();
        }

        auto Property::setDiffuseColor(QColor color) -> void {
            this->m_diffuseColor = color;

            this->m_vtkActor->GetProperty()->SetDiffuseColor(color.redF(), color.greenF(), color.blueF());
            this->update();

            emit this->diffuseColorChanged();
        }

        auto Property::setSpecularColor(QColor color) -> void {
            this->m_specularColor = color;

            this->m_vtkActor->GetProperty()->SetSpecularColor(color.redF(), color.greenF(), color.blueF());
            this->update();

            emit this->specularColorChanged();
        }

        auto Property::setAmbientColor(QColor color) -> void {
            this->m_ambientColor = color;

            this->m_vtkActor->GetProperty()->SetAmbientColor(color.redF(), color.greenF(), color.blueF());
            this->update();

            emit this->ambientColorChanged();
        }

        auto Property::setEdgeColor(QColor color) -> void {
            this->m_edgeColor = color;

            this->m_vtkActor->GetProperty()->SetEdgeColor(color.redF(), color.greenF(), color.blueF());
            this->update();

            emit this->edgeColorChanged();
        }

        auto Property::setFrontfaceCulling(bool enabled) -> void {
            this->m_vtkActor->GetProperty()->SetFrontfaceCulling(enabled);
            emit this->frontfaceCullingChanged();
            this->update();
        }

        auto Property::setBackfaceCulling(bool enabled) -> void {
            this->m_vtkActor->GetProperty()->SetBackfaceCulling(enabled);
            emit this->backfaceCullingChanged();
            this->update();
        }

        auto Property::setEdgeVisibility(bool visible) -> void {
            this->m_vtkActor->GetProperty()->SetEdgeVisibility(visible);
            this->edgeVisibilityChanged();
            this->update();
        }

        auto Property::setLighting(bool lighting) -> void {
            this->m_vtkActor->GetProperty()->SetLighting(lighting);
            emit this->lightingChanged();
            this->update();
        }

        auto Property::setShading(bool shading) -> void {
            this->m_vtkActor->GetProperty()->SetShading(shading);
            emit shadingChanged();
            this->update();
        }

        void Property::setOpacity(float opacity) {
            this->m_vtkActor->GetProperty()->SetOpacity(opacity);
            emit this->opacityChanged();
            this->update();
        }

        auto Property::setLineWidth(float lineWidth) -> void {
            this->m_vtkActor->GetProperty()->SetLineWidth(lineWidth);
            emit this->lineWidthChanged();
            this->update();
        }

        auto Property::setPointSize(float pointSize) -> void {
            this->m_vtkActor->GetProperty()->SetPointSize(pointSize);
            emit this->pointSizeChanged();
            this->update();
        }

        auto Property::setInterpolation(Interpolation interpolation) -> void {
            this->m_vtkActor->GetProperty()->SetInterpolation(interpolation);
            emit this->interpolationChanged();
            this->update();
        }

        auto Property::setRepresentation(Representation representation) -> void {
            this->m_vtkActor->GetProperty()->SetRepresentation(representation);
            emit this->representationChanged();
            this->update();
        }

        auto Property::setAmbient(float ambient) -> void {
            this->m_vtkActor->GetProperty()->SetAmbient(ambient);
            emit this->ambientChanged();
            this->update();
        }

        auto Property::setDiffuse(float diffuse) -> void {
            this->m_vtkActor->GetProperty()->SetDiffuse(diffuse);
            emit this->diffuseChanged();
            this->update();
        }

        auto Property::setSpecular(float specular) -> void {
            this->m_vtkActor->GetProperty()->SetSpecular(specular);
            emit this->specularChanged();
            this->update();
        }

        auto Property::setSpecularPower(float specularPower) -> void {
            this->m_vtkActor->GetProperty()->SetSpecularPower(specularPower);
            emit this->specularPowerChanged();
            this->update();
        }

        auto Property::getColor() -> QColor {
            return this->m_color;
        }

        auto Property::getDiffuseColor() -> QColor {
            return this->m_diffuseColor;
        }

        auto Property::getSpecularColor() -> QColor {
            return this->m_specularColor;
        }

        auto Property::getAmbientColor() -> QColor {
            return this->m_ambientColor;
        }

        auto Property::getEdgeColor() -> QColor {
            return this->m_edgeColor;
        }

        auto Property::getEdgeVisibility() -> bool {
            return this->m_vtkActor->GetProperty()->GetEdgeVisibility();
        }

        auto Property::getLighting() -> bool {
            return this->m_vtkActor->GetProperty()->GetLighting();
        }

        auto Property::getShading() -> bool {
            return this->m_vtkActor->GetProperty()->GetShading();
        }

        auto Property::getFrontfaceCulling() -> bool {
            return this->m_vtkActor->GetProperty()->GetFrontfaceCulling();
        }

        auto Property::getBackfaceCulling() -> bool {
            return this->m_vtkActor->GetProperty()->GetBackfaceCulling();
        }

        auto Property::getOpacity() -> float {
            return this->m_vtkActor->GetProperty()->GetOpacity();
        }

        auto Property::getLineWidth() -> float {
            return this->m_vtkActor->GetProperty()->GetLineWidth();
        }

        auto Property::getPointSize() -> float {
            return this->m_vtkActor->GetProperty()->GetPointSize();
        }

        auto Property::getInterpolation() -> Interpolation {
            return this->m_interpolation;
        }

        auto Property::getRepresentation() -> Representation {
            return this->m_representation;
        }

        auto Property::getAmbient() -> float {
            return this->m_vtkActor->GetProperty()->GetAmbient();
        }

        auto Property::getDiffuse() -> float {
            return this->m_vtkActor->GetProperty()->GetDiffuse();
        }

        auto Property::getSpecular() -> float {
            return this->m_vtkActor->GetProperty()->GetSpecular();
        }

        auto Property::getSpecularPower() -> float {
            return this->m_vtkActor->GetProperty()->GetSpecularPower();
        }

        Property::~Property() {
            this->m_vtkActor = 0;
            this->m_actor = 0;
        }
    }
}
