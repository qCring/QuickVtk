#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkStripper.h>

namespace quick::Vtk {

    class Stripper : public PolyDataAlgorithm {
        Q_OBJECT
        Q_PROPERTY(int maximumLength READ getMaximumLength WRITE setMaximumLength NOTIFY maximumLengthChanged);
        Q_PROPERTY(bool passCellDataAsFieldData READ getPassCellDataAsFieldData WRITE setPassCellDataAsFieldData NOTIFY passCellDataAsFieldDataChanged);
        Q_PROPERTY(bool passThroughCellIds READ getPassThroughCellIds WRITE setPassThroughCellIds NOTIFY passThroughCellIdsChanged);
        Q_PROPERTY(bool passThroughPointIds READ getPassThroughPointIds WRITE setPassThroughPointIds NOTIFY passThroughPointIdsChanged);
        Q_PROPERTY(bool joinContiguousSegments READ getJoinContiguousSegments WRITE setJoinContiguousSegments NOTIFY joinContiguousSegmentsChanged);
    private:
        vtkSmartPointer<vtkStripper> m_vtkObject = nullptr;
        static Qml::Register::Class<Stripper> Register;
    public:
        Stripper();
        auto setMaximumLength(int) -> void;
        auto getMaximumLength() -> int;
        auto setPassCellDataAsFieldData(bool) -> void;
        auto getPassCellDataAsFieldData() -> bool;
        auto setPassThroughCellIds(bool) -> void;
        auto getPassThroughCellIds() -> bool;
        auto setPassThroughPointIds(bool) -> void;
        auto getPassThroughPointIds() -> bool;
        auto setJoinContiguousSegments(bool) -> void;
        auto getJoinContiguousSegments() -> bool;
    signals:
        void maximumLengthChanged();
        void passCellDataAsFieldDataChanged();
        void passThroughCellIdsChanged();
        void passThroughPointIdsChanged();
        void joinContiguousSegmentsChanged();
    };
}
