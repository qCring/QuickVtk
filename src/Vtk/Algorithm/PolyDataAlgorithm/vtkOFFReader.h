#pragma once

#include <vtkPolyDataAlgorithm.h>

class vtkOFFReader : public vtkPolyDataAlgorithm {
private:
    char *FileName;
public:
    static vtkOFFReader *New();
    vtkTypeMacro(vtkOFFReader,vtkPolyDataAlgorithm);
    vtkSetStringMacro(FileName);
    vtkGetStringMacro(FileName);
protected:
    vtkOFFReader();
    int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) override;
    int RequestData_VtkStyle(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
    int RequestData_QuickStyle(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
    ~vtkOFFReader();
};
